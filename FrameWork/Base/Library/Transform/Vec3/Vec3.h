#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>
#include "../../MyMath/MyMath.h"

//3D�x�N�g��
struct Vec3 {
	//�x�N�g���̐���
	float x{ 0.0f };
	float y{ 0.0f };
	float z{ 0.0f };

	//�R���X�g���N�^
	Vec3() = default;
	Vec3(float x_, float y_, float z_) : x{ x_ }, y{ y_ }, z{ z_ } {};

	//�x�N�g���̒���
	float length() const {
		return sqrt(lengthSquared());
	}
	//�x�N�g����2��̒���
	float lengthSquared() const {
		return x * x + y * y * z * z;
	}
	//������̃x�N�g���Ƃ̓���
	float dot(const Vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}
	//������̃x�N�g���Ƃ̊O��
	Vec3 cross(const Vec3& other) const {
		return Vec3{ y * other.z - z * other.y,
					 z * other.x - x * other.z,
					 x * other.y - y * other.x };
	}
	//������̃x�N�g���Ƃ̋���
	float distance(const Vec3& other) const {
		return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) + (other.z - z) * (other.z - z));
	}
	//���K���x�N�g��(���� = 1)
	Vec3 normalized() const {
		float l = length();
		if (l == 0) {//����Ȃ�0�ɋ߂���
			return *this;
		}
		return{ x / length() , y / length() , z / length()};
	}
	//�[���x�N�g�����H
	bool isZero() const {
		return x == 0.0 && y == 0.0f && z == 0.0f;
	}
	//��r���Ċe�����̑傫�����̐��������o��
	Vec3 Max(const Vec3& value1, const Vec3& value2) {
		Vec3 result;
		result.x = (value1.x > value2.x) ? value1.x : value2.x;
		result.y = (value1.y > value2.y) ? value1.y : value2.y;
		result.z = (value1.z > value2.z) ? value1.z : value2.z;
		return result;
	}
	//��r���Ċe�����̏��������̐��������o��
	Vec3 Min(const Vec3& value1, const Vec3& value2) {
		Vec3 result;
		result.x = (value1.x < value2.x) ? value1.x : value2.x;
		result.y = (value1.y < value2.y) ? value1.y : value2.y;
		result.z = (value1.z < value2.z) ? value1.z : value2.z;
		return result;
	}
	//�x�N�g���̐��`��� ( t �� 0.0�`1.0 )
	Vec3 Lerp(const Vec3& from, const Vec3& to, float t) {
		return MyMath::lerp(from, to, MyMath::clamp01(t));
	}
	//�x�N�g���̃N�����v( target �� min �� max �̒l�ɗ��߂�)
	Vec3 clamp(Vec3& target, const Vec3& min, const Vec3& max) {
		return MyMath::clamp(target, min, max);
	}
	//2�_�� (���g����to ) �̊p�x��Ԃ�
	float angle(const Vec3& to) {
		float denominator = std::sqrt(lengthSquared() * to.lengthSquared()); // ����
		float cos = MyMath::clamp(dot(to) / denominator, -1.0f, 1.0f);
		return MyMath::Rad_to_Deg * std::acos(cos);//acos = -1�`1�̊ԂŊp�x�����߂�
	}

	//Vec3{0, 0, 0}
	static Vec3 zero() {
		return Vec3{ 0.0 , 0.0 , 0.0 };
	}
	//Vec3{1, 1, 1}
	static Vec3 one() {
		return Vec3{ 1.0 , 1.0 , 1.0 };
	}
	//Vec3{0, 1, 0}
	static Vec3 up() {
		return Vec3{ 0.0 , 1.0 , 0.0 };
	}
	//Vec3{0, -1, 0}
	static Vec3 down() {
		return Vec3{ 0.0 ,-1.0 , 0.0 };
	}
	//Vec3{-1, 0, 0}
	static Vec3 left() {
		return Vec3{-1.0 , 0.0 , 0.0 };
	}
	//Vec3{1, 0, 0}
	static Vec3 right() {
		return Vec3{ 1.0 , 0.0 , 0.0 };
	}
	//Vec3{0, 0, 1}
	static Vec3 forward() {
		return Vec3{ 0.0 , 0.0 , 1.0 };
	}
	//Vec3{0, 0, -1}
	static Vec3 back() {
		return Vec3{ 0.0 , 0.0 ,-1.0 };
	}



	// <�P�����Z�q>


	Vec3 operator + () const {
		return *this;
	}
	//�t�x�N�g��
	Vec3 operator - () const {
		return { -x , -y , -z};
	}


	// <�񍀉��Z�q>


	//���Z
	Vec3 operator + (const Vec3& other) {
		return { x + other.x , y + other.y , z + other.z };
	}
	//���Z
	Vec3 operator - (const Vec3& other) {
		return { x - other.x , y - other.y , z - other.z};
	}
	//��Z(�X�J���[�{)
	Vec3 operator * (float s) {
		return { x * s , y * s , z * s};
	}
	//���Z(�X�J���[�{)
	Vec3 operator / (float s) {
		return { x * s , y * s , z * s};
	}


	// <����������Z�q>


	//���Z
	Vec3 operator +=(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	//���Z
	Vec3 operator -= (const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	//���Z(�X�J���[�{)
	Vec3 operator *= (float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	//���Z(�X�J���[�{)
	Vec3 operator /= (float s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}


	// <��r���Z�q>
	//��(int)�ɃL���X�g���Ă�͕̂��������_�ł̔�r�Ō덷���������


	//��r���ē������H
	bool operator == (const Vec3& other) const {
		return ((int)x == (int)other.x && (int)y == (int)other.y && (int)z == (int)other.z);
	}
	//��r���ĈႤ���H
	bool operator != (const Vec3& other) const {
		return ((int)x != (int)other.x && (int)y != (int)other.y && (int)z != (int)other.z);
	}
	//���ӂ��E�ӂ��傫�� or �������H
	bool operator >= (const Vec3& other) const {
		return ((int)x >= (int)other.x && (int)y >= (int)other.y && (int)z >= (int)other.z);
	}
	//���ӂ��E�ӂ�菬���� or �������H
	bool operator <= (const Vec3& other) const {
		return ((int)x <= (int)other.x && (int)y <= (int)other.y && (int)z <= (int)other.z);
	}
	//���ӂ��E�ӂ��傳�����H
	bool operator > (const Vec3& other) const {
		return ((int)x > (int)other.x && (int)y > (int)other.y && (int)z > (int)other.z);
	}
	//���ӂ��E�ӂ�菬�������H
	bool operator < (const Vec3& other) const {
		return ((int)x < (int)other.x && (int)y < (int)other.y && (int)z < (int)other.z);
	}
};


// <�t���[�֐�>


//Vec3�����̏�Z
inline Vec3 operator *(float s, const Vec3& self) {
	return { s * self.x , s * self.y , s * self.z};
}
//const�ł̉��Z
inline 	const Vec3 operator + (const Vec3& self,const Vec3& other) {
	return { self.x + other.x , self.y + other.y , self.z + other.z };
}
//const�ł̌��Z
inline const Vec3 operator - (const Vec3& self, const Vec3& other) {
	return { self.x - other.x , self.y - other.y , self.z - other.z };
}

#endif // !VECTOR3_H_
