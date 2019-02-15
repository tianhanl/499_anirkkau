HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
ifeq ($(SYSTEM),Darwin)
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -lgrpc++_reflection\
           -ldl
else
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl
endif
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = ../protos

vpath %.proto $(PROTOS_PATH)

all: backend_store_server service_layer_server command_line

command_line: command_line.cc backend_store.pb.o backend_store.grpc.pb.o service_layer.pb.o service_layer.grpc.pb.o server_clients.o
	$(CXX) $^ $(LDFLAGS) -o $@ -lgflags

backend_store_server: backend_store.pb.o backend_store.grpc.pb.o service_layer.pb.o service_layer.grpc.pb.o server_clients.o backend_store_server.o
	$(CXX) $^ $(LDFLAGS) -o $@ -lgflags

service_layer_server: service_layer.pb.o service_layer.grpc.pb.o backend_store.pb.o backend_store.grpc.pb.o server_clients.o service_layer_server.o
	$(CXX) $^ $(LDFLAGS) -o $@ -lgflags

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

clean:
	rm -f *.o *.pb.cc *.pb.h command_line server_clients backend_store_server service_layer_server