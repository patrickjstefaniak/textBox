//
//  boxControl.h
//  textBoxes
//
//  Created by Patrick Stefaniak on 5/13/16.
//
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"
#include "boxes.h"
#include "cinder/Json.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#pragma once

class boxControl {
public:
    boxControl () {}
    
    void loadBoxes();
    void drawBoxes();
    void placeBoxes();
    void moveBoxesOut();
    void moveBoxesIn();
    void mouseIn(vec2 mp);
    boxes whichBox(vec2 mp);
    void whereAreBoxes();
    
    int numBoxes;
    ci::JsonTree jsonT;
    std::vector<boxes> vBoxes;
};