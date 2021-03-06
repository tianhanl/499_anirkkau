#include <iostream>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include "backend_store.grpc.pb.h"
#include "backend_store_client.h"
#include "service_layer.grpc.pb.h"
#include "service_layer_client.h"
#include "service_layer_server.h"

Status ServiceLayerServiceImpl::registeruser(ServerContext* context,
                                             const RegisterRequest* request,
                                             RegisterReply* reply) {
  // Register Implementation
  std::string type = "register";

  KeyValueStoreClient store_client(grpc::CreateChannel(
      "localhost:50000", grpc::InsecureChannelCredentials()));
  std::string new_user = request->username();

  // value is irrelevent since the KVS will check for username validity
  std::string value = "";

  std::string response = store_client.put(new_user, value, type);
  if (response == "success") {
    registered_users_.insert(new_user);
    return Status::OK;
  } else {
    return Status::CANCELLED;
  }
}

Status ServiceLayerServiceImpl::chirp(ServerContext* context,
                                      const ChirpRequest* request,
                                      ChirpReply* reply) {
  // Chirp Implementation
  std::string type = "chirp";

  KeyValueStoreClient store_client(grpc::CreateChannel(
      "localhost:50000", grpc::InsecureChannelCredentials()));
  std::string chirp_username = request->username();
  std::string chirp_text = request->text();
  std::string chirp_id = GenerateChirpID();
  std::string chirp_parent_id = request->parent_id();

  // Generate Chirp
  Chirp chirp;
  chirp.set_username(chirp_username);
  chirp.set_text(chirp_text);
  chirp.set_id(chirp_id);
  chirp.set_parent_id(chirp_parent_id);

  // Serialize Chirp
  std::string chirp_str = chirp.SerializeAsString();
  std::string response = store_client.put(chirp_id, chirp_str, type);

  if (response == "success") {
    // Push into chirp_log_. Every chirp gets logged in the Service Layer
    //(for Monitor)
    chirp_log_.push_back(chirp_str);

    return Status::OK;
  } else {
    return Status::CANCELLED;
  }
}

Status ServiceLayerServiceImpl::follow(ServerContext* context,
                                       const FollowRequest* request,
                                       FollowReply* reply) {
  // Follow Implementation
  std::string type = "follow";

  KeyValueStoreClient store_client(grpc::CreateChannel(
      "localhost:50000", grpc::InsecureChannelCredentials()));
  std::string username = request->username();
  std::string to_follow = request->to_follow();
  std::string response = store_client.put(username, to_follow, "follow");

  if (response == "success") {
    return Status::OK;
  } else {
    return Status::CANCELLED;
  }
}

Status ServiceLayerServiceImpl::read(ServerContext* context,
                                     const ReadRequest* request,
                                     ReadReply* reply) {
  // Read Implementation
  std::string type = "read";

  KeyValueStoreClient store_client(grpc::CreateChannel(
      "localhost:50000", grpc::InsecureChannelCredentials()));
  std::string chirp_id = request->chirp_id();

  std::vector<Chirp> chirp_Obj_thread;
  chirp_Obj_thread = store_client.get(chirp_id, type);

  std::string chirp_thread = "";
  if (chirp_Obj_thread.size() == 0) {
    return Status::CANCELLED;
  }

  // Loop over and set up the user output as chirp_thread
  for (Chirp chirp : chirp_Obj_thread) {
    std::string chirp_text(chirp.text());
    std::string chirp_username(chirp.username());
    chirp_thread += chirp_username;
    chirp_thread += " chirped: ";
    chirp_thread += chirp_text;
    chirp_thread += "\n==================\n";
  }

  reply->set_chirp_thread(chirp_thread);

  return Status::OK;
}

