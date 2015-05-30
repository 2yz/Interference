#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"

class HelloWorld : public cocos2d::Layer, public cocostudio::WidgetCallBackHandlerProtocol
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void onEnter() override;
	void onClick();
	void setPhyWorld(cocos2d::PhysicsWorld* world);
private:
	cocos2d::PhysicsWorld* m_world;
	void addNewSpriteAtPosition(cocos2d::Point p);
	void onMouseUp(cocos2d::Event *event);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
};

#endif // __HELLOWORLD_SCENE_H__
