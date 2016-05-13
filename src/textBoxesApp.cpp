#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "boxes.h"
#include "cinder/Timeline.h"
#include "boxControl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

bool        hold;
boxControl  boxC;

class textBoxesApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void mouseMove( MouseEvent event ) override;
    
    
    float               pageYdip;
    bool                isMain, isExit;
    
    Anim<float>         shadowA, pageTopY, pageBotY, pageX, pageShadow,
                        xBoxA, pTitleA, pSubA, pBodyA, pTitleY, pSubY, pBodyY;
    
    string              curTitle, curSub, curBody;
    gl::TextureFontRef  pTitleFont, pSubFont, pBodyFont;
    gl::TextureRef      pBodyT;
    Color               pTitleC, pSubC, pBodyC;
    TextBox             pBodyBox;
    Rectf               exit;
    
};

void textBoxesApp::setup()
{
    setWindowSize(800, 600);
    isMain = true;
    boxC.loadBoxes();
    
    //page info
    shadowA = 0;
    pageYdip = 50;
    pageTopY = 50;
    pageBotY = 100;
    pageX = getWindowWidth()/2;
    pageShadow = .3;
    xBoxA = pTitleA = pSubA = pBodyA = 0;
    pBodyFont = gl::TextureFont::create( Font("Bodoni 72", 15));
    pSubFont = gl::TextureFont::create( Font("Bodoni 72", 17));
    pTitleFont = gl::TextureFont::create( Font("Bodoni 72", 25));
    pBodyC = Color(.15,.15,.15);
    pSubC = Color(.2, .15, .2);
    pTitleC = Color(.1, .1, .1);
    pTitleY = 60;
    pSubY = 90;
    pBodyY = 120;
    pBodyBox = TextBox().alignment(TextBox::LEFT).font(pBodyFont->getFont()).size(vec2(getWindowWidth() * 9 / 13 - 50,getWindowHeight() - 100));
    
    //disables clicking during transition between main and page
    hold = false;

}

void changeHold(){
    hold = !hold;
}

void moveBoxesBack(){
    boxC.moveBoxesIn();
}

void textBoxesApp::mouseDown( MouseEvent event )
{
    if(!hold){
        //boxC.whereAreBoxes();
    //if clicked on 'main screen' - no page showing
    if(isMain){
        
        hold = true;
        isMain = false;
        
        boxC.moveBoxesOut();
        timeline().apply(&shadowA, 0.5f, 0.5f, EaseOutQuad());
        timeline().apply(&pageX, getWindowWidth()/2 - (getWindowWidth() * 9.0f / 26), 0.5f, EaseOutQuad());
        timeline().apply(&pageTopY, 0.0f, 0.5f, EaseOutQuad());
        timeline().apply(&pageShadow, 0.9f, 0.5f, EaseOutQuad());
        
        timeline().apply(&xBoxA, 1.0f, 0.2f, EaseOutQuad()).appendTo(&pageShadow);
        timeline().apply(&pTitleA, 1.0f, 0.2f, EaseOutQuad()).appendTo(&xBoxA);
        timeline().apply(&pTitleY, 50.0f, 0.2f, EaseOutQuad()).appendTo(&xBoxA);
        timeline().apply(&pSubA, 1.0f, 0.2f, EaseOutQuad()).appendTo(&pTitleA);
        timeline().apply(&pSubY, 80.0f, 0.2f, EaseOutQuad()).appendTo(&pTitleA);
        timeline().apply(&pBodyA, 1.0f, 0.2f, EaseOutQuad()).appendTo(&pSubA);
        timeline().apply(&pBodyY, 110.0f, 0.2f, EaseOutQuad()).appendTo(&pSubA).finishFn(*changeHold);
        boxes cur = boxC.whichBox(event.getPos());
        
        curBody = cur.pageBody;
        curTitle = cur.title;
        curSub = cur.pageSub;
        
    }else{
        if(exit.contains(event.getPos())){
            hold = true;
            isMain = true;
            timeline().apply(&pBodyA, 0.0f, 0.2f, EaseOutQuad());
            timeline().apply(&pBodyY, 120.0f, 0.2f, EaseOutQuad());
            timeline().apply(&xBoxA, 0.0f, 0.2f, EaseOutQuad());
            timeline().apply(&pSubA, 0.0f, 0.2f, EaseOutQuad()).appendTo(&pBodyA);
            timeline().apply(&pSubY, 90.0f, 0.2f, EaseOutQuad()).appendTo(&pBodyA);
            timeline().apply(&pTitleA, 0.0f, 0.2f, EaseOutQuad()).appendTo(&pSubA);
            timeline().apply(&pTitleY, 60.0f, 0.2f, EaseOutQuad()).appendTo(&pSubA).finishFn(*moveBoxesBack);
        
            timeline().apply(&shadowA, 0.0f, 0.5f, EaseOutQuad()).appendTo(&pTitleA);
            timeline().apply(&pageX, getWindowWidth()/2 * 1.0f, 0.5f, EaseOutQuad()).appendTo(&pTitleA);
            timeline().apply(&pageTopY, 50.0f, 0.5f, EaseOutQuad()).appendTo(&pTitleA);
            timeline().apply(&pageShadow, 0.6f, 0.5f, EaseOutQuad()).appendTo(&pTitleA).finishFn(*changeHold);
        }
    }
    }
}


