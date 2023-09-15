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

int strbrk::s_p_s::scan_string()
{
    char q = *_pos;
    while((_pos != _end) && (*_pos != q)) ++_pos;
    if(_pos == _end)
    {
        --_pos;
        if(*_pos != q) return -1;
    }
    return 0;
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


/*!
 * \brief strbrk::s_p_s::operator >>  Initiate a new strbrk::word instance at the current position:
 * \param aWord
 * \return reftoself
 *
 * \note Be aware that the instance of word has no end iterator yet.
 */
strbrk::s_p_s &strbrk::s_p_s::operator>>(strbrk::word &aWord)
{
    aWord.begin    = _pos;
    aWord.line     = _line;
    aWord.column   = _col;
    aWord.offset   = _index = (uint64_t) (_pos - _begin);
    aWord.str_end =  _end;
    return *this;
}


/*!
 * \brief strbrk::scan_to scans to c from a - So to 'localize' the char 'c' from the iterator a and set an new iteraot iterator to the position of 'c'.
 * \param a the start/initial position iterator from where to scan
 * \param c the char that ends the scan
 * \return iterator position of c
 */
strbrk::iterator strbrk::scan_to(strbrk::iterator a, char c) const
{
    strbrk::iterator p = a;
    ++p;
    while((p != _data.c.end()) && (*p != c))
        ++p;
    return p;
}

bool strbrk::append(s_p_s& cursor, strbrk::config_data& dat, const strbrk::word& w)
{
    dat.words.push_back({w.begin, cursor._pos, cursor._end, w.line, w.column, w.offset});
    return ++cursor;
}



///*!
// * @brief break/split/tokenize,etc... the content of a string into pieces, including the provided delimiters as tokens if option strbrk::option::keep is set.
// * or discarded if option strbrk::option::discard is set.
// *
// * If a sequence of string is surrounded by string quotes, then that `string` sequence will be put in a token, with its quote
// * characters if keep option is set, or without them if discard option is set
// * @param reference to a config_data instance
// * @return number of "Words/tokens" contained into the data.words.
//*/
//std::size_t strbrk::operator()(strbrk::config_data& dt)
//{
//    if(dt.delimiters.empty())  dt.delimiters = strbrk::_default_token_separators;
//    // dt.words must be clear()'ed
//    dt.words.clear();
//    s_p_s cursor(dt.c);

//     // Initiate a new word with the beginning of the sequence at the current cursor position.
//    word w;
//    cursor >> w;
//    while(cursor.end())
//    {
//        strbrk::iterator cc = cursor._pos;
//        if(data.delimiters.find(*cc) != std::string_view::npos)
//        {
//            if(data.o == strbrk::keep)
//                append(cursor, dt, w);
//            cursor++; // and skip whitespaces. Ignore end of string here it is checked above at the loop
//            cursor >> w; // init new word
//            continue;
//        }

//    }
//    return 0;
//}



/*!
    * @brief break/split/tokenize,etc... the content of a string into pieces.
    * @param none
    * @return number of "Words/tokens" contained into the data.words.
    * @notice : After several years of experience and experimentations, We have determined that
    * white-spaces/ctrl or spacing characters are silent and implicit delimiters, in addition to the ones supplied by \c aDelimiters.
*/
std::size_t strbrk::operator()(strbrk::config_data& data)
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
    _data = data;
    word w;
    cursor >> w; // Initiate the first word.
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
    if(cursor._pos > w.begin)
        data.words.push_back({w.begin, cursor._pos - 1, cursor._end, w.line, w.column, w.offset});

    return data.words.size();
}




