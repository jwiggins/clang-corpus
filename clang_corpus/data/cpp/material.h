/*
    material.h
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdlib.h>
#include <string.h>
#include "color.h"

class Material {
public:
                     Material();
                     Material(const Material &m);
                     ~Material() { if (tex) free(tex); }

    Material &       operator=(const Material &m);

    void             SetTexture(unsigned char *data, int w, int h, int size);
    color_t          GetTexelColor(float u, float v) const;

    void             SetIndexOfRefraction(float n) { nRefract = n; }
    float            IndexOfRefraction() const { return nRefract; }

    void             SetColor(const color_t &c) { bColor = c; }
    color_t          Color() const { return bColor; }

    void             SetSpecularColor(const color_t &c) { sColor = c; }
    color_t          SpecularColor() const { return sColor; }

    void             SetDiffuseColor(const color_t &c) { dColor = c; }
    color_t          DiffuseColor() const { return dColor; }

    void             SetShininess(float s) { shiny = s; }
    float            Shininess() const { return shiny; }

    void             SetReflectivity(float r) { reflectivity = r; }
    float            Reflectivity() const { return reflectivity; }

    void             SetRefractivity(float r) { refractivity = r; }
    float            Refractivity() const { return refractivity; }

    void             SetTransparency(float t) { transparency = t; }
    float            Transparency() const { return transparency; }

private:

    float            nRefract, shiny;
    float            reflectivity, refractivity, transparency;
    color_t          bColor,sColor,dColor;
    int              tWidth, tHeight, tSize;
    unsigned char    *tex;
};

#endif
