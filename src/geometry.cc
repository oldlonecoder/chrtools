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


#include "chrtools/geometry.h"
#include "chrtools/stracc.h"







bool dim::operator < (const dim& dwh) const
{
    return dwh.area() > area();
}

bool dim::operator == (const dim& dwh) const
{
    return area() == dwh.area();
}

bool dim::operator > (const dim& dwh) const
{
    return area() > dwh.area();
}

bool dim::operator != (const dim& dwh) const
{
    return area() != dwh.area();
}



rect::rect(rect&& r) noexcept:
a(std::move(r.a)),
b(std::move(r.b)),
wh(std::move(r.wh))
{

}
rect::rect(const rect& r) :
a(r.a),
b(r.b),
wh(r.wh)
{

}


rect& rect::operator=(rect&& r) noexcept
{
    a = std::move(r.a);
    b = std::move(r.b);
    wh = std::move(r.wh);
    return *this;
}

void rect::set_topleft(point pt)
{
    a = pt;
    b = { a.x + wh.h-1, a.y + wh.h-1 };
}


rect& rect::operator=(const rect& r)
{
    a = r.a;
    b = r.b;
    wh = r.wh;
    return *this;

}


dim::operator std::string() const
{
    //stracc str = "{{%d,%d}, {%d,%d}, %d %d}: %d";
    //str << min.x << min.y << max.x << max.y << w << h << w*h;
    stracc str;
    if(size_policy())
    {
        str = "(%d/(%d,%d),%d/(%d,%d)):%d";
        str << w << minmum.x << maximum.x << h << minmum.y << maximum.y << w*h;
    }
    else
    {
        str = "(%d,%d):%d";
        str << w << h << w*h;
    }
    return  str();
}


//- -------------------------------- winbuffer ------------------------------------------------------------


winbuffer &winbuffer::gotoxy(int x, int y)
{
    cxy = {x, y};
    return *this;
}

void winbuffer::set_geometry(int w, int h)
{
    r = rect(point(0,0),dim{w,h});

    clear();
}

winbuffer &winbuffer::operator++()
{
    if(cxy.x >= r.wh.w)
    {
        if(cxy.y <= r.wh.h)
        {
            cxy.y++;
            cxy.x = 0;
        }
    }
    else
        cxy.x++;

    return *this;
}

winbuffer &winbuffer::operator++(int)
{
    if(cxy.x >= r.wh.w)
    {
        if(cxy.y <= r.wh.h)
        {
            cxy.y++;
            cxy.x = 0;
        }
    }
    else
        cxy.x++;
    return *this;
}

winbuffer &winbuffer::operator--()
{

    return *this;
}

winbuffer &winbuffer::operator--(int)
{
    return *this;
}

/// <summary>
/// Serge Lussier
/// p = 3
/// 10-13 + 3;
///        *   Serge L*
/// </summary>
/// <param name="txt"></param>
/// <returns></returns>
winbuffer &winbuffer::put(const std::string &txt)
{
    std::size_t line_width = r.width() - cxy.x;
    auto ln = txt.length();

    auto dx = line_width <= ln ? line_width : ln;

    std::string::iterator crs = win->str().begin() + cxy.y * r.width() + cxy.x;
    auto p   = txt.begin();
    for(size_t x = 0; x < dx; x++)
        *crs++ = *p++;

    cxy.x += line_width;

    return *this;
}

void winbuffer::clear()
{
    if(!win)
        win = new stracc;
    else
        win->clear();

    *win = std::string(r.width() * r.height(), ' ');
    //std::cerr << __PRETTY_FUNCTION__ << "contents: '" << win->_d << "'\n";
}

void winbuffer::release()
{
    delete win;
}

std::string winbuffer::details()
{
    stracc str = "winbuffer details:\n";
    str << r.to_string() << " cursor: " << std::string(cxy);
    return str();
}

winbuffer::operator std::string()
{
    std::string str;
    if(!win)
        return "oops! there is no such defined and initialised area!";
    str += '\n';
    for(int l = 0; l < r.height(); l++)
    {
        for(int c = 0; c < r.width(); c++)
            str += *(win->str().begin() + (l * r.width() + c));
        str += '\n';
    }
    return str;
}


rect::operator std::string() const
{
    stracc str = "[{%d,%d} {%d,%d}]:{%d*%d}[%d]";
    str << a.x << a.y << b.x << b.y << wh.w << wh.h << wh.w * wh.h;
    return str();
    // return std::format("[{{{},{}}} {{{},{}}}]:{{{}*{}}}[{}]", a.x, a.y, b.x, b.y, sz.w, sz.h, sz.w * sz.h);
}

std::string rect::to_string() const
{
    return this->operator std::string();
}

winbuffer & winbuffer::operator<<(point xy)
{
    gotoxy(xy.x, xy.y);
    return *this;
}

point point::maximum(const point &b) const
{
    point c;
    if(x <= b.x) c.x = b.x; else c.x = x;
    if(y <= b.y) c.y = b.y; else c.y = y;
    return c;
}

point point::minimum(const point &b) const
{
    point c;
    if(x >= b.x) c.x = b.x; else c.x = x;
    if(y >= b.y) c.y = b.y; else c.y = y;
    return c;
}



