#include <iostream>
#include <string>
#include <vector>
#include "device_rpc_client.h"
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::CreateChannel;
using grpc::StatusCode;

int main(int argc, char **argv) {
    // 创建网络连接;
    std::string server_address("localhost:8888");
    DeviceRpcClient client(grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials()));

    // 获取设备列表
    std::cout << "获取设备列表信息" << std::endl;
    std::vector<std::string> device_names = client.GetDeviceStringList();
    for (const auto &name: device_names) {
        std::cout << name << std::endl;
    }
    std::cout << std::endl;

    // 获取从机数量
    std::cout << "获取从机数量" << std::endl;
    int slaveCnt = client.GetDeviceSlaveCnt("PCS1");
    std::cout << "slaveCnt: " << slaveCnt << std::endl;
    std::cout << std::endl;

    // 获取设备具体信息
    std::cout << "获取设备具体信息" << std::endl;
    std::map<std::string, std::string> deviceInfo = client.GetDeviceInfo("PCS1");
    for (const auto &info: deviceInfo) {
        std::cout << info.first << ": " << info.second << std::endl;
    }
    std::cout << std::endl;

    // 获取从机表
    std::cout << "获取从机表" << std::endl;
    std::vector<std::vector<std::string>> table = client.GetDeviceTableBySlaveId("PCS1", 1, "");
    for (const auto &row: table) {
        for (const auto &col: row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return 0;
}