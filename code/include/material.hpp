#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <cmath>

class Material {
public:

    explicit Material(const Vector3f &d_color, const Vector3f &s_color = Vector3f::ZERO, float s = 0) :
            diffuseColor(d_color), specularColor(s_color), shininess(s) {

    }

    virtual ~Material() = default;

    virtual Vector3f getDiffuseColor() const {
        return diffuseColor;
    }
    
    float cla(float a){
        return((a>0)?a:0);
    }

    Vector3f Shade(const Ray &ray, const Hit &hit,
                   const Vector3f &dirToLight, const Vector3f &lightColor) {
        Vector3f shaded = Vector3f::ZERO;
        Vector3f R=2*Vector3f::dot(hit.getNormal(),dirToLight.normalized())*hit.getNormal()-dirToLight.normalized();
        shaded+=diffuseColor*cla(Vector3f::dot(dirToLight.normalized(),hit.getNormal()))
        +specularColor*std::pow(cla(Vector3f::dot(-ray.getDirection().normalized(),R)),shininess);
        shaded=shaded*lightColor;
        return shaded;
    }

protected:
    Vector3f diffuseColor;
    Vector3f specularColor;
    float shininess;
};


#endif // MATERIAL_H
