#ifndef SPHERE_COLLISION_H_
#define SPHERE_COLLISION_H_

#include "../../Parent/Component.h"
#include "../../../Transform/Transform.h"
#include "../../../../GameObject/Parent/GameObject.h"

class SphereCollision : public Component {
public:
	//�R���X�g���N�^
	SphereCollision(float radius = 0.0f, const Vec3& center = Vec3{0.0f,0.0f,0.0f}, GameObject* owner = nullptr);
	virtual ~SphereCollision() {};
	virtual void update(GameObject* obj) override;
	virtual void draw(GameObject* obj) override;
	//���s�ړ�
	SphereCollision translate(const Vec3& pos) const;
	//���W�̐ݒ�
	SphereCollision transform(const Vec3& pos, float radius);
	//�d�Ȃ��Ă��邩�H
	bool intersects(const SphereCollision& other) const;
	//�f�o�b�N�\��
	void draw_debug() const;
	//���S���W��Ԃ�
	Vec3 get_center() const;
	//���a��Ԃ�
	float get_radius() const;

private:
	//���a
	float radius{ 0.0f };
	//���S���W
	Vec3 center{ 0.0f,0.0f,0.0f };
	//���Ƌ����d�Ȃ������H
	bool CollisionSphereAndSphere(const SphereCollision& other) const;
};
#endif // !SPHERE_COLLISION_H_