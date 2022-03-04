#pragma once

#include "../../Parent/GameObject.h"

#include "../../../Library/Component/Child/SphereCollision/SphereCollision.h"

class TestObject : public GameObject{
public:
	TestObject(const Vec3& position);

	virtual void update() override;

	virtual void draw() const override;

private:
	SphereCollision* col;
};

