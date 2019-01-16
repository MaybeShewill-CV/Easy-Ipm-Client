/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: beecLogger.h
* Date: 18-11-16 下午1:23
************************************************/

// 为避免使用更多的第三方库 实现一个简单可复用的LOG库,输出格式仿照GLOG

#pragma once

#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <thread>
#include <mutex>

#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define LOG(log_level) \
    beec::common::log_utils::BeecLogger(log_level).print_log_info(log_level, __FILENAME__, __LINE__)

#define INIT_BEEC_LOG(log_path) \
    beec::common::log_utils::initialize_beec_logger(log_path)

enum LogLevel {
    INFO,
    WARN,
    ERROR,
    FATAL
};

namespace beec {
namespace common {
namespace log_utils {

void initialize_beec_logger(const std::string &log_filename);

class BeecLogger {

    friend void initialize_beec_logger(const std::string &log_filename);

public:

    BeecLogger() = default;

    ~BeecLogger();

    explicit BeecLogger(LogLevel level) : _m_log_level(level) {
        _m_ofs_mtx.lock();
        _m_ios_mtx.lock();
    }

    template<typename T>
    inline BeecLogger& operator<<(const T &obj) {

        if (_m_log_file.is_open()) {
            _m_log_file << obj << std::flush;
        }

        std::cout << obj << std::flush;

        return *this;
    }

    static BeecLogger& print_log_info(
        LogLevel severity,
        const std::string &file,
        int line);

private:

    LogLevel _m_log_level;

    static std::ofstream _m_log_file;
    static std::mutex _m_ios_mtx; // 标准iostream输出流锁
    static std::mutex _m_ofs_mtx; // 标准文件输出流锁
};

}
}
}

//TODO LUOYAO(luoyao@baidu.com) 需要解决一个问题:
//TODO 1.静态编译,运行时会崩溃,动态编译则不会出现这个问题
