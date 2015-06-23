#include "CameraManager.h"
#include "ConfigUtil.h"
#include "Player.h"
#include "BackgroundManager.h"

USING_NS_CC;

cocos2d::Camera* CameraManager::camera_ = nullptr;

CameraManager::CameraManager() : delta_time_(0.0f), background_manager_(nullptr), battle_manager_(nullptr)
{
}

CameraManager::~CameraManager()
{
	camera_ = nullptr;
}

bool CameraManager::init()
{
	if (!Node::init())
		return false;
	// Create Camera
	camera_ = Camera::createOrthographic(config::visible_width, config::visible_height, 0.0f, 1000.0f);
	camera_->setCameraFlag(CameraFlag::USER1);
	// camera_->setPosition3D(Vec3((config::kBattleScene.x - config::visible_width) / 2, (config::kBattleScene.y - config::visible_height) / 2, 400));
	// camera_->lookAt(Vec3((config::kBattleScene.x - config::visible_width) / 2, (config::kBattleScene.y - config::visible_height) / 2, 0));
	this->addChild(camera_);
	setListener();
	scheduleUpdate();
	return true;
}

void CameraManager::setListener()
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

cocos2d::Camera* CameraManager::getCamera()
{
	return camera_;
}

void CameraManager::setCameraPosition(cocos2d::Vec2 position)
{
	if (camera_ == nullptr) return;
	camera_->setPosition3D(Vec3(position.x, position.y, 400));
	camera_->lookAt(Vec3(position.x, position.y, 0));
}

void CameraManager::addBattleManager(BattleManager* battle_manager)
{
	if (battle_manager_ != nullptr)
		return;
	battle_manager_ = battle_manager;
	this->addChild(battle_manager_, 1);
}

void CameraManager::removeBattleManager()
{
	if (battle_manager_ == nullptr)
		return;
	this->removeChild(battle_manager_);
	battle_manager_ = nullptr;
}

void CameraManager::addBackgroundManager(BackgroundManager* background_manager)
{
	if (background_manager_ != nullptr)
		return;
	background_manager_ = background_manager;
	this->addChild(background_manager_, 0);
}

void CameraManager::removeBackgroundManager()
{
	if (background_manager_ == nullptr)
		return;
	this->removeChild(background_manager_);
	background_manager_ = nullptr;
}

void CameraManager::update(float delta_time)
{
	// TODO setCameraMask at Every Node
	setCameraMask(1 << 1);
	delta_time_ = delta_time;
}