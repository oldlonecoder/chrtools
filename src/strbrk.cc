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

#include "chrtools/strbrk.h"


[[maybe_unused]] std::string strbrk::_default_token_separators = "\\%(){}[]`$#@!;,~?^&<>=+-*/:.";


std::string strbrk::word::operator()() const
{
    std::string Str;
    if(begin == end)
        Str.insert(Str.begin(), begin, end + 1);
    else
        Str.insert(Str.begin(), begin, end + 1);

    return Str;
}

std::string strbrk::word::operator*() const
{
    std::string Str;
    if(begin == end)
        Str.insert(Str.begin(), begin, end + 1);
    else
        Str.insert(Str.begin(), begin, end + 1);

    return Str;

}

std::string strbrk::word::mark() const
{
    std::string Str;
    std::string_view::iterator CStart = begin - offset;

    //int                   l  = 1;
    auto cc = CStart;
    // localiser le debut de la ligne;
    while(*cc && (cc > CStart) && (*cc != '\n') && (*cc != '\r'))
        --cc;
    // debut de la ligne ou de la source:
    if(cc >= CStart)
    {
        if((*cc == '\n') || (*cc == '\r'))
            ++cc;
        while((cc != str_end) && (*cc != '\n') && (*cc != '\r'))
            Str += *cc++;
    }

    Str += '\n'; ///@todo Encode new line.
    for(int x = 1; x < column; x++)
        Str += ' ';
    Str += '^';
    return Str;
}

std::string strbrk::word::location()
{
    std::ostringstream Str;
    Str << '(' << line << ',' << column << ')';
    return Str.str();
}


// ------------------------ strbrk::s_p_s --------------------------------


strbrk::s_p_s::s_p_s(std::string_view aStr):
    _begin(aStr.cbegin()),
    _pos(aStr.cbegin()),
    _end(aStr.cbegin())
{

}

/*!
    @note Enleveer le code de trop (suivi du num de ligne et de la col).
*/
bool strbrk::s_p_s::skip_ws()
{
    if(end())
        return false;

    while(isspace(*_pos))
    {
        switch(*_pos)
        {
        case 10:
        {
            if((++_pos) >= _end)
                return false;
            if(*_pos == 13)
                ++_pos;
            ++_line;
            _col = 1;
        }
            break;
        case 13:
        {
            if((++_pos) >= _end)
                return false;
            if(*_pos == 10)
                ++_pos;
            ++_line;
            _col = 1;
        }
            break;
        case '\t':++_pos;
            ++_col;
            break;
        default:++_pos;
            ++_col;
            break;
        }
    }
    return _pos < _end;

}


bool strbrk::s_p_s::end() const
{
    return _pos >= _end;
}


bool strbrk::s_p_s::operator++()
{
    if(_pos >= _end)
        return false;
    ++_pos;
    ++_col;
    if(_pos >= _end)
        return false;
    return skip_ws();
}
bool strbrk::s_p_s::operator++(int)
{
    if(_pos >= _end)
        return false;
    ++_pos;
    ++_col;
    if(_pos >= _end)
        return false;
    return skip_ws();
}

strbrk::s_p_s &strbrk::s_p_s::operator>>(strbrk::word &aWord)
{
    aWord.begin    = _pos;
    aWord.line     = _line;
    aWord.column      = _col;
    aWord.offset = _index = (uint64_t) (_pos - _begin);
    return *this;
}

strbrk::iterator strbrk::scan_to(strbrk::iterator aStart, char c) const
{
    strbrk::iterator p = aStart;
    ++p;
    while((p != data.c.end()) && (*p != c))
        ++p;
    return p;
}


/*!
    * @brief break/split/tokenize,etc... the content of a string into pieces.
    * @param none
    * @return number of "Words/tokens" contained into the data.words.
    * @notice : After several years of experience and experimentations, We have determined that
    * white-spaces/ctrl or spacing characters are silent and implicit delimiters, in addition to the ones supplied by \c aDelimiters.
*/
std::size_t strbrk::operator()()
{
    std::string_view _d(data.c);
    if(_d.empty())
        std::cerr << "---> content is empty!";

    if(data.delimiters.empty())
        data.delimiters = strbrk::_default_token_separators;

    strbrk::s_p_s cursor;
    cursor.reset(_d);
    if(!cursor.skip_ws())
        return 0;

    word w;
    cursor >> w;
    while(!cursor.end())
    {
        strbrk::iterator cc = cursor._pos;
        if(data.delimiters.find(*cursor._pos) != std::string::npos)
        {
            cc = cursor._pos;
            if(cc > w.begin)
            {
                --cc;
                data.words.push_back({w.begin, cc, cursor._end, w.line, w.column, w.offset});
                cursor >> w;
                cc = cursor._pos;
            }

            // '//' as one token_t insbookd of having two consecutive '/'
            if((*cursor._pos == '/') && (*(cursor._pos + 1) == '/'))
                ++cursor;

            if(data.o == strbrk::opt::keep)
            {
                data.words.push_back({w.begin, cursor._pos, cursor._end, w.line, w.column, w.offset});
            }
            ++cursor;
            //std::cout << "        Iterator eos: " << _Cursor.end() << "\n";
            if(!cursor.end())
                cursor >> w;
            else
            {
                return data.words.size();
            }

        }
        else if((*cursor._pos == '\'') || (*cursor._pos == '"'))
        { // Quoted litteral string...
            cursor >> w;
            if(data.o == strbrk::opt::keep)
            {
                // Create the three parts of the quoted string: (") + (litteral) + (") ( or ' )
                // So, we save the token_t coords anyway.
                data.words.push_back({w.begin, w.begin, cursor._end, w.line, w.column, w.offset});
            }

            strbrk::iterator p = scan_to(w.begin + (data.o == strbrk::opt::keep ? 0 : 1), *cursor._pos); // w.B is the starting position, _Cursor.m is the quote delim.
            while(cursor._pos < p)
                ++cursor; // compute white spaces!!!

            if(data.o == strbrk::opt::keep)
            {
                // then push the litteral that is inside the quotes.
                data.words.push_back({w.begin + 1, p - 1, cursor._end, w.line, w.column, w.offset});
                //++_Cursor; // _Cursor now on the closing quote
                cursor >> w; // Litteral is done, update w.
                data.words.push_back({w.begin, p, cursor._end, w.line, w.column, w.offset});
            }
            else
            {
                // Push the entire quote delims surrounding the litteral as the token_t.
                data.words.push_back({w.begin, cursor._pos, cursor._end, w.line, w.column, w.offset});
            }
            if(++cursor)
                cursor >> w;
            else
                return data.words.size();

        }
        else
        {
            cc = cursor._pos;
            ++cc;
            if(cc == cursor._end)
            {
                ++cursor._pos;
                break;
            }
            if(isspace(*cc))
            {
                if(w.begin < cc)
                {
                    data.words.push_back({w.begin, cc - 1, cursor._end, w.line, w.column, w.offset});
                    ++cursor;
                }

                if(cursor.skip_ws())
                {
                    cursor >> w;
                    continue;
                }
                return data.words.size();
            }
            if(!cursor.end())
                ++cursor; // advance offset to the next separator/white space.
        }

    }


    return 0;
}




