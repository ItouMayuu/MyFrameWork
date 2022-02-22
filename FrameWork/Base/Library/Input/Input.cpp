#include "Input.h"
#include "../Screen/Screen.h"
#include "../../Library/MyMath/MyMath.h"

Input::Input(int pad){
	this->input_pad_ = pad;
}

Input::~Input(){
}

void Input::update(){

	//�p�b�h��Ԃ��擾
	GetJoypadXInputState(input_pad_, &input_);
	// 1f �O�̃p�b�h�̏�Ԃ�o�^		[�⑫] 16 = �{�^���̐�
	for (int i = 0; i < 16; i++) {
		pad_prev_state_[i] = pad_current_state_[i];
	}
	//���݂̃p�b�h�̏�Ԃ��擾
	for (int i = 0; i < 16; i++) {
		pad_current_state_[i] = input_.Buttons[i];
	}

	// 1f �O�̃L�[�{�[�h�̏�Ԃ�o�^
	for (int i = 0; i < 256; i++) {
		key_prev_state_[i] = key_current_state_[i];
	}
	//���݂̃L�[�{�[�h�̏�Ԃ��擾
	GetHitKeyStateAll(key_current_state_);

	// 1f �O�̃}�E�X�̏�Ԃ�o�^
	mouse_prev_pos_ = mouse_current_pos_;
	//���݂̃}�E�X�̏�Ԃ��擾
	GetMousePoint(&get_mouseX, &get_mouseY); //���݈ʒu�擾
	mouse_current_pos_ = Vec2((float)get_mouseX, (float)get_mouseY);
	// 1f �O�̃}�E�X�̓��͂�o�^
	mouse_prev_state_ = mouse_current_state_;
	//���݂̃}�E�X���͂��擾
	mouse_current_state_ = GetMouseInput();

	//�}�E�X����ʓ���
	//KeepCursorInScreen();
}

//Pad , Key , Mouse �����ꂩ���������Ă��
bool Input::GetInput(std::string ActionName){
	return GetPad(ActionName) || GetKey(ActionName) || GetMouse(ActionName);
}

//Pad , Key , Mouse �����ꂩ�����ꂽ�u��
bool Input::GetInputDown(std::string ActionName){
	return GetPadDown(ActionName) || GetKeyDown(ActionName) || GetMouseDown(ActionName);
}

//Pad , Key , Mouse �����ꂩ�����ꂽ��
bool Input::GetInputUp(std::string ActionName){
	return GetPadUp(ActionName) || GetKeyUp(ActionName) || GetMouseUp(ActionName);
}

//���݂̃p�b�h�̏�Ԃ�����
bool Input::GetPad(int buttonID){
	return pad_current_state_[buttonID];
}

//�p�b�h�p�̖��O�œo�^����Ă���{�^����T��
bool Input::GetPad(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Pad);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԋm���true
		if (GetPad(id)) {
			return GetPad(id);
		}
	}
	//�����ꂽ��Ԕ�m���false
	return false;
}

//�������{�^�������� = 1(������Ă���) , �O�� = 0(������Ă��Ȃ�) �̏ꍇtrue�ŕԋp  ->  1 AND (NOT)0 = 1
bool Input::GetPadDown(int buttonID){
	return pad_current_state_[buttonID] & ~pad_prev_state_[buttonID];
}

//�p�b�h�p�̖��O�œo�^����Ă���{�^����T��
bool Input::GetPadDown(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Pad);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԋm���true
		if (GetPadDown(id)) {
			return GetPadDown(id);
		}
	}
	//�����ꂽ��Ԕ�m���false
	return false;
}

//�������{�^�������� = 0(������Ă��Ȃ�) , �O�� = 1(������Ă���) �̏ꍇtrue�ŕԋp  ->  1 AND (NOT)0 = 1
bool Input::GetPadUp(int buttonID){
	return pad_prev_state_[buttonID] & ~pad_current_state_[buttonID];
}

//�p�b�h�p�̖��O�œo�^����Ă���{�^����T��
bool Input::GetPadUp(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Pad);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԋm���true
		if (GetPadUp(id)) {
			return GetPadUp(id);
		}
	}
	//�����ꂽ��Ԕ�m���false
	return false;
}

//�p�b�h�� L�X�e�B�b�N �̒l�� 0�`1 �ɂ��ĕԋp
Vec2 Input::GetPadLeftStick(){
	// [�⑫] ���X�̎��l�� 32767 �̂��ߏ��Z
	Vec2 tempVec = Vec2((float)input_.ThumbLX / 32767.0f, (float)input_.ThumbLY / 32767.0f);
	tempVec.y = -tempVec.y;
	return tempVec;
}

