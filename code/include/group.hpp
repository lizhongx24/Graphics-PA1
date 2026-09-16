#ifndef GROUP_H
#define GROUP_H


#include "object3d.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <vector>


class Group : public Object3D {

public:

    Group() {}

    explicit Group (int num_objects) {
        Objgroup.reserve(num_objects);
    }

    ~Group() override {
        Objgroup.clear();
    }

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        bool flag=false;
        for(int i=0;i<Objgroup.size();i++){
            if(Objgroup[i]->intersect(r,h,tmin)){
                flag=true;
            }
        }
        return flag;
    }

    void addObject(int index, Object3D *obj) {
        Objgroup.insert(Objgroup.begin()+index,obj);
    }

    int getGroupSize() {
        return Objgroup.size();
    }

private:
    std::vector<Object3D*> Objgroup;

};

#endif
	
