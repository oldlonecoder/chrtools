/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all code in this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/

#pragma once
#include "chrtools/stracc.h"



//using std::string;
using std::string;

class STR_PUBLIC strbrk
{
    [[maybe_unused]] static std::string _default_token_separators;
    using iterator = std::string_view::iterator;
    using list     = std::vector<std::string>;

 public:

    enum opt{
        keep,
        discard
    };
    strbrk() = default;
    ~strbrk() = default;

    struct STR_PUBLIC  word
    {
        strbrk::iterator begin;
        strbrk::iterator end;
        strbrk::iterator str_end;

        std::string operator()() const;
        std::string operator*() const;

        using list = std::vector<strbrk::word>;
        using iterator = strbrk::word::list::iterator;
        [[maybe_unused]] [[nodiscard]] std::string mark() const;

        int         line   = 1;
        int         column = 1;
        std::size_t offset = 0;
        std::string location();
    };

    struct STR_PUBLIC  config_data
    {
        std::string_view c;
        std::string_view delimiters;
        strbrk::opt o;
        strbrk::word::list words;
    };

    config_data& config() { return data; }
//    std::size_t operator()(strbrk::word::list &Collection, std::string aDelimiters = "", strbrk::opt aopt = strbrk::keep) const;
    std::size_t operator()();

    strbrk::iterator scan_to(strbrk::iterator start_, char c_) const;
private:
    struct s_p_s
    {
        std::string_view::iterator _begin;
        std::string_view::iterator _pos;
        std::string_view::iterator _end; /// ...

        int      _line  = 1;
        int      _col   = 1;
        uint64_t _index = 0;

        s_p_s() = default;
        ~s_p_s() = default;

        explicit s_p_s(std::string_view str_);
        bool skip_ws();
        [[nodiscard]] bool end() const;
        bool operator++();
        bool operator++(int);
        void reset(std::string_view str_)
        {
            _pos   = _begin = str_.begin();
            _line  = _col   = 1;
            _index = 0;
            _end  = str_.end();
        }
        s_p_s &operator>>(strbrk::word &word_);
    } _cursor;
private:
    config_data data;

};



