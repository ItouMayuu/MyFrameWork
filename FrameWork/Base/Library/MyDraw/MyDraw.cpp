#include "MyDraw.h"
#include "../Transform/Transform.h"
#include "../../Resource/Image/Image.h"

Vec3 MyDraw::XYZ_ARROW = VGet(1, -1, 1);
bool MyDraw::IsReverseX_Tex{ false };
bool MyDraw::IsReverseY_Tex{ false };
bool MyDraw::IsReverseZ_Tex{ false };

void MyDraw::Init() {
	// Z�o�b�t�@���g�p(3D��ԂőO��֌W���ӎ����Ȃ��ŕ`��)
	SetUseZBuffer3D(TRUE);
	// Z�o�b�t�@�ɏ�������(�F���ȊO���L�^)
	SetWriteZBuffer3D(TRUE);
}

					   // ���S���W , ���a , �|���S���ׂ̍��� , �f�B�t���[�Y�J���[ , �X�y�L�����[�J���[ , �h��Ԃ���
int MyDraw::DrawSphere3D(Vec3 center, float r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag){
	return DxLib::DrawSphere3D(DxLib::VGet(center.x, center.y, center.z), r, DivNum, DifColor, SpcColor, FillFlag);
}
					   // �n�_ , �I�_ , ���̐F
int MyDraw::DrawLine3D(Vec3 pos1, Vec3 pos2, unsigned int color){
	return DxLib::DrawLine3D(DxLib::VGet(pos1.x, pos1.y, pos1.z), DxLib::VGet(pos2.x, pos2.y, pos2.z), color);
}

