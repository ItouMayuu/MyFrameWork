#include "GameObjectManager.h"
#include "../../../GameObject/Parent/GameObject.h"
#include "../../../Library/Component/Parent/Component.h"

GameObjectManager::~GameObjectManager(){
    clear();
}

void GameObjectManager::add(std::shared_ptr<GameObject> gameobject){
    game_objects_.push_back(gameobject);
}

void GameObjectManager::update(){
    for (auto go : game_objects_) {
        go->component_update();
        go->update();
    }
}

void GameObjectManager::draw(){
    for (auto go : game_objects_) {
        go->component_draw();
        go->draw();
    }
}

void GameObjectManager::remove(){
    //イテレータで削除
    for (auto i = game_objects_.begin(); i != game_objects_.end();) {
        if ((*i)->is_dead()) {
            i = game_objects_.erase(i);
        } else {
            i++;
        }
    }
}

std::shared_ptr<GameObject> GameObjectManager::find(const std::string& name) const{
    //名前が一致したらそのゲームオブジェクトを返す
    for (auto go : game_objects_) {
        if (go->name() == name) {
            return go;
        }
    }//なにもなければnullを返す
    return nullptr;
}

std::vector<std::shared_ptr<GameObject>> GameObjectManager::find_with_tag(const std::string& tag) const{
    std::vector<std::shared_ptr<GameObject>> result;
    //タグが一致したゲームオブジェクトたちを返す
    for (auto go : game_objects_) {
        if (go->tag() == tag) {
            result.push_back(go);
        }
    }//全て検索したら結果を返す
    return result;
}

int GameObjectManager::count() const{
    return (int)game_objects_.size();
}

int GameObjectManager::count_with_tag(const std::string& tag) const{
    int result = 0;
    //タグが一致したゲームオブジェクトをカウントして返す
    for (auto go : game_objects_) {
        if (go->tag() == tag) {
            result++;
        }
    }
    return result;
}

void GameObjectManager::clear(){
    game_objects_.clear();
}

void GameObjectManager::component_clear(GameObject* owner, std::string comp_tag){
    //現在のコンポーネントの範囲保存
    std::vector<std::shared_ptr<Component>> c = owner->get_components();

    for (auto i = c.begin(); i != c.end();) {
        if ((*i)->tag == comp_tag) {//タグが一致したら削除
            i = owner->get_components().erase(i);
        }
        else {
            i++;
        }
    }
}

void GameObjectManager::component_add(GameObject* owner,std::shared_ptr<Component> comp){
    owner->get_components().push_back(comp);
}

void GameObjectManager::component_clear_all(GameObject* owner){
    owner->get_components().clear();
}
