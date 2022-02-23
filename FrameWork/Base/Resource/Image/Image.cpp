#include "Image.h"
#include <string>

DivImage Image::mapChip{ 16,16,32,32 };//Xの数, Yの数, Xのサイズ, Yのサイズ
int Image::Boss{ -1 };
int Image::Box{ -1 };

//画像の読み込み
void Image::Init(){

	// メモリを確保後div画像をロード
	Image::LoadDivGraphs("ResourceFile/ImageFile/mapchip.png", mapChip);
	for (int i = 0; i < mapChip.AllNum; i++)
	{   // 画像読込失敗
		if (mapChip.HandleArray[i] == -1) assert("マップチップ" + std::to_string(i) + "番読込失敗" == "");
	}

	Boss = LoadGraph("ResourceFile/ImageFile/boss1.png");
	assert(Boss != -1);

	Box = MV1LoadModel("ResourceFile/ImageFile/box.mv1");
	assert(Box != -1);
}

int Image::LoadDivGraphs(const TCHAR* FileName, DivImage& divImage){
	return DxLib::LoadDivGraph(FileName, divImage.XNum * divImage.YNum, divImage.XNum, divImage.YNum,
		divImage.XSize, divImage.YSize, divImage.HandleArray);
}