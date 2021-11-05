#pragma once
#include "IEnemy.h"


class SimpleEnemy : public IEnemy {
public:
	SimpleEnemy();
	~SimpleEnemy();
	static SimpleEnemy* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);
	static SimpleEnemy* createSimpleEnemy();
	virtual bool init() override;
private:
	
};

