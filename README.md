# grpc_example
C++ of  grpc_example.

protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` device.proto


proto: DeviceService{rpc} server client

Server:
    server : DeviceService::Service

Client:
    client : DeviceService::NewStub(CreateChannel(server_address));
