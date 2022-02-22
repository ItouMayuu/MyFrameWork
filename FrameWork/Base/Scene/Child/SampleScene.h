#ifndef SAMPLE_SCENE_H_
#define SAMPLE_SCENE_H_

#include "../Parent/Scene.h"
#include "../../Library/GameManager/GameManager.h"

//シーンのサンプル
class SampleScene : public Scene {
public:
	SampleScene();

	~SampleScene() {};

	void init() override;

	void update() override;

	void draw() override;

	void fin() override;

private:
	GameManager& gm = GameManager::GetInstance();
};

#endif // !SAMPLE_SCENE_H_
