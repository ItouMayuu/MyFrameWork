#ifndef SPHERE_COLLISION_H_
#define SPHERE_COLLISION_H_

#include "../../Parent/Component.h"
#include "../../../Transform/Transform.h"
#include "../../../../GameObject/Parent/GameObject.h"

class SphereCollision : public Component {
public:
	//コンストラクタ
	SphereCollision(float radius = 0.0f, const Vec3& center = Vec3{0.0f,0.0f,0.0f}, GameObject* owner = nullptr);
	virtual ~SphereCollision() {};
	virtual void update(GameObject* obj) override;
	virtual void draw(GameObject* obj) override;
	//平行移動
	SphereCollision translate(const Vec3& pos) const;
	//座標の設定
	SphereCollision transform(const Vec3& pos, float radius);
	//重なっているか？
	bool intersects(const SphereCollision& other) const;
	//デバック表示
	void draw_debug() const;
	//中心座標を返す
	Vec3 get_center() const;
	//半径を返す
	float get_radius() const;

private:
	//半径
	float radius{ 0.0f };
	//中心座標
	Vec3 center{ 0.0f,0.0f,0.0f };
	//球と球が重なったか？
	bool CollisionSphereAndSphere(const SphereCollision& other) const;
};
#endif // !SPHERE_COLLISION_H_