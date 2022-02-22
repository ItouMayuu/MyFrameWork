#ifndef GAME_H_
#define GAME_H_

#include "Scene/SceneManager.h"
#include "Library/GameManager/GameManager.h"
#include "Library/GameManager/GameObjectManager/GameObjectManager.h"

class Game
{
public:
	Game();

	void Init();

	void Update();

	void Draw();

private:
	//シーンマネージャー
	SceneManager& sm = SceneManager::GetInstance();
	//ゲームマネージャー
	GameManager& gm = GameManager::GetInstance();

	//使うボタンを登録する
	void RegisterButton();
};
#endif // !GAME_H_