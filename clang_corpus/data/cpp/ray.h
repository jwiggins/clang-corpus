/*
    ray.h
    $Id: ray.h,v 1.2 2002/11/18 02:35:00 prok Exp prok $
*/

#ifndef RAY_H
#define RAY_H

#include <stdio.h>
#include "veclib.h"

class Ray {
public:
               Ray();
               Ray(const Vector3 &p0, const Vector3 &p1);
               Ray(const Ray &r);
               ~Ray() {}

    void       Set(const Vector3 &p0, const Vector3 &p1);
    bool       IsValid() const { return valid; }

    Vector3    Origin() const { return origin; }
    Vector3    EndPoint() const { return endpoint; }
    Vector3    Direction() const { return direction; }

    Vector3    PointAt(float t) const;
    float      TForPoint(const Vector3 &P) const;

    void       Print() const;

private:

    Vector3    origin, endpoint;
    Vector3    direction;
    bool       valid;
};

inline Ray::Ray()
: origin(0.0,0.0,0.0),
endpoint(0.0,0.0,0.0),
direction(0.0,0.0,0.0),
valid(false)
{}

inline Ray::Ray(const Ray &r)
: origin(r.origin),
endpoint(r.endpoint),
direction(r.direction),
valid(r.valid)
{}

inline Ray::Ray(const Vector3 &p0, const Vector3 &p1)
: origin(p0),
endpoint(p1),
direction(p1 - p0),
valid(true)
{
    // make sure direction is unit length
    direction.Normalize();
}

inline void Ray::Set(const Vector3 &p0, const Vector3 &p1)
{
    origin = p0;
    endpoint = p1;
    direction = p1 - p0; direction.Normalize();
    valid = true;
}

inline Vector3 Ray::PointAt(float t) const
{
    return origin + (direction * t);
}

inline float Ray::TForPoint(const Vector3 &P) const
{
    // direction is unit, so the length of the vector between
    // P and the origin is also the t value needed to obtain P
    return (P-origin).Magnitude();
}

inline void Ray::Print() const
{
    printf("Ray: (%f,%f,%f) + (%f,%f,%f)*t\n", origin.X(),origin.Y(),origin.Z(),
           direction.X(),direction.Y(),direction.Z());
}

#endif

