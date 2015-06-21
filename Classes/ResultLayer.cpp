#include "ResultLayer.h"
#include "BattleScene.h"

USING_NS_CC;

ResultLayer* ResultLayer::create(const std::string& label_text, const std::string& button_text)
{
	ResultLayer *pRet = new(std::nothrow) ResultLayer(label_text, button_text);
	CALL_INIT();
}

ResultLayer::ResultLayer(const std::string& label_text, const std::string& button_text) : PopupLayer(label_text,button_text)
{
}

void ResultLayer::buttonListener(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;
	case ui::Widget::TouchEventType::ENDED:
		BattleScene::getInstance()->openMenu();
		this->onDestroy();
		break;
	default:
		break;
	}
}