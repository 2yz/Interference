#include "AppDelegate.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "ConfigUtil.h"

USING_NS_CC;

AppDelegate::AppDelegate() 
{
	initConfigXML();
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
		glview = GLViewImpl::createWithRect("Interference", Rect(0, 0, 1280, 720));
		director->setOpenGLView(glview);
	}
	// 960 * 640
	director->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	// director->setAnimationInterval(1.0 / 60);
	
	// Initial ConfigUtil
	ConfigUtil::visibleSize = Director::getInstance()->getVisibleSize();
	ConfigUtil::visibleOrigin = Director::getInstance()->getVisibleOrigin();
	ConfigUtil::visibleWidth = ConfigUtil::visibleOrigin.x + ConfigUtil::visibleSize.width;
	ConfigUtil::visibleHeight = ConfigUtil::visibleOrigin.y + ConfigUtil::visibleSize.height;

	FileUtils::getInstance()->addSearchPath("res");
	
	// 读取纹理贴度集合
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(UserDefault::getInstance()->getStringForKey("textureFileName"));

	//读取爆炸动画帧并存入AnimationCache
	Vector<SpriteFrame*> explosionAnimationVector;
	for (int i = 0; i < 9; i++)
	{
		char animitionFileName[32] = { 0 };
		sprintf(animitionFileName, "explosion%02d.png", i + 1);
		auto fm = SpriteFrameCache::getInstance()->getSpriteFrameByName(animitionFileName);
		explosionAnimationVector.pushBack(fm);
	}
	auto explosionAnimation = Animation::createWithSpriteFrames(explosionAnimationVector, 0.5f / 9.0f, 1);
	AnimationCache::getInstance()->addAnimation(explosionAnimation, "explosion");

	// create a scene. it's an autorelease object
	auto scene = GameScene::create();
	// auto scene = HelloWorld::createScene();

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

void AppDelegate::initConfigXML()
{
	UserDefault::getInstance()->setStringForKey("textureFileName", "texture.plist");
	UserDefault::getInstance()->setFloatForKey("intervalOfAddBullet", 0.2f);
	//UserDefault::getInstance()->setFloatForKey("intervalOfAddCloud",20.0f);
	UserDefault::getInstance()->setFloatForKey("intervalOfAddEnemy", 0.5f);
	UserDefault::getInstance()->setFloatForKey("intervalOfAddEnemyBullet", 0.2f);
	UserDefault::getInstance()->setIntegerForKey("damageOfInitBullet", 100);
	UserDefault::getInstance()->setIntegerForKey("damageOfDeltaWhenLevelUp", 50);
	UserDefault::getInstance()->setIntegerForKey("damageOfBigBomb", 400);
	UserDefault::getInstance()->setFloatForKey("probabilityOfBaseEnemyAppear", 0.4f);
	UserDefault::getInstance()->setFloatForKey("probabilityOfDeltaEnemyAppear", 0.007f);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy1", 200);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy2", 400);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy3", 400);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss", 18000);
	//UserDefault::getInstance()->setIntegerForKey("FlytimeOfCloud",35);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfEnemy1", 10);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfEnemy2", 10);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfEnemy3", 5);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfEnemyBossAppear", 7);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfGiftLevelUp", 12);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfGiftBigBomb", 12);
	UserDefault::getInstance()->setFloatForKey("BackgroundScorllSpeed", 0.5);
}