#include "SceneManager.h"
#include "Parent/NullScene/NullScene.h"

//�k���V�[�����쐬
static std::shared_ptr<NullScene> null_scene_ = std::make_shared<NullScene>();

SceneManager::SceneManager()
	: current_scene_{ null_scene_ }{
	//���݂̃V�[���Ƀk���V�[�����w��
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
	//���݂̃V�[�����I�������Ă���V�[���ύX���ύX��̃V�[����������
	fin();
	current_scene_ = scenes_[scene];
	init();
}

void SceneManager::add_scene(std::string SceneName, std::shared_ptr<Scene> sceneClass){
	scenes_[SceneName] = sceneClass; 
}
