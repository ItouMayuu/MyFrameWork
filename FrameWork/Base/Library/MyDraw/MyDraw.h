#ifndef MYDRAW_H_
#define MYDRAW_H_

struct Vec3;
class Transform;
class DivImage;

#include <DxLib.h>

//XYZ•½–Ê‚Ìw’è
enum class Plane {
	X = 1,
	Y,
	Z
};

class MyDraw {
public:
	static Vec3 XYZ_ARROW;
	static bool IsReverseX_Tex;
	static bool IsReverseY_Tex;
	static bool IsReverseZ_Tex;

	//‰Šú‰»
	static void Init();
	//3D‹óŠÔ‚Å‹…‚ğ•`‰æ
	static int DrawSphere3D(Vec3 center, float r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag);
	//3D‹óŠÔ‚Åü‚ğ•`‰æ
	static int DrawLine3D(Vec3 pos1, Vec3 pos2, unsigned int color);
	//À•WŒn‚Ì“ˆê
	static Vec3 VGet(float x, float y, float z);
	//3D‹óŠÔ‚Åƒ{ƒbƒNƒX‚ğ•`‰æ
	static void DrawDivRotaDivBoxF3D(float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag = true, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);
	//3D‹óŠÔ‚Å‰æ‘œ•`‰æ
	static int DrawDivRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag = true, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);
	//3D‹óŠÔ‚Å°‚Ì•`‰æ
	static int DrawDivRotaFloorF3D(Plane plane, float xf, float yf, float zf, double ExRate, double Angle, DivImage& divImage, int id, int TransFlag = true, int ReverseXFlag = false, int ReverseYFlag = false, int ReverseZFlag = false);

	//3Dƒ‚ƒfƒ‹‚Ì•`‰æ
	static int Draw3DModel(int model, Transform transform);

private:
	//•½–Ê‚É‡‚í‚¹‚Ä‰ñ“]²‚ğ‘I‘ğ
	static Vec3 VecAngle(Plane plane, double angle);
};

#endif // !MY_DRAW_H_
