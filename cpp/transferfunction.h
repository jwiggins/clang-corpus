/*
    transferfunction.h
    $Id: transferfunction.h,v 1.5 2003/05/04 23:51:35 prok Exp $
*/

#ifndef TRANSFER_FUNCTION_H
#define TRANSFER_FUNCTION_H

#include <list>
#include "color.h"

using namespace std;

struct opac {
    float pos;
    float alpha;
};

struct color {
    float pos;
    color_t col;
};

class TransferFunction {
public:
                        TransferFunction();
                        TransferFunction(const TransferFunction &t);
                        ~TransferFunction();

    void                AddOpacity(float position, float opacity);
    void                AddColor(float position, float r, float g, float b);

    float               GetOpacity(float density) const;
    color_t             GetColor(float density) const;

    void                SetDensityRange(float lower, float upper);
    void                Print() const;

private:

    float               mRStart, mREnd;
    list<opac>          mOpacities;
    list<color>         mColors;
};

inline TransferFunction::TransferFunction()
: mOpacities(), mColors()
{
    mRStart = 0.0;
    mREnd = 1.0;
}

inline TransferFunction::TransferFunction(const TransferFunction &t)
:mRStart(t.mRStart),mREnd(t.mREnd),
mOpacities(t.mOpacities), mColors(t.mColors)
{
}

inline TransferFunction::~TransferFunction()
{
    // nothin!
}

inline void TransferFunction::AddOpacity(float position, float opacity)
{
    opac o;
    bool ins=false;

    // fill it in
    o.pos = position;
    o.alpha = opacity;
    // add it to the opacities vector
    for (list<opac>::iterator i=mOpacities.begin(); !ins && i != mOpacities.end(); ++i)
    {
        if (position <= i->pos)
        {
            mOpacities.insert(i, o);
            ins = true;
        }
    }
    if (!ins)
        mOpacities.push_back(o);
}

inline void TransferFunction::AddColor(float position, float r, float g, float b)
{
    color c;
    color_t rgb(r,g,b);
    bool ins=false;

    // fill it in
    c.pos = position;
    c.col = rgb;
    // add it to the colors vector
    for (list<color>::iterator i=mColors.begin(); !ins && i != mColors.end(); ++i)
    {
        if (position <= i->pos)
        {
            mColors.insert(i, c);
            ins = true;
        }
    }
    if (!ins)
        mColors.push_back(c);
}

inline float TransferFunction::GetOpacity(float density) const
{
    float dScaled, result;
    list<opac>::const_iterator i = mOpacities.begin();
    opac b, a;

    // what is density when scaled to the range [0,1] ?
    dScaled = (density-mRStart) / (mREnd-mRStart);

    while (i != mOpacities.end() && dScaled >= i->pos)
        ++i;

    b = *i;
    a = *(--i);

    result = a.alpha + (dScaled-a.pos)*((b.alpha-a.alpha)/(b.pos-a.pos));

    return result;
}

inline color_t TransferFunction::GetColor(float density) const
{
    color_t result;
    float dScaled;
    list<color>::const_iterator i = mColors.begin();

    // what is density when scaled to the range [0,1] ?
    dScaled = (density-mRStart) / (mREnd-mRStart);

    while (i != mColors.end() && dScaled >= i->pos)
        i++;

    color b = *i, a = *(--i);
    float xpos=dScaled-a.pos;

    result.r = a.col.r+xpos*((b.col.r-a.col.r)/(b.pos-a.pos));
    result.g = a.col.g+xpos*((b.col.g-a.col.g)/(b.pos-a.pos));
    result.b = a.col.b+xpos*((b.col.b-a.col.b)/(b.pos-a.pos));

    return result;
}

inline void TransferFunction::SetDensityRange(float lower, float upper)
{
    mRStart = lower;
    mREnd = upper;
}

inline void TransferFunction::Print() const
{
    for (list<opac>::const_iterator i=mOpacities.begin(); i != mOpacities.end(); ++i)
        printf("opacity: position = %f(%f), alpha = %f\n",
                    i->pos, (i->pos-mRStart)*(mREnd-mRStart), i->alpha);

    for (list<color>::const_iterator i=mColors.begin(); i != mColors.end(); ++i)
        printf("color: position = %f(%f), RGB = (%f,%f,%f)\n",
                    i->pos, (i->pos-mRStart)*(mREnd-mRStart), i->col.r,i->col.g,i->col.b);
}

#endif

