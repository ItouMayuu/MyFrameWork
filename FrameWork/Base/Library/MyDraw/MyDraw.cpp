#include "MyDraw.h"
#include "../Transform/Transform.h"
#include "../../Resource/Image/Image.h"

Vec3 MyDraw::XYZ_ARROW = VGet(1, -1, 1);
bool MyDraw::IsReverseX_Tex{ false };
bool MyDraw::IsReverseY_Tex{ false };
bool MyDraw::IsReverseZ_Tex{ false };

void MyDraw::Init() {
	// Zバッファを使用(3D空間で前後関係を意識しないで描画)
	SetUseZBuffer3D(TRUE);
	// Zバッファに書き込み(色情報以外も記録)
	SetWriteZBuffer3D(TRUE);
}

					   // 中心座標 , 半径 , ポリゴンの細かさ , ディフューズカラー , スペキュラーカラー , 塗りつぶすか
int MyDraw::DrawSphere3D(Vec3 center, float r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag){
	return DxLib::DrawSphere3D(DxLib::VGet(center.x, center.y, center.z), r, DivNum, DifColor, SpcColor, FillFlag);
}
					   // 始点 , 終点 , 線の色
int MyDraw::DrawLine3D(Vec3 pos1, Vec3 pos2, unsigned int color){
	return DxLib::DrawLine3D(DxLib::VGet(pos1.x, pos1.y, pos1.z), DxLib::VGet(pos2.x, pos2.y, pos2.z), color);
}

Vec3 MyDraw::VGet(float x, float y, float z){
	if (XYZ_ARROW.x == 1 && XYZ_ARROW.y == 1 && XYZ_ARROW.z == 1) {
		//DX 2D描画座標系
		return VGet(x, y, z);
	}
	else if (XYZ_ARROW.x == 1 && XYZ_ARROW.y == -1 && XYZ_ARROW.z == 1) {
		//DX 3D描画座標系
		return VGet(x, -y, z);
	}

	Vec3 result;
	if (XYZ_ARROW.x == 1) result.x = x;
	else result.x = -x;
	if (XYZ_ARROW.y == 1) result.y = y;
	else result.y = -y;
	if (XYZ_ARROW.z == 1) result.z = z;
	else result.z = -z;

	return result;
}

