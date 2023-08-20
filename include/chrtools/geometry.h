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

//
#pragma once
#include "chrtools/stracc.h"






using T = int;
struct STR_PUBLIC point
{

    T x = 0;
    T y = 0;

    using list = std::vector<point>;
    using iterator = point::list::iterator;
    using const_iterator = point::list::const_iterator;

    point() {};
    point(point&&) noexcept = default;
    ~point() {}

    point(T x_, T y_) :x(x_), y(y_) {}
    point(const point& p)
    {
        x = p.x;
        y = p.y;
    }


    point& operator = (const point& p) { x = p.x; y = p.y; return *this; }

    point& operator -= (const point& dxy)
    {
        x -= dxy.x;
        y -= dxy.y;
        return *this;
    }


    point& operator += (const point& dxy)
    {
        x += dxy.x;
        y += dxy.y;
        return *this;
    }

    point operator + (const point& dxy) const
    {
        return {dxy.x+x, dxy.y+y};
    }

    point maximum ( const point& b) const;
    point minimum ( const point& b) const;
    point operator - (const point& dxy) const
    {
        return { x - dxy.x, y - dxy.y };
    }

    point& operator ()(T x_, T y_)
    {
        x = x_;
        y = y_;
        return *this;
    }
    operator std::string() const
    {
        stracc str = "{%d,%d}";
        str << x << y;
        return str();
    }
};


struct STR_PUBLIC dim
{
    int w = 0;
    int h = 0;

    point minmum{};
    point maximum{};

    operator bool() const { return ((w > 0) && ( h > 0)); }
    operator std::string() const;

    bool operator < (const dim& dwh) const;
    bool operator == (const dim& dwh) const;
    bool operator > (const dim& dwh) const ;
    bool operator != (const dim& dwh) const;

    bool size_policy() const { return !((minmum.x <= 0) && (minmum.y <= 0) && (maximum.x <= 0) && (maximum.y <= 0));}

    T area() const { return w * h; }
};


// assign : {a.x(x), a.y(y), b.x(x + w - 1), b.y(y + h - 1)}
// width{ return  b.x - a.x + 1; }

struct STR_PUBLIC rect
{

    point a;
    point b;
    dim   wh;

    using list = std::vector<rect>;
    using iterator = rect::list::iterator;
    using const_iterator = rect::list::const_iterator;

    rect() {}
    ~rect() {}
    rect(rect&& r) noexcept;
    rect(const rect& r);


    rect& operator=(rect&& r) noexcept;
    rect& operator=(const rect& r) ;

    rect(point a_, point b_)
    {
        a = a_;
        b = b_;
        wh.w = b.x-a.x + 1;
        wh.h = b.y-a.y + 1;
    }

    /*!
     * \brief Construct a rect from the dim values.
     * \param wh
     */
    rect(const dim& dxy)
    {
        a = {};
        wh = dxy;
        b = { a.x + wh.w-1, a.y + wh.h -1 };
    }
    /*!
     * \brief Construct a rect from the dim values, at point a_.
     * \param a_
     * \param d
     */
    rect(point a_, dim d)
    {
        a = a_;
        wh = d;
        b = {a.x+d.w-1, a.y+d.h-1};
    }

    void assign(T x, T y, T w, T h)
    {
        a = { x,y };
        b = { x + w-1, y + h-1 };
        wh = {w,h};
    }

    void set_topleft(point pt);

    void assign(point a_, point b_)
    {
        a = a_;
        b = b_;
        wh.w = b.x - a.x+1;
        wh.h = b.y - a.y+1;
    }

    void assign(point a_, dim dxy)
    {
        a = a_;
        wh = dxy;
        b = { a.x + dxy.w - 1, a.y + dxy.h - 1 };
    }


    rect& operator += (point dx)
    {
        a += dx;
        b += dx;
        return *this;
    }
    rect& operator -= (point dx)
    {
        a -= dx;
        b -= dx;
        return *this;
    }
    void resize(dim new_sz)
    {
        assign({ a.x, a.y }, new_sz);
    }

    void move_at(const point& p)
    {
        a.x = p.x;
        a.y = p.y;
        b.x = a.x + wh.w - 1;
        b.y = a.y + wh.h - 1;
    }


    bool in(point p) const
    {
        return ((p.x >= a.x) && (p.x <= b.x) && (p.y >= a.y) && (p.y <= b.y));
    }


    void move(point dt)
    {
        a += dt;
        b += dt;
    }

    int width()  const { return wh.w; }
    int height() const  { return wh.h; }

    bool operator [](const point& p) const
    {
        return ((p.x >= a.x) && (p.x <= b.x) && (p.y >= a.y) && (p.y <= b.y));
    }

    /*!
        @brief intersection between this (A) and r (B).

        @note A & B must be on the same referential offset. Undefined behaviour otherwise.
        @author &copy; 1996, 2023, Serge Lussier, (oldlonecoder@gmail.com)
        @code
       A+==============================+
        |                              |
        |  B+==========================|===========+
        |   |                          |           |
        |   |                          |           |
        +==============================+           |
            |                                      |
            |                                      |
            +======================================+
        @endcode
    */
    rect operator & (rect r) const
    {
        rect A;
        A.a = { std::max(a.x, r.a.x), std::max(a.y ,r.a.y)};
        A.b = { std::min(b.x, r.b.x), std::min(b.y, r.b.y)};

        auto c = in(A.a) || in(A.b);
        //A += B.a;
        if (!c)
            A.wh = {  };
        else{
            A.wh.w = A.b.x-A.a.x+1;
            A.wh.h = A.b.y-A.a.y+1;
        }
        // Need to check again...
        if ((A.wh.h <= 0) || (A.wh.w <= 0))
            A.wh = {};

        return A;
    }

    /*!
     * \brief operator / Get the intersection between this and rhs then get the origin of this from rhs
     * \param rhs
     * \return result rect
     */
    rect operator / (rect rhs)
    {
        rect A = *this & rhs;
        A -= a;
        return A;
    }
    /*!
        @brief merges this and r
    */
    rect operator | (rect r) const
    {
        rect ret;
        point a_ = { r.a.x <= a.x ? r.a.x : a.x, r.a.y <= a.y ? r.a.y : a.y };
        point b_ = { r.b.x <= b.x ? r.b.x : b.x, r.b.y <= b.y ? r.b.y : b.y };
        ret.assign(a_, b_);
        return ret;
    }

    rect operator + (const point& xy)const {
        rect r = *this;
        r.a.x += xy.x;
        r.a.y += xy.y;
        r.b.x += xy.x;
        r.b.y += xy.y;
        r.wh = wh;
        return r;
    }

    std::string to_string() const;
    operator std::string() const ;
    operator bool() const
    {

        return wh.operator bool();
    }
};



struct STR_PUBLIC winbuffer
{
    stracc* win = nullptr;
    point cxy;
    rect r;

    winbuffer& gotoxy(int x, int y);
    winbuffer& operator << (point xy);
    void set_geometry(int w, int h);

    // internal cursor movements:
    winbuffer& operator ++();
    winbuffer& operator ++(int);
    winbuffer& operator --();
    winbuffer& operator --(int);
    // --------------------------
    template<typename T> winbuffer& operator << (T v)
    {
        stracc str;
        str << v;
        return put(str());
    }




    winbuffer& put(const std::string& txt);

    void clear();
    void release();
    std::string details();
    operator std::string();// {return win ? win->str() : "";}

};




