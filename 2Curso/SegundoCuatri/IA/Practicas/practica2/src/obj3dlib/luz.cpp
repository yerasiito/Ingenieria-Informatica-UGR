#include"obj3dlib/luz.hpp"
#include <cmath>

void Luz::draw(){
    if(encendida==true){
        GLfloat posL[4] = {10.0,10.0,0.0,10.0};
        GLfloat ambi[4] = {0.3,0.3,0.3,0.3};
        GLfloat diff[4] = {0.3,0.3,0.3,0.3};
        GLfloat spec[4] = {0.3,0.3,0.3,0.3};
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
        glLightfv(nLuz,GL_POSITION,posL);
        glLightfv(nLuz,GL_AMBIENT,ambi);
        glLightfv(nLuz,GL_DIFFUSE,diff);
        glLightfv(nLuz,GL_SPECULAR,spec);
        glEnable(nLuz);
    }
    else{
        glDisable(nLuz);
    }
}
