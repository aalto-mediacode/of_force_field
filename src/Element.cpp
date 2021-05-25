#include "Element.hpp"

void Element::setup(glm::vec2 originV) {
    posV=originV;
    velV={ofRandom(-1,1),ofRandom(-1,1)};
    accelV={ofRandom(-1,1),ofRandom(-0.01,0.01)};
}

void Element::update() {
    //velV+=accelV;
    posV+=velV;
    if(posV.x>ofGetWidth()-5 || posV.x<5){
        velV.x*=-1;
        accelV.x*=-1;
    }
}

void Element::draw() {
    ofFill();
    ofDrawRectangle(posV, 4, 4);
    ofDrawRectangle(posV.x-4,posV.y-4, 4, 4);
    ofDrawRectangle(posV.x+4,posV.y-4, 4, 4);
    ofDrawRectangle(posV.x,posV.y-8, 4, 4);

//    ofDrawRectangle(posV, 8, 8);
//    ofDrawRectangle(posV.x-8,posV.y-8, 8, 8);
//    ofDrawRectangle(posV.x-16,posV.y-16, 8, 8);
//    ofDrawRectangle(posV.x+8,posV.y-8, 8, 8);
//    ofDrawRectangle(posV.x+16,posV.y-16, 8, 8);
//    ofDrawRectangle(posV.x+8,posV.y+8, 8, 8);
//    ofDrawRectangle(posV.x+16,posV.y+16, 8, 8);
//    ofDrawRectangle(posV.x-8,posV.y+8, 8, 8);
//    ofDrawRectangle(posV.x-16,posV.y+16, 8, 8);

    
}