Status ServiceLayerServiceImpl::monitor(ServerContext* context,
                                        const MonitorRequest* request,
                                        ServerWriter<MonitorReply>* writer) {
  // Monitor Implementation
  // 1) Grabs a list of all usernames that the monitoring user follows
  // 2) Every chirp that goes through the service layer is checked
  // to see if it's relevent to the monitoring user
  // i.e. we check if the latest chirp's author belongs to the monitoring user's
  // following list 3) If so, display chirp to monitoring user
  std::string type = "monitor";

  KeyValueStoreClient store_client(grpc::CreateChannel(
      "localhost:50000", grpc::InsecureChannelCredentials()));
  std::string username = request->username();

  // Error check
  std::vector<std::string> following_list =
      store_client.getFollowingList(username, type);
  if (following_list.size() == 0) {  // User doesn't follow anyone yet
    return Status::CANCELLED;
  }

  // Error check
  int last_index = chirp_log_.size() - 1;
  if (last_index < 0) {
    std::cout << "Error: Nobody has chirped yet!" << std::endl;
    return Status::OK;
  }

  // If latest chirp's username is in following_list return chirp
  std::string latest_chirp_bytes = chirp_log_.at(last_index);
  Chirp chirp_obj;
  chirp_obj.ParseFromString(latest_chirp_bytes);
  std::string latest_chirper = chirp_obj.username();

  // Check if user follows latest chirper
  for (std::string follow : following_list) {
    if (follow == latest_chirper) {
      MonitorReply reply;
      reply.set_chirp_bytes(latest_chirp_bytes);
      writer->Write(reply);
    }
  }

  return Status::OK;
}

Status ServiceLayerServiceImpl::stream(ServerContext* context,
                                       const StreamRequest* request,
                                       ServerWriter<StreamReply>* writer) {
  // Extract variables out of request
  const std::string& username = request->username();
  const std::string& hashtag = request->hashtag();
  const std::string& from = request->from();

  // Check is user registered
  if (registered_users_.find(username) == registered_users_.end()) {
    return Status::CANCELLED;
  }

  // Empty log id used to indicate current list is empty
  const std::string& kEmptyLodId = "empty_log";

  KeyValueStoreClient store_client(grpc::CreateChannel(
      "localhost:50000", grpc::InsecureChannelCredentials()));
  // If no chirps have been created yet, return a special chirp to indicate it
  if (chirp_log_.empty()) {
    StreamReply stream_reply;
    Chirp chirp;
    chirp.set_id(kEmptyLodId);
    CloneChirp(chirp, stream_reply.mutable_chirp());
    writer->Write(stream_reply);
    return Status::OK;
  }
  // If `from` is empty, this request is used to synchronize start location
  // in chirp_log_, return last chirp to use its id as from in next request.
  if (from.empty()) {
    const std::string& latest_chirp_bytes = chirp_log_.back();
    StreamReply stream_reply;
    Chirp back_chirp;
    back_chirp.ParseFromString(latest_chirp_bytes);
    CloneChirp(back_chirp, stream_reply.mutable_chirp());
    writer->Write(stream_reply);
    return Status::OK;
  }

  std::vector<Chirp> chirps_with_hashtag;

  // Iterate from back of chirp_log_ for new chirps since `from`
  auto currIterator = chirp_log_.end();
  while (currIterator != chirp_log_.begin()) {
    --currIterator;
    Chirp curr_chirp;
    curr_chirp.ParseFromString(*currIterator);
    if (from != kEmptyLodId && from == curr_chirp.id()) {
      break;
    }
    if (ContainsHashtag(curr_chirp.text(), hashtag)) {
      chirps_with_hashtag.push_back(curr_chirp);
    }
  }

  // Use this list to ensure the chirps is ordered from oldest to latest
  for (int i = chirps_with_hashtag.size() - 1; i >= 0; i--) {
    StreamReply stream_reply;
    CloneChirp(chirps_with_hashtag[i], stream_reply.mutable_chirp());
    writer->Write(stream_reply);
  }

  return Status::OK;
}

std::string ServiceLayerServiceImpl::GenerateChirpID() {
  chirp_count_++;
  std::string CurrentClientID = "cid//";
  std::string count_str = std::to_string(chirp_count_);
  CurrentClientID += count_str;

  return CurrentClientID;
}

void ServiceLayerServiceImpl::CloneChirp(const Chirp& chirp,
                                         Chirp* mutable_chirp) {
  mutable_chirp->set_text(chirp.text());
  mutable_chirp->set_id(chirp.id());
  mutable_chirp->set_parent_id(chirp.parent_id());
  mutable_chirp->set_username(chirp.username());
}

bool ServiceLayerServiceImpl::ContainsHashtag(const std::string& text,
                                              const std::string& hashtag) {
  std::stringstream text_stream(text);
  std::string part;
  // split text by space and check is hashtag a part of text
  while (text_stream >> part) {
    if (hashtag.compare(part) == 0) {
      return true;
    }
  }
  return false;
}

void RunServer() {
  std::string server_address("0.0.0.0:50002");
  ServiceLayerServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
