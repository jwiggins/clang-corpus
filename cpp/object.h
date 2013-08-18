/*
    object.h
    $Id: object.h,v 1.4 2002/11/21 07:56:17 prok Exp prok $
*/

#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"
#include "material.h"
#include "color.h"

/* pure virtual base class for a generic geometric object */
class Object {
public:
                                Object() {}
                                Object(const Object &o) {}
    virtual                     ~Object() {}

    virtual Object  *           clone() const = 0;

    virtual bool                NearestIntersection(const Ray &r,
                                                    float *t,
                                                    int *index) const = 0;
    virtual bool                Intersections(const Ray &r,
                                              float **t_list,
                                              int **index_list,
                                              int *count) const = 0;

    virtual Vector3             NormalAtPoint(const Vector3 &P,
                                              int index) const = 0;

    virtual Ray                 ReflectedRay(const Ray &r,
                                             float t, int index) const = 0;
    virtual Ray                 RefractedRay(const Ray &r,
                                             float t,
                                             int index,
                                             float n_i=1.0) const = 0;

    virtual void                SetSurfaceMaterial(const Material &m) = 0;
    virtual const Material  &   SurfaceMaterial() const = 0;
    virtual color_t             ColorAt(const Vector3 &P) const = 0;
    virtual color_t             SpecularColorAt(const Vector3 &P) const = 0;
    virtual color_t             DiffuseColorAt(const Vector3 &P) const = 0;

private:
};

#endif

