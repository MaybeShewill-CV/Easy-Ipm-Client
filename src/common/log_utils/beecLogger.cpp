/************************************************
* Copyright 2014 Baidu Inc. All Rights Reserved.
* Author: Luo Yao (luoyao@baidu.com)
* File: beecLogger.cpp
* Date: 18-11-16 下午1:23
************************************************/

#include "beecLogger.h"

#include <chrono>

namespace beec {
namespace common {
namespace log_utils {

std::ofstream BeecLogger::_m_log_file;
std::mutex BeecLogger::_m_ios_mtx;
std::mutex BeecLogger::_m_ofs_mtx;
BeecLogger _m_beec_logger;

/***
 * 初始化logger
 * @param log_filename
 */
void initialize_beec_logger(const std::string &log_filename) {

    BeecLogger::_m_log_file.open(log_filename.c_str(), std::ios::out);

    // 检查文件输出流是否已经被打开
    bool is_open = true;
    if (!BeecLogger::_m_log_file.is_open()) {

        std::cout << "无法创建日志文件: " << log_filename << ", 请检查是否需要重新创建目录" << std::endl;
        is_open = false;
    }
    if (!is_open) {
        exit(0);
    }
}

/***
 * 析构函数
 */
BeecLogger::~BeecLogger() {

    if (_m_log_file.is_open()) {
        _m_log_file << "\n" << std::flush;
    }

    std::cout << "\n" << std::flush;

    if (_m_log_level == FATAL && _m_log_file.is_open()) {
        _m_log_file.close();
        std::abort();
    }

    _m_ios_mtx.unlock();
    _m_ofs_mtx.unlock();
}

/***
 * 打印log信息
 * @param severity
 * @param file
 * @param line
 * @return
 */
BeecLogger& BeecLogger::print_log_info(
    LogLevel severity,
    const std::string &file,
    int line) {

    std::string log_level;
    switch (severity) {
    case INFO:
        log_level = "INFO";
        break;
    case WARN:
        log_level = "WARN";
        break;
    case ERROR:
        log_level = "ERROR";
        break;
    case FATAL:
        log_level = "FATAL";
        break;
    default:
        log_level = "INFO";
    }

    auto now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    auto pid = std::this_thread::get_id();

    if (_m_log_file.is_open()) {

        _m_log_file << log_level << " "
                    << std::put_time(std::localtime(&now_time), "%H.%M.%S") << " "
                    << pid << " " << file << ":" << line << "] ";
    }

    std::cout << log_level << " "
              << std::put_time(std::localtime(&now_time), "%H.%M.%S") << " "
              << pid << " " << file << ":" << line << "] ";


    return _m_beec_logger;
}

}
}
}
