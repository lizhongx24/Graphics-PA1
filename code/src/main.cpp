#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "scene_parser.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "group.hpp"
#include "light.hpp"

#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    for (int argNum = 1; argNum < argc; ++argNum) {
        std::cout << "Argument " << argNum << " is: " << argv[argNum] << std::endl;
    }

    if (argc != 3) {
        cout << "Usage: ./bin/PA1 <input scene file> <output bmp file>" << endl;
        return 1;
    }
    string inputFile = argv[1];
    string outputFile = argv[2]; 
    SceneParser sceneParser(inputFile.c_str());
    Image img(sceneParser.getCamera()->getWidth(),sceneParser.getCamera()->getHeight());
    for(int x=0;x<sceneParser.getCamera()->getWidth();x++){
        for(int y=0;y<sceneParser.getCamera()->getHeight();y++){
            Ray camRay=sceneParser.getCamera()->generateRay(Vector2f(x,y));
            Group* baseGroup=sceneParser.getGroup();
            Hit hit;
            bool isIntersect =sceneParser.getGroup()->intersect(camRay,hit,0);
            if(isIntersect){
                Vector3f finalColor= Vector3f::ZERO;
                for(int li=0;li<sceneParser.getNumLights();++li){
                    Light* light=sceneParser.getLight(li);
                    Vector3f L,lightColor;
                    light->getIllumination(camRay.pointAtParameter(hit.getT()),L,lightColor);
                    finalColor+=hit.getMaterial()->Shade(camRay,hit,L,lightColor);
                }
                img.SetPixel(x,y,finalColor);
            }
            else{
                img.SetPixel(x,y,sceneParser.getBackgroundColor());
            }
        }
    }
    img.SaveImage(outputFile.c_str());
    cout << "Hello! Computer Graphics!" << endl;
    return 0;
}

