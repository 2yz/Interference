#include "CameraNode.h"
#include "ConfigUtil.h"
#include "Player.h"
#include "GameBackgroundLayer.h"

USING_NS_CC;

cocos2d::Camera* CameraNode::camera_ = nullptr;

CameraNode::CameraNode() : game_background_layer_(nullptr), delta_time_(0.0f)
{
}

CameraNode::~CameraNode()
{
	camera_ = nullptr;
	game_background_layer_ = nullptr;
}

bool CameraNode::init()
{
	if (!Node::init())
		return false;
	// Create Camera
	camera_ = Camera::createOrthographic(config::visible_width, config::visible_height, 0.0f, 1000.0f);
	camera_->setCameraFlag(CameraFlag::USER1);
	camera_->setPosition3D(Vec3((config::kBattleScene.x - config::visible_width) / 2, (config::kBattleScene.y - config::visible_height) / 2, 400));
	camera_->lookAt(Vec3((config::kBattleScene.x - config::visible_width) / 2, (config::kBattleScene.y - config::visible_height) / 2, 0));
	this->addChild(camera_);
	// Create Background
	game_background_layer_ = GameBackgroundLayer::create();
	this->addChild(game_background_layer_, 0);
	setListener();
	scheduleUpdate();
	return true;
}

void CameraNode::setListener()
{
	auto camera_listener = EventListenerCustom::create(CAMERA_EVENT, [=](EventCustom* event)
	{
		Player* player = static_cast<Player*>(event->getUserData());
		auto positionDelta = player->getPosition() - Vec2(config::visible_width / 2, config::visible_height / 2) - camera_->getPosition();
		auto eye = camera_->getPosition3D() + Vec3(positionDelta.x * player->getTraceCoefficient() * delta_time_, positionDelta.y * player->getTraceCoefficient() * delta_time_, 0.0f);
		camera_->setPosition3D(eye);
		eye.z = 0.0f;
		camera_->lookAt(eye);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(camera_listener, this);
}

cocos2d::Camera* CameraNode::getCamera()
{
	return camera_;
}

void CameraNode::addBattleLayer(BattleLayer* battle_layer)
{
	if (battle_layer_ == nullptr)
		battle_layer_ = battle_layer;
}

void CameraNode::removeBattleLayer()
{
	removeChild(battle_layer_, true);
	battle_layer_ = nullptr;
}

void CameraNode::update(float deltaTime)
{
	// TODO setCameraMask at Every Node
	setCameraMask(1 << 1);
	delta_time_ = deltaTime;
}