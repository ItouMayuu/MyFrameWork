#include "Player.h"
#include "DxLib.h"

#include "../../../Library/MyDraw/MyDraw.h"
#include "../../../Library/Component/Child/TestComponent/TestComponent.h"
#include "../../../Library/Input/Input.h"

Player::Player(){
	this->name_ = "Player";
	this->tag_ = "PlayerTag";
	this->components.push_back(std::make_shared<test>(this));
}

void Player::update(){
	InputHandle();
}

void Player::draw() const{
	DrawString(0, 0, std::to_string(w).c_str(), GetColor(255, 255, 255));
	DrawString(x_ , y_ , "ƒvƒŒƒCƒ„[", GetColor(255, 255, 255));
}

void Player::load_status(int hp, int mp){
	hp_ = hp;
	mp_ = mp;
}

void Player::InputHandle() {

	//w = gm.input_->GetMouseWheel();

	w = gm.input_->GetPadLeftTrigger();

	if (gm.input_->AnyKeyDown()) {
		//gm.input_->PadVibration(100, 2000);
	}
	if (gm.input_->GetInputDown("Jump")) {
		y_ = 400;
	}

	if (gm.input_->GetInputDown("End")) {
		DxLib_End();
	}
	Vec2 velocity{ 0.0f,0.0f};

	velocity = gm.input_->GetPadLeftStick() * 10;


	if (gm.input_->GetInput("Forward")) {
		velocity.y = -1;
	}
	if (gm.input_->GetInput("Backward")) {
		velocity.y = 1;
	}
	if (gm.input_->GetInput("ToLeft")) {
		velocity.x = -1;
	}
	if (gm.input_->GetInput("ToRight")) {
		velocity.x = 1;
	}

	x_ += velocity.x;
	y_ += velocity.y;
}