Vec3 MyDraw::VGet(float x, float y, float z){
	if (XYZ_ARROW.x == 1 && XYZ_ARROW.y == 1 && XYZ_ARROW.z == 1) {
		//DX 2D�`����W�n
		return VGet(x, y, z);
	}
	else if (XYZ_ARROW.x == 1 && XYZ_ARROW.y == -1 && XYZ_ARROW.z == 1) {
		//DX 3D�`����W�n
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
	//Y������
	float adjustY = (((float)ExRate - 1.0f) * 16.0f);

	//�T�C�R����6�ʂ�`��
	DrawDivRotaGraphF3D(Plane::Y, xf, yf - (imageHeight / 2) + adjustY, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::Y, xf, yf + (imageHeight / 2) + adjustY, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	// X�����̗����͍��E���]
	DrawDivRotaGraphF3D(Plane::X, xf - (imageWidth / 2), yf + adjustY, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, !ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::X, xf + (imageWidth / 2), yf + adjustY, zf, ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	// Z�����̗����͍��E���]
	DrawDivRotaGraphF3D(Plane::Z, xf, yf + adjustY, zf - (imageHeight / 2), ExRate, Angle, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
	DrawDivRotaGraphF3D(Plane::Z, xf, yf + adjustY, zf + (imageHeight / 2), ExRate, Angle, divImage, id, TransFlag, !ReverseXFlag, ReverseYFlag, ReverseZFlag);
	return;
}

int MyDraw::DrawDivRotaGraphF3D(Plane plane, float xf, float yf, float zf, double ExRate, Vec3 Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag){
	//�E��E����n��Y�����̕����ɏ]�����W��ϊ�
	Vec3 CONVERT_XYZ = Vec3(xf, yf, zf);
	float Xf = CONVERT_XYZ.x, Yf = CONVERT_XYZ.y, Zf = CONVERT_XYZ.z;

	if (id < 0 && divImage.AllNum <= id) { assert("div�摜ID�w��͈͊O" == ""); return -1; }

	int imageWidth  = divImage.XSize;
	int imageHeight = divImage.YSize;
	float u_X0 = 0.0F, v_Y0 = 0.0F; //�_Vertex[0]��u��v�̒l
	float u_X3 = 1.0F, v_Y3 = 1.0F; //�_Vertex[3]��u��v�̒l
	if (divImage.XNum > 1 || divImage.YNum > 1)
	{   // div�����摜�̕����ʒu�m��̂��߉�u�Əcv�̒l���v�Z
		int divX = id % divImage.XNum;//����X��ԍ�
		int divY = id / divImage.XNum;//����Y�s�ԍ�
		u_X0 = (float)divX / (float)(divImage.XNum);
		v_Y0 = (float)divY / (float)(divImage.YNum);
		u_X3 = (float)(divX + 1) / (float)(divImage.XNum);
		v_Y3 = (float)(divY + 1) / (float)(divImage.YNum);
	}

	// �y�g��k����ExRate�z�������ĉ摜�T�C�Y���Čv�Z
	imageWidth = (int)(imageWidth * ExRate);  // �g��k�������摜�̕�
	imageHeight = (int)(imageHeight * ExRate);// �g��k�������摜�̍���
	float halfWidth = (float)(imageWidth / 2);//�摜����1/2(��Ɍv�Z���g���܂킵�ď����팸)
	float halfHeight = (float)(imageHeight / 2);//�摜������1/2(��Ɍv�Z���g���܂킵�ď����팸)
	//�y�e�N�X�`�����]�����z��halfWidth�ƍ���halfHeight���}�C�i�X�ɂ��邱�ƂŔ��]
	// ��ReverseXFlag��IsReverseX_Texture�������]�́y���]�̔��]��=���]���Ȃ�!�z
	// �y���]�̔��]��=���]���Ȃ�!�z�́�XOR�y�r���I�_���a ^ ���Z�q�z
	if ((IsReverseX_Tex ^ (ReverseXFlag == TRUE))
		&& (plane == Plane::Y || plane == Plane::Z))
	{   // �}�C�i�X���Ńe�N�X�`�����]
		halfWidth = -halfWidth;
	}
	if ((IsReverseY_Tex ^ (ReverseYFlag == TRUE))
		&& (plane == Plane::X || plane == Plane::Z))
	{   // �}�C�i�X���Ńe�N�X�`�����]
		halfHeight = -halfHeight;
	}
	if (IsReverseZ_Tex ^ (ReverseZFlag == TRUE))
	{   // �}�C�i�X���Ńe�N�X�`�����]
		if (plane == Plane::X) halfWidth = -halfWidth;
		if (plane == Plane::Y) halfHeight = -halfHeight;
	}

	// ��CG�́y�ŏ��P�ʂ͎O�p�`�z2D�̓h�b�g�̏W���ŕ`�����yCG�͎O�p�`�̏W���ŕ`���z
	VERTEX_3D Vertex[6]; // �|���S���Q���Ȃ̂ŁA���_�͂U��(�O�p3�_�~2)

	// �����_���̃Z�b�g
	{   // Plane=X �Ȃ� X���ʂ�(Y,Z) = (yf,zf)���S�ɕ`��
		// Plane=Y �Ȃ� Y���ʂ�(X,Z) = (xf,zf)���S�ɕ`��
		// Plane=Z �Ȃ� Z���ʂ�(X,Y) = (xf,yf)���S�ɕ`��
		// ��]�͈ȉ������N�Q��
		// https://dxlib.xsrv.jp/cgi/patiobbs/patio.cgi?mode=past&no=2749
		MATRIX TransformMatrix;
		// ��]( x, y, z����]�̏��ɉ�]������A���W�ړ��s��ɂ�蕽�s�ړ�)
		// ����MMult�͍s��̏�Z�y��Z��������x����]��y����]��z����]�����s�ړ��z
		//���y��������]�͓�����������̂ŃN�H�[�^�j�I������������������z
		TransformMatrix = MGetRotX(Angle.x);
		TransformMatrix = MMult(TransformMatrix, MGetRotY(Angle.y));
		TransformMatrix = MMult(TransformMatrix, MGetRotZ(Angle.z));
		//���y���W�ړ��s��ɂ��ړ��z
		TransformMatrix = MMult(TransformMatrix, MGetTranslate(DxLib::VGet(Xf, Yf, Zf)));

		if (plane == Plane::X)
		{   //���W�Œ蕽�ʁ�������������������X���ʎw��
			Vertex[0].pos = VTransform(DxLib::VGet(0.0F, +halfHeight, -halfWidth), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(0.0F, +halfHeight, +halfWidth), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(0.0F, -halfHeight, -halfWidth), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(0.0F, -halfHeight, +halfWidth), TransformMatrix);
		}
		else if (plane == Plane::Y)
		{   //���W�Œ蕽�ʁ���������������������������������Y���ʎw��
			Vertex[0].pos = VTransform(DxLib::VGet(-halfWidth, 0.0F, +halfHeight), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(+halfWidth, 0.0F, +halfHeight), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(-halfWidth, 0.0F, -halfHeight), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(+halfWidth, 0.0F, -halfHeight), TransformMatrix);
		}
		else // if (plane == Plane::Z)
		{   //���W�Œ蕽�ʁ���������������������������������������������������Z���ʎw��
			Vertex[0].pos = VTransform(DxLib::VGet(-halfWidth, +halfHeight, 0.0F), TransformMatrix);
			Vertex[1].pos = VTransform(DxLib::VGet(+halfWidth, +halfHeight, 0.0F), TransformMatrix);
			Vertex[2].pos = VTransform(DxLib::VGet(-halfWidth, -halfHeight, 0.0F), TransformMatrix);
			Vertex[3].pos = VTransform(DxLib::VGet(+halfWidth, -halfHeight, 0.0F), TransformMatrix);
		}
		Vertex[4].pos = Vertex[2].pos; // �_2�Ɠ_4�͓����ʒu
		Vertex[5].pos = Vertex[1].pos; // �_1�Ɠ_5�͓����ʒu
		//���_0 �_1&5 �_4&2 �_3 ��4�_�̎l�p�`��`��

		// ��div�����摜���l���ɓ���āyUV�W�J�z�؂�o���ʒu��0.0�`1.0�Ŏw��
		Vertex[0].u = u_X0; Vertex[0].v = v_Y0;
		Vertex[1].u = u_X3; Vertex[1].v = v_Y0;
		Vertex[2].u = u_X0; Vertex[2].v = v_Y3;
		Vertex[3].u = u_X3; Vertex[3].v = v_Y3;
		Vertex[4].u = u_X0; Vertex[4].v = v_Y3;
		Vertex[5].u = u_X3; Vertex[5].v = v_Y0;

		// �P�x(���邳)�͑S�n�_100%
		Vertex[0].r = Vertex[0].g = Vertex[0].b = 255;
		Vertex[1].r = Vertex[1].g = Vertex[1].b = 255;
		Vertex[2].r = Vertex[2].g = Vertex[2].b = 255;
		Vertex[3].r = Vertex[3].g = Vertex[3].b = 255;
		Vertex[4].r = Vertex[4].g = Vertex[4].b = 255;
		Vertex[5].r = Vertex[5].g = Vertex[5].b = 255;

		// a(�A���t�@�s�����x) ���ő�l(255=�s���� 0=����)
		Vertex[0].a = 255; Vertex[1].a = 255;
		Vertex[2].a = 255;
		Vertex[5].a = 255;
		Vertex[4].a = 255; Vertex[3].a = 255;
		//����̏��̓_�œ_0 �_1&5 �_4&2 �_3 ��4�_�̎l�p�`��`��
	}

	// �|���S�����Q���`��
	return DrawPolygon3D(Vertex, 2, divImage.HandleArray[id], TransFlag);
}

int MyDraw::DrawDivRotaFloorF3D(Plane plane, float xf, float yf, float zf, double ExRate, double Angle, DivImage& divImage, int id, int TransFlag, int ReverseXFlag, int ReverseYFlag, int ReverseZFlag){
	Vec3 AngleVec = VecAngle(plane, Angle);
	int imageHeight = divImage.YSize;
												                     //�p�x������VECTOR��
	return DrawDivRotaGraphF3D(plane, xf, yf - imageHeight / 2, zf, ExRate, AngleVec, divImage, id, TransFlag, ReverseXFlag, ReverseYFlag, ReverseZFlag);
}

Vec3 MyDraw::VecAngle(Plane plane, double angle){
	Vec3 angleVec = VGet(0, 0, 0);

	if (plane == Plane::X) angleVec.x = (float)angle;
	else if (plane == Plane::Y) angleVec.y = (float)angle;
	else if (plane == Plane::Z) angleVec.z = (float)angle;

	return angleVec;
}
