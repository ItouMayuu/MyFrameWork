#ifndef NULLSCENE_H_
#define NULLSCENE_H_

#include "../Scene.h"

//ヌルを指すシーン
class NullScene : public Scene {
public:
	void init() override;
	void update() override;
	void draw() override;
	void fin() override;
};

#endif // !SCENE_H_
