#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

class Sphere : public Object3D {
public:
    Sphere() :center(Vector3f(0,0,0)),radius(1),Object3D(){
    }

    Sphere(const Vector3f &center, float radius, Material *material) :center(center),radius(radius),Object3D(material) {
    }

    ~Sphere() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        Vector3f l=center-r.getOrigin();
        float tp=Vector3f::dot(l,r.getDirection());
        float d=std::sqrt(l.length()*l.length()-tp*tp);
        if(l.length()==radius && tp==0){
            return false;
        }
        if(l.length()>radius){
            if(tp<0){
                return false;
            }
            if(d>radius){
                return false;
            }
        }
        float t1=std::sqrt(radius*radius-d*d);
        float t=(l.length()>radius)? tp-t1:tp+t1;
        if(t<tmin){
            return false;
        }
        if(t>=h.getT()){
            return false;
        }
        Vector3f n=r.pointAtParameter(t)-center;
        h.set(t,material,n.normalized());
        return true;
    }

protected:
    Vector3f center;
    float radius;
};


#endif
