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

#include "chrtools/stracc.h"



#include <chrono>




//impl_rttn(stracc)


stracc& stracc::operator += (const stracc& acc)
{
    _d += acc();
    return *this;
}


std::string::size_type stracc::_scan_arg(std::string::size_type _pos)
{
    //std::cerr << "line:" << __LINE__<< ":_scan_arg(" << _pos << ") : '" << _d << "'\n";
    _arg_pos = _d.find("%", _pos);
    if(_arg_pos != std::string::npos)
    {
        //std::cerr << "check _d[arg_pos+1]: _d[" << _arg_pos + 1 << "] : '" << _d[_arg_pos+1] << "'\n";

        if(_arg_pos < _d.length())
        {
            if(_d[_arg_pos + 1] == '%')
            {
                // forcément sur l'autre cas : '%' donc _d contient "%%" :
                _d.erase(_arg_pos,1);
                std::cerr << "_d.erase(" << _arg_pos << ",1) : '" << _d << "'\n" <<
                             "=> _d[arg_pos+1] = '" << _d[_arg_pos+1] << "'\n";
                std::cerr << "recurse at: " << _arg_pos+1 << ":\n";
                return _scan_arg(_arg_pos+1);
            }
            //std::cerr << " return valid argument position: " << _arg_pos << " > '" << _d << "'\n";
            return _arg_pos;
        }
        if(_d[_arg_pos+1] == ' ')
            return _scan_arg(_arg_pos+1);

    }
    return std::string::npos;
}



stracc& stracc::operator , (const stracc& acc)
{
    _d += acc();
    return *this;
}

stracc& stracc::operator , (Icon::Type Ic)
{
    _d += Icon::Data[Ic];
    return *this;
}
stracc& stracc::operator , (Accent::Type Ac)
{
    _d += Accent::Data[Ac];
    return *this;
}

stracc& stracc::operator , (chattr::pair arg_)
{
    _d += arg_();
    return *this;
}

stracc::stracc()
{
}


stracc::~stracc()
{
    _d.clear();
}

stracc &stracc::fill(char c, int count)
{
    _d += std::string(count, c);
    return *this;
}

stracc& stracc::operator << (chattr::pair arg_)
{
    std::string dd = attr<chattr::format::ansi256>::bg(arg_.bg);
    dd += attr<chattr::format::ansi256>::fg(arg_.fg);
    return _format(dd);
}


stracc& stracc::operator<<(color::type arg_)
{
    return _format(attr<chattr::format::ansi256>::fg(arg_));
}

stracc &stracc::operator<<(const stracc &acc)
{
    return _format(acc());
}

stracc &stracc::operator<<(Icon::Type Ic)
{
    return _format(Icon::Data[Ic]);
}

stracc &stracc::operator<<(Accent::Type Ac)
{
    return _format(Accent::Data[Ac]);
}

void stracc::clear()
{
    _d.clear();
}

std::string stracc::make_str(const char* B, const char* E)
{
    std::string Str;
    const char* C = B;
    if ((!B) || (!E) || (!*B) || (!*E))
        return Str;
    while (C <= E)
        Str += *C++;

    return Str;
}

std::string stracc::now(const std::string& str_fmt)
{
    // Old archaic code...
    // time_t rawtime;
    // struct tm* timeinfo;
    // char tmb[180];
    // std::time(&rawtime);
    // timeinfo = std::localtime(&rawtime);
    // std::strftime(tmb, 60, str_fmt.c_str(), timeinfo);
    // std::string _s = tmb;
    // //return tmb;


    auto current = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::to_time_t(current);
    auto local = localtime(&now);
    std::ostringstream ostr;
    ostr << std::put_time(local, str_fmt.c_str());
    return ostr.str();
}



