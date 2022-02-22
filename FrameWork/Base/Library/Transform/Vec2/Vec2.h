#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <cmath>
#include "../../MyMath/MyMath.h"

using namespace std;

//2Dベクトル
struct Vec2 {
	//ベクトルの成分
	float x{ 0.0f };
	float y{ 0.0f };

	//コンストラクタ
	Vec2() = default;
	Vec2(float x_, float y_) : x{ x_ }, y{ y_ } {};
	
	//ベクトルの長さ
	float length() const {
		return sqrt(lengthSquared());
	}
	//ベクトルの長さの2乗
	float lengthSquared() const {
		return x * x + y * y;
	}
	//もう一つのベクトルとの内積
	float dot(const Vec2& other) const {
		return x * other.x + y * other.y;
	}
	//もう一つのベクトルとの外積
	float cross(const Vec2& other) const {
		return x * other.y - y * other.x;
	}
	//もう一つのベクトルとの距離
	float distance(const Vec2& other) const {
		return sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
	}
	//正規化ベクトル(長さ = 1)
	Vec2 normalized() const {
		float l = length();
		if (l == 0) {//限りなく0に近い時
			return *this;
		}
		return{ x / l , y / l };
	}
	//ゼロベクトルか？
	bool isZero() const {
		return x == 0.0 && y == 0.0f;
	}
	//比較して各成分の大きい方の成分を取り出す
	Vec2 Max(const Vec2& value1, const Vec2& value2) {
		return Vec2{ max(value1.x,value2.x) , max(value1.y,value2.y) };
	}
	//比較して各成分の小さい方の成分を取り出す
	Vec2 Min(const Vec2& value1, const Vec2& value2) {
		return Vec2{ min(value1.x,value2.x) , min(value1.y,value2.y) };
	}
	//ベクトルの線形補間 ( t は 0.0～1.0 )
	Vec2 lerp(const Vec2& from, const Vec2& to, float t) {
		return MyMath::lerp(from, to, MyMath::clamp01(t));
	}
	//ベクトルのクランプ( target を min と max の値に留める)
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


	// <単項演算子>


	Vec2 operator + () const {
		return *this;
	}
	//逆ベクトル
	Vec2 operator - () const {
		return { -x , -y };
	}


	// <二項演算子>


	//加算
	Vec2 operator + (const Vec2& other) {
		return { x + other.x , y + other.y };
	}
	//減算
	Vec2 operator - (const Vec2& other) {
		return { x - other.x , y - other.y };
	}
	//乗算(スカラー倍)
	Vec2 operator * (float s) {
		return { x * s , y * s };
	}
	//除算(スカラー倍)
	Vec2 operator / (float s) {
		return { x * s , y * s };
	}


	// <複合代入演算子>


	//加算
	Vec2& operator +=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	//減算
	Vec2& operator -= (const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	//加算(スカラー倍)
	Vec2& operator *= (float s) {
		x *= s;
		y *= s;
		return *this;
	}
	//除算(スカラー倍)
	Vec2& operator /= (float s) {
		x /= s;
		y /= s;
		return *this;
	}


	// <比較演算子>
	//※(int)にキャストしてるのは浮動小数点での比較で誤差が生じる為


	//比較して同じか？
	bool operator == (const Vec2& other) const {
		return ((int)x == (int)other.x && (int)y == (int)other.y);
	}
	//比較して違うか？
	bool operator != (const Vec2& other) const {
		return ((int)x != (int)other.x && (int)y != (int)other.y);
	}
	//左辺が右辺より大きい or 同じか？
	bool operator >= (const Vec2& other) const {
		return ((int)x >= (int)other.x && (int)y >= (int)other.y);
	}
	//左辺が右辺より小さい or 同じか？
	bool operator <= (const Vec2& other) const {
		return ((int)x <= (int)other.x && (int)y <= (int)other.y);
	}
	//左辺が右辺より大さいか？
	bool operator > (const Vec2& other) const {
		return ((int)x > (int)other.x && (int)y > (int)other.y);
	}
	//左辺が右辺より小さいか？
	bool operator < (const Vec2& other) const {
		return ((int)x < (int)other.x && (int)y < (int)other.y);
	}
};


// <フリー関数>


//Vec2が後ろの乗算
inline Vec2 operator *(float s, const Vec2& self) {
	return { s * self.x , s * self.y };
}

#endif // !VECTOR2_H_
