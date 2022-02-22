#ifndef TEST_COMPONENT_H_
#define TEST_COMPONENT_H_

#include "../../Parent/Component.h"
#include <string>
class test : public Component {
public:
	test(GameObject* owner) : Component{ owner } {};

	virtual ~test() {};

	int counter = 0;

	virtual void update(GameObject* obj) override {
		counter++;
	}

	virtual void draw(GameObject* obj) override {
		DrawStringF(200.0f, 200.0f, std::to_string(counter).c_str(), GetColor(255, 255, 255));
	}
};
#endif // !TEST_COMPONENT_H_