void MyDraw::DrawDivRotaDivBoxF3D(float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag){
	float imageWidth  = (float)divImage.XSize * (float)ExRate;
	float imageHeight = (float)divImage.YSize * (float)ExRate;
	//Y軸調整
	float adjustY = (((float)ExRate - 1.0f) * 16.0f);

	//サイコロの6面を描く
	DrawDivRotaGraphF3D(Plane::Y, xf, yf - (imageHeight / 2) + adjustY, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::Y, xf, yf + (imageHeight / 2) + adjustY, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	// X方向の裏側は左右反転
	DrawDivRotaGraphF3D(Plane::X, xf - (imageWidth / 2), yf + adjustY, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, !ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::X, xf + (imageWidth / 2), yf + adjustY, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	// Z方向の裏側は左右反転
	DrawDivRotaGraphF3D(Plane::Z, xf, yf + adjustY, zf - (imageHeight / 2), ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::Z, xf, yf + adjustY, zf + (imageHeight / 2), ExRate, Angle, divImage, id, TransFlag, !ReverseXFlag, ReverseYFlag, ReverseZFlag);
	return;
}

int MyDraw::DrawDivRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag){
	//右手・左手系とY軸矢印の方向に従い座標を変換
	Vec3 CONVERT_XYZ = Vec3(xf, yf, zf);
	float Xf = CONVERT_XYZ.x, Yf = CONVERT_XYZ.y, Zf = CONVERT_XYZ.z;

	if (id < 0 && divImage.AllNum <= id) { assert("div画像ID指定範囲外" == ""); return -1; }

	int imageWidth  = divImage.XSize;
	int imageHeight = divImage.YSize;
	float u_X0 = 0.0F, v_Y0 = 0.0F; //点Vertex[0]のuとvの値
	float u_X3 = 1.0F, v_Y3 = 1.0F; //点Vertex[3]のuとvの値
	if (divImage.XNum > 1 || divImage.YNum > 1)
	{   // div分割画像の分割位置確定のため横uと縦vの値を計算
		int divX = id % divImage.XNum;//分割X列番号
		int divY = id / divImage.XNum;//分割Y行番号
		u_X0 = (float)divX / (float)(divImage.XNum);
		v_Y0 = (float)divY / (float)(divImage.YNum);
		u_X3 = (float)(divX + 1) / (float)(divImage.XNum);
		v_Y3 = (float)(divY + 1) / (float)(divImage.YNum);
	}

	// 【拡大縮小率ExRate】をかけて画像サイズを再計算
	imageWidth = (int)(imageWidth * ExRate);  // 拡大縮小した画像の幅
	imageHeight = (int)(imageHeight * ExRate);// 拡大縮小した画像の高さ
	float halfWidth = (float)(imageWidth / 2);//画像幅の1/2(先に計算し使いまわして処理削減)
	float halfHeight = (float)(imageHeight / 2);//画像高さの1/2(先に計算し使いまわして処理削減)
	//【テクスチャ反転処理】幅halfWidthと高さhalfHeightをマイナスにすることで反転
	// ★ReverseXFlagとIsReverseX_Texture両方反転は【反転の反転で=反転しない!】
	// 【反転の反転で=反転しない!】は★XOR【排他的論理和 ^ 演算子】
	if ((IsReverseX_Tex ^ (ReverseXFlag == TRUE))
		&& (plane == Plane::Y || plane == Plane::Z))
	{   // マイナス幅でテクスチャ反転
		halfWidth = -halfWidth;
	}
	if ((IsReverseY_Tex ^ (ReverseYFlag == TRUE))
		&& (plane == Plane::X || plane == Plane::Z))
	{   // マイナス幅でテクスチャ反転
		halfHeight = -halfHeight;
	}
	if (IsReverseZ_Tex ^ (ReverseZFlag == TRUE))
	{   // マイナス幅でテクスチャ反転
		if (plane == Plane::X) halfWidth = -halfWidth;
		if (plane == Plane::Y) halfHeight = -halfHeight;
	}

	// ★CGの【最小単位は三角形】2Dはドットの集合で描くが【CGは三角形の集合で描く】
	VERTEX_3D Vertex[6]; // ポリゴン２枚なので、頂点は６個(三角3点×2)

	// ★頂点情報のセット
	{   // Plane=X なら X平面に(Y,Z) = (yf,zf)中心に描画
		// Plane=Y なら Y平面に(X,Z) = (xf,zf)中心に描画
		// Plane=Z なら Z平面に(X,Y) = (xf,yf)中心に描画
		// 回転は以下リンク参照
		// https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=past&no=2749
		MATRIX TransformMatrix;
		// 回転( x, y, z軸回転の順に回転した後、座標移動行列により平行移動)
		// ★★MMultは行列の乗算【乗算した順にx軸回転→y軸回転→z軸回転→平行移動】
		//★【複数軸回転は頭が混乱するのでクォータニオンをつかうやり方もある】
		TransformMatrix = MGetRotX(Angle.x);
		TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
		TransformMatrix = MMult(TransformMatrix, MGetRotZ(Angle.z));
		//★【座標移動行列により移動】
		TransformMatrix = MMult(TransformMatrix, MGetTranslate(DxLib::VGet(Xf, Yf, Zf)));

		if (plane == Plane::X)
		{   //座標固定平面→→→→→→→→→↓X平面指定
			Vertex[0].pos = VTransform(DxLib::VGet(0.0F, +halfHeight, -halfWidth), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(0.0F, +halfHeight, +halfWidth), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(0.0F, -halfHeight, -halfWidth), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(0.0F, -halfHeight, +halfWidth), TransformMatrix);
		}
		else if (plane == Plane::Y)
		{   //座標固定平面→→→→→→→→→→→→→→→→↓Y平面指定
			Vertex[0].pos = VTransform(DxLib::VGet(-halfWidth, 0.0F, +halfHeight), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(+halfWidth, 0.0F, +halfHeight), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(-halfWidth, 0.0F, -halfHeight), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(+halfWidth, 0.0F, -halfHeight), TransformMatrix);
		}
		else // if (plane == Plane::Z)
		{   //座標固定平面→→→→→→→→→→→→→→→→→→→→→→→→→↓Z平面指定
			Vertex[0].pos = VTransform(DxLib::VGet(-halfWidth, +halfHeight, 0.0F), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(+halfWidth, +halfHeight, 0.0F), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(-halfWidth, -halfHeight, 0.0F), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(+halfWidth, -halfHeight, 0.0F), TransformMatrix);
		}
		Vertex[4].pos = Vertex[2].pos; // 点2と点4は同じ位置
		Vertex[5].pos = Vertex[1].pos; // 点1と点5は同じ位置
		//↑点0 点1&5 点4&2 点3 の4点の四角形を描く

		// ★div分割画像を考慮に入れて【UV展開】切り出し位置を0.0～1.0で指定
		Vertex[0].u = u_X0; Vertex[0].v = v_Y0;
		Vertex[1].u = u_X3; Vertex[1].v = v_Y0;
		Vertex[2].u = u_X0; Vertex[2].v = v_Y3;
		Vertex[3].u = u_X3; Vertex[3].v = v_Y3;
		Vertex[4].u = u_X0; Vertex[4].v = v_Y3;
		Vertex[5].u = u_X3; Vertex[5].v = v_Y0;

		// 輝度(明るさ)は全地点100%
		Vertex[0].r = Vertex[0].g = Vertex[0].b = 255;
		Vertex[1].r = Vertex[1].g = Vertex[1].b = 255;
		Vertex[2].r = Vertex[2].g = Vertex[2].b = 255;
		Vertex[3].r = Vertex[3].g = Vertex[3].b = 255;
		Vertex[4].r = Vertex[4].g = Vertex[4].b = 255;
		Vertex[5].r = Vertex[5].g = Vertex[5].b = 255;

		// a(アルファ不透明度) も最大値(255=不透明 0=透明)
		Vertex[0].a = 255; Vertex[1].a = 255;
		Vertex[2].a = 255;
		Vertex[5].a = 255;
		Vertex[4].a = 255; Vertex[3].a = 255;
		//↑上の順の点で点0 点1&5 点4&2 点3 の4点の四角形を描く
	}

	// ポリゴンを２枚描画
	return DrawPolygon3D(Vertex, 2, divImage.HandleArray[id], TransFlag);
}

int MyDraw::DrawDivRotaFloorF3D(Plane plane, float xf, float yf, float zf, double ExRate, double Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag){
	Vec3 AngleVec = VecAngle(plane, Angle);
	int imageHeight = divImage.YSize;
												                     //角度だけ↓VECTOR化
	return DrawDivRotaGraphF3D(plane, xf, yf - imageHeight / 2, zf, ExRate, AngleVec, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
}

Vec3 MyDraw::VecAngle(Plane plane, double angle){
	Vec3 angleVec = VGet(0, 0, 0);

	if (plane == Plane::X) angleVec.x = (float)angle;
	else if (plane == Plane::Y) angleVec.y = (float)angle;
	else if (plane == Plane::Z) angleVec.z = (float)angle;

	return angleVec;
}
