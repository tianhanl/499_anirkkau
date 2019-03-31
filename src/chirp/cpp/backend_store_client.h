#ifndef BACKEND_STORE_CLIENT_H
#define BACKEND_STORE_CLIENT_H

#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <sstream>

#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include "backend_store.grpc.pb.h"
#include "service_layer.grpc.pb.h"

// Client Includes
using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

// Server Includes
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

// Chirp Includes
using chirp::KeyValueStore;
using chirp::PutRequest;
using chirp::PutReply;
using chirp::GetRequest;
using chirp::GetReply;
using chirp::DeleteRequest;
using chirp::DeleteReply;

using chirp::ServiceLayer;
using chirp::Timestamp;
using chirp::Chirp;
using chirp::RegisterRequest;
using chirp::RegisterReply;
using chirp::ChirpRequest;
using chirp::ChirpReply;
using chirp::FollowRequest;
using chirp::FollowReply;
using chirp::ReadRequest;
using chirp::ReadReply;
using chirp::MonitorRequest;
using chirp::MonitorReply;

class KeyValueStoreClient {
  public:
    std::string put(const std::string& key, const std::string& value, const std::string& type);

    std::vector<Chirp> get(const std::string& key, const std::string& type);

    std::vector<std::string> getFollowingList(const std::string& key, const std::string& type);

    std::string deletekey(const std::string& key);

    GetRequest MakeGetRequest(const std::string& key);

    KeyValueStoreClient(std::shared_ptr<Channel> channel) 
      : stub_(KeyValueStore::NewStub(channel)) {}

  private:
    std::unique_ptr<KeyValueStore::Stub> stub_;
};

#endif //BACKEND_STORE_CLIENT_H