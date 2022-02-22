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
	//�R���X�g���N�^
	Map(float startPos, std::string stageName);
	//�f�X�g���N�^
	~Map();
	//�ʒu�̍X�V
	void Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj = NULL);
	//
	int GetTerrain(float worldX, float worldY);
	//
	int SetTerrain(float worldX, float worldY, int Data);
	//
	void DrawTerrain();
	//
	bool isWall(float worldX, float worldY);

	//1�}�X�̃T�C�Y
	const int CellSize = 32;

	CsvInt terrain;
	CsvInt enemyData;

private:

	GameManager& gm = GameManager::GetInstance();

	const bool spawnIsOval = false;//�ȉ~�`�œG��spawn -> true

	//Cell���Ƃɒ�`
	const int None = -1;
	//�ǔ��肳����u���b�N���`
	std::vector<int> Wall{ 0 };


	//�G���ǂݍ��܂��͈�
	int spawnRangeX = 30;
	int spawnRangeY = 30;

	//�A�z�z�� < �ʒu , �o��flag >
	std::map<CellXY, bool> SpawnDic;

	//���S����`�� -> ���S�����
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
