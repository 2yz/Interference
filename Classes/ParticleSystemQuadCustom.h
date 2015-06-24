#ifndef  PARTICLE_SYSTEM_QUAD_CUSTOM_H_
#define  PARTICLE_SYSTEM_QUAD_CUSTOM_H_

#include "cocos2d.h"
#include "TimeCoefficient.h"

class ParticleSystemQuadCustom : public cocos2d::ParticleSystemQuad, public TimeCoefficient
{
public:
	static ParticleSystemQuadCustom * create(const std::string& filename);
	virtual void setParent(Node* parent) override;
	virtual void update(float dt) override;
};

#endif // PARTICLE_SYSTEM_QUAD_CUSTOM_H_

