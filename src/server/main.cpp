//
// Created by 19327 on 2026/01/22/星期四.
//
#include <memory>
#include "device_rpc_service.h"
#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

void run_server() {
    std::string server_address("localhost:8888");
    // proto: DeviceService{rpc} server client
    // server : DeviceService::Service
    // client : DeviceService::NewStub(CreateChannel(server_address));
    DeviceRpcServer deviceRpcServer;
    ServerBuilder builder;
    builder.RegisterService(&deviceRpcServer);
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    run_server();
    return 1;
}