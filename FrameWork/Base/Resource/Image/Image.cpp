#include "Image.h"
#include <string>

DivImage Image::mapChip{ 16,16,32,32 };//X�̐�, Y�̐�, X�̃T�C�Y, Y�̃T�C�Y
int Image::Boss{ -1 };
int Image::Box{ -1 };

//�摜�̓ǂݍ���
void Image::Init(){

	// ���������m�ی�div�摜�����[�h
	Image::LoadDivGraphs("ResourceFile/ImageFile/mapchip.png", mapChip);
	for (int i = 0; i < mapChip.AllNum; i++)
	{   // �摜�Ǎ����s
		if (mapChip.HandleArray[i] == -1) assert("�}�b�v�`�b�v" + std::to_string(i) + "�ԓǍ����s" == "");
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