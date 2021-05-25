#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mySound.load("Bio-Unit_Network.mp3");
    mySound.setLoop(true);
    mySound.play();
    
    ofHideCursor();
    ofBackground(0);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetCircleResolution(80);
    
    grid=4.5;
    add={1,1};
    butxy.set(ofGetWidth()*0.25,ofGetHeight()/2-40,190,60);
    butxyz.set(ofGetWidth()*0.5,ofGetHeight()/2-40,190,60);
    butstr.set(ofGetWidth()*0.75,ofGetHeight()/2-40,190,60);
    
    for(float x=grid*-1; x<=grid; x+=0.07){
        for(float y=grid*-1; y<=grid; y+=0.07){
            glm::vec2 v = {x+ofNoise(1)*0.003,y+ofNoise(1)*0.003};
            points.push_back(v);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    nBands=512;
    mySpectrum=ofSoundGetSpectrum(nBands);
    width=ofGetWidth()/nBands;
    for(int i=0;i<nBands;i++){
        posX=ofMap(i,0,nBands,0,ofGetWidth());
        sizeF=ofMap(mySpectrum[i],0,nBands,2,20);
        height=mySpectrum[i]*ofGetHeight();
     //   ofDrawRectangle(posX,ofGetHeight()/2, width, height);
    }

    
    //XYZ
    if(bXyzIsClicked){
        ofSetLineWidth(0.8);
        ofBackground(0);
    
        if (points.empty()) {
            bXyzIsClicked = false;
            
        }
         
        int point_idx=0;
        for(int p=0; p<points.size(); p++){
            xx=ofMap(points[p].x, -6.5, 6.5, 0, ofGetWidth());
            yy=ofMap(points[p].y, -6.5, 6.5, 0, ofGetHeight());
            zz=ofMap(points[p].y, -6.5, 6.5, 0, ofGetHeight());
            
            
            float blue=ofMap(point_idx,0,10000,90,255);
            float red=ofMap(ofGetMouseX(),0,ofGetWidth(),0,50);
            ofFill();
            ofSetColor(red,blue,255);
            ofDrawRectangle(xx,yy,zz,sizeF,0.5);
            ofDrawRectangle(xx,yy,zz,0.5,sizeF);
            
            //vector field calculations
            float n = TWO_PI * 10 * ofNoise(points[p].x/divi, points[p].y/divi);
            glm::vec2 v = {cos(n),sin(n)};
            
            float speedX = vector_scale * v.x;
            float speedY = vector_scale * v.y;
            
            if(xx>ofGetWidth()-30||xx<30){
                points.erase(points.begin()+p);
            }
            if(yy<30||yy>ofGetHeight()-30){
                points.erase(points.begin()+p);
            }
           
            points[p].x += speedX;
            points[p].y += speedY;
            point_idx++;
        }
        
        time+=0.02;
        
        //XY
    } else if (bXyIsClicked){
        
        ofSetLineWidth(0.8);
        ofBackground(0);

            if (points.empty()) {
                bXyIsClicked = false;}
            
            int point_idx=0;
            for(int p=0; p<points.size(); p++){
                xx=ofMap(points[p].x, -6.5, 6.5, 0, ofGetWidth());
                yy=ofMap(points[p].y, -6.5, 6.5, 0, ofGetHeight());

                float blue=ofMap(point_idx,0,10000,100,220);
                float red=ofMap(ofGetMouseX(),0,ofGetWidth(),0,50);
                ofNoFill();
                ofSetColor(red,blue,255,200);
                ofDrawCircle(xx,yy,size);
                ofFill();
                ofDrawCircle(xx,yy,0.7);
                
                //vector field calculations
                float n = TWO_PI * 3 * ofNoise(points[p].x/divi, points[p].y/divi);
                glm::vec2 v = {cos(n),sin(n)};
                
                float speedX = vector_scale * v.x;
                float speedY = vector_scale * v.y;
                
                if(xx<30||xx>ofGetWidth()-30){
                    points.erase(points.begin()+p);
                }
                if(yy<30||yy>ofGetHeight()-30){
                    points.erase(points.begin()+p);
                    cout << speedY << endl;
                }
                
                points[p].x += speedX;
                points[p].y += speedY;
                point_idx++;
            }
            time+=0.02;
        
        //strings
    }else if(bstrIsClicked){
            ofSetLineWidth(0.8);
            ofBackground(0);
            if (points.empty()) {
                bstrIsClicked = false;
            }
        int point_idx=0;
            for(int p=0; p<points.size(); p++){
                xx=ofMap(points[p].x, -6.5, 6.5, 0, ofGetWidth());
                yy=ofMap(points[p].y, -6.5, 6.5, 0, ofGetHeight());
                zz=ofMap(points[p].y, -6.5, 6.5, 0, ofGetHeight());
                
                ofPushMatrix();
                ofTranslate(xx, yy);
                ofRotateXDeg(point_idx/100);
                ofSetColor(255);
                ofFill();
                ofDrawRectangle(xx,yy,zz,8,1);
                ofDrawRectangle(xx,yy,zz,1,8);
                ofPopMatrix();
                
                //vector field calculations
                float n = TWO_PI * 4 * ofNoise(points[p].x/10, points[p].y/10);
                glm::vec2 v = {cos(n),sin(n)};
                float speedX = vector_scale/2 * v.x;
                float speedY = vector_scale/2 * v.y;
                
                if(xx>ofGetWidth()-30||xx<30){
                    points.erase(points.begin()+p);
                }
                if(yy<30||yy>ofGetHeight()-30){
                    points.erase(points.begin()+p);
                }
                points[p].x += speedX;
                points[p].y += speedY;
                point_idx++;
            }
            
            time+=0.02;
        
        //UI
    } else {
        ofNoFill();
        ofSetLineWidth(1);
        ofSetColor(ofColor::white);
        ofDrawRectangle(butxyz);
        ofDrawRectangle(butxy);
        ofDrawRectangle(butstr);
        ofDrawBitmapString("XYZ", ofGetWidth()*0.25-5,ofGetHeight()/2-37);
        ofDrawBitmapString("XY", ofGetWidth()*0.5-10,ofGetHeight()/2-37);
        ofDrawBitmapString("strings", ofGetWidth()*0.75-25,ofGetHeight()/2-37);
        ofDrawBitmapString("R for reset", ofGetWidth()/2-40,ofGetHeight()-200);
    }
    
    ofSetColor(ofColor::white);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 15);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='r'){
        points.clear();
        ofApp::setup();
        divi+=ofRandom(-1,10);
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    points.push_back(add);
    vector_scale=ofMap(ofGetMouseX(),0,ofGetWidth(),-0.03,0.03);
    divi=ofMap(ofGetMouseY(),0,ofGetHeight(),2,30);
    size=ofMap(ofGetMouseY(),0,ofGetHeight(),5,23);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bXyzIsClicked = butxyz.inside(x+95,y+30);
    bXyIsClicked = butxy.inside(x+95,y+30);
    bstrIsClicked = butstr.inside(x+95,y+30);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
