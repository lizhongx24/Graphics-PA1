#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// TODO: implement this class and add more fields as necessary,
class Triangle: public Object3D {

public:
	Triangle() = delete;
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m) : a(a),b(b),c(c),Object3D(m) {
	}

	bool intersect( const Ray& ray,  Hit& hit , float tmin) override {
		Vector3f E1=a-b;
		Vector3f E2=a-c;
		Vector3f S=a-ray.getOrigin();
		Matrix3f D=Matrix3f(ray.getDirection(),E1,E2);
		Matrix3f A=Matrix3f(S,E1,E2);
		Matrix3f B=Matrix3f(ray.getDirection(),S,E2);
		Matrix3f C=Matrix3f(ray.getDirection(),E1,S);
		float d=D.determinant();
		if(d==0){
			return false;
		}
		float t=A.determinant()/d;
		float ta=B.determinant()/d;
		float tb=C.determinant()/d;
		if(t>0 && ta>=0 && ta<=1 && tb>=0 && tb<=1 && ta+tb<=1){
			if(t<tmin){
				return false;
			}
			if(t>=hit.getT()){
				return false;
			}
			Vector3f n=Vector3f::cross(E1,E2).normalized();
			n=(Vector3f::dot(n,ray.getDirection())<0)?n:-n;
			hit.set(t,material,n);
			return true;
		}
        return false;
	}
	Vector3f normal;
	Vector3f vertices[3];
protected:
	Vector3f a;
	Vector3f b;
	Vector3f c;
};

#endif //TRIANGLE_H