void textBoxesApp::mouseMove( MouseEvent event )
{
    if(isMain){
        boxC.mouseIn(event.getPos());
    }else{
        if(exit.contains(event.getPos())){
            isExit = true;
        }
        else{
            isExit = false;
        }
    }
}

void textBoxesApp::update()
{
        exit = Rectf(getWindowWidth() - pageX - 40, 20, getWindowWidth() - pageX - 20, 40);
}

void textBoxesApp::draw()
{
	gl::clear();
    boxC.drawBoxes();
    gl::color(0,0,0,shadowA);
    gl::drawSolidRect(Rectf(0,0,getWindowWidth(), getWindowHeight()));
    

    //draw left side of page
    Path2d mPath ;
    mPath.moveTo( vec2( pageX ,  0));
    mPath.lineTo( vec2( getWindowWidth() / 2,   pageTopY));
    pageBotY = getWindowHeight() - pageTopY;
    mPath.lineTo( vec2( getWindowWidth() / 2,   pageBotY));
    mPath.lineTo( vec2( pageX,  getWindowHeight()));
    mPath.close();
    gl::color(.9, .9, .9);
    gl::drawSolid(mPath);
    
    //right side of page
    mPath.clear();
    mPath.moveTo( vec2( getWindowWidth() - pageX, 0));
    mPath.lineTo( vec2( getWindowWidth()/2, pageTopY));
    mPath.lineTo( vec2( getWindowWidth()/2, pageBotY));
    mPath.lineTo( vec2( getWindowWidth() - pageX, getWindowHeight()));
    mPath.close();
    gl::color(pageShadow, pageShadow, pageShadow);
    gl::drawSolid(mPath);
    
    //draw x
    if(isExit){
        gl::color(.85,.85,.85, xBoxA);
        gl::drawSolidRect(exit);
    }
    gl::color(.12,.12,.12,xBoxA);
    gl::drawLine(vec2(getWindowWidth() - pageX - 40, 20), vec2(getWindowWidth() - pageX - 20, 40));
    gl::drawLine(vec2(getWindowWidth() - pageX - 40, 40), vec2(getWindowWidth() - pageX - 20, 20));
    
    
    //draw text
    gl::color(ColorA(pTitleC.r, pTitleC.g,pTitleC.b, pTitleA));
    pTitleFont->drawString(curTitle, vec2( pageX + 30, pTitleY));
    gl::color(ColorA(pSubC.r, pSubC.g, pSubC.b, pSubA));
    pSubFont->drawString(curSub, vec2(pageX + 30, pSubY));
    
    pBodyBox.text(curBody).setColor(ColorA(pBodyC.r,pBodyC.g,pBodyC.b,pBodyA));
    pBodyT = gl::Texture2d::create(pBodyBox.render());
    gl::pushMatrices();
    gl::translate(vec2(pageX + 30, pBodyY));
    gl::draw(pBodyT);
    gl::popMatrices();
    
    
    
}


CINDER_APP( textBoxesApp, RendererGl( RendererGl::Options().msaa( 4 ) ))
