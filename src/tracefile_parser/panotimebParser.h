/************************************************
* Copyright 2018 Baidu Inc. All Rights Reserved.
* Author: Luo Yao
* File: panotimebParser.h
* Date: 18-12-11 下午1:41
************************************************/

#pragma once

#include <string>
#include <vector>

#include <boost/unordered_map.hpp>

namespace beec {
namespace tracefile_parser {

struct PanotimeBItem
{
    std::string keydate_id;
    uint32_t capture_id;
    double xxx;
    double yyy;
    double ne_xxx;
    double north_rad;
    double pitch_deg;
    double roll_deg;
    uint32_t q;

    PanotimeBItem() : keydate_id(""), capture_id(0), xxx(0.0), yyy(0.0),
        ne_xxx(0.0), north_rad(0.0), pitch_deg(0.0), roll_deg(0.0), q(0) {}

    PanotimeBItem &operator=(const PanotimeBItem &panobitem) {

        keydate_id = panobitem.keydate_id;
        capture_id = panobitem.capture_id;
        xxx = panobitem.xxx;
        yyy = panobitem.yyy;
        ne_xxx = panobitem.ne_xxx;
        north_rad = panobitem.north_rad;
        pitch_deg = panobitem.pitch_deg;
        roll_deg = panobitem.roll_deg;
        q = panobitem.q;

        return *this;
    };

    PanotimeBItem(const PanotimeBItem &panobitem) {

        keydate_id = panobitem.keydate_id;
        capture_id = panobitem.capture_id;
        xxx = panobitem.xxx;
        yyy = panobitem.yyy;
        ne_xxx = panobitem.ne_xxx;
        north_rad = panobitem.north_rad;
        pitch_deg = panobitem.pitch_deg;
        roll_deg = panobitem.roll_deg;
        q = panobitem.q;
    };

};

class PanotimebParser {

    using key_type = uint32_t;
    using value_type = PanotimeBItem;
    using keys_type = std::vector<key_type>;
    using map_type = boost::unordered_map<key_type, value_type>;
    using iterator_type = map_type::iterator;
    using const_iterator_type = map_type::const_iterator;

public:

    explicit PanotimebParser(const std::string &panotime_file);
    ~PanotimebParser() = default;

    const PanotimeBItem & operator[](key_type capture_id);

    const_iterator_type begin() const
    {
        return _panob_map.begin();
    }

    const_iterator_type end() const
    {
        return _panob_map.end();
    }

    const keys_type &keys() const
    {
        return _keys;
    }

    std::string keydate() const
    {
        return _keydate;
    }

protected:

    map_type _panob_map;
    keys_type _keys;
    std::string _keydate;

private:

    PanotimebParser() = default;

    void parse_keydate(const std::string &panotime_file);

};

}
}
