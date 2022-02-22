#ifndef MYMATH_H_
#define MYMATH_H_

using namespace std;

//���w�֘A�N���X
class MyMath {
public:

	//�~����
	static const float PI;
	//��2
	static const float Sqrt2;
	//�x���@�ɂ��邽�߂̒l
	static const float Deg_to_Rad;
	//�ʓx�@(���W�A��)�ɂ��邽�߂̒l
	static const float Rad_to_Deg;

	// v �� min �� max �̊Ԃɗ��߂�
	template <class T>
	static T clamp(T v, T min, T max) {
		return (v < min) ? min : (v > max) ? max : v;
	}
	// v �� 0 �� 1 �̊Ԃɗ��߂�
	static float clamp01(float v) {
		return clamp(v, 0.0f, 1.0f);
	}
	// a �� b �̊Ԃ� t(0�`1) �ɂ����`��Ԃ�����
	template <class T>
	static T lerp(T a, T b, float t) {
		return a + (b - a) * clamp01(t);
	}
};

#endif
