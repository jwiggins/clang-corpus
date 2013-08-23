/*
    sphere.h
    $Id: sphere.h,v 1.4 2002/11/21 07:57:40 prok Exp prok $
*/

#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include "object.h"

class Sphere : public Object {
public:
                                Sphere();
                                Sphere(const Vector3 &c, float r);
                                Sphere(const Sphere &s);
    virtual                     ~Sphere() {}

    virtual Object  *           clone() const { return (new Sphere(*this)); }

    virtual bool                NearestIntersection(const Ray &r,
                                                    float *t,
                                                    int *index) const;
    virtual bool                Intersections(const Ray &r,
                                              float **t_list,
                                              int **index_list,
                                              int *count) const;

    virtual Vector3             NormalAtPoint(const Vector3 &P,
                                              int index) const;

    virtual Ray                 ReflectedRay(const Ray &r,
                                             float t, int index) const;
    virtual Ray                 RefractedRay(const Ray &r,
                                             float t,
                                             int index,
                                             float n_i=1.0) const;

    virtual void                SetSurfaceMaterial(const Material &m) { mat = m; }
    virtual const Material  &   SurfaceMaterial() const { return mat; }
    virtual color_t             ColorAt(const Vector3 &P) const;
    virtual color_t             SpecularColorAt(const Vector3 &P) const;
    virtual color_t             DiffuseColorAt(const Vector3 &P) const;

    // needed for CSG support
    const Vector3   &           Center() const { return center; }
    float                       Radius() const { return radius; }

private:

    Material                    mat;

    Vector3                     center;
    float                       radius;
};

#endif

