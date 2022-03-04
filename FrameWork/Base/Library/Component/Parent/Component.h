#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <unordered_map>
#include <DxLib.h>
#include "../../GameManager/GameManager.h"

class GameObject;

class Component {
public:
	//���̃N���X�����L����N���X�̃|�C���^
	GameObject* owner;
	//�^�O��
	std::string tag = "";
	//��ނ̃^�O��
	std::string typeTag = "";
	
	GameManager& gm = GameManager::GetInstance();

	//�R���X�g���N�^
	Component(GameObject* owner) : owner{ owner } {};
	//���z�f�X�g���N�^
	virtual ~Component() {};
	virtual void update(GameObject* obj = nullptr) {};
	virtual void draw(GameObject* obj = nullptr) {};
};

#endif // !COMPONENT_H_
