/************************************************
* Copyright 2014 Baidu Inc. All Rights Reserved.
* Author: Luo Yao (luoyao@baidu.com)
* File: frametimeParser.h
* Date: 18-11-7 下午7:44
************************************************/

#pragma once

// 轨迹文件frametime.txt文件解析

#include <string>
#include <unordered_map>
#include <vector>

namespace beec {
namespace tracefile_parser {

struct IMUAttitude {
    // IMU俯仰角(度)
    double pitch;
    // IMU(度)
    double roll;
    // IMU俯仰角(度)
    double yaw;
    // 高程
    double hell;
    // 高程差
    double hell_diff;
    // 对应照片编号
    std::string capture_id;

    IMUAttitude() : pitch(0.0), roll(0.0), yaw(0.0), hell(0.0), hell_diff(0.0), capture_id("") {}

    IMUAttitude(
        const double pitch,
        const double roll,
        const double yaw,
        const double hell,
        const double hell_diff,
        const std::string &capture_id) :
        pitch(pitch), roll(roll), yaw(yaw), hell(hell), hell_diff(hell_diff), capture_id(capture_id) {}

    IMUAttitude &operator=(const IMUAttitude &attitude) {

        pitch = attitude.pitch;
        roll = attitude.roll;
        yaw = attitude.yaw;
        hell = attitude.hell;
        hell_diff = attitude.hell_diff;
        capture_id = attitude.capture_id;

        return *this;
    };

    IMUAttitude(const IMUAttitude &attitude) {

        pitch = attitude.pitch;
        roll = attitude.roll;
        yaw = attitude.yaw;
        hell = attitude.hell;
        hell_diff = attitude.hell_diff;
        capture_id = attitude.capture_id;
    };

};

class FrametimeParser {

    using _value_type = IMUAttitude;
    using _key_type = std::string;

public:
    FrametimeParser() = default;

    ~FrametimeParser() = default;

    explicit FrametimeParser(const std::string &frametime_file_path);

    FrametimeParser(const FrametimeParser &frametime_parser);

    FrametimeParser &operator=(const FrametimeParser &frametime_parser);

    const _value_type &operator[](const _key_type &index) {
        return _m_attitude_map[index];
    }

    bool contains_item(const _key_type &index) {
        return _m_attitude_map.find(index) != _m_attitude_map.end();
    }

    IMUAttitude get_start_attitude() const {
        return _m_start_attitude;
    }

    IMUAttitude get_end_attitude() const {
        return _m_end_attitude;
    }

    const std::vector<_key_type> get_pic_ids() const {
        return _m_keys;
    };

    void reset() {

        _m_start_attitude = IMUAttitude();
        _m_end_attitude = IMUAttitude();

        _m_attitude_map.clear();
        std::unordered_map<_key_type, _value_type>().swap(_m_attitude_map);

        _m_keys.clear();
        std::vector<_key_type>().swap(_m_keys);
    }

private:
    IMUAttitude _m_start_attitude; // 车天起始姿态
    IMUAttitude _m_end_attitude; // 车天结束姿态

    std::unordered_map<_key_type, _value_type> _m_attitude_map; // 每张图像对应的imu姿态字典

    std::vector<_key_type> _m_keys; // 车天照片编号列表

    // 初始化frametime解析器
    void init_frametime_parser(const std::string &frametime_file_path);

};
}
}
