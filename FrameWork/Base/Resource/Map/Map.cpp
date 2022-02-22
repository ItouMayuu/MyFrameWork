#include "Map.h"

Map::Map(float startPos, std::string stageName){
	//csv�f�[�^�̓ǂݎ��J�n�ʒu
	posX = startPos;
	posY = startPos;
	//�f�[�^�����[�h
	terrain.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_terrain.csv");
	enemyData.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_enemy.csv");

	//�G�o���˒���ݒ�Ȃ�
	assert(spawnRangeX > 0 && spawnRangeY > 0);

	//������
	InitSpawnDic(spawnRangeX, spawnRangeY);

}

Map::~Map(){
	terrain.clear();
	enemyData.clear();
}

void Map::InitSpawnDic(int rangeCellX, int rangeCellY) {
	SpawnDic.clear();//��U�������N���A����̂ŃQ�[�����̍Đݒ����(�����������Ԃ͂�����)
// �G�o���˒��̎���������
// �� X = A cos�� Y = B sin��(���ȉ~�̕�����)
// �� �ȉ~�̔��a r = ��(A�~A�~cos�Ɓ~cos�� + B�~B�~sin�Ɓ~sin��)
// �� x��2�� + y��2�� < r�Ȃ�Αȉ~�̓���
	float A2 = (float)(rangeCellX * rangeCellX);
	float B2 = (float)(rangeCellY * rangeCellY);//2��
	for (int x = -rangeCellX; x <= rangeCellX; x++)
	{
		for (int y = -rangeCellY; y <= rangeCellY; y++)
		{
			float theta = (float)std::atan2(y, x);//�t�O�p�֐�
			float cos_t = std::cos(theta);
			float sin_t = std::sin(theta);
			float r2 = A2 * cos_t + B2 * sin_t * sin_t;
			// �� x��2�� + y��2�� < r�Ȃ�Αȉ~�̓���
			//�ȉ~�̓����Ȃ玫��SpawnDic[(x,y)] = true;�Ƃ��ēo�^
			//�y��zSpawnDic[(3,2)] = true;
			if (x * x + y * y <= r2) {}//SpawnDic[CellXY(x, y)] = true; �ȉ~�̏ꍇ�͂�����g���ĉ��̕����R�����g�A�E�g
			else SpawnDic[CellXY(x, y)] = true;	//�y���l�p�`�ɂ������Ƃ��͂�����z
		}
	}
}

void Map::Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj){
	bool isMoveCell = false;//�ړ����Ȃ��Ȃ����s
	deltaSumX = deltaX;
	deltaSumY = deltaY;
	if (deltaSumX <= -CellSize || CellSize <= deltaSumX ||
		deltaSumY <= -CellSize || CellSize <= deltaSumY) {
		isMoveCell = true;
	}

	if (isMoveCell) {
		float deltaMoveX = deltaSumX;//���܂����ړ��ʂ��ړ��ʂƂ���
		float deltaMoveY = deltaSumY;
		int deltaCellX = (int)deltaMoveX / CellSize;//�ړ��ʂ��}�X��
		int deltaCellY = (int)deltaMoveY / CellSize;
		//�덷����
		if     (deltaSumX <= -CellSize) deltaSumX += CellSize;
		else if (CellSize <= deltaSumX) deltaSumX -= CellSize;
		if     (deltaSumY <= -CellSize) deltaSumY += CellSize;
		else if (CellSize <= deltaSumY) deltaSumY -= CellSize;
		//�ڕW�}�X(iter)�͎˒��}�X���ǂ���
		for (auto iter = SpawnDic.begin(); iter != SpawnDic.end(); iter++) {
			if (iter->second == true) {//�˒���
				CellXY xy = iter->first;//�}�X��o�^

				int searchX = xy.X + deltaCellX;//�}�X�ڂ�XY�ɕ���
				int searchY = xy.Y + deltaCellY;
				//�ڕW�}�X�͓o�^�ς݂�
				CellXY searchXY(searchX, searchY);
				if (SpawnDic.count(searchXY) == 1) {//map.count -> ����������
					//�o�^�ς݂Ȃ玟�̃}�X��
					if (SpawnDic[searchXY] == true) continue;
				}

				int mapX = 0, mapY = 0;
				if (baseObj != NULL) {//��ƂȂ�I�u�W�F�N�g������Ȃ炻�̈ʒu�����
					mapX = searchX + (int)(baseObj->transform().position().x / CellSize);
					mapY = searchY + (int)(baseObj->transform().position().y / CellSize);
				}
				else {//��I�u�W�F�N�g�̎w��Ȃ���Ό���Pos�����
					mapX = searchX + (int)(posX / CellSize);
					mapY = searchY + (int)(posY / CellSize);
				}

				int objID = -1;
				if (0 <= mapY && 0 <= mapX && mapY < (int)enemyData.size() && mapX < (int)enemyData[mapY].size()) {
					objID = enemyData[mapY][mapX];//�f�[�^�A�N�Z�X������ID�擾
					enemyData[mapY][mapX] = -1;//�擾�ς݃f�[�^�폜
					if (objID != -1)printfDx("newID %d(%d,%d)\n", objID, mapX, mapY);//�f�o�b�O�p()��ʂɉf��
				}
				SpawnObject(mapX, mapY, objID);//�}�b�v�f�[�^�Ăяo��
			}
		}
	}
	posX += deltaX;
	posY += deltaY;
}

