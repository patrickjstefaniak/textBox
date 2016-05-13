//
//  boxes.cpp
//  textBoxes
//
//  Created by Patrick Stefaniak on 5/11/16.
//
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "boxes.h"
#include "cinder/Timeline.h"


using namespace ci;
using namespace ci::app;
using namespace std;

boxes::boxes(float x, float y, string t, string mS, string pS, string pB, Color c, Color f ){
    xPos = x;
    yPos = y;
    title = t;
    bCol = c;
    fCol = f;
    origSY = sY;
    origX = xPos;
    mainSub = mS;
    pageSub = pS;
    pageBody = pB;
    bwid = getWindowWidth() / 2;
    bhei = getWindowHeight() / 2;
    sY = yPos + (bhei / 2);
    origSY = sY;
    bfont = gl::TextureFont::create( Font("Bodoni 72", 26));
    sfont = gl::TextureFont::create( Font("Bodoni 72", 15));
    moreFont = gl::TextureFont::create( Font("Arial Bold", 11));
    isIn = false;
    moreY = 50;
    moreA = 0;
}

void boxes::drawBoxes(){
    gl::color(bCol);
    gl::drawSolidRect(Rectf(xPos, yPos, xPos + bwid, yPos + bhei));
    
    gl::color(fCol);
    
    bfont->drawString(title, vec2(xPos + (bwid / 2) - (bfont->measureString(title).x / 2) , sY));
    sfont->drawString(pageSub,  vec2(xPos + (bwid / 2) - (sfont->measureString(pageSub).x / 2) , sY + 20));
    
    gl::color(ColorA(fCol.r, fCol.g, fCol.b, moreA));
    
    float mH = 31;
    float mW = 30;
    float rad = 30;
    Path2d more;
    more.moveTo(                                                          vec2(xPos + (bwid / 2) - mW,   sY + moreY));
    more.lineTo(                                                          vec2(xPos + (bwid / 2) + mW,   sY + moreY));
    more.curveTo(vec2(xPos + (bwid / 2) + (mW + rad), sY + moreY),
                 vec2(xPos + (bwid / 2) + (mW + rad), sY + moreY + mH),   vec2(xPos + (bwid / 2) + mW,   sY + moreY + mH));
    more.lineTo(                                                          vec2(xPos + (bwid / 2) - mW,   sY + moreY + mH));
    more.curveTo(vec2(xPos + (bwid / 2) - (mW + rad), sY + moreY + mH),
                 vec2(xPos + (bwid / 2) - (mW + rad), sY + moreY),        vec2(xPos + (bwid / 2) - mW,   sY + moreY) );
    more.close();
    gl::draw(more);
    moreFont->drawString("VIEW MORE", vec2(xPos + (bwid / 2) - (moreFont->measureString("VIEW MORE").x / 2), sY + moreY + (mH / 2) + (moreFont->measureString("VIEW MORE").y/ 3)));
}

void boxes::mouseIn(vec2 mPos){
    bool curState = isMIn( mPos);
    if(!isIn){
        if(curState){
            isIn = true;
            //animate text up a little, adjust alpha and position of 'read more'
            timeline().apply( &sY, origSY - 20.0f, 0.3f, EaseOutQuad());
            timeline().apply(&moreA, 1.0f, 0.3f, EaseOutQuad());
            timeline().apply(&moreY, 40.0f, 0.3f, EaseOutQuad());
        }
    }else{
        if(!curState){
            isIn = false;
            //animate text down a little
            timeline().apply( &sY, origSY , 0.3f, EaseOutQuad());
            timeline().apply(&moreA, 0.0f, 0.3f, EaseOutQuad());
            timeline().apply(&moreY, 50.0f, 0.3f, EaseOutQuad());
        }
    }
}

//move boxes to side of screen

void boxes::moveBoxOut(){
    float xGoal;
    if(xPos < getWindowWidth()/2){
        xGoal = bwid * 9 / (-13);
    }else{
        xGoal = getWindowWidth() / 2 + (bwid * 9 / 13);
    }
    timeline().apply(&xPos, xGoal, 0.5f, EaseOutQuad());
}

void boxes::moveBoxIn(){
    timeline().apply(&xPos, origX, 0.5f, EaseOutQuad() );
}

//is the mouse inside the box
bool boxes::isMIn( vec2 mPos){
    if(xPos < mPos.x &&
       yPos < mPos.y &&
       xPos + bwid > mPos.x &&
       yPos + bhei > mPos.y){
        return true;
    }else{
        return false;
    }
}