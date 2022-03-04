#ifndef PLAYER_H_
#define PLAYER_H_

#include "../../Parent/GameObject.h"
#include "../../../Library/GameManager/GameManager.h"

#include "../../../Library/Component/Child/SphereCollision/SphereCollision.h"

class Player : public GameObject {
public:
	//SphereCollision collision{ 100.0f,transform_.position(),this };

	Player(const Vec3& position);
	
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

	SphereCollision* col;
};

#endif // !PLAYER_H_