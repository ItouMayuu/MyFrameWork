#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "../Vec3/Vec3.h"
#include <cmath>

struct Quaternion {
	float x{ 0.0f }; // Xé≤ pitch
	float y{ 0.0f }; // Yé≤ yaw
	float z{ 0.0f }; // Zé≤ roll
	float w{ 0.0f }; // äpìx

	Quaternion() = default;

	Quaternion(float x_, float y_, float z_, float w_)
		:x{ x_ }, y{ y_ }, z{ z_ }, w{ w_ }{};
	//íPà ÉNÉHÅ[É^ÉjÉIÉìÇï‘Ç∑
	Quaternion identity() {
		return Quaternion{ 0.0f,0.0f,0.0f,1.0f };
	}
	//ì‡êœ
	float dot(const Quaternion q) const {
		return x * q.x  +  y * q.y  +  z * q.z  +  w * q.w;
	}
	//í∑Ç≥
	float length() const{
		return sqrt(dot(*this));
	}
	//ê≥ãKâª
	Quaternion normalized() {
		float l = length();
		if (l == 0) {//å¿ÇËÇ»Ç≠0Ç…ãﬂÇ¢éû
			return *this;
		}
		return Quaternion{ x / l,y / l,z / l,w / l };
	}

	
	// <ìÒçÄââéZéq>


	//â¡éZ
	Quaternion operator + (const Quaternion& other) const {
		return { x + other.x, y + other.y, z + other.z, w + other.w };
	}
	//å∏éZ
	Quaternion operator - (const Quaternion& other) const {
		return { x - other.x, y - other.y , z - other.z, w - other.w };
	}
	//èÊéZ
	Quaternion operator * (const Quaternion& other) const {
		return{ w * other.x - z * other.y + y * other.z + x * other.w,
			    z * other.x + w * other.y - x * other.z + y * other.w,
			   -y * other.x + x * other.y + w * other.z + z * other.w,
			   -x * other.x - y * other.y - z * other.z + w * other.w };
	}
	//â¡éZ(ÉXÉJÉâÅ[î{)
	Quaternion operator * (float s) {
		return { x * s , y * s , z * s , w * s };
	}


	// <ï°çáë„ì¸ââéZéq>


	//â¡éZ
	Quaternion& operator += (const Quaternion& other) {
		x += other.x;	y += other.y;
		z += other.z;	w += other.w;
		return *this;
	}
	//å∏éZ
	Quaternion& operator -= (const Quaternion& other) {
		x -= other.x;	y -= other.y;
		z -= other.z;	w -= other.w;
		return *this;
	}
	//èÊéZ(ÉXÉJÉâÅ[î{)
	Quaternion& operator *= (const Quaternion& other) {
		x *= other.x;	y *= other.y;
		z *= other.z;	w *= other.w;
		return *this;
	}
};

inline Quaternion operator * (float s , Quaternion& q) {
	return { s * q.x,s * q.y,s * q.z,s * q.w };
}

inline Vec3 operator * (const Quaternion& rotation, const Vec3& point) {
	float x = rotation.x * 2.0f;
	float y = rotation.y * 2.0f;
	float z = rotation.z * 2.0f;
	float xx = rotation.x * x;
	float yy = rotation.y * y;
	float zz = rotation.z * z;
	float xy = rotation.x * y;
	float xz = rotation.x * z;
	float yz = rotation.y * z;
	float wx = rotation.w * x;
	float wy = rotation.w * y;
	float wz = rotation.w * z;
	Vec3 result;
	result.x = (1.0f - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
	result.y = (xy + wz) * point.x + (1.0f - (xx + zz)) * point.y + (yz - wx) * point.z;
	result.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0f - (xx + yy)) * point.z;
	return result;
}

#endif // !QUATERNION_H_