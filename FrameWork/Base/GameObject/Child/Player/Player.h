#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../Parent/GameObject.h"
#include "../../../Library/GameManager/GameManager.h"

class Player : public GameObject {
public:
	Player();
	
	void update() override;

	void draw() const override;

	//セーブデータからの値を取得
	void load_status(int hp, int mp);

private:
	GameManager& gm = GameManager::GetInstance();

	//テスト用
	int hp_{ 0 };
	int mp_{ 0 };

	float x_{ 0 };
	float y_{ 0 };
	float z_{ 0 };

	float w{ 0 };

	void InputHandle();
};

#endif // !PLAYER_H_