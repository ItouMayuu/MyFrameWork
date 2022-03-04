#include "SampleScene.h"

#include "../../Library/GameManager/GameObjectManager/GameObjectManager.h"
#include "../../GameObject/Child/Player/Player.h"
#include "../../Library/Transform/Vec2/Vec2.h"
#include "../../Library/Transform/Vec3/Vec3.h"
#include "../../Library/MyMath/MyMath.h"
#include "../../Library/DataSave/DataSave.h"
#include "../../Resource/Map/Map.h"

#include "../../GameObject/Child/TestObject/TestObject.h"

#include <string>
#include "DxLib.h"

SampleScene::SampleScene(){
}

void SampleScene::init() {
	//仮にプレイヤー追加
	gm.player_ = std::make_shared<Player>(Vec3{200,200,200});
	//ゲームオブジェクトマネージャーにも登録 ※操作はgm.player_で大丈夫
	gm.game_object_manager_->add(gm.player_);
	gm.game_object_manager_->add(std::make_shared<TestObject>(Vec3{600,200,200}));
	//マップ追加
	gm.map_ = std::make_shared<Map>(0, "Stage1");
	//データのセーブテスト
	//gm.data_save_->Save();
}

void SampleScene::update(){
	//全ゲームオブジェクトの更新
	gm.game_object_manager_->update();
	gm.game_object_manager_->remove();
}

void SampleScene::draw(){
	//全ゲームオブジェクトの描画
	gm.game_object_manager_->draw();
	//マップの描画
	gm.map_->DrawTerrain();
}

void SampleScene::fin(){
	//全ゲームオブジェクトの削除
	gm.game_object_manager_->clear();
}
