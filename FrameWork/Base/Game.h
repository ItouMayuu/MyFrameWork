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
	//�V�[���}�l�[�W���[
	SceneManager& sm = SceneManager::GetInstance();
	//�Q�[���}�l�[�W���[
	GameManager& gm = GameManager::GetInstance();

	//�g���{�^����o�^����
	void RegisterButton();
};
#endif // !GAME_H_