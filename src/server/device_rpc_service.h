//
// Created by 19327 on 2026/01/21/星期三.
//
#ifndef GRPC_EXPLAME_DEVICE_RPC_SERVICE_H
#define GRPC_EXPLAME_DEVICE_RPC_SERVICE_H

#include <memory>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/status.h>
#include "../proto/device.grpc.pb.h" // 假设这是由protoc生成的grpc服务头文件
#include "../proto/device.pb.h"      // 假设这是由protoc生成的消息头文件
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::CreateChannel;
using namespace device_service;

class DeviceRpcServer final : public DeviceService::Service {
public:
    DeviceRpcServer() {
        for (auto &item: peers_) {
            std::string address = item.first;
            auto channel = CreateChannel(address, grpc::InsecureChannelCredentials());
            auto stub_ = DeviceService::NewStub(channel);
            item.second = std::move(stub_);
        }
    };

    // 设备列表信息
    grpc::Status GetDeviceList(grpc::ServerContext *context, const DeviceNameListRequest *request,
                               DeviceNameListResponse *response);

    // 获得设备从机数量
    grpc::Status GetDeviceSlaveCnt(grpc::ServerContext *context, const DeviceSlaveCntRequest *request,
                                   DeviceSlaveCntResponse *response);

    // 设备详细信息
    grpc::Status DeviceInfo(grpc::ServerContext *context, const DeviceInfoRequest *request,
                            DeviceInfoResponse *response);

    // 根据设备名称和从机id和测点信息获取设备详细信息
    grpc::Status GetDeviceTableBySlaveId(grpc::ServerContext *context, const DeviceTableBySlaveIdRequest *request,
                                         DeviceTableBySlaveIdResponse *response);

private:
    std::map<std::string, std::unique_ptr<DeviceService::Stub>> peers_;
    std::map<std::string, bool> _deviceMap = {
            {"PCS1", true},
            {"PCS2", true},
            {"BMS1", true},
            {"BMS2", true},
    };

    // 检查设备是否存在
    grpc::Status checkDevice(grpc::ServerContext *context, const DeviceNameListRequest *request,
                             DeviceNameListResponse *response);
};

#endif //GRPC_EXPLAME_DEVICE_RPC_SERVICE_H