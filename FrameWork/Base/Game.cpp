#include "Game.h"
#include "DxLib.h"

#include "Library/GameManager/GameObjectManager/GameObjectManager.h"
#include "Library/DataSave/DataSave.h"
#include "Library/Input/Input.h"
#include "Resource/Image/Image.h"
#include "Library/MyDraw/MyDraw.h"

#include "Scene/SceneManager.h"
#include "Scene/Child/SampleScene.h"

Game::Game(){
	//シーンの追加
	sm.add_scene("SampleScene", std::make_shared<SampleScene>());
}

void Game::Init(){
	//ゲームオブジェクトマネージャーを作成
	gm.game_object_manager_ = std::make_shared<GameObjectManager>();
	//セーブクラスを作成
	gm.data_save_ = std::make_shared<DataSave>();
	//インプットクラスを作成
	gm.input_ = std::make_shared<Input>();
	//使うボタンの登録
	RegisterButton();
	//イメージクラスの初期化
	Image::Init();
	MyDraw::Init();
	
	//指定シーンにチェンジ
	sm.change_scene("SampleScene");
}

void Game::Update(){
	sm.update();//60fps
	gm.input_->update();
}

void Game::Draw(){
	sm.draw();
	//DrawString(0, 0, "Hello World",GetColor(255,255,255),NULL);
}

void Game::RegisterButton(){
	gm.input_->RegisterButton("Forward", KEY_INPUT_W, InputType::KeyBoard);
	gm.input_->RegisterButton("Backward", KEY_INPUT_S, InputType::KeyBoard);
	gm.input_->RegisterButton("ToLeft", KEY_INPUT_A, InputType::KeyBoard);
	gm.input_->RegisterButton("ToRight", KEY_INPUT_D, InputType::KeyBoard);
	gm.input_->RegisterButton("Jump", KEY_INPUT_SPACE, InputType::KeyBoard);
	gm.input_->RegisterButton("End", KEY_INPUT_ESCAPE, InputType::KeyBoard);
	gm.input_->RegisterButton("Up", KEY_INPUT_UP, InputType::KeyBoard);
	gm.input_->RegisterButton("Down", KEY_INPUT_DOWN, InputType::KeyBoard);

	gm.input_->RegisterButton("Forward", XINPUT_BUTTON_DPAD_UP, InputType::Pad);
	gm.input_->RegisterButton("Backward", XINPUT_BUTTON_DPAD_DOWN, InputType::Pad);
	gm.input_->RegisterButton("ToLeft", XINPUT_BUTTON_DPAD_LEFT, InputType::Pad);
	gm.input_->RegisterButton("ToRight", XINPUT_BUTTON_DPAD_RIGHT, InputType::Pad);

	gm.input_->RegisterButton("ToLeft", MOUSE_INPUT_LEFT, InputType::Mouse);
	gm.input_->RegisterButton("ToRight", MOUSE_INPUT_RIGHT, InputType::Mouse);
}

