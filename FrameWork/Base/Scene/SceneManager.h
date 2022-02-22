#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "../Scene/Parent/Scene.h"
#include <string>
#include <memory>
#include <unordered_map>
#include "../Library/NotChangingLibrary/Singleton.h"


class SceneManager : public Singleton<SceneManager>{
public:
	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//������
	void init();
	//���t���[��update
	void update();
	//�`��
	void draw();
	//�I��
	void fin();
	//�V�[���ύX (�ύX��̃V�[����)
	void change_scene(std::string scene);
	//�V�[���̒ǉ� (�ǉ�����V�[���� , �ǉ�����V�[���N���X)
	void add_scene(std::string SceneName, std::shared_ptr<Scene> sceneClass);

private:
	//�ǉ������V�[���������o�^���Ă܂Ƃ߂Ă���
	std::unordered_map<std::string, std::shared_ptr<Scene>> scenes_;

	//���݂̃V�[��
	std::shared_ptr<Scene> current_scene_;
};
#endif
