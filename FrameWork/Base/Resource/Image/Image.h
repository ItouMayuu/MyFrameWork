#ifndef IMAGE_H_
#define IMAGE_H_

#include <assert.h>
#include <array>
#include <vector>
#include <DxLib.h>

//分割画像を取り扱うクラス
class DivImage {
public:
	int XNum = 0;//分割数
	int YNum = 0;
	int XSize = 0;
	int YSize = 0;
	int* HandleArray = NULL;
	int AllNum = 0;//画像の分割総数

	DivImage(int XNum, int YNum, int XSize, int YSize) {
		//初期化コンストラクタ
		this->XNum = XNum;
		this->YNum = YNum;
		this->XSize = XSize;
		this->YSize = YSize;
		AllNum = XNum * YNum;
		//配列を確保して -1 で初期化
		this->HandleArray = new int[AllNum];
		for (int i = 0; i < AllNum; i++) HandleArray[i] = -1;
		int* ary = HandleArray;

#ifdef _DEBUG
	//	ImagePowCheck((*this));
#endif
	};

	~DivImage(){
		//メモリの解放
		if (this->HandleArray != NULL)
			delete[] this->HandleArray;
	};

#ifdef _DEBUG // デバッグ機能
	// 2のべき乗か計算
	bool is_pow2(unsigned int x) {
		return (x != 0) && (x & (x - 1)) == 0;
	}
	void ImagePowCheck(DivImage& divImage) {
		//3D画像 = 2のべき乗
		if (divImage.XSize > 0 && divImage.YSize > 0
			&& is_pow2(divImage.XSize) && is_pow2(divImage.YSize)) return;
		else assert("3Dで使う画像サイズが2のべき乗でない" == "");
	}
#endif

	//コピー・代入をprivateで禁止
private:
	//コピーコンストラクタ
	DivImage(const DivImage& divImage) {};

	//代入演算子
	DivImage& operator = (const DivImage & divImage){};
};

class Image {
public:
	Image() {};
	~Image() {};

	//分割画像の読み込み
	static int LoadDivGraphs(const TCHAR* FileName, DivImage& divImage);
	static void Init();

	static DivImage mapChip;
	static int Boss;
	static int Box;
};

#endif // !IMAGE_H_
