#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <map>
#include <memory>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <DxLib.h>

#include "../../Library/Screen/Screen.h"
#include "../../Library/Gamemanager/GameManager.h"
#include "../../GameObject/Parent/GameObject.h"
#include "../Image/Image.h"
#include "../../Library/Csv/CsvStruct.h"
#include "../../Library/MyDraw/MyDraw.h"

class Map {
public:
	struct CellXY {
		int X = 0;
		int Y = 0;
		CellXY(int X, int Y) : X{ X }, Y{ Y }{};
		bool operator < (const CellXY& otherXY) const {
			if (Y < otherXY.Y) return true;
			if (Y > otherXY.Y) return false;
			if (X < otherXY.X) return true;
			if (X > otherXY.X) return false;
			return false;
		}
	};
	//コンストラクタ
	Map(float startPos, std::string stageName);
	//デストラクタ
	~Map();
	//位置の更新
	void Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj = NULL);
	//
	int GetTerrain(float worldX, float worldY);
	//
	int SetTerrain(float worldX, float worldY, int Data);
	//
	void DrawTerrain();
	//
	bool isWall(float worldX, float worldY);

	//1マスのサイズ
	const int CellSize = 32;

	CsvInt terrain;
	CsvInt enemyData;

private:

	GameManager& gm = GameManager::GetInstance();

	const bool spawnIsOval = false;//楕円形で敵をspawn -> true

	//Cellごとに定義
	const int None = -1;
	//壁判定させるブロックを定義
	std::vector<int> Wall{ 0 };


	//敵が読み込まれる範囲
	int spawnRangeX = 30;
	int spawnRangeY = 30;

	//連想配列 < 位置 , 出現flag >
	std::map<CellXY, bool> SpawnDic;

	//中心から描画 -> 中心を特定
	float rotaGraphShiftX = CellSize / 2.0f;
	float rotaGraphShiftY = CellSize / 2.0f;

	float posX = 0;
	float posY = 0;

	float deltaSumX = 0;
	float deltaSumY = 0;

	void InitSpawnDic(int rangeCellX, int rangeCellY);

	void SpawnObject(int mapX, int mapY, int objID);
};

#endif // !MAP_H_
