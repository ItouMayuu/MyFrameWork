#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../Parent/GameObject.h"
#include "../../../Library/GameManager/GameManager.h"

class Player : public GameObject {
public:
	Player();
	
	void update() override;

	void draw() const override;

	//�Z�[�u�f�[�^����̒l���擾
	void load_status(int hp, int mp);

private:
	GameManager& gm = GameManager::GetInstance();

	//�e�X�g�p
	int hp_{ 0 };
	int mp_{ 0 };

	void InputHandle();
};

#endif // !PLAYER_H_