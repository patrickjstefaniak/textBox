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
            Color bC = Color(b["boxColorR"].getValue<float>(), b["boxColorG"].getValue<float>(), b["boxColorB"].getValue<float>());
            Color tC = Color(b["textColorR"].getValue<float>(), b["textColorG"].getValue<float>(), b["textColorB"].getValue<float>());
            boxes cBox = boxes(t , s , ps, pb, bC, tC);
            vBoxes.push_back(cBox);
            
            
        }
        numBoxes = vBoxes.size();
        placeBoxes();
        
        //whereAreBoxes();
        
        
    }
    catch(Exception &exc) {
        LOG_EXCEPTION( exc);
    }
}

void boxControl::placeBoxes(){
    int i = 0;
    for(boxes &b: vBoxes){
        b.bwid = getWindowWidth()/2;
        b.xPos = (i % 2) * (getWindowWidth() / 2);
        
        //if there is an even number of boxes
        if(numBoxes % 2 == 0){
            
            //math here is wrong ! only works for 4, not 2 or 6
            
            b.bhei = getWindowHeight() / (numBoxes / 2);
            b.yPos = floor(i / 2) * b.bhei;
            b.sY = b.bhei / 2;
            
        //if there is odd number of boxes
        }else{
            if((i + 1) % 2 == 0){
                b.bhei = getWindowHeight() / ((numBoxes - 1) / 2);
                b.yPos = floor(i / 2) * b.bhei;
                b.sY = b.bhei / 2;
            }else{
                b.bhei = getWindowHeight() / ((numBoxes + 1) / 2);
                b.yPos = floor(i / 2) * b.bhei;
                b.sY = b.bhei / 2;
            }
        }
        //b.bhei = getWindowHeight()/2;
        //b.yPos = floor(i / 2) * (getWindowHeight() / 2);
        b.origSY = b.sY;
        b.origX = b.xPos;
        i ++;
    }
    whereAreBoxes();
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