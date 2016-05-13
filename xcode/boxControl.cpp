//
//  boxControl.cpp
//  textBoxes
//
//  Created by Patrick Stefaniak on 5/13/16.
//
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "boxes.h"
#include "cinder/Timeline.h"
#include "boxControl.h"
#include "cinder/Log.h"


using namespace ci;
using namespace ci::app;
using namespace std;

#define LOG_EXCEPTION( exc )	{ CI_LOG_E( "exception caught: " << System::demangleTypeName( typeid( exc ).name() ) << ", what: " << exc.what() ); }

void boxControl::loadBoxes(){
    
    try {
        jsonT = JsonTree( app::loadAsset( "config.json"));
        vBoxes.clear();
        for( const auto &b : jsonT["boxes"]){
            string t = b["title"].getValue();
            string s = b["mainSub"].getValue();
            string ps = b["pageSub"].getValue();
            string pb = b["pageBody"].getValue();
            boxes cBox = boxes(t , s , ps, pb);
            vBoxes.push_back(cBox);
            
            
        }
        numBoxes = vBoxes.size();
        placeBoxes();
        
        //whereAreBoxes();
        //just assuming 4, to test json
        
        
    }
    catch(Exception &exc) {
        LOG_EXCEPTION( exc);
    }
}

void boxControl::placeBoxes(){
    int i = 0;
    for(boxes &b: vBoxes){
        b.bwid = getWindowWidth()/2;
        b.bhei = getWindowHeight()/2;
        b.xPos = (i % 2) * (getWindowWidth() / 2);
        b.yPos = floor(i / 2) * (getWindowHeight() / 2);
        b.origSY = b.sY;
        b.origX = b.xPos;
        b.bCol = Color(i/4.0, 1, 1);
        b.fCol = Color(.1,.1,.1);
        i ++;
    }
}

void boxControl::moveBoxesIn(){
    for(boxes &b: vBoxes){
        b.moveBoxIn();
    }
}

void boxControl::moveBoxesOut(){
    for(boxes &b: vBoxes){
        b.moveBoxOut();
    }
}

void boxControl::drawBoxes(){
    for(boxes &b: vBoxes){
        b.drawBox();
    }
}

void boxControl::mouseIn(vec2 mp){
    for(boxes &b: vBoxes){
        b.mouseIn(mp);
    }
}

boxes boxControl::whichBox(vec2 mp){
    for(boxes &b: vBoxes){
        if(b.isIn){
            return b;
        }
    }
    return vBoxes.back();
}

void boxControl::whereAreBoxes(){
    for(boxes &b: vBoxes){
        cout << b.title << "  xpos: " << b.xPos << "  ypos: " << b.yPos << "  \n";
    }
}