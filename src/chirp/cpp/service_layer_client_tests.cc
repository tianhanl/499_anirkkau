#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <thread>

#include <grpcpp/grpcpp.h>
#include "backend_store.grpc.pb.h"
#include "service_layer.grpc.pb.h"
#include "service_layer_client.h"
using chirp::Chirp;
using chirp::Timestamp;

// Tests Stream(username, hashtag) method for ServiceLayer
// When a invalid `username` is given, stream method should return error
TEST(ServiceLayerClientStream, InvalidUserNameShouldReturnError) {}

// When a user that current `username` is following sent a chirp not containing
// `hashtag`, stream function should return a empty vector
TEST(ServiceLayerClientStream, NonRelatedChirpShouldNotStream) {}

// When a user that current `username` is following sent a chrip containing the
// `hashtag`, stream function should return a vector conains this chirp
TEST(ServiceLayerClientStream, SingleMatchingHashtagChirpShouldWork) {}

// When multiple users that `username` is following sent chirps containing the
// `hashtag`, stream function should return a vector conains those
// chirps
TEST(ServiceLayerClientStream, MultipleMatchingHashtagChirpShouldWork) {}

// When a user that current `username` is following sent a chrip containing
// multiple hashtags and one of them is `hashtag`, stream function should return
// a vector conains this chirp
TEST(ServiceLayerClientStream,
     ChirpWithMultipleHashtagShouldWorkForSingleMatching) {}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}