/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: file_system_processor.h
* Date: 18-1-15 下午5:28
************************************************/

// 文件系统处理类

#pragma once

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    TypeName& operator=(const TypeName&)

#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace beec {
namespace common {
namespace file_system_utils {
class FileSystemProcessor {
public:
    FileSystemProcessor() = default;

    ~FileSystemProcessor() = default;

    enum SEARCH_OPTION_T {
        TOPDIRECTORYONLY = 1,
        ALLDIRECTORIES
    };

    // 判断文件存在
    static bool is_file_exist(const std::string &file_path);

    // 判断文件夹存在
    static bool is_directory_exist(const std::string &dir_path);

    // 判断路径是文件夹
    static bool is_directory(const std::string &file_path);

    // 获取路径中的文件名
    static std::string get_file_name(const std::string &file_path);

    // 获取路径中的文件Extension
    static std::string get_file_extension(const std::string &file_path);

    // 获取路径中的文件夹名
    static std::string get_directory_name(const std::string &file_path);

    // 获取文件路径中的父级目录路径
    static std::string get_parent_path(const std::string &file_path);

    // 获取文件的文件名
    static std::string get_file_base_name(const std::string &file_path);

    // 获取文件夹中的文件
    static void get_directory_files(const std::string &src_dir,
                                    std::vector<std::string> &files_vec,
                                    const std::string &extension/* = "."*/,
                                    SEARCH_OPTION_T search_option /*= TopDirectoryOnly*/);

    // 统计文件夹中的文件数量
    static int get_directory_file_nums(const std::string &src_dir,
                                       const std::string &extension/* = "."*/,
                                       SEARCH_OPTION_T search_option /*= TopDirectoryOnly*/);

    // 获取文件夹中的子文件夹路径
    static void get_sub_directory(const std::string &src_dir,
                                  std::vector<std::string> &sub_folders_vec);

    // 获取文件大小
    static int get_file_size(const std::string &file_path);

    // 创建目录(如父级目录不存在则创建失败)
    static bool create_directory(const std::string &dir_path);

    // 创建目录(如父级目录不存在则创建父级目录)
    static bool create_directories(const std::string &dir_path);

    // 判断文件结尾
    static bool is_file_end_with(const std::string &file_path, const std::string &end_str);

    // 判断文件开头
    static bool is_file_start_with(const std::string &file_path, const std::string &start_str);

    // 删除文件夹
    static bool remove_dir(const std::string &dir_path);

    // 删除文件
    static bool remove_file(const std::string &file_path);

    // 拷贝文件夹
    static bool copy_directory(const std::string &src_dir, const std::string &dst_dir);

    // 拼接文件路径
    static std::string combine_path(const std::string &path_1, const std::string &path_2);

    // 转换大写
    static void to_upper(std::string &_str);

    // 转换小写
    static void to_lower(std::string &_str);

    // 获取JPEG图像文件列表
    static bool get_jpgfiles(const std::string &filedir, std::vector<std::string> &jpgfiles);

    // 获取TXT文件列表
    static bool get_txtfiles(const std::string &filedir, std::vector<std::string> &txtfiles);

    DISALLOW_COPY_AND_ASSIGN(FileSystemProcessor);

};
}
}
}