void Map::SpawnObject(int mapX, int mapY, int objID){
	float spawnX = (float)(mapX * CellSize) + rotaGraphShiftX;//�����ʒu�m��
	float spawnY = (float)(mapY * CellSize) + rotaGraphShiftY;

	if (objID == -1) return;//���̉���ID���킹�čĐ�������̂�ǉ�
	else assert("�GID" + std::to_string(objID) + "�ł̐��������͖�����" == "");
}

int Map::GetTerrain(float worldX, float worldY){
	if (worldX < 0 || worldY < 0) return None;//���̍��W�͖���

	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//�͈͊O������

	return terrain[mapY][mapX];//�n�`ID�����o���ԋp
}

int Map::SetTerrain(float worldX, float worldY, int Data){
	if (worldX < 0 || worldY < 0) return None;//���̍��W�͖���

	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//�͈͊O������

	terrain[mapY][mapX] = Data;//�f�[�^�X�V

	return terrain[mapY][mapX];//�����ꏊ��ԋp
}

void Map::DrawTerrain(){
	for (int cellX = 0; cellX <= terrain.Width - 1; cellX++)
	{
		for (int cellY = 0; cellY <= terrain.Height; cellY++)
		{
			float x = (float)(cellX * CellSize) + rotaGraphShiftX;//�ʒu�m��
			float y = (float)(cellY * CellSize) + rotaGraphShiftY;

			int id = -1;
			if (cellY < (int)terrain.size() && cellX < (int)terrain[cellY].size())//�񎟌��z��͈͓���ID��ǂݎ��
			{
				id = terrain[cellY][cellX];//�f�[�^��ۑ�
			}
			if (0 <= id && id < Image::mapChip.AllNum) {
				MyDraw::DrawDivRotaFloorF3D(Plane::Y, x, 0, y, 1.0, 0, Image::mapChip, id);
				if (id == 0) {
					MyDraw::DrawDivRotaDivBoxF3D(x, -0, y, 1.0, MyDraw::VGet(0, 0, 0), Image::mapChip, id);
				}
			}

			//DrawRotaGraphF(x, y, 1, 0, Image::mapChip.HandleArray[id], 1);//ID�ɏ]���ă}�b�v�`�b�v��`��
		}
	}
}

bool Map::isWall(float worldX, float worldY){
	int terrainID = GetTerrain(worldX, worldY);

	for (auto i : Wall) {
		return terrainID == i;
	}
	return false;
}