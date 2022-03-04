#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>
#include "../../MyMath/MyMath.h"

//3Dベクトル
struct Vec3 {
	//ベクトルの成分
	float x{ 0.0f };
	float y{ 0.0f };
	float z{ 0.0f };

	//コンストラクタ
	Vec3() = default;
	Vec3(float x_, float y_, float z_) : x{ x_ }, y{ y_ }, z{ z_ } {};

	//ベクトルの長さ
	float length() const {
		return sqrt(lengthSquared());
	}
	//ベクトルの2乗の長さ
	float lengthSquared() const {
		return x * x + y * y * z * z;
	}
	//もう一つのベクトルとの内積
	float dot(const Vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}
	//もう一つのベクトルとの外積
	Vec3 cross(const Vec3& other) const {
		return Vec3{ y * other.z - z * other.y,
					 z * other.x - x * other.z,
					 x * other.y - y * other.x };
	}
	//もう一つのベクトルとの距離
	float distance(const Vec3& other) const {
		return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) + (other.z - z) * (other.z - z));
	}
	//正規化ベクトル(長さ = 1)
	Vec3 normalized() const {
		float l = length();
		if (l == 0) {//限りなく0に近い時
			return *this;
		}
		return{ x / length() , y / length() , z / length()};
	}
	//ゼロベクトルか？
	bool isZero() const {
		return x == 0.0 && y == 0.0f && z == 0.0f;
	}
	//比較して各成分の大きい方の成分を取り出す
	Vec3 Max(const Vec3& value1, const Vec3& value2) {
		Vec3 result;
		result.x = (value1.x > value2.x) ? value1.x : value2.x;
		result.y = (value1.y > value2.y) ? value1.y : value2.y;
		result.z = (value1.z > value2.z) ? value1.z : value2.z;
		return result;
	}
	//比較して各成分の小さい方の成分を取り出す
	Vec3 Min(const Vec3& value1, const Vec3& value2) {
		Vec3 result;
		result.x = (value1.x < value2.x) ? value1.x : value2.x;
		result.y = (value1.y < value2.y) ? value1.y : value2.y;
		result.z = (value1.z < value2.z) ? value1.z : value2.z;
		return result;
	}
	//ベクトルの線形補間 ( t は 0.0～1.0 )
	Vec3 Lerp(const Vec3& from, const Vec3& to, float t) {
		return MyMath::lerp(from, to, MyMath::clamp01(t));
	}
	//ベクトルのクランプ( target を min と max の値に留める)
	Vec3 clamp(Vec3& target, const Vec3& min, const Vec3& max) {
		return MyMath::clamp(target, min, max);
	}
	//2点間 (自身からto ) の角度を返す
	float angle(const Vec3& to) {
		float denominator = std::sqrt(lengthSquared() * to.lengthSquared()); // 分母
		float cos = MyMath::clamp(dot(to) / denominator, -1.0f, 1.0f);
		return MyMath::Rad_to_Deg * std::acos(cos);//acos = -1～1の間で角度を求める
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



	// <単項演算子>


	Vec3 operator + () const {
		return *this;
	}
	//逆ベクトル
	Vec3 operator - () const {
		return { -x , -y , -z};
	}


	// <二項演算子>


	//加算
	Vec3 operator + (const Vec3& other) {
		return { x + other.x , y + other.y , z + other.z };
	}
	//減算
	Vec3 operator - (const Vec3& other) {
		return { x - other.x , y - other.y , z - other.z};
	}
	//乗算(スカラー倍)
	Vec3 operator * (float s) {
		return { x * s , y * s , z * s};
	}
	//除算(スカラー倍)
	Vec3 operator / (float s) {
		return { x * s , y * s , z * s};
	}


	// <複合代入演算子>


	//加算
	Vec3 operator +=(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	//減算
	Vec3 operator -= (const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	//加算(スカラー倍)
	Vec3 operator *= (float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	//除算(スカラー倍)
	Vec3 operator /= (float s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}


	// <比較演算子>
	//※(int)にキャストしてるのは浮動小数点での比較で誤差が生じる為


	//比較して同じか？
	bool operator == (const Vec3& other) const {
		return ((int)x == (int)other.x && (int)y == (int)other.y && (int)z == (int)other.z);
	}
	//比較して違うか？
	bool operator != (const Vec3& other) const {
		return ((int)x != (int)other.x && (int)y != (int)other.y && (int)z != (int)other.z);
	}
	//左辺が右辺より大きい or 同じか？
	bool operator >= (const Vec3& other) const {
		return ((int)x >= (int)other.x && (int)y >= (int)other.y && (int)z >= (int)other.z);
	}
	//左辺が右辺より小さい or 同じか？
	bool operator <= (const Vec3& other) const {
		return ((int)x <= (int)other.x && (int)y <= (int)other.y && (int)z <= (int)other.z);
	}
	//左辺が右辺より大さいか？
	bool operator > (const Vec3& other) const {
		return ((int)x > (int)other.x && (int)y > (int)other.y && (int)z > (int)other.z);
	}
	//左辺が右辺より小さいか？
	bool operator < (const Vec3& other) const {
		return ((int)x < (int)other.x && (int)y < (int)other.y && (int)z < (int)other.z);
	}
};


// <フリー関数>


//Vec3が後ろの乗算
inline Vec3 operator *(float s, const Vec3& self) {
	return { s * self.x , s * self.y , s * self.z};
}
//const版の加算
inline 	const Vec3 operator + (const Vec3& self,const Vec3& other) {
	return { self.x + other.x , self.y + other.y , self.z + other.z };
}
//const版の減算
inline const Vec3 operator - (const Vec3& self, const Vec3& other) {
	return { self.x - other.x , self.y - other.y , self.z - other.z };
}

#endif // !VECTOR3_H_
