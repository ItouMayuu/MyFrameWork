#include "Input.h"
#include "../Screen/Screen.h"
#include "../../Library/MyMath/MyMath.h"

Input::Input(int pad){
	this->input_pad_ = pad;
}

Input::~Input(){
}

void Input::update(){

	//パッド状態を取得
	GetJoypadXInputState(input_pad_, &input_);
	// 1f 前のパッドの状態を登録		[補足] 16 = ボタンの数
	for (int i = 0; i < 16; i++) {
		pad_prev_state_[i] = pad_current_state_[i];
	}
	//現在のパッドの状態を取得
	for (int i = 0; i < 16; i++) {
		pad_current_state_[i] = input_.Buttons[i];
	}

	// 1f 前のキーボードの状態を登録
	for (int i = 0; i < 256; i++) {
		key_prev_state_[i] = key_current_state_[i];
	}
	//現在のキーボードの状態を取得
	GetHitKeyStateAll(key_current_state_);

	// 1f 前のマウスの状態を登録
	mouse_prev_pos_ = mouse_current_pos_;
	//現在のマウスの状態を取得
	GetMousePoint(&get_mouseX, &get_mouseY); //現在位置取得
	mouse_current_pos_ = Vec2((float)get_mouseX, (float)get_mouseY);
	// 1f 前のマウスの入力を登録
	mouse_prev_state_ = mouse_current_state_;
	//現在のマウス入力を取得
	mouse_current_state_ = GetMouseInput();

	//マウスを画面内に
	//KeepCursorInScreen();
}

//Pad , Key , Mouse いずれか押し続けてる間
bool Input::GetInput(std::string ActionName){
	return GetPad(ActionName) || GetKey(ActionName) || GetMouse(ActionName);
}

//Pad , Key , Mouse いずれか押された瞬間
bool Input::GetInputDown(std::string ActionName){
	return GetPadDown(ActionName) || GetKeyDown(ActionName) || GetMouseDown(ActionName);
}

//Pad , Key , Mouse いずれか離されたら
bool Input::GetInputUp(std::string ActionName){
	return GetPadUp(ActionName) || GetKeyUp(ActionName) || GetMouseUp(ActionName);
}

//現在のパッドの状態を検索
bool Input::GetPad(int buttonID){
	return pad_current_state_[buttonID];
}

//パッド用の名前で登録されているボタンを探す
bool Input::GetPad(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Pad);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態確定でtrue
		if (GetPad(id)) {
			return GetPad(id);
		}
	}
	//押された状態非確定でfalse
	return false;
}

//押したボタンが現在 = 1(押されている) , 前回 = 0(押されていない) の場合trueで返却  ->  1 AND (NOT)0 = 1
bool Input::GetPadDown(int buttonID){
	return pad_current_state_[buttonID] & ~pad_prev_state_[buttonID];
}

//パッド用の名前で登録されているボタンを探す
bool Input::GetPadDown(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Pad);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態確定でtrue
		if (GetPadDown(id)) {
			return GetPadDown(id);
		}
	}
	//押された状態非確定でfalse
	return false;
}

//押したボタンが現在 = 0(押されていない) , 前回 = 1(押されている) の場合trueで返却  ->  1 AND (NOT)0 = 1
bool Input::GetPadUp(int buttonID){
	return pad_prev_state_[buttonID] & ~pad_current_state_[buttonID];
}

//パッド用の名前で登録されているボタンを探す
bool Input::GetPadUp(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Pad);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態確定でtrue
		if (GetPadUp(id)) {
			return GetPadUp(id);
		}
	}
	//押された状態非確定でfalse
	return false;
}

//パッドの Lスティック の値を 0～1 にして返却
Vec2 Input::GetPadLeftStick(){
	// [補足] 元々の軸値が 32767 のため除算
	Vec2 tempVec = Vec2((float)input_.ThumbLX / 32767.0f, (float)input_.ThumbLY / 32767.0f);
	tempVec.y = -tempVec.y;
	return tempVec;
}

//パッドの Rスティック の値を 0～1 にして返却
Vec2 Input::GetPadRightStick() {
	// [補足] 元々の軸値が 32767 のため除算
	Vec2 tempVec = Vec2((float)input_.ThumbRX / 32767.0f, (float)input_.ThumbRY / 32767.0f);
	tempVec.y = -tempVec.y;
	return tempVec;
}

//パッドの Lトリガーの値を 0～1 にして返却  
float Input::GetPadLeftTrigger(){
	// [補足] 元々の値が 255 のため除算
	return (float)input_.LeftTrigger / 255.0f;
}

//パッドの Rトリガーの値を 0～1 にして返却  
float Input::GetPadRightTrigger(){
	// [補足] 元々の値が 255 のため除算
	return (float)input_.RightTrigger / 255.0f;
}

//現在のキーボードの状態を検索
bool Input::GetKey(int keyID){
	return key_current_state_[keyID];
}

//キーボードの名前で登録されているボタンを探す
bool Input::GetKey(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, KeyBoard);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態確定でtrue
		if (GetKey(id)) {
			return GetKey(id);
		}
	}
	//押された状態非確定でfalse
	return false;
}

//押したボタンが現在 = 1(押されている) , 前回 = 0(押されていない) の場合trueで返却  ->  1 AND (NOT)0 != 0
bool Input::GetKeyDown(int keyID){
	return key_current_state_[keyID] & ~key_prev_state_[keyID];
}

