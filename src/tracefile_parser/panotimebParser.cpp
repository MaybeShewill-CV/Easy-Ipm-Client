/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: panotimebParser.cpp
* Date: 18-12-11 下午1:41
************************************************/

#include "panotimebParser.h"

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace beec {
namespace tracefile_parser {

/*****
 * Public function sets
 */

/***
 * 构造函数
 * @param panotime_file
 */
PanotimebParser::PanotimebParser(const std::string &panotime_file) {

    parse_keydate(panotime_file);
    std::ifstream ifile(panotime_file);
    std::vector<std::string> lines;
    while (ifile)
    {
        std::string line;
        std::getline(ifile, line);
        lines.push_back(line);
    }
    _keys.reserve(lines.size());
    for (auto &line : lines) {

        if (line[0] == '#')
        {
            continue;
        }
        std::vector<std::string> split_res;
        boost::split(split_res, line, boost::is_any_of(" "));
        if (split_res.size() != 25) {
            continue;
        }

        PanotimeBItem item;
        item.capture_id = boost::lexical_cast<uint32_t>(split_res[0]);
        item.xxx = boost::lexical_cast<double>(split_res[4]);
        item.yyy = boost::lexical_cast<double>(split_res[5]);
        item.ne_xxx = boost::lexical_cast<double>(split_res[6]);
        item.north_rad = boost::lexical_cast<double>(split_res[7]);

        item.keydate_id = boost::to_lower_copy(split_res[9]);

        item.pitch_deg = boost::lexical_cast<double>(split_res[17]);
        item.roll_deg = boost::lexical_cast<double>(split_res[18]);
        item.q = boost::lexical_cast<uint32_t>(split_res[19]);
        _panob_map[item.capture_id] = item;
        _keys.push_back(item.capture_id);
    }
}

/***
 * 返回轨迹点轨迹信息
 * @param capture_id
 * @return
 */
const PanotimeBItem& PanotimebParser::operator[](PanotimebParser::key_type capture_id) {

    return _panob_map[capture_id];
}

/*****
 * Private function sets
 */

/***
 * 解析车天号
 * @param panotime_file
 */
void PanotimebParser::parse_keydate(const std::string &panotime_file) {

    std::string filename = boost::filesystem::path(panotime_file).filename().string();
    _keydate = boost::to_lower_copy(filename.substr(8, 10));
}

}
}
