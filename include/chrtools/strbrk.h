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
    using iterator = std::string::const_iterator;
    using list     = std::vector<std::string>;
 public:

    enum opt{
        keep,
        discard
    };
    strbrk() = default;
    ~strbrk() = default;

    struct STR_PUBLIC  token_t
    {
        std::string::const_iterator mStart;
        std::string::const_iterator mEnd;
        std::string::const_iterator mSE;

        std::string operator()() const;
        std::string operator*() const;

        using list = std::vector<strbrk::token_t>;
        using iterator = strbrk::token_t::list::iterator;
        [[maybe_unused]] [[nodiscard]] std::string Mark() const;

        int         mLine     = 1;
        int         mCol      = 1;
        std::size_t mPosition = 0;

        std::string location();
    };

    struct STR_PUBLIC  config_data
    {
        const char* c;
        std::string delimiters;
        strbrk::opt o;
        strbrk::token_t::list tokens;
    };


    std::size_t operator()(strbrk::token_t::list &Collection, std::string aDelimiters = "", strbrk::opt aopt = strbrk::keep) const;
    strbrk::iterator scan_to(strbrk::iterator start_, char c_) const;
private:
    struct s_p_s
    {
        std::string::const_iterator _begin;
        std::string::const_iterator _pos;
        std::string::const_iterator _end; /// ...

        int      _line  = 1;
        int      _col   = 1;
        uint64_t _index = 0;

        s_p_s() = default;
        ~s_p_s() = default;

        explicit s_p_s(const std::string& str_);
        bool skip_ws();
        [[nodiscard]] bool end() const;
        bool operator++();
        bool operator++(int);
        void reset(const std::string& str_)
        {
            _pos   = _begin = str_.cbegin();
            _line  = _col   = 1;
            _index = 0;
            _end  = str_.cend();
        }
        s_p_s &operator>>(strbrk::token_t &word_);
    } _cursor;
public:
    strbrk& operator=(const std::string& str_);
    strbrk& operator=(const char* str_);
    std::string operator()(){ return data.c; }
private:
    config_data data;

};



