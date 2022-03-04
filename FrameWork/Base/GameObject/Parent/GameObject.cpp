#include "GameObject.h"
#include "../../Library/Component/Parent/Component.h"

void GameObject::update(){

}

void GameObject::draw() const{

}

void GameObject::draw_transparent() const{

}

void GameObject::draw_gui() const{
    
}

void GameObject::die(){
    dead_ = true;
}

bool GameObject::is_dead() const{
    return dead_;
}

const std::string& GameObject::name() const{
    return name_;
}

const std::string& GameObject::tag() const{
    return tag_;
}

const Transform& GameObject::transform() const{
    return transform_;
}

Transform& GameObject::transform(){
    return transform_;
}

void GameObject::component_update(){
    for (const auto& c : components) {
        c->update(this);
    }
}

void GameObject::component_draw(){
    for (const auto& c : components) {
        c->draw(this);
    }
}

std::vector<std::shared_ptr<Component>> GameObject::get_components(){
    return components;
}