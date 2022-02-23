#include "Player.h"
#include "DxLib.h"

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
	DrawString(0, 0, std::to_string(transform_.position().x).c_str(), GetColor(255, 255, 255));
	DrawString(0, 30, std::to_string(transform_.position().y).c_str(), GetColor(255, 255, 255));
	MyDraw::Draw3DModel(Image::Box, transform());
}

void Player::load_status(int hp, int mp){
	hp_ = hp;
	mp_ = mp;
}

void Player::InputHandle() {

	if (gm.input_->AnyKeyDown()) {
		//gm.input_->PadVibration(100, 2000);
	}

	if (gm.input_->GetInputDown("End")) {
		DxLib_End();
	}
	Vec3 velocity{ 0.0f,0.0f,0.0f };

	velocity.x = gm.input_->GetPadLeftStick().x * 10;
	velocity.z = gm.input_->GetPadLeftStick().y * 10;

	if (gm.input_->GetInput("Forward")) {
		velocity.z = 10;
	}
	if (gm.input_->GetInput("Backward")) {
		velocity.z = -10;
	}
	if (gm.input_->GetInput("ToLeft")) {
		velocity.x = -10;
	}
	if (gm.input_->GetInput("ToRight")) {
		velocity.x = 10;
	}
	if (gm.input_->GetInput("Up")) {
		velocity.y = 10;
	}
	if (gm.input_->GetInput("Down")) {
		velocity.y = -10;
	}

	//À•W‚ÌŠ„‚è“–‚Ä
	Vec3 position = transform_.position();
	position += velocity;
	transform_.position(position);
}