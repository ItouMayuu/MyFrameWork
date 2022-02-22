#ifndef MYMATH_H_
#define MYMATH_H_

using namespace std;

//数学関連クラス
class MyMath {
public:

	//円周率
	static const float PI;
	//√2
	static const float Sqrt2;
	//度数法にするための値
	static const float Deg_to_Rad;
	//弧度法(ラジアン)にするための値
	static const float Rad_to_Deg;

	// v を min と max の間に留める
	template <class T>
	static T clamp(T v, T min, T max) {
		return (v < min) ? min : (v > max) ? max : v;
	}
	// v を 0 と 1 の間に留める
	static float clamp01(float v) {
		return clamp(v, 0.0f, 1.0f);
	}
	// a と b の間で t(0～1) による線形補間をする
	template <class T>
	static T lerp(T a, T b, float t) {
		return a + (b - a) * clamp01(t);
	}
};

#endif
