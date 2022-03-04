#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <string>

#include "../../Library/GameManager/GameManager.h"
#include "../../Library/Transform/Transform.h"
#include "../../Library/MyDraw/MyDraw.h"
#include "../../Resource/Image/Image.h"

class Component;

//�Q�[���I�u�W�F�N�g�N���X	�@��Shared_ptr��this���g����悤��
class GameObject : public std::enable_shared_from_this<GameObject>{
public:
	//�R���X�g���N�^
	GameObject() = default;
	//���z�f�X�g���N�^
	virtual ~GameObject() = default;
	//�Q�[���I�u�W�F�N�g�̍X�V
	virtual void update();
	//�`��
	virtual void draw() const;
	//�������̕`��
	virtual void draw_transparent() const;
	//GUI�̕`��
	virtual void draw_gui() const;
	//���S����
	void die();
	//���S���Ă��邩�H
	bool is_dead() const;
	//���O���擾
	const std::string& name() const;
	//�^�O�����擾
	const std::string& tag() const;
	//�g�����X�t�H�[�����擾(const��)
	const Transform& transform() const;
	//�g�����X�t�H�[�����擾
	Transform& transform();

	//�R���|�[�l���g�̍X�V
	void component_update();
	//�R���|�[�l���g�̕`��
	void component_draw();
	//�R���|�[�l���g���擾
	std::vector<std::shared_ptr<Component>> get_components();
	//���ڃR���|�[�l���g���擾
	template<typename ComponentType>
	typename ComponentType* get_comp(const std::string& tag) const {
		//�^�O����v������R���|�[�l���g��Ԃ�
			for (auto cp : components) {
				if (cp->tag == tag) {
					ComponentType* cps = (ComponentType*)&cp;
					return cps;
				}
			}//�Ȃɂ��Ȃ����null��Ԃ�
		return nullptr;
	}
	
	//�R�s�[�֎~
	GameObject(const GameObject& other) = delete;
	GameObject& operator = (const GameObject& other) = delete;

protected:
	//�^�O��
	std::string tag_;
	//���O
	std::string name_;
	//�g�����X�t�H�[��
	Transform transform_;
	//���S�t���O
	bool dead_{ false };
	//�R���|�[�l���g�̔z��
	std::vector<std::shared_ptr<Component>> components;

private:

	GameManager& gm = GameManager::GetInstance();
};

#endif // !GAME_OBJECT_H_