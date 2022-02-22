#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <cmath>
#include "../../MyMath/MyMath.h"

using namespace std;

//2D�x�N�g��
struct Vec2 {
	//�x�N�g���̐���
	float x{ 0.0f };
	float y{ 0.0f };

	//�R���X�g���N�^
	Vec2() = default;
	Vec2(float x_, float y_) : x{ x_ }, y{ y_ } {};
	
	//�x�N�g���̒���
	float length() const {
		return sqrt(lengthSquared());
	}
	//�x�N�g���̒�����2��
	float lengthSquared() const {
		return x * x + y * y;
	}
	//������̃x�N�g���Ƃ̓���
	float dot(const Vec2& other) const {
		return x * other.x + y * other.y;
	}
	//������̃x�N�g���Ƃ̊O��
	float cross(const Vec2& other) const {
		return x * other.y - y * other.x;
	}
	//������̃x�N�g���Ƃ̋���
	float distance(const Vec2& other) const {
		return sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
	}
	//���K���x�N�g��(���� = 1)
	Vec2 normalized() const {
		float l = length();
		if (l == 0) {//����Ȃ�0�ɋ߂���
			return *this;
		}
		return{ x / l , y / l };
	}
	//�[���x�N�g�����H
	bool isZero() const {
		return x == 0.0 && y == 0.0f;
	}
	//��r���Ċe�����̑傫�����̐��������o��
	Vec2 Max(const Vec2& value1, const Vec2& value2) {
		return Vec2{ max(value1.x,value2.x) , max(value1.y,value2.y) };
	}
	//��r���Ċe�����̏��������̐��������o��
	Vec2 Min(const Vec2& value1, const Vec2& value2) {
		return Vec2{ min(value1.x,value2.x) , min(value1.y,value2.y) };
	}
	//�x�N�g���̐��`��� ( t �� 0.0�`1.0 )
	Vec2 lerp(const Vec2& from, const Vec2& to, float t) {
		return MyMath::lerp(from, to, MyMath::clamp01(t));
	}
	//�x�N�g���̃N�����v( target �� min �� max �̒l�ɗ��߂�)
	Vec2 clamp(Vec2& target, const Vec2& min, const Vec2& max) {
		return MyMath::clamp(target, min, max);
	}

	// Vec2(0, 0)
	Vec2 zero() {
		return Vec2{ 0.0f, 0.0f };
	}

	// Vec2(1, 1)
	Vec2 one() {
		return Vec2{ 1.0f, 1.0f };
	}

	// Vec2(0, -1)
	Vec2 up() {
		return Vec2{ 0.0f, -1.0f };
	}

	// Vec2(0, 1)
	Vec2 down() {
		return Vec2{ 0.0f, 1.0f };
	}

	// Vec2(-1, 0)
	Vec2 left() {
		return Vec2{ -1.0f, 0.0f };
	}

	// Vec2(1, 0)
	Vec2 right() {
		return Vec2{ 1.0f, 0.0f };
	}


	// <�P�����Z�q>


	Vec2 operator + () const {
		return *this;
	}
	//�t�x�N�g��
	Vec2 operator - () const {
		return { -x , -y };
	}


	// <�񍀉��Z�q>


	//���Z
	Vec2 operator + (const Vec2& other) {
		return { x + other.x , y + other.y };
	}
	//���Z
	Vec2 operator - (const Vec2& other) {
		return { x - other.x , y - other.y };
	}
	//��Z(�X�J���[�{)
	Vec2 operator * (float s) {
		return { x * s , y * s };
	}
	//���Z(�X�J���[�{)
	Vec2 operator / (float s) {
		return { x * s , y * s };
	}


	// <����������Z�q>


	//���Z
	Vec2& operator +=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	//���Z
	Vec2& operator -= (const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	//���Z(�X�J���[�{)
	Vec2& operator *= (float s) {
		x *= s;
		y *= s;
		return *this;
	}
	//���Z(�X�J���[�{)
	Vec2& operator /= (float s) {
		x /= s;
		y /= s;
		return *this;
	}


	// <��r���Z�q>
	//��(int)�ɃL���X�g���Ă�͕̂��������_�ł̔�r�Ō덷���������


	//��r���ē������H
	bool operator == (const Vec2& other) const {
		return ((int)x == (int)other.x && (int)y == (int)other.y);
	}
	//��r���ĈႤ���H
	bool operator != (const Vec2& other) const {
		return ((int)x != (int)other.x && (int)y != (int)other.y);
	}
	//���ӂ��E�ӂ��傫�� or �������H
	bool operator >= (const Vec2& other) const {
		return ((int)x >= (int)other.x && (int)y >= (int)other.y);
	}
	//���ӂ��E�ӂ�菬���� or �������H
	bool operator <= (const Vec2& other) const {
		return ((int)x <= (int)other.x && (int)y <= (int)other.y);
	}
	//���ӂ��E�ӂ��傳�����H
	bool operator > (const Vec2& other) const {
		return ((int)x > (int)other.x && (int)y > (int)other.y);
	}
	//���ӂ��E�ӂ�菬�������H
	bool operator < (const Vec2& other) const {
		return ((int)x < (int)other.x && (int)y < (int)other.y);
	}
};


// <�t���[�֐�>


//Vec2�����̏�Z
inline Vec2 operator *(float s, const Vec2& self) {
	return { s * self.x , s * self.y };
}

#endif // !VECTOR2_H_