//�p�b�h�� R�X�e�B�b�N �̒l�� 0�`1 �ɂ��ĕԋp
Vec2 Input::GetPadRightStick() {
	// [�⑫] ���X�̎��l�� 32767 �̂��ߏ��Z
	Vec2 tempVec = Vec2((float)input_.ThumbRX / 32767.0f, (float)input_.ThumbRY / 32767.0f);
	tempVec.y = -tempVec.y;
	return tempVec;
}

//�p�b�h�� L�g���K�[�̒l�� 0�`1 �ɂ��ĕԋp  
float Input::GetPadLeftTrigger(){
	// [�⑫] ���X�̒l�� 255 �̂��ߏ��Z
	return (float)input_.LeftTrigger / 255.0f;
}

//�p�b�h�� R�g���K�[�̒l�� 0�`1 �ɂ��ĕԋp  
float Input::GetPadRightTrigger(){
	// [�⑫] ���X�̒l�� 255 �̂��ߏ��Z
	return (float)input_.RightTrigger / 255.0f;
}

//���݂̃L�[�{�[�h�̏�Ԃ�����
bool Input::GetKey(int keyID){
	return key_current_state_[keyID];
}

//�L�[�{�[�h�̖��O�œo�^����Ă���{�^����T��
bool Input::GetKey(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, KeyBoard);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԋm���true
		if (GetKey(id)) {
			return GetKey(id);
		}
	}
	//�����ꂽ��Ԕ�m���false
	return false;
}

//�������{�^�������� = 1(������Ă���) , �O�� = 0(������Ă��Ȃ�) �̏ꍇtrue�ŕԋp  ->  1 AND (NOT)0 != 0
bool Input::GetKeyDown(int keyID){
	return key_current_state_[keyID] & ~key_prev_state_[keyID];
}

//�L�[�{�[�h�̖��O�œo�^����Ă���{�^����T��
bool Input::GetKeyDown(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, KeyBoard);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԋm���true
		if (GetKey(id)) {
			return GetKey(id);
		}
	}
	//�����ꂽ��Ԕ�m���false
	return false;
}

//�������{�^�������� = 0(������Ă��Ȃ�) , �O�� = 1(������Ă���) �̏ꍇtrue�ŕԋp  ->  1 AND (NOT)0 = != 0
bool Input::GetKeyUp(int keyID){
	return key_prev_state_[keyID] & key_current_state_[keyID];
}

//�L�[�{�[�h�̖��O�œo�^����Ă���{�^����T��
bool Input::GetKeyUp(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, KeyBoard);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԋm���true
		if (GetKey(id)) {
			return GetKey(id);
		}
	}
	//�����ꂽ��Ԕ�m���false
	return false;
}

//���݃}�E�X�������Ă邩��Ԃ� & ���������������Ԃ�
bool Input::IsMouseMoving(Vec2* velo){
	Vec2 tempVec = mouse_current_pos_ - mouse_prev_pos_;
	tempVec.y = -tempVec.y;//VS�̎d�l�� y���𔽓]
	*velo = tempVec;
	//���݈ʒu�ƑO��ʒu���������true
	return mouse_current_pos_ != mouse_prev_pos_;
}

//���݃}�E�X�����������Ă��邩
bool Input::GetMouse(int button){
	return mouse_current_state_ & button;
}

//�}�E�X�p�ɖ��O�ɓo�^����Ă���{�^����T��
bool Input::GetMouse(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Mouse);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԋm���true
		if (GetMouse(id)) {
			return GetMouse(id);
		}
	}
	//�����ꂽ��Ԕ�m���false
	return false;
}

//�������{�^�������� = 1(������Ă���) , �O�� = 0(������Ă��Ȃ�) �̏ꍇtrue�ŕԋp  ->  1 AND (NOT)0 != 0
bool Input::GetMouseDown(int button){
	return ((mouse_current_state_ & button) & ~(mouse_prev_state_ & button)) != 0;
}

//�}�E�X�p�ɖ��O�ɓo�^����Ă���{�^����T��
bool Input::GetMouseDown(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Mouse);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԋm���true
		if (GetMouseDown(id)) {
			return GetMouseDown(id);
		}
	}
	//�����ꂽ��Ԕ�m���false
	return false;
}

//�������{�^�������� = 0(������Ă��Ȃ�) , �O�� = 1(������Ă���) �̏ꍇtrue�ŕԋp  ->  1 AND (NOT)0 = != 0
bool Input::GetMouseUp(int button){
	return ((mouse_prev_state_ & button) & ~(mouse_current_state_ & button)) != 0;
}

