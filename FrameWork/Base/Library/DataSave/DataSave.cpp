#include "DataSave.h"
#include <stdio.h>
#pragma warning(disable : 4996)//fopenが使いたい場合のエラー回避 
errno_t error;//エラーを返す ※fopen_sを使う場合に使用

#include "../../GameObject/Child/Player/Player.h"

void DataSave::Save(){
	//保存したいデータを書きこむ構造体
	SaveData_t Data = { 200,
						 10,
					   9999,
		                  3 };		//本来はGameManager経由で持ってくる感じ
	//バイナリファイルを開く fopen関数Mode一覧 http://www.bohyoh.com/CandCPP/C/Library/fopen.html
	FILE *fp = fopen("SaveData.txt", "wb");
	//NULLならエラー
	if (fp == NULL) {
		//エラー処理
		return;
	}

	//ファイルに値を出力
	fwrite(&Data, sizeof(SaveData_t), 1, fp);
	//ファイルを閉じる
	fclose(fp);
}

void DataSave::Load(){
	//読み取った値を保存する構造体
	SaveData_t Data;
	//バイナリファイルを開く
	FILE* fp = fopen("SaveData.txt", "rb");
	//NULLならエラー
	if (fp == NULL) {
		//エラー処理
		return;
	}

	//ファイルから値を読み取る
	fread(&Data, sizeof(SaveData_t), 1, fp);
	//ファイルを閉じる
	fclose(fp);

	//値の割り当て
	AssignValue(Data);
}

void DataSave::AssignValue(SaveData_t& data){
	//ここでロードした値を割り当てる処理を書く
	gm.player_->load_status(data.HP, data.MP);
}
