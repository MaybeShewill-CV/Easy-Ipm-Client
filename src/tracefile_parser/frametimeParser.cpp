/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: frametimeParser.cpp
* Date: 18-11-7 下午7:44
************************************************/

#include "frametimeParser.h"

#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "common/file_system_utils/file_system_processor.h"
#include "common/log_utils/beecLogger.h"

namespace beec {
namespace tracefile_parser {

using beec::common::file_system_utils::FileSystemProcessor;

/****
 * Public function sets
 */

/***
 * 构造函数
 * @param frametime_file_path
 */
FrametimeParser::FrametimeParser(const std::string &frametime_file_path) {

    init_frametime_parser(frametime_file_path);
}

/***
 * 赋值构造函数
 * @param frametime_parser
 */
FrametimeParser::FrametimeParser(const FrametimeParser &frametime_parser) {

    _m_start_attitude = frametime_parser._m_start_attitude;
    _m_end_attitude = frametime_parser._m_end_attitude;

    _m_attitude_map = frametime_parser._m_attitude_map;

    _m_keys = frametime_parser._m_keys;
}

/***
 * 赋值构造函数
 * @param ipm_model
 * @return
 */
FrametimeParser &FrametimeParser::operator=(const FrametimeParser &frametime_parser) {

    _m_start_attitude = frametime_parser._m_start_attitude;
    _m_end_attitude = frametime_parser._m_end_attitude;

    _m_attitude_map = frametime_parser._m_attitude_map;

    _m_keys = frametime_parser._m_keys;

    return *this;
}

/****
 * Private function sets
 */

/***
 * 解析frametime文件获取imu姿态信息用于初始化frametime parser
 * @param frametime_file_path
 */
void FrametimeParser::init_frametime_parser(const std::string &frametime_file_path) {

    if (!FileSystemProcessor::is_file_exist(frametime_file_path)) {
        LOG(INFO) << "Frametime文件: " << frametime_file_path << " 不存在";
        return;
    }

    std::ifstream ifile(frametime_file_path);

    std::vector<std::string> lines;
    while (ifile) {
        std::string line;
        std::getline(ifile, line);
        lines.push_back(line);
    }

    _m_keys.reserve(lines.size());

    for (auto &line : lines) {
        line = boost::trim_left_copy(line);
        if (line[0] == 'h' || line[0] == 'p') {
            continue;
        }

        std::vector<std::string> split_res;
        boost::split(split_res, line, boost::is_any_of(" "));

        if (split_res.size() != 31) {
            continue;
        }

        IMUAttitude item;

        item.hell = boost::lexical_cast<double>(split_res[5]);
        item.yaw = boost::lexical_cast<double>(split_res[9]);
        item.pitch = boost::lexical_cast<double>(split_res[10]);
        item.roll = boost::lexical_cast<double>(split_res[11]);
        item.capture_id = split_res[20].substr(0, split_res[20].rfind('.'));


        _m_attitude_map.insert(std::make_pair(item.capture_id, item));
        _m_keys.push_back(item.capture_id);
    }

    _m_start_attitude = _m_attitude_map[_m_keys[0]];
    _m_end_attitude = _m_attitude_map[_m_keys[_m_keys.size() - 1]];

    for (auto &item : _m_attitude_map) {
        item.second.hell_diff = item.second.hell - _m_start_attitude.hell;
    }
}
}
}
