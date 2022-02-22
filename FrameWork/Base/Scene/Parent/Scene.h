#ifndef SCENE_H_
#define SCENE_H_

//�eScene�̐e�N���X
class Scene {
public:
	//���z�f�X�g���N�^
	virtual ~Scene() = default;

	//�p���V�[���̏�����
	virtual void init() = 0;

	//�p���V�[���̍X�V
	virtual void update() = 0;

	//�p���V�[���̕`��
	virtual void draw() = 0;

	//�p���V�[���̏I��
	virtual void fin() = 0;
};

#endif // !SCENE_H_
