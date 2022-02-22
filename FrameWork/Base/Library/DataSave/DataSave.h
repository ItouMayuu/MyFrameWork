#ifndef DATASAVE_H_
#define DATASAVE_H_

#include "../GameManager/GameManager.h"

//セーブするデータの構造体
typedef struct SaveData_t {
	int HP;		//HP
	int MP;		//MP
	int Money;	//所持金
	int Exp;
};

//バイナリファイルを使用したセーブデータ
class DataSave {
public:
	 DataSave() {};

	~DataSave() {};
	//データを保存
	void Save();
	//データをロード
	void Load();

private:
	GameManager& gm = GameManager::GetInstance();

	//ロードした値を割り当てる
	void AssignValue(SaveData_t& data);
};

#endif // !DATASAVE_H_
