#include "NullScene.h"
#include <DxLib.h>

void NullScene::init(){
}

void NullScene::update(){

}

void NullScene::draw(){
	DrawString(0, 0, "NullSceneですわ。ChangeSceneのスペルミスですわ!", GetColor(255, 255, 255));
}

void NullScene::fin(){
}
