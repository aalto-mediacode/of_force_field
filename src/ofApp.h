#pragma once

#include "ofMain.h"
#include "Element.hpp"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    vector <Element> myElement;
    vector <glm::vec2> points;
    float vector_scale=0.003;
    float time=0;

    float xx;
    float yy;
    float zz;
    ofPolyline line;
    glm::vec2 add;
    
    float size;
    float divi;
    float grid;
    
    ofRectangle butxy;
    ofRectangle butxyz;
    ofRectangle butstr;
    bool bXyIsClicked=false;
    bool bXyzIsClicked=false;
    bool bstrIsClicked=false;
    
    ofSoundPlayer mySound;
    float *mySpectrum;
    float width;
    float posX;
    float height;
    float sizeF;
    int nBands;
    
};
