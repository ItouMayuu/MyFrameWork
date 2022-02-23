#ifndef TRANFORM_H_
#define TRANFORM_H_

#include "Quaternion/Quaternion.h"
#include "Vec3/Vec3.h"
#include "Vec2/Vec2.h"

class Transform {
public:
	//コンストラクタ
	Transform() = default;
	//デストラクタ
	~Transform() {};
	//前方向を取得
	Vec3 forward() const {
		return rotation_ * Vec3::forward();
	}
	//横方向を取得
	Vec3 right() const {
		return rotation_ * Vec3::right();
	}
	//上方向を取得
	Vec3 up() {
		return rotation_ * Vec3::up();
	}
	//transformの位置を取得
	Vec3 position() const {
		return position_;
	}
	//transformの位置を設定
	Vec3 position(const Vec3& position) {
		return position_ = position;
	}
	//transformの回転を取得
	Quaternion rotation() const {
		return rotation_;
	}
	//transformの回転を設定
	Quaternion rotation(const Quaternion& rotation) {
		return rotation_ = rotation;
	}
	//transformのスケールを取得
	Vec3 scale() const{
		return scale_;
	}
	//transformのスケールを設定
	Vec3 scale(const Vec3& scale) {
		return scale_ = scale;
	}



private:
	//ポジション
	Vec3 position_{ 0.0f,0.0f,0.0f };
	//回転
	Quaternion rotation_{ 0.0f,0.0f,0.0f,1.0f };
	//スケール
	Vec3 scale_{ 1.0f,1.0f,1.0f };

	//持ち主
	void* owner_{ nullptr };
};

#endif // !TRANFORM_H_