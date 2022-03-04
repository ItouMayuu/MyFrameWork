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
	//���Ƀv���C���[�ǉ�
	gm.player_ = std::make_shared<Player>(Vec3{200,200,200});
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�ɂ��o�^ �������gm.player_�ő��v
	gm.game_object_manager_->add(gm.player_);
	gm.game_object_manager_->add(std::make_shared<TestObject>(Vec3{600,200,200}));
	//�}�b�v�ǉ�
	gm.map_ = std::make_shared<Map>(0, "Stage1");
	//�f�[�^�̃Z�[�u�e�X�g
	//gm.data_save_->Save();
}

void SampleScene::update(){
	//�S�Q�[���I�u�W�F�N�g�̍X�V
	gm.game_object_manager_->update();
	gm.game_object_manager_->remove();
}

void SampleScene::draw(){
	//�S�Q�[���I�u�W�F�N�g�̕`��
	gm.game_object_manager_->draw();
	//�}�b�v�̕`��
	gm.map_->DrawTerrain();
}

void SampleScene::fin(){
	//�S�Q�[���I�u�W�F�N�g�̍폜
	gm.game_object_manager_->clear();
}
