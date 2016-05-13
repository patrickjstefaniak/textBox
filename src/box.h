//
//  boxes.h
//  textBoxes
//
//  Created by Patrick Stefaniak on 5/11/16.
//
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#pragma once

class boxes {
public:
    boxes () {}
    boxes (float x, float y, string title, string mainSub, string pageSub, string pageBody, Color c, Color f);
    
    void drawBoxes();
    void mouseIn(vec2 mPos);
    bool isMIn(vec2 mPos);
    void moveBoxOut();
    void moveBoxIn();
    
    float               bwid, bhei, yPos, sX, origSY, origX;
    Anim<float>         xPos, sY, moreY, moreA;
    Color               bCol, fCol;
    string              title, mainSub, pageSub, pageBody;
    gl::TextureFontRef  bfont, sfont, moreFont, pageSubFont;
    bool                isIn;
};