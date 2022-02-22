#include "Map.h"

Map::Map(float startPos, std::string stageName){
	//csvデータの読み取り開始位置
	posX = startPos;
	posY = startPos;
	//データをロード
	terrain.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_terrain.csv");
	enemyData.Load(CellSize, "ResourceFile/MapFile/" + stageName + "_enemy.csv");

	//敵出現射程非設定なら
	assert(spawnRangeX > 0 && spawnRangeY > 0);

	//初期化
	InitSpawnDic(spawnRangeX, spawnRangeY);

}

Map::~Map(){
	terrain.clear();
	enemyData.clear();
}

void Map::InitSpawnDic(int rangeCellX, int rangeCellY) {
	SpawnDic.clear();//一旦辞書をクリアするのでゲーム中の再設定も可(だが処理時間はかかる)
// 敵出現射程の辞書初期化
// ★ X = A cosθ Y = B sinθ(←楕円の方程式)
// ★ 楕円の半径 r = √(A×A×cosθ×cosθ + B×B×sinθ×sinθ)
// ★ xの2乗 + yの2乗 < rならば楕円の内側
	float A2 = (float)(rangeCellX * rangeCellX);
	float B2 = (float)(rangeCellY * rangeCellY);//2乗
	for (int x = -rangeCellX; x <= rangeCellX; x++)
	{
		for (int y = -rangeCellY; y <= rangeCellY; y++)
		{
			float theta = (float)std::atan2(y, x);//逆三角関数
			float cos_t = std::cos(theta);
			float sin_t = std::sin(theta);
			float r2 = A2 * cos_t + B2 * sin_t * sin_t;
			// ★ xの2乗 + yの2乗 < rならば楕円の内側
			//楕円の内側なら辞書SpawnDic[(x,y)] = true;として登録
			//【例】SpawnDic[(3,2)] = true;
			if (x * x + y * y <= r2) {}//SpawnDic[CellXY(x, y)] = true; 楕円の場合はこれを使って下の方をコメントアウト
			else SpawnDic[CellXY(x, y)] = true;	//【★四角形にしたいときはこちら】
		}
	}
}

void Map::Scroll(float deltaX, float deltaY, std::shared_ptr<GameObject> baseObj){
	bool isMoveCell = false;//移動しないなら非実行
	deltaSumX = deltaX;
	deltaSumY = deltaY;
	if (deltaSumX <= -CellSize || CellSize <= deltaSumX ||
		deltaSumY <= -CellSize || CellSize <= deltaSumY) {
		isMoveCell = true;
	}

	if (isMoveCell) {
		float deltaMoveX = deltaSumX;//溜まった移動量を移動量とする
		float deltaMoveY = deltaSumY;
		int deltaCellX = (int)deltaMoveX / CellSize;//移動量をマス化
		int deltaCellY = (int)deltaMoveY / CellSize;
		//誤差調整
		if     (deltaSumX <= -CellSize) deltaSumX += CellSize;
		else if (CellSize <= deltaSumX) deltaSumX -= CellSize;
		if     (deltaSumY <= -CellSize) deltaSumY += CellSize;
		else if (CellSize <= deltaSumY) deltaSumY -= CellSize;
		//目標マス(iter)は射程マスかどうか
		for (auto iter = SpawnDic.begin(); iter != SpawnDic.end(); iter++) {
			if (iter->second == true) {//射程内
				CellXY xy = iter->first;//マスを登録

				int searchX = xy.X + deltaCellX;//マス目をXYに分割
				int searchY = xy.Y + deltaCellY;
				//目標マスは登録済みか
				CellXY searchXY(searchX, searchY);
				if (SpawnDic.count(searchXY) == 1) {//map.count -> 見つかったか
					//登録済みなら次のマスへ
					if (SpawnDic[searchXY] == true) continue;
				}

				int mapX = 0, mapY = 0;
				if (baseObj != NULL) {//基準となるオブジェクトがあるならその位置を基準に
					mapX = searchX + (int)(baseObj->transform().position().x / CellSize);
					mapY = searchY + (int)(baseObj->transform().position().y / CellSize);
				}
				else {//基準オブジェクトの指定なければ現状Posを基準に
					mapX = searchX + (int)(posX / CellSize);
					mapY = searchY + (int)(posY / CellSize);
				}

				int objID = -1;
				if (0 <= mapY && 0 <= mapX && mapY < (int)enemyData.size() && mapX < (int)enemyData[mapY].size()) {
					objID = enemyData[mapY][mapX];//データアクセス成功でID取得
					enemyData[mapY][mapX] = -1;//取得済みデータ削除
					if (objID != -1)printfDx("newID %d(%d,%d)\n", objID, mapX, mapY);//デバッグ用()画面に映る
				}
				SpawnObject(mapX, mapY, objID);//マップデータ呼び出し
			}
		}
	}
	posX += deltaX;
	posY += deltaY;
}

void Map::SpawnObject(int mapX, int mapY, int objID){
	float spawnX = (float)(mapX * CellSize) + rotaGraphShiftX;//生成位置確定
	float spawnY = (float)(mapY * CellSize) + rotaGraphShiftY;

	if (objID == -1) return;//この下でID合わせて再生するものを追加
	else assert("敵ID" + std::to_string(objID) + "版の生成処理は未実装" == "");
}

int Map::GetTerrain(float worldX, float worldY){
	if (worldX < 0 || worldY < 0) return None;//負の座標は無視

	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//範囲外も無視

	return terrain[mapY][mapX];//地形IDを取り出し返却
}

int Map::SetTerrain(float worldX, float worldY, int Data){
	if (worldX < 0 || worldY < 0) return None;//負の座標は無視

	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	if (mapX >= terrain.Width || mapY >= terrain.Height) return None;//範囲外も無視

	terrain[mapY][mapX] = Data;//データ更新

	return terrain[mapY][mapX];//入れる場所を返却
}

void Map::DrawTerrain(){
	for (int cellX = 0; cellX <= terrain.Width - 1; cellX++)
	{
		for (int cellY = 0; cellY <= terrain.Height; cellY++)
		{
			float x = (float)(cellX * CellSize) + rotaGraphShiftX;//位置確定
			float y = (float)(cellY * CellSize) + rotaGraphShiftY;

			int id = -1;
			if (cellY < (int)terrain.size() && cellX < (int)terrain[cellY].size())//二次元配列範囲内のIDを読み取る
			{
				id = terrain[cellY][cellX];//データを保存
			}
			if (0 <= id && id < Image::mapChip.AllNum) {
				MyDraw::DrawDivRotaFloorF3D(Plane::Y, x, 0, y, 1.0, 0, Image::mapChip, id);
				if (id == 0) {
					MyDraw::DrawDivRotaDivBoxF3D(x, -0, y, 1.0, MyDraw::VGet(0, 0, 0), Image::mapChip, id);
				}
			}

			//DrawRotaGraphF(x, y, 1, 0, Image::mapChip.HandleArray[id], 1);//IDに従ってマップチップを描画
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