//キーボードの名前で登録されているボタンを探す
bool Input::GetKeyDown(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, KeyBoard);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態確定でtrue
		if (GetKey(id)) {
			return GetKey(id);
		}
	}
	//押された状態非確定でfalse
	return false;
}

//押したボタンが現在 = 0(押されていない) , 前回 = 1(押されている) の場合trueで返却  ->  1 AND (NOT)0 = != 0
bool Input::GetKeyUp(int keyID){
	return key_prev_state_[keyID] & key_current_state_[keyID];
}

//キーボードの名前で登録されているボタンを探す
bool Input::GetKeyUp(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, KeyBoard);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態確定でtrue
		if (GetKey(id)) {
			return GetKey(id);
		}
	}
	//押された状態非確定でfalse
	return false;
}

//現在マウスが動いてるかを返す & 動かした方向も返す
bool Input::IsMouseMoving(Vec2* velo){
	Vec2 tempVec = mouse_current_pos_ - mouse_prev_pos_;
	tempVec.y = -tempVec.y;//VSの仕様上 y軸を反転
	*velo = tempVec;
	//現在位置と前回位置が違ったらtrue
	return mouse_current_pos_ != mouse_prev_pos_;
}

//現在マウスを押し続けているか
bool Input::GetMouse(int button){
	return mouse_current_state_ & button;
}

//マウス用に名前に登録されているボタンを探す
bool Input::GetMouse(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Mouse);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態確定でtrue
		if (GetMouse(id)) {
			return GetMouse(id);
		}
	}
	//押された状態非確定でfalse
	return false;
}

//押したボタンが現在 = 1(押されている) , 前回 = 0(押されていない) の場合trueで返却  ->  1 AND (NOT)0 != 0
bool Input::GetMouseDown(int button){
	return ((mouse_current_state_ & button) & ~(mouse_prev_state_ & button)) != 0;
}

//マウス用に名前に登録されているボタンを探す
bool Input::GetMouseDown(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Mouse);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態確定でtrue
		if (GetMouseDown(id)) {
			return GetMouseDown(id);
		}
	}
	//押された状態非確定でfalse
	return false;
}

//押したボタンが現在 = 0(押されていない) , 前回 = 1(押されている) の場合trueで返却  ->  1 AND (NOT)0 = != 0
bool Input::GetMouseUp(int button){
	return ((mouse_prev_state_ & button) & ~(mouse_current_state_ & button)) != 0;
}

//マウス用に名前に登録されているボタンを探す
bool Input::GetMouseUp(std::string ActionName){
	std::vector<int> tempVec = InputIDFromList(ActionName, Mouse);
	//見つけたボタンの状態を検索
	for (auto id : tempVec) {
		//押された状態確定でtrue
		if (GetMouseUp(id)) {
			return GetMouseUp(id);
		}
	}
	//押された状態非確定でfalse
	return false;
}

//現在のマウスの位置を返す
Vec2 Input::GetMousePos(){
	return mouse_current_pos_;
}

//マウスのホイールの回転量を返す(手前 - , 奥 + )
float Input::GetMouseWheel(){
	return GetMouseWheelRotVolF();
}

void Input::RegisterButton(std::string action, int buttonID, int inputType){
	//仮保存用リスト
	std::vector<std::string> tempVec;
	//登録したいアクションの名前・対応ボタン・インプット種類を登録
	tempVec.push_back(action);
	tempVec.push_back(std::to_string(buttonID));
	tempVec.push_back(std::to_string(inputType));
	//登録したデータをメインのリストに入れる
	buttonName.push_back(tempVec);
	//仮保存用リストを削除
	tempVec.clear();
}

//マウスをウィンドウ内に収める ( Unity方式 )
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

//マウスを表示・非表示にする
void Input::IsShowCursor(bool b){
	SetMouseDispFlag(b);
}

//どれかのボタンが押されたら
bool Input::AnyKeyDown(){
	bool pad_state = false;
	bool key_state = false;
	bool mouse_state = false;

	//すべてのパッドボタンを探す
	for (int i = 0; i < 16; i++) {
		if (GetPadDown(i) == 1) {
			pad_state = 1;
			break;
		}
	}
	//すべてのキーボードボタンを探す
	for (int i = 0; i < 256; i++) {
		if (GetKeyDown(i) == 1) {
			key_state = 1;
			break;
		}
	}
	//マウスのボタンが押された瞬間
	if (mouse_current_state_ & ~mouse_prev_state_) {
		mouse_state = 1;
	}

	return key_state || pad_state || mouse_state;
}


void Input::PadVibration(int power, int time, int effectIndex){
	//振動を開始 (自身のpad , 振動の強さ(0～1000) , 振動時間(ミリ秒) , どのモーターを振動させるか※通常は-1でOK
	StartJoypadVibration(input_pad_, power, time, effectIndex);
}

void Input::PadStickDeadZone(float zone){
	//スティックの傾きが zone以下の場合傾き判定をなくす (0～1)
	SetJoypadDeadZone(input_pad_, MyMath::clamp01(zone));
}

std::vector<int> Input::InputIDFromList(std::string action, int inputType){
	//仮保存用リストを作成
	std::vector<int> tempVec;
	for (int i = 0; i < buttonName.size(); i++) {
		//指定されたアクション名 かつ インプットの種類が一致
		if (buttonName[i][ActionName] == action &&
			std::stoi(buttonName[i][InputType]) == inputType) {
			//仮保存用リストにボタンIDを登録
			tempVec.push_back(std::stoi(buttonName[i][InputID]));
		}
	}
	return tempVec;
}
