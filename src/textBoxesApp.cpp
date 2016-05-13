#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "boxes.h"
#include "cinder/Timeline.h"

using namespace ci;
using namespace ci::app;
using namespace std;

boxes box[4];
bool hold;

class textBoxesApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void mouseMove( MouseEvent event ) override;
    
    boxes whichBox( vec2 mPos);
    boxes box1;
    boxes box2;
    boxes box3;
    boxes box4;
    
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
    box1 = boxes(0, 0,
                 "Title 1",
                 "this is box1 mainSub",
                 "this is box1 subtitle",
                 "          Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce molestie et odio efficitur rutrum. Quisque interdum urna ut lacinia tristique. Suspendisse sed risus risus. Fusce consequat dignissim scelerisque. Donec viverra tellus at est posuere pharetra. Praesent hendrerit neque sed fringilla sodales. Curabitur lacus erat, accumsan in dictum nec, tempor nec orci. \n\n         Pellentesque eget pulvinar ligula, et egestas justo. Donec id quam vitae arcu porttitor suscipit. In ac augue et libero facilisis porttitor. Quisque ut diam sit amet mauris efficitur suscipit. Vivamus eget cursus justo. Donec fringilla placerat tempor. Donec et dolor fringilla, rutrum nisi et, rutrum velit. Praesent scelerisque elit id nisi tincidunt, ac malesuada turpis pretium. Proin sollicitudin ex vel augue rhoncus fringilla ut id purus. Fusce nec quam nec dolor convallis hendrerit. Fusce diam tellus, posuere a mauris a, sodales fermentum arcu. Curabitur eget iaculis diam, ut luctus ex. Pellentesque ultricies, diam vitae elementum pretium, diam ante vestibulum justo, id auctor neque metus sit amet lectus.",
                 Color(39 / 255.0, 48 / 255.0, 83 / 255.0) ,
                 Color(.95, .95, .95));
    
    box2 = boxes(getWindowWidth()/2, 0,
                 "Title 2",
                 "this is box1 mainSub",
                 "this is box2 subtitle",
                 "          Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce molestie et odio efficitur rutrum. Quisque interdum urna ut lacinia tristique. Suspendisse sed risus risus. Fusce consequat dignissim scelerisque. Donec viverra tellus at est posuere pharetra. Praesent hendrerit neque sed fringilla sodales. Curabitur lacus erat, accumsan in dictum nec, tempor nec orci. Pellentesque eget pulvinar ligula, et egestas justo. Donec id quam vitae arcu porttitor suscipit. In ac augue et libero facilisis porttitor. Quisque ut diam sit amet mauris efficitur suscipit. Vivamus eget cursus justo. Donec fringilla placerat tempor. Donec et dolor fringilla, rutrum nisi et, rutrum velit. Praesent scelerisque elit id nisi tincidunt, ac malesuada turpis pretium. Proin sollicitudin ex vel augue rhoncus fringilla ut id purus. Fusce nec quam nec dolor convallis hendrerit. Fusce diam tellus, posuere a mauris a, sodales fermentum arcu. Curabitur eget iaculis diam, ut luctus ex. Pellentesque ultricies, diam vitae elementum pretium, diam ante vestibulum justo, id auctor neque metus sit amet lectus.\n\n           Donec sollicitudin lectus nec odio lacinia viverra. Vestibulum sagittis nunc ut ante fermentum eleifend. Proin scelerisque ullamcorper libero, et volutpat tellus pharetra eu. Sed ante velit, tincidunt vel malesuada sed, congue ut felis. Aliquam malesuada interdum metus eu porttitor. Nullam non commodo augue, eu lacinia ante. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Pellentesque quis nisi libero.",
                 Color(98 / 255.0, 72 / 255.0, 131 / 255.0) ,
                 Color(.95, .95, .95));
    
    box3 = boxes(0, getWindowHeight()/2,
                 "Title 3",
                 "this is box1 mainSub",
                 "this is box3 subtitle",
                 "          Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce molestie et odio efficitur rutrum. Quisque interdum urna ut lacinia tristique. Suspendisse sed risus risus. Fusce consequat dignissim scelerisque. Donec viverra tellus at est posuere pharetra. Praesent hendrerit neque sed fringilla sodales. Curabitur lacus erat, accumsan in dictum nec, tempor nec orci. Pellentesque eget pulvinar ligula, et egestas justo. Donec id quam vitae arcu porttitor suscipit. In ac augue et libero facilisis porttitor. Quisque ut diam sit amet mauris efficitur suscipit. Vivamus eget cursus justo. Donec fringilla placerat tempor. Donec et dolor fringilla, rutrum nisi et, rutrum velit. Praesent scelerisque elit id nisi tincidunt, ac malesuada turpis pretium. Proin sollicitudin ex vel augue rhoncus fringilla ut id purus. Fusce nec quam nec dolor convallis hendrerit. Fusce diam tellus, posuere a mauris a, sodales fermentum arcu. Curabitur eget iaculis diam, ut luctus ex. Pellentesque ultricies, diam vitae elementum pretium, diam ante vestibulum justo, id auctor neque metus sit amet lectus.\n\n           Donec suscipit egestas ante, eget condimentum tortor sollicitudin luctus. Pellentesque at mi mi. Quisque lorem sem, scelerisque at tristique sit amet, posuere egestas urna. Duis volutpat diam tortor, aliquet hendrerit libero malesuada fermentum. Mauris sit amet diam iaculis, interdum dui a, varius mauris. Fusce sapien dolor, lobortis sed urna vitae, cursus cursus diam. Phasellus ac facilisis erat. Vivamus sit amet velit non quam congue eleifend. Fusce malesuada pulvinar dolor eget tempus. Etiam consequat metus ac dui luctus, ac suscipit ipsum efficitur. Vivamus eget convallis odio.",
                 Color(236 / 255.0, 238 / 255.0, 236 / 255.0) ,
                 Color(.1, .1, .1));
    
    box4 = boxes(getWindowWidth()/2, getWindowHeight()/2,
                 "Title 4",
                 "this is box1 mainSub",
                 "this is box4 subtitle",
                 "          Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce molestie et odio efficitur rutrum. Quisque interdum urna ut lacinia tristique. Suspendisse sed risus risus. Fusce consequat dignissim scelerisque. Donec viverra tellus at est posuere pharetra. Praesent hendrerit neque sed fringilla sodales. Curabitur lacus erat, accumsan in dictum nec, tempor nec orci. Pellentesque eget pulvinar ligula, et egestas justo. Donec id quam vitae arcu porttitor suscipit. In ac augue et libero facilisis porttitor. Quisque ut diam sit amet mauris efficitur suscipit. Vivamus eget cursus justo. Donec fringilla placerat tempor. Donec et dolor fringilla, rutrum nisi et, rutrum velit. Praesent scelerisque elit id nisi tincidunt, ac malesuada turpis pretium. Proin sollicitudin ex vel augue rhoncus fringilla ut id purus. Fusce nec quam nec dolor convallis hendrerit. Fusce diam tellus, posuere a mauris a, sodales fermentum arcu. Curabitur eget iaculis diam, ut luctus ex. Pellentesque ultricies, diam vitae elementum pretium, diam ante vestibulum justo, id auctor neque metus sit amet lectus.\n\n           Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed ultrices a neque sed volutpat. Fusce massa tortor, mattis sit amet sagittis sit amet, sodales nec justo. Donec mollis erat non felis pellentesque pretium. Fusce congue ante rutrum, luctus lectus non, tristique felis. Nulla lacinia tellus ac ante semper volutpat. Praesent id enim nisi. Fusce ut mollis quam. Cras mollis libero diam, in hendrerit lacus interdum id. Sed feugiat ut quam vitae dignissim. Mauris ut ultrices orci. Vivamus odio lectus, eleifend dignissim iaculis eu, pharetra vitae odio.",
                 Color(102 / 255.0, 200 / 255.0, 140 / 255.0) ,
                 Color(.95, .95, .95));
    
    box[0] = box1;
    box[1] = box2;
    box[2] = box3;
    box[3] = box4;
    isMain = true;
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
    hold = false;

}

void changeHold(){
    hold = !hold;
}

void moveBoxesBack(){
    for(boxes &b: box){
        b.moveBoxIn();
    }
    
}

void textBoxesApp::mouseDown( MouseEvent event )
{
    if(!hold){
    //if clicked on 'main screen' - no page showing
    if(isMain){
        for(boxes &b: box){
            b.moveBoxOut();
        }
        hold = true;
        isMain = false;
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
        boxes cur = whichBox(event.getPos());
        
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
        for(boxes &b: box){
            b.mouseIn(event.getPos());
        }
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
    for(boxes &b: box){
        b.drawBoxes();
    }
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


//returns which box has been clicked
boxes textBoxesApp::whichBox(vec2 mPos){
    for(boxes &b: box){
        if(b.isMIn(mPos)){
            return b;
        }
    }
    return box1;
}

CINDER_APP( textBoxesApp, RendererGl( RendererGl::Options().msaa( 4 ) ))
