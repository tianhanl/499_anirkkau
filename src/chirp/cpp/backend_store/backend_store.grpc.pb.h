// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: backend_store.proto
#ifndef GRPC_backend_5fstore_2eproto__INCLUDED
#define GRPC_backend_5fstore_2eproto__INCLUDED

#include "backend_store.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace chirp {

// message DeleteRequest {
//   bytes key = 1;
// }
//
// message DeleteReply {
//   // Empty because success/failure is signaled via GRPC status.
// }
//
class KeyValueStore final {
 public:
  static constexpr char const* service_full_name() {
    return "chirp.KeyValueStore";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status put(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::chirp::PutReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chirp::PutReply>> Asyncput(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chirp::PutReply>>(AsyncputRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chirp::PutReply>> PrepareAsyncput(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::chirp::PutReply>>(PrepareAsyncputRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::chirp::GetRequest, ::chirp::GetReply>> get(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::chirp::GetRequest, ::chirp::GetReply>>(getRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chirp::GetRequest, ::chirp::GetReply>> Asyncget(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chirp::GetRequest, ::chirp::GetReply>>(AsyncgetRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chirp::GetRequest, ::chirp::GetReply>> PrepareAsyncget(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::chirp::GetRequest, ::chirp::GetReply>>(PrepareAsyncgetRaw(context, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void put(::grpc::ClientContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response, std::function<void(::grpc::Status)>) = 0;
      virtual void get(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::chirp::GetRequest,::chirp::GetReply>* reactor) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::chirp::PutReply>* AsyncputRaw(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::chirp::PutReply>* PrepareAsyncputRaw(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientReaderWriterInterface< ::chirp::GetRequest, ::chirp::GetReply>* getRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::chirp::GetRequest, ::chirp::GetReply>* AsyncgetRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::chirp::GetRequest, ::chirp::GetReply>* PrepareAsyncgetRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status put(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::chirp::PutReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chirp::PutReply>> Asyncput(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chirp::PutReply>>(AsyncputRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chirp::PutReply>> PrepareAsyncput(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::chirp::PutReply>>(PrepareAsyncputRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientReaderWriter< ::chirp::GetRequest, ::chirp::GetReply>> get(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::chirp::GetRequest, ::chirp::GetReply>>(getRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::chirp::GetRequest, ::chirp::GetReply>> Asyncget(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::chirp::GetRequest, ::chirp::GetReply>>(AsyncgetRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::chirp::GetRequest, ::chirp::GetReply>> PrepareAsyncget(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::chirp::GetRequest, ::chirp::GetReply>>(PrepareAsyncgetRaw(context, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void put(::grpc::ClientContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response, std::function<void(::grpc::Status)>) override;
      void get(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::chirp::GetRequest,::chirp::GetReply>* reactor) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::chirp::PutReply>* AsyncputRaw(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::chirp::PutReply>* PrepareAsyncputRaw(::grpc::ClientContext* context, const ::chirp::PutRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientReaderWriter< ::chirp::GetRequest, ::chirp::GetReply>* getRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::chirp::GetRequest, ::chirp::GetReply>* AsyncgetRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::chirp::GetRequest, ::chirp::GetReply>* PrepareAsyncgetRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_put_;
    const ::grpc::internal::RpcMethod rpcmethod_get_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status put(::grpc::ServerContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response);
    virtual ::grpc::Status get(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chirp::GetReply, ::chirp::GetRequest>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_put : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_put() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_put() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status put(::grpc::ServerContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestput(::grpc::ServerContext* context, ::chirp::PutRequest* request, ::grpc::ServerAsyncResponseWriter< ::chirp::PutReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_get() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chirp::GetReply, ::chirp::GetRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestget(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::chirp::GetReply, ::chirp::GetRequest>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(1, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_put<WithAsyncMethod_get<Service > > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_put : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_put() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::chirp::PutRequest, ::chirp::PutReply>(
          [this](::grpc::ServerContext* context,
                 const ::chirp::PutRequest* request,
                 ::chirp::PutReply* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->put(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithCallbackMethod_put() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status put(::grpc::ServerContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void put(::grpc::ServerContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_get() {
      ::grpc::Service::experimental().MarkMethodCallback(1,
        new ::grpc::internal::CallbackBidiHandler< ::chirp::GetRequest, ::chirp::GetReply>(
          [this] { return this->get(); }));
    }
    ~ExperimentalWithCallbackMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chirp::GetReply, ::chirp::GetRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::experimental::ServerBidiReactor< ::chirp::GetRequest, ::chirp::GetReply>* get() {
      return new ::grpc::internal::UnimplementedBidiReactor<
        ::chirp::GetRequest, ::chirp::GetReply>;}
  };
  typedef ExperimentalWithCallbackMethod_put<ExperimentalWithCallbackMethod_get<Service > > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_put : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_put() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_put() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status put(::grpc::ServerContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_get() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chirp::GetReply, ::chirp::GetRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_put : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_put() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_put() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status put(::grpc::ServerContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestput(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_get() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chirp::GetReply, ::chirp::GetRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void Requestget(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(1, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_put : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_put() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->put(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_put() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status put(::grpc::ServerContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void put(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_get : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_get() {
      ::grpc::Service::experimental().MarkMethodRawCallback(1,
        new ::grpc::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this] { return this->get(); }));
    }
    ~ExperimentalWithRawCallbackMethod_get() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status get(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::chirp::GetReply, ::chirp::GetRequest>* stream)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::experimental::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* get() {
      return new ::grpc::internal::UnimplementedBidiReactor<
        ::grpc::ByteBuffer, ::grpc::ByteBuffer>;}
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_put : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_put() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::chirp::PutRequest, ::chirp::PutReply>(std::bind(&WithStreamedUnaryMethod_put<BaseClass>::Streamedput, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_put() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status put(::grpc::ServerContext* context, const ::chirp::PutRequest* request, ::chirp::PutReply* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status Streamedput(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::chirp::PutRequest,::chirp::PutReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_put<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_put<Service > StreamedService;
};

}  // namespace chirp


#endif  // GRPC_backend_5fstore_2eproto__INCLUDED
