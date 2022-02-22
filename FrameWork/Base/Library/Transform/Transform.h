#ifndef TRANFORM_H_
#define TRANFORM_H_

#include "Quaternion/Quaternion.h"
#include "Vec3/Vec3.h"
#include "Vec2/Vec2.h"

class Transform {
public:
	//�R���X�g���N�^
	Transform() = default;
	//�f�X�g���N�^
	~Transform() {};
	//�O�������擾
	Vec3 forward() const {
		return rotation_ * Vec3::forward();
	}
	//���������擾
	Vec3 right() const {
		return rotation_ * Vec3::right();
	}
	//��������擾
	Vec3 up() {
		return rotation_ * Vec3::up();
	}
	//transform�̈ʒu���擾
	Vec3 position() const {
		return position_;
	}
	//transform�̉�]���擾
	Quaternion rotation() const {
		return rotation_;
	}
	//transform�̃X�P�[�����擾
	Vec3 scale() const{
		return scale_;
	}



private:
	//�|�W�V����
	Vec3 position_{ 0.0f,0.0f,0.0f };
	//��]
	Quaternion rotation_{ 0.0f,0.0f,0.0f,1.0f };
	//�X�P�[��
	Vec3 scale_{ 1.0f,1.0f,1.0f };

	//������
	void* owner_{ nullptr };
};

#endif // !TRANFORM_H_