//�}�E�X�p�ɖ��O�ɓo�^����Ă���{�^����T��
bool Input::GetMouseUp(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Mouse);
	//�������{�^���̏�Ԃ�����
	for (auto id : tempVec) {
		//�����ꂽ��Ԋm���true
		if (GetMouseUp(id)) {
			return GetMouseUp(id);
		}
	}
	//�����ꂽ��Ԕ�m���false
	return false;
}

//���݂̃}�E�X�̈ʒu��Ԃ�
Vec2 Input::GetMousePos(){
	return mouse_current_pos_;
}

//�}�E�X�̃z�C�[���̉�]�ʂ�Ԃ�(��O - , �� + )
float Input::GetMouseWheel(){
	return GetMouseWheelRotVolF();
}

void Input::RegisterButton(std::string action, int buttonID, int inputType){
	//���ۑ��p���X�g
	std::vector<std::string> tempVec;
	//�o�^�������A�N�V�����̖��O�E�Ή��{�^���E�C���v�b�g��ނ�o�^
	tempVec.push_back(action);
	tempVec.push_back(std::to_string(buttonID));
	tempVec.push_back(std::to_string(inputType));
	//�o�^�����f�[�^�����C���̃��X�g�ɓ����
	buttonName.push_back(tempVec);
	//���ۑ��p���X�g���폜
	tempVec.clear();
}

//�}�E�X���E�B���h�E���Ɏ��߂� ( Unity���� )
void Input::KeepCursorInScreen(){
	if (mouse_current_pos_.x < 0) {
		mouse_current_pos_.x = (float)Screen::Width;
		mouse_prev_pos_ = mouse_current_pos_;
	}
	else if (mouse_current_pos_.x > (float)Screen::Width) {
		mouse_current_pos_.x = 0;
		mouse_prev_pos_ = mouse_current_pos_;
	}
	if (mouse_current_pos_.y < 0) {
		mouse_current_pos_.y = (float)Screen::Height;
		mouse_prev_pos_ = mouse_current_pos_;
	}
	else if (mouse_current_pos_.y > (float)Screen::Height) {
		mouse_current_pos_.y = 0;
		mouse_prev_pos_ = mouse_current_pos_;
	}
	SetMousePoint((int)mouse_current_pos_.x, (int)mouse_current_pos_.y);
}

//�}�E�X��\���E��\���ɂ���
void Input::IsShowCursor(bool b){
	SetMouseDispFlag(b);
}

//�ǂꂩ�̃{�^���������ꂽ��
bool Input::AnyKeyDown(){
	bool pad_state = false;
	bool key_state = false;
	bool mouse_state = false;

	//���ׂẴp�b�h�{�^����T��
	for (int i = 0; i < 16; i++) {
		if (GetPadDown(i) == 1) {
			pad_state = 1;
			break;
		}
	}
	//���ׂẴL�[�{�[�h�{�^����T��
	for (int i = 0; i < 256; i++) {
		if (GetKeyDown(i) == 1) {
			key_state = 1;
			break;
		}
	}
	//�}�E�X�̃{�^���������ꂽ�u��
	if (mouse_current_state_ & ~mouse_prev_state_) {
		mouse_state = 1;
	}

	return key_state || pad_state || mouse_state;
}


void Input::PadVibration(int power, int time, int effectIndex){
	//�U�����J�n (���g��pad , �U���̋���(0�`1000) , �U������(�~���b) , �ǂ̃��[�^�[��U�������邩���ʏ��-1��OK
	StartJoypadVibration(input_pad_, power, time, effectIndex);
}

void Input::PadStickDeadZone(float zone){
	//�X�e�B�b�N�̌X���� zone�ȉ��̏ꍇ�X��������Ȃ��� (0�`1)
	SetJoypadDeadZone(input_pad_, MyMath::clamp01(zone));
}

std::vector<int> Input::InputIDFromList(std::string action, int inputType){
	//���ۑ��p���X�g���쐬
	std::vector<int> tempVec;
	for (int i = 0; i < buttonName.size(); i++) {
		//�w�肳�ꂽ�A�N�V������ ���� �C���v�b�g�̎�ނ���v
		if (buttonName[i][ActionName] == action &&
			std::stoi(buttonName[i][InputType]) == inputType) {
			//���ۑ��p���X�g�Ƀ{�^��ID��o�^
			tempVec.push_back(std::stoi(buttonName[i][InputID]));
		}
	}
	return tempVec;
}
