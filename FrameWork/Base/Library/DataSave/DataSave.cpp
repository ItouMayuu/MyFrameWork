#include "DataSave.h"
#include <stdio.h>
#pragma warning(disable : 4996)//fopen���g�������ꍇ�̃G���[��� 
errno_t error;//�G���[��Ԃ� ��fopen_s���g���ꍇ�Ɏg�p

#include "../../GameObject/Child/Player/Player.h"

void DataSave::Save(){
	//�ۑ��������f�[�^���������ލ\����
	SaveData_t Data = { 200,
						 10,
					   9999,
		                  3 };		//�{����GameManager�o�R�Ŏ����Ă��銴��
	//�o�C�i���t�@�C�����J�� fopen�֐�Mode�ꗗ http://www.bohyoh.com/CandCPP/C/Library/fopen.html
	FILE *fp = fopen("SaveData.txt", "wb");
	//NULL�Ȃ�G���[
	if (fp == NULL) {
		//�G���[����
		return;
	}

	//�t�@�C���ɒl���o��
	fwrite(&Data, sizeof(SaveData_t), 1, fp);
	//�t�@�C�������
	fclose(fp);
}

void DataSave::Load(){
	//�ǂݎ�����l��ۑ�����\����
	SaveData_t Data;
	//�o�C�i���t�@�C�����J��
	FILE* fp = fopen("SaveData.txt", "rb");
	//NULL�Ȃ�G���[
	if (fp == NULL) {
		//�G���[����
		return;
	}

	//�t�@�C������l��ǂݎ��
	fread(&Data, sizeof(SaveData_t), 1, fp);
	//�t�@�C�������
	fclose(fp);

	//�l�̊��蓖��
	AssignValue(Data);
}

void DataSave::AssignValue(SaveData_t& data){
	//�����Ń��[�h�����l�����蓖�Ă鏈��������
	gm.player_->load_status(data.HP, data.MP);
}
