#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <list>
#include <vector>
#include <string>
#include <memory>

#include "../GameManager.h"

//�O����`
class GameObject;
class Component;

//�Q�[���I�u�W�F�N�g�S�̂��Ǘ�����}�l�[�W���[�N���X
class GameObjectManager {
public:
	//�f�t�H���g�R���X�g���N�^
	GameObjectManager() = default;
	//�f�X�g���N�^
	~GameObjectManager();
	//�A�N�^�[�̒ǉ�
	void add(std::shared_ptr<GameObject> gameobject);
	//�A�N�^�[�S�̂̍X�V
	void update();
	//�A�N�^�[�S�̂̕`��
	void draw();
	//���S���Ă���A�N�^�[�̍폜
	void remove();
	//�L���X�g�Ȃ��Œ��ڃA�N�^�[���擾
	template<typename GameObjectType>
	GameObjectType* get(const std::string& tag) const {
		//���O����v�����炻�̃Q�[���I�u�W�F�N�g��Ԃ�
		for (auto go : game_objects_) {
			if (go->name() == tag) {
				GameObjectType* gos = (GameObjectType*)&go;
				return gos;
			}
		}//�Ȃɂ��Ȃ����null��Ԃ�
		return nullptr;
	}
	//�A�N�^�[�̌���
	std::shared_ptr<GameObject> find(const std::string& name) const;
	//�w�肵���^�O�������A�N�^�[�̌���
	std::vector<std::shared_ptr<GameObject>> find_with_tag(const std::string& tag) const;
	//�S�̂̃A�N�^�[����Ԃ�
	int count() const;
	//�w�肵���^�O�������A�N�^�[��Ԃ�
	int count_with_tag(const std::string& tag) const;
	//�S�A�N�^�[���폜
	void clear();

	//����̃R���|�[�l���g�̍폜
	void component_clear(GameObject* owner, std::string tag);
	//�R���|�[�l���g�̒ǉ�
	void component_add(GameObject* owner,std::shared_ptr<Component> comp);
	//�S�ẴR���|�[�l���g�̍폜
	void component_clear_all(GameObject* owner);

	//�R�s�[�h�~
	GameObjectManager(const GameObjectManager& other) = delete;
	GameObjectManager& operator = (const GameObjectManager& other) = delete;

private:
	//�S�A�N�^�[�̃��X�g
	std::list<std::shared_ptr<GameObject>> game_objects_;
	//�Q�[���}�l�[�W���[�ێ�
	GameManager& gm = GameManager::GetInstance();
};

#endif // !GAME_OBJECT_MANAGER_H_