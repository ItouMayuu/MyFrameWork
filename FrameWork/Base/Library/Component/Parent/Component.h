#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <unordered_map>
#include <DxLib.h>
#include "../../GameManager/GameManager.h"

class GameObject;

class Component {
public:
	//このクラスを所有するクラスのポインタ
	GameObject* owner;
	//タグ名
	std::string tag = "";
	//種類のタグ名
	std::string typeTag = "";
	
	GameManager& gm = GameManager::GetInstance();

	//コンストラクタ
	Component(GameObject* owner) : owner{ owner } {};
	//仮想デストラクタ
	virtual ~Component() {};
	virtual void update(GameObject* obj = nullptr) {};
	virtual void draw(GameObject* obj = nullptr) {};
};

#endif // !COMPONENT_H_
