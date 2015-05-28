#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
	// rootNode->getChildByName("")->

    addChild(rootNode);
	
	auto nothing = rootNode->getChildByName("nothing");
	auto myScene = rootNode->getChildByName("Scene");
	auto sprite = rootNode->getChildByName("Default");
	auto button1 = rootNode->getChildByName("Button_1");
	auto node1 = rootNode->getChildByName("Node_1");
	auto button2 = rootNode->getChildByName("Button_2");
	auto slider1 = rootNode->getChildByName("Node_1")->getChildByName("Slider_1");
		
	//���ض����� 
	ActionTimeline *action = CSLoader::createTimeline("MainScene.csb");
	rootNode->runAction(action);
	//ע!!!��ͬһ���ļ������Ľڵ�ֻ��ʹ��ͬһ���ļ������Ķ����� 
	//Ƕ�׽ڵ�Ķ������Զ����ض�����������Ƕ�׽ڵ�->getActionByTag(Ƕ�׽ڵ�->getTag()) ����ȡ���� 

	//���Ŷ����� 
	action->gotoFrameAndPlay(0, 60, true);//�ӵ�0֡��60֡ѭ�����š������������غ���

    return true;
}
