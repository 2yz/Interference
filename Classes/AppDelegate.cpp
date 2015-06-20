#include "AppDelegate.h"
#include "BattleScene.h"
#include "LogoScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate()
{

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() 
{
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::createWithRect(PROGRAM_NAME, Rect(0, 0, 1280, 720));
		director->setOpenGLView(glview);
	}
	director->getOpenGLView()->setCursorVisible(false);
	// 960 * 640
	director->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	// director->setAnimationInterval(1.0 / 60);
	
	// Initial ConfigUtil
	config::visible_size = Director::getInstance()->getVisibleSize();
	config::visible_origin = Director::getInstance()->getVisibleOrigin();
	config::visible_width = config::visible_origin.x + config::visible_size.width;
	config::visible_height = config::visible_origin.y + config::visible_size.height;

	FileUtils::getInstance()->addSearchPath("res");
	
	srand(time(nullptr));

	// create a scene. it's an autorelease object
	auto scene = LogoScene::create();
	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() 
{
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() 
{
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
