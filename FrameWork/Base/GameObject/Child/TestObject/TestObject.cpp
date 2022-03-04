#include "TestObject.h"

TestObject::TestObject(const Vec3& position){
	this->name_ = "Test";
	this->tag_ = "TestTag";
	this->components.push_back(std::make_shared<SphereCollision>(100, position, this));
	transform_.position(position);
	col = get_comp<SphereCollision>("SphereCollision");
}

void TestObject::update()
{
}

void TestObject::draw() const{
	col->draw_debug();
}
