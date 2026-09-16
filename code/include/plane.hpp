#ifndef PLANE_H
#define PLANE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

class Plane : public Object3D {
public:
    Plane() {}

    Plane(const Vector3f &normal, float d, Material *m) : normal(normal),d(d),Object3D(m) {}

    ~Plane() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        if(Vector3f::dot(normal,r.getDirection())==0){
            return false;
        }
        float t=-(-d+Vector3f::dot(normal,r.getOrigin()))/(Vector3f::dot(normal,r.getDirection()));
        if(t<tmin){
            return false;
        }
        if(t>=h.getT()){
            return false;
        }
        Vector3f n=normal.normalized();
        n=(Vector3f::dot(n,r.getDirection())<0)?n:-n;
        h.set(t,material,n);
        return true;
    }

protected:
    Vector3f normal;
    float d;

};

#endif //PLANE_H
		

