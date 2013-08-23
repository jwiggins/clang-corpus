/*
    csg_object.h
    $Id: csg_object.h,v 1.1 2002/11/21 07:55:22 prok Exp prok $
*/

#ifndef CSG_OBJECT_H
#define CSG_OBJECT_H

#include <math.h>
#include "sphere.h"
#include "object.h"

enum csg_op {
    CSG_INTERSECT = 0,
    CSG_DIFFERENCE
};

class CSGObj : public Object {
public:
                                CSGObj();
                                CSGObj(const Sphere &s1,
                                       const Sphere &s2, csg_op op);
                                CSGObj(const CSGObj &c);
    virtual                     ~CSGObj() {}

    virtual Object  *           clone() const { return (new CSGObj(*this)); }

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
                                             float t,
                                             int index) const;
    virtual Ray                 RefractedRay(const Ray &r,
                                             float t,
                                             int index,
                                             float n_i=1.0) const;

    virtual void                SetSurfaceMaterial(const Material &m) { mat = m; }
    virtual const Material  &   SurfaceMaterial() const { return mat; }
    virtual color_t             ColorAt(const Vector3 &P) const;
    virtual color_t             SpecularColorAt(const Vector3 &P) const;
    virtual color_t             DiffuseColorAt(const Vector3 &P) const;

private:
    Material                    mat;
    Sphere                      A,B;
    csg_op                      oper;
};

#endif

