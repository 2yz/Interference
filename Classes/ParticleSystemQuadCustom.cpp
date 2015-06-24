#include "ParticleSystemQuadCustom.h"

ParticleSystemQuadCustom* ParticleSystemQuadCustom::create(const std::string& filename)
{
	ParticleSystemQuadCustom *ret = new (std::nothrow) ParticleSystemQuadCustom();
	if (ret && ret->initWithFile(filename))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}

void ParticleSystemQuadCustom::setParent(Node* parent)
{
	ParticleSystemQuad::setParent(parent);
	setTimeParent(dynamic_cast<TimeCoefficient*>(parent));
}

void ParticleSystemQuadCustom::update(float dt)
{
	ParticleSystemQuad::update(dt*getTimeCoefficient());
}