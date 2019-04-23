
#include "service_layer_client.h"

#include <iostream>
#include <string>
#include <thread>

#include <grpcpp/grpcpp.h>
#include <gtest/gtest.h>
#include "backend_store.grpc.pb.h"
#include "service_layer.grpc.pb.h"

using chirp::Chirp;
using chirp::Timestamp;

// `hashtag` should begin with '#'
TEST(ServiceLayerClientStreamInput, HashtagShouldBeginWithHashSign) {
  ServiceLayerClient client(grpc::CreateChannel(
      "localhost:50002", grpc::InsecureChannelCredentials()));
  const std::string username = "HashtagShouldBeginWithHashSign";
  client.registeruser(username);
  EXPECT_FALSE(client.stream(username, "test", [](Chirp chirp) {}));
}

// `hashtag` should contain one or more nonblank characters after it
TEST(ServiceLayerClientStreamInput, HashtagShouldContainNonBlankCharacters) {
  ServiceLayerClient client(grpc::CreateChannel(
      "localhost:50002", grpc::InsecureChannelCredentials()));
  const std::string username = "HashtagShouldContainNonBlankCharacters";
  client.registeruser(username);
  EXPECT_FALSE(client.stream(username, "#", [](Chirp chirp) {}));
  EXPECT_FALSE(client.stream(username, "# ", [](Chirp chirp) {}));
}

// Create a chirp should succeed
// TEST(ServiceLayerClientStreamInput, InvalidUsernameShouldReturnError) {
//   ServiceLayerClient client(grpc::CreateChannel(
//       "localhost:50002", grpc::InsecureChannelCredentials()));
//   EXPECT_FALSE(client.stream("invalid_username", "#test", [](Chirp chirp)
//   {}));
// }

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}