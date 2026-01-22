//
// Created by 19327 on 2026/01/22/星期四.
//

#ifndef GRPC_EXAMPLE_DEVICE_RPC_CLIENT_H
#define GRPC_EXAMPLE_DEVICE_RPC_CLIENT_H

#include <map>
#include <vector>
#include <memory>
#include <string>
#include "../proto/device.pb.h"
#include "../proto/device.grpc.pb.h"

using grpc::Channel;
using grpc::ChannelInterface;
using grpc::Status;
using grpc::ClientContext;
using namespace device_service;

class DeviceRpcClient {
private:
    std::unique_ptr<DeviceService::Stub> stub_;

public:
    explicit DeviceRpcClient(const std::shared_ptr<ChannelInterface> &channel);

    std::vector<std::string> GetDeviceStringList();

    int GetDeviceSlaveCnt(const std::string &deviceName);

    std::map<std::string, std::string> GetDeviceInfo(const std::string &deviceName);

    std::vector<std::vector<std::string>>
    GetDeviceTableBySlaveId(const std::string &deviceName, int slaveId, std::string pointName);
};


#endif //GRPC_EXAMPLE_DEVICE_RPC_CLIENT_H