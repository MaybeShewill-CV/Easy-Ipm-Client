//
// Created by baidu on 18-1-12.
//

#include "file_system_processor.h"

#include <boost/algorithm/string.hpp>
#include <iostream>

namespace beec {
namespace common {
namespace file_system_utils {
bool FileSystemProcessor::is_file_exist(const std::string &file_path) {
    return boost::filesystem::is_regular_file(file_path.c_str()) &&
           boost::filesystem::exists(file_path.c_str());
}

bool FileSystemProcessor::is_directory(const std::string &file_path) {
    return boost::filesystem::is_directory(boost::filesystem::path(file_path));
}

bool FileSystemProcessor::is_directory_exist(const std::string &dir_path) {
    boost::filesystem::path p(dir_path.c_str());
    return boost::filesystem::is_directory(p) &&
           boost::filesystem::exists(p);
}

void FileSystemProcessor::get_directory_files(const std::string &src_dir,
        std::vector<std::string> &files_vec,
        const std::string &extension,
        SEARCH_OPTION_T search_option) {

    boost::filesystem::path src_path(src_dir);
    if (is_file_exist(src_dir)) {
        return;
    }
    typedef boost::filesystem::directory_iterator d_iterator;
    if (boost::filesystem::is_directory(src_path)) {
        d_iterator tmp_dir_end;
        d_iterator tmp_dir_iter(src_path);
        for (; tmp_dir_iter != tmp_dir_end; ++tmp_dir_iter) {
            if (boost::filesystem::is_directory(*tmp_dir_iter)) {
                if (search_option == ALLDIRECTORIES) {
                    get_directory_files(tmp_dir_iter->path().string(),
                                        files_vec,
                                        extension,
                                        search_option);
                }
            } else if (boost::filesystem::is_regular_file(*tmp_dir_iter)) {
                if (std::strcmp(extension.c_str(), ".") == 0) {
                    files_vec.push_back(tmp_dir_iter->path().string());
                } else {
                    if (is_file_end_with(tmp_dir_iter->path().string(), extension)) {
                        files_vec.push_back(tmp_dir_iter->path().string());
                    }
                }
            }
        }
    } else {
        if (is_file_end_with(src_dir, extension)) {
            files_vec.push_back(src_dir);
        }
    }
}

int FileSystemProcessor::get_directory_file_nums(const std::string &src_dir,
        const std::string &extension,
        SEARCH_OPTION_T search_option) {
    std::vector<std::string> files_vec;
    get_directory_files(src_dir, files_vec, extension, search_option);

    return static_cast<int>(files_vec.size());
}

std::string FileSystemProcessor::get_file_extension(const std::string &file_path) {

    auto file_name = get_file_name(file_path);
    return boost::filesystem::extension(file_name);
}

void FileSystemProcessor::get_sub_directory(const std::string &src_dir,
        std::vector<std::string> &sub_folders_vec) {
    boost::filesystem::path src_path(src_dir);
    if (is_file_exist(src_dir)) {
        return;
    }

    typedef boost::filesystem::directory_iterator d_iter;
    if (is_directory(src_dir)) {
        d_iter d_iter_end;
        d_iter d_iter_start(src_path);
        for (; d_iter_start != d_iter_end; ++d_iter_start) {
            if (boost::filesystem::is_directory(*d_iter_start)) {
                sub_folders_vec.push_back(d_iter_start->path().string());
            }
        }
    } else {
        return;
    }
}

std::string FileSystemProcessor::get_file_base_name(const std::string &file_path) {
    return boost::filesystem::path(file_path.c_str()).stem().string();
}

std::string FileSystemProcessor::get_directory_name(const std::string &file_path) {
    return boost::filesystem::path(file_path.c_str()).filename().string();
}

std::string FileSystemProcessor::get_parent_path(const std::string &file_path) {
    boost::filesystem::path p(file_path.c_str());
    return p.parent_path().c_str();
}

std::string FileSystemProcessor::get_file_name(const std::string &file_path) {
    return boost::filesystem::path(file_path.c_str()).filename().string();
}

bool FileSystemProcessor::remove_dir(const std::string &dir_path) {
    return static_cast<bool>(boost::filesystem::
                             remove_all(boost::filesystem::path(dir_path.c_str())));
}

bool FileSystemProcessor::remove_file(const std::string &file_path) {
    return static_cast<bool>(boost::filesystem::remove(boost::filesystem::path(file_path.c_str())));
}

bool FileSystemProcessor::create_directory(const std::string &dir_path) {
    return boost::filesystem::create_directory(boost::filesystem::path(dir_path.c_str()));
}

bool FileSystemProcessor::create_directories(const std::string &dir_path) {
    return boost::filesystem::create_directories(boost::filesystem::path(dir_path.c_str()));
}

bool FileSystemProcessor::is_file_end_with(const std::string &file_path,
        const std::string &end_str) {

    std::string _path = get_file_name(file_path);
    return boost::algorithm::ends_with(_path.c_str(), end_str.c_str());
}

bool FileSystemProcessor::is_file_start_with(const std::string &file_path,
        const std::string &start_str) {
    std::string _path = get_file_name(file_path);
    return boost::algorithm::starts_with(_path.c_str(), start_str.c_str());
}

void FileSystemProcessor::to_upper(std::string &_str) {
    return boost::algorithm::to_upper(_str);
}

void FileSystemProcessor::to_lower(std::string &_str) {
    return boost::algorithm::to_lower(_str);
}

int FileSystemProcessor::get_file_size(const std::string &file_path) {
    return static_cast<int>(boost::filesystem::file_size(file_path));
}

bool FileSystemProcessor::copy_directory(const std::string &source,
        const std::string &destination) {
    try {
        // Check whether the function call is valid
        if (!boost::filesystem::exists(source) || !boost::filesystem::is_directory(source)) {
            std::cerr << "Source directory " << source
                      << " does not exist or is not a directory." << '\n';
            return false;
        }
        if (!boost::filesystem::exists(destination)) {
            // Create the destination directory
            if (!boost::filesystem::create_directory(destination)) {
                std::cerr << "Unable to create destination directory"
                          << destination << '\n';
                return false;
            }
        }
    }
    catch (boost::filesystem::filesystem_error const &e) {
        std::cerr << e.what() << '\n';
        return false;
    }
    // Iterate through the source directory
    boost::filesystem::directory_iterator file(source);
    for (; file != boost::filesystem::directory_iterator(); ++file) {
        try {
            boost::filesystem::path current(file->path());
            if (boost::filesystem::is_directory(current)) {
                if (!copy_directory(current.c_str(), (destination / current.filename()).c_str())) {
                    return false;
                }
            } else {
                boost::filesystem::copy_file(current, destination / current.filename());
            }
        }
        catch (boost::filesystem::filesystem_error const &e) {
            std::cerr << e.what() << '\n';
        }
    }
    return true;
}

std::string FileSystemProcessor::combine_path(const std::string &path_1, const std::string &path_2) {
    boost::filesystem::path p_1(path_1);
    return (p_1 /= path_2).string();
}

bool FileSystemProcessor::get_jpgfiles(const std::string &filedir,
                                       std::vector<std::string> &jpgfiles) {
    get_directory_files(filedir, jpgfiles, ".jpg", SEARCH_OPTION_T::ALLDIRECTORIES);

    return !jpgfiles.empty();
}

bool FileSystemProcessor::get_txtfiles(const std::string &filedir,
                                       std::vector<std::string> &txtfiles) {
    get_directory_files(filedir, txtfiles, ".txt", SEARCH_OPTION_T::ALLDIRECTORIES);

    return !txtfiles.empty();
}
}
}
}
