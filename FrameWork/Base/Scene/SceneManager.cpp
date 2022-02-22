#include "SceneManager.h"
#include "Parent/NullScene/NullScene.h"

//ヌルシーンを作成
static std::shared_ptr<NullScene> null_scene_ = std::make_shared<NullScene>();

SceneManager::SceneManager()
	: current_scene_{ null_scene_ }{
	//現在のシーンにヌルシーンを指定
}

SceneManager::~SceneManager(){

}

void SceneManager::init(){
	current_scene_->init();
}

void SceneManager::update(){
	current_scene_->update();
}

void SceneManager::draw(){
	current_scene_->draw();
}

void SceneManager::fin(){
	current_scene_->fin();
	current_scene_ = null_scene_;
}

void SceneManager::change_scene(std::string scene){
	//現在のシーンを終了させてからシーン変更し変更先のシーンを初期化
	fin();
	current_scene_ = scenes_[scene];
	init();
}

void SceneManager::add_scene(std::string SceneName, std::shared_ptr<Scene> sceneClass){
	scenes_[SceneName] = sceneClass; 
}
