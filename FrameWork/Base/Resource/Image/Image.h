#ifndef IMAGE_H_
#define IMAGE_H_

#include <assert.h>
#include <array>
#include <vector>
#include <DxLib.h>

//�����摜����舵���N���X
class DivImage {
public:
	int XNum = 0;//������
	int YNum = 0;
	int XSize = 0;
	int YSize = 0;
	int* HandleArray = NULL;
	int AllNum = 0;//�摜�̕�������

	DivImage(int XNum, int YNum, int XSize, int YSize) {
		//�������R���X�g���N�^
		this->XNum = XNum;
		this->YNum = YNum;
		this->XSize = XSize;
		this->YSize = YSize;
		AllNum = XNum * YNum;
		//�z����m�ۂ��� -1 �ŏ�����
		this->HandleArray = new int[AllNum];
		for (int i = 0; i < AllNum; i++) HandleArray[i] = -1;
		int* ary = HandleArray;

#ifdef _DEBUG
	//	ImagePowCheck((*this));
#endif
	};

	~DivImage(){
		//�������̉��
		if (this->HandleArray != NULL)
			delete[] this->HandleArray;
	};

#ifdef _DEBUG // �f�o�b�O�@�\
	// 2�ׂ̂��悩�v�Z
	bool is_pow2(unsigned int x) {
		return (x != 0) && (x & (x - 1)) == 0;
	}
	void ImagePowCheck(DivImage& divImage) {
		//3D�摜 = 2�ׂ̂���
		if (divImage.XSize > 0 && divImage.YSize > 0
			&& is_pow2(divImage.XSize) && is_pow2(divImage.YSize)) return;
		else assert("3D�Ŏg���摜�T�C�Y��2�ׂ̂���łȂ�" == "");
	}
#endif

	//�R�s�[�E�����private�ŋ֎~
private:
	//�R�s�[�R���X�g���N�^
	DivImage(const DivImage& divImage) {};

	//������Z�q
	DivImage& operator = (const DivImage & divImage){};
};

class Image {
public:
	Image() {};
	~Image() {};

	//�����摜�̓ǂݍ���
	static int LoadDivGraphs(const TCHAR* FileName, DivImage& divImage);
	static void Init();

	static DivImage mapChip;
	static int Boss;
	static int Box;
};

#endif // !IMAGE_H_
