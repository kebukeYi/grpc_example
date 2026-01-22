# grpc_example
C++ of  grpc_example.

protoc --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` device.proto


proto: DeviceService{rpc} server client

Server:
    server : DeviceService::Service

Client:
    client : DeviceService::NewStub(CreateChannel(server_address));

### cmake
只加载项目下第一个CMakeList.txt即可;
grpc_example/CMakeList.txt(load,edit)

grpc_example/src/CMakeList.txt(no load,only edit)
grpc_example/src/client/CMakeList.txt(no load,only edit)
grpc_example/src/server/CMakeList.txt(no load,only edit)