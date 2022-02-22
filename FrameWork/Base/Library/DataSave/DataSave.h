#ifndef DATASAVE_H_
#define DATASAVE_H_

#include "../GameManager/GameManager.h"

//�Z�[�u����f�[�^�̍\����
typedef struct SaveData_t {
	int HP;		//HP
	int MP;		//MP
	int Money;	//������
	int Exp;
};

//�o�C�i���t�@�C�����g�p�����Z�[�u�f�[�^
class DataSave {
public:
	 DataSave() {};

	~DataSave() {};
	//�f�[�^��ۑ�
	void Save();
	//�f�[�^�����[�h
	void Load();

private:
	GameManager& gm = GameManager::GetInstance();

	//���[�h�����l�����蓖�Ă�
	void AssignValue(SaveData_t& data);
};

#endif // !DATASAVE_H_