/* ==【ボタン一覧】============================================


----- [パッドボタン] ------------------------------------------

XINPUT_BUTTON_DPAD_UP				// デジタル方向ボタン上	 
XINPUT_BUTTON_DPAD_DOWN				// デジタル方向ボタン下  
XINPUT_BUTTON_DPAD_LEFT				// デジタル方向ボタン左  
XINPUT_BUTTON_DPAD_RIGHT			// デジタル方向ボタン右	 
XINPUT_BUTTON_START					// STARTボタン			 
XINPUT_BUTTON_BACK					// BACKボタン			 
XINPUT_BUTTON_LEFT_THUMB			// 左スティック押し込み	 
XINPUT_BUTTON_RIGHT_THUMB			// 右スティック押し込み	 
XINPUT_BUTTON_LEFT_SHOULDER			// LBボタン				 
XINPUT_BUTTON_RIGHT_SHOULDER		// RBボタン				 
XINPUT_BUTTON_A						// Aボタン				 
XINPUT_BUTTON_B						// Bボタン				 
XINPUT_BUTTON_X						// Xボタン				 
XINPUT_BUTTON_Y						// Yボタン

XINPUT_BUTTON_LEFT_TRIGGHER			// 左トリガーボタン ※自分で追加
XINPUT_BUTTON_RIGHT_TRIGGER			// 右トリガーボタン

※スティック・トリガーボタンはInputクラス内の関数を使用


----- [マウスボタン] -------------------------------------------


MOUSE_INPUT_LEFT					// マウス左ボタン		
MOUSE_INPUT_RIGHT					// マウス右ボタン		
MOUSE_INPUT_MIDDLE					// マウス中央ボタン			
MOUSE_INPUT_4						// マウス４ボタン		
MOUSE_INPUT_5						// マウス５ボタン		
MOUSE_INPUT_6						// マウス６ボタン		
MOUSE_INPUT_7						// マウス７ボタン		
MOUSE_INPUT_8						// マウス８ボタン			


----- [キーボードボタン] ---------------------------------------


KEY_INPUT_BACK						// バックスペースキー
KEY_INPUT_TAB						// タブキー
KEY_INPUT_RETURN					// エンターキー

KEY_INPUT_LSHIFT					// 左シフトキー
KEY_INPUT_RSHIFT					// 右シフトキー
KEY_INPUT_LCONTROL					// 左コントロールキー
KEY_INPUT_RCONTROL					// 右コントロールキー
KEY_INPUT_ESCAPE					// エスケープキー
KEY_INPUT_SPACE						// スペースキー
KEY_INPUT_PGUP						// ＰａｇｅＵＰキー
KEY_INPUT_PGDN						// ＰａｇｅＤｏｗｎキー
KEY_INPUT_END						// エンドキー
KEY_INPUT_HOME						// ホームキー
KEY_INPUT_LEFT						// 左キー
KEY_INPUT_UP						// 上キー
KEY_INPUT_RIGHT						// 右キー
KEY_INPUT_DOWN						// 下キー
KEY_INPUT_INSERT					// インサートキー
KEY_INPUT_DELETE					// デリートキー

KEY_INPUT_MINUS						// －キー
KEY_INPUT_YEN						// ￥キー
KEY_INPUT_PREVTRACK					// ＾キー
KEY_INPUT_PERIOD					// ．キー
KEY_INPUT_SLASH						// ／キー
KEY_INPUT_LALT						// 左ＡＬＴキー
KEY_INPUT_RALT						// 右ＡＬＴキー
KEY_INPUT_SCROLL					// ScrollLockキー
KEY_INPUT_SEMICOLON					// ；キー
KEY_INPUT_COLON						// ：キー
KEY_INPUT_LBRACKET					// ［キー
KEY_INPUT_RBRACKET					// ］キー
KEY_INPUT_AT						// ＠キー
KEY_INPUT_BACKSLASH					// ＼キー
KEY_INPUT_COMMA						// ，キー
KEY_INPUT_CAPSLOCK					// CaspLockキー
KEY_INPUT_PAUSE						// PauseBreakキー

KEY_INPUT_NUMPAD0					// テンキー０
KEY_INPUT_NUMPAD1					// テンキー１
KEY_INPUT_NUMPAD2					// テンキー２
KEY_INPUT_NUMPAD3					// テンキー３
KEY_INPUT_NUMPAD4					// テンキー４
KEY_INPUT_NUMPAD5					// テンキー５
KEY_INPUT_NUMPAD6					// テンキー６
KEY_INPUT_NUMPAD7					// テンキー７
KEY_INPUT_NUMPAD8					// テンキー８
KEY_INPUT_NUMPAD9					// テンキー９
KEY_INPUT_MULTIPLY					// テンキー＊キー
KEY_INPUT_ADD						// テンキー＋キー
KEY_INPUT_SUBTRACT					// テンキー－キー
KEY_INPUT_DECIMAL					// テンキー．キー
KEY_INPUT_DIVIDE					// テンキー／キー
KEY_INPUT_NUMPADENTER				// テンキーのエンターキー

KEY_INPUT_F1						// Ｆ１キー
KEY_INPUT_F2						// Ｆ２キー
KEY_INPUT_F3						// Ｆ３キー
KEY_INPUT_F4						// Ｆ４キー
KEY_INPUT_F5						// Ｆ５キー
KEY_INPUT_F6						// Ｆ６キー
KEY_INPUT_F7						// Ｆ７キー
KEY_INPUT_F8						// Ｆ８キー
KEY_INPUT_F9						// Ｆ９キー
KEY_INPUT_F10						// Ｆ１０キー
KEY_INPUT_F11						// Ｆ１１キー
KEY_INPUT_F12						// Ｆ１２キー

KEY_INPUT_A							// Ａキー
KEY_INPUT_B							// Ｂキー
KEY_INPUT_C							// Ｃキー
KEY_INPUT_D							// Ｄキー
KEY_INPUT_E							// Ｅキー
KEY_INPUT_F							// Ｆキー
KEY_INPUT_G							// Ｇキー
KEY_INPUT_H							// Ｈキー
KEY_INPUT_I							// Ｉキー
KEY_INPUT_J							// Ｊキー
KEY_INPUT_K							// Ｋキー
KEY_INPUT_L							// Ｌキー
KEY_INPUT_M							// Ｍキー
KEY_INPUT_N							// Ｎキー
KEY_INPUT_O							// Ｏキー
KEY_INPUT_P							// Ｐキー
KEY_INPUT_Q							// Ｑキー
KEY_INPUT_R							// Ｒキー
KEY_INPUT_S							// Ｓキー
KEY_INPUT_T							// Ｔキー
KEY_INPUT_U							// Ｕキー
KEY_INPUT_V							// Ｖキー
KEY_INPUT_W							// Ｗキー
KEY_INPUT_X							// Ｘキー
KEY_INPUT_Y							// Ｙキー
KEY_INPUT_Z							// Ｚキー
KEY_INPUT_0							// ０キー
KEY_INPUT_1							// １キー
KEY_INPUT_2							// ２キー
KEY_INPUT_3							// ３キー
KEY_INPUT_4							// ４キー
KEY_INPUT_5							// ５キー
KEY_INPUT_6							// ６キー
KEY_INPUT_7							// ７キー
KEY_INPUT_8							// ８キー
KEY_INPUT_9							// ９キー
*/