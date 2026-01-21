set(TARGET device_rpc_server)

file(GLOB_RECURSE RPC_SERVER_SOURCES "${CMAKE_SOURCE_DIR}/src/server/*.cpp")

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

message(STATUS "Using protobuf-${Protobuf_VERSION}")
message(STATUS "Using gRPC-${gRPC_VERSION}")

include_directories(${GRPC_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS})

add_executable(${TARGET} ${RPC_SERVER_SOURCES})

target_include_directories(${TARGET} PUBLIC ${GTEST_INCLUDE_DIRS})
target_link_libraries(${TARGET} PUBLIC gtest gtest_main)
target_link_libraries(${TARGET} PUBLIC gRPC::gRPC++_reflection protobuf::libprotobuf)
