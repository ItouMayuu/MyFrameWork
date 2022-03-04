#include "SphereCollision.h"
#include "../../../MyDraw/MyDraw.h"
#include "../../../../GameObject/Parent/GameObject.h"

SphereCollision::SphereCollision(float radius, const Vec3& center, GameObject* owner)
    : Component(owner){
    this->tag = "SphereCollision";
    this->typeTag = "Collision";
    this->radius = radius;
    this->center = center;
}

void SphereCollision::update(GameObject* obj){
    //transform(obj->transform().position(),radius);
}

void SphereCollision::draw(GameObject* obj){
   // draw_debug();
}

SphereCollision SphereCollision::translate(const Vec3& pos) const{
    return SphereCollision{ radius , center + pos , owner};
}

SphereCollision SphereCollision::transform(const Vec3& center, float radius){
    this->center = center;
    this->radius = radius;
    return SphereCollision( radius , center , owner);
}

bool SphereCollision::intersects(const SphereCollision& other) const{
    return CollisionSphereAndSphere(other) == true;
}

void SphereCollision::draw_debug() const{
    MyDraw::DrawSphere3D(center, radius, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), false);
}

Vec3 SphereCollision::get_center() const{
    return center;
}

float SphereCollision::get_radius() const{
    return radius;
}

bool SphereCollision::CollisionSphereAndSphere(const SphereCollision& other) const{
    Vec3 v;
    v = other.center - center;
    float r;
    r = (float)std::pow(radius + other.radius, 2);

    return v.lengthSquared() <= r;
}
