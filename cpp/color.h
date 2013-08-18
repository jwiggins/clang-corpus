/*
    color.h
    $Id: color.h,v 1.1.1.1 2003/04/19 05:18:21 prok Exp $
*/

#ifndef COLOR_H
#define COLOR_H

struct color_t {
                    color_t() { r=0.0; g=0.0; b=0.0; }
                    color_t(const color_t &c) { r=c.r; g=c.g; b=c.b; }
                    color_t(float _r, float _g, float _b) { r=_r; g=_g; b=_b; }

    color_t &       operator=(const color_t &c)
                    { r=c.r; g=c.g; b=c.b; return *this; }
    color_t         operator*(float a) const
                    {
                        color_t res;
                        res.r = a * r;
                        res.g = a * g;
                        res.b = a * b;
                        return res;
                    }
    friend color_t  operator*(float a, const color_t &c)
                    {
                        return c*a;
                    }
    color_t         operator*(const color_t &c)
                    {
                        color_t res;
                        res.r = c.r * r;
                        res.g = c.g * g;
                        res.b = c.b * b;
                        return res;
                    }
    color_t         operator+(const color_t &c)
                    {
                        color_t res;
                        res.r = c.r + r;
                        res.g = c.g + g;
                        res.b = c.b + b;
                        return res;
                    }

    float           r,g,b;
};

#endif
