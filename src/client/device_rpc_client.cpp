//
// Created by 19327 on 2026/01/22/星期四.
//

#include "device_rpc_client.h"

DeviceRpcClient::DeviceRpcClient(const std::shared_ptr<ChannelInterface> &channel) :
        stub_(DeviceService::NewStub(channel, grpc::StubOptions())) {}

std::vector<std::string> DeviceRpcClient::GetDeviceStringList() {
    ClientContext context;
    DeviceNameListRequest request;
    DeviceNameListResponse response;

    Status status = stub_->GetDeviceList(&context, request, &response);

    if (status.ok()) {
        std::vector<std::string> device_names;
        for (const auto &name: response.device_names()) {
            device_names.push_back(name);
        }
        return device_names;
    } else {
        std::cerr << "GetDeviceStringList Failed: " << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return {};
    }
}

int DeviceRpcClient::GetDeviceSlaveCnt(const std::string &deviceName) {
    DeviceSlaveCntRequest request;
    request.set_device_name(deviceName);
    DeviceSlaveCntResponse response;
    ClientContext context;
    Status status = stub_->GetDeviceSlaveCnt(&context, request, &response);
    if (status.ok()) {
        int slaveCnt = response.slave_cnt();
        return slaveCnt;
    } else {
        std::cerr << "GetDeviceSlaveCnt Failed:" << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return -1;
    }
}

std::map<std::string, std::string> DeviceRpcClient::GetDeviceInfo(const std::string &deviceName) {
    DeviceInfoRequest request;
    request.set_device_name(deviceName);
    DeviceInfoResponse response;
    ClientContext context;
    Status status = stub_->DeviceInfo(&context, request, &response);
    if (status.ok()) {
        std::map<std::string, std::string> infoMap;
        infoMap["ip"] = response.info().ip();
        infoMap["port"] = std::to_string(response.info().port());
        infoMap["type"] = response.info().type();
        infoMap["server_status"] = std::to_string(response.info().server_status());
        infoMap["simulate_status"] = std::to_string(response.info().simulate_status());
        infoMap["plan_status"] = std::to_string(response.info().plan_status());
        return infoMap;
    } else {
        std::cerr << "GetDeviceInfo Failed: " << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return {};
    }
}

std::vector<std::vector<std::string>>
DeviceRpcClient::GetDeviceTableBySlaveId(const std::string &deviceName, int slaveId, std::string pointName) {
    DeviceTableBySlaveIdRequest request;
    DeviceTableBySlaveIdResponse response;
    ClientContext context;
    request.set_device_name(deviceName);
    request.set_slave_id(slaveId);
    request.set_point_name(pointName);

    Status status = stub_->GetDeviceTableBySlaveId(&context, request, &response);
    if (status.ok()) {
        std::vector<std::vector<std::string>> table;

        // 处理列表头数据
        DeviceTableRow headRow = response.head_data();
        std::vector<std::string> head;
        for (const std::string &value: headRow.row()) {
            head.push_back(value);
        }
        table.push_back(head);

        // 处理列表数据
        for (int i = 0; i < response.table_data().size(); i++) {
            DeviceTableRow tableRow = response.table_data().Get(i);
            std::vector<std::string> row;
            for (const std::string &value: tableRow.row()) {
                row.push_back(value);
            }
            table.push_back(row);
        }
        return table;
    } else {
        std::cout << "GetDeviceTableBySlaveId error: " << status.error_message() << std::endl;
        return {};
    }
}