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
	//�V�[���̒ǉ�
	sm.add_scene("SampleScene", std::make_shared<SampleScene>());
}

void Game::Init(){
	//�Q�[���I�u�W�F�N�g�}�l�[�W���[���쐬
	gm.game_object_manager_ = std::make_shared<GameObjectManager>();
	//�Z�[�u�N���X���쐬
	gm.data_save_ = std::make_shared<DataSave>();
	//�C���v�b�g�N���X���쐬
	gm.input_ = std::make_shared<Input>();
	//�g���{�^���̓o�^
	RegisterButton();
	//�C���[�W�N���X�̏�����
	Image::Init();
	MyDraw::Init();
	
	//�w��V�[���Ƀ`�F���W
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

/* ==�y�{�^���ꗗ�z============================================


----- [�p�b�h�{�^��] ------------------------------------------

XINPUT_BUTTON_DPAD_UP				// �f�W�^�������{�^����	 
XINPUT_BUTTON_DPAD_DOWN				// �f�W�^�������{�^����  
XINPUT_BUTTON_DPAD_LEFT				// �f�W�^�������{�^����  
XINPUT_BUTTON_DPAD_RIGHT			// �f�W�^�������{�^���E	 
XINPUT_BUTTON_START					// START�{�^��			 
XINPUT_BUTTON_BACK					// BACK�{�^��			 
XINPUT_BUTTON_LEFT_THUMB			// ���X�e�B�b�N��������	 
XINPUT_BUTTON_RIGHT_THUMB			// �E�X�e�B�b�N��������	 
XINPUT_BUTTON_LEFT_SHOULDER			// LB�{�^��				 
XINPUT_BUTTON_RIGHT_SHOULDER		// RB�{�^��				 
XINPUT_BUTTON_A						// A�{�^��				 
XINPUT_BUTTON_B						// B�{�^��				 
XINPUT_BUTTON_X						// X�{�^��				 
XINPUT_BUTTON_Y						// Y�{�^��

XINPUT_BUTTON_LEFT_TRIGGHER			// ���g���K�[�{�^�� �������Œǉ�
XINPUT_BUTTON_RIGHT_TRIGGER			// �E�g���K�[�{�^��

���X�e�B�b�N�E�g���K�[�{�^����Input�N���X���̊֐����g�p


----- [�}�E�X�{�^��] -------------------------------------------


MOUSE_INPUT_LEFT					// �}�E�X���{�^��		
MOUSE_INPUT_RIGHT					// �}�E�X�E�{�^��		
MOUSE_INPUT_MIDDLE					// �}�E�X�����{�^��			
MOUSE_INPUT_4						// �}�E�X�S�{�^��		
MOUSE_INPUT_5						// �}�E�X�T�{�^��		
MOUSE_INPUT_6						// �}�E�X�U�{�^��		
MOUSE_INPUT_7						// �}�E�X�V�{�^��		
MOUSE_INPUT_8						// �}�E�X�W�{�^��			


----- [�L�[�{�[�h�{�^��] ---------------------------------------


KEY_INPUT_BACK						// �o�b�N�X�y�[�X�L�[
KEY_INPUT_TAB						// �^�u�L�[
KEY_INPUT_RETURN					// �G���^�[�L�[

KEY_INPUT_LSHIFT					// ���V�t�g�L�[
KEY_INPUT_RSHIFT					// �E�V�t�g�L�[
KEY_INPUT_LCONTROL					// ���R���g���[���L�[
KEY_INPUT_RCONTROL					// �E�R���g���[���L�[
KEY_INPUT_ESCAPE					// �G�X�P�[�v�L�[
KEY_INPUT_SPACE						// �X�y�[�X�L�[
KEY_INPUT_PGUP						// �o�������t�o�L�[
KEY_INPUT_PGDN						// �o�������c�������L�[
KEY_INPUT_END						// �G���h�L�[
KEY_INPUT_HOME						// �z�[���L�[
KEY_INPUT_LEFT						// ���L�[
KEY_INPUT_UP						// ��L�[
KEY_INPUT_RIGHT						// �E�L�[
KEY_INPUT_DOWN						// ���L�[
KEY_INPUT_INSERT					// �C���T�[�g�L�[
KEY_INPUT_DELETE					// �f���[�g�L�[

KEY_INPUT_MINUS						// �|�L�[
KEY_INPUT_YEN						// ���L�[
KEY_INPUT_PREVTRACK					// �O�L�[
KEY_INPUT_PERIOD					// �D�L�[
KEY_INPUT_SLASH						// �^�L�[
KEY_INPUT_LALT						// ���`�k�s�L�[
KEY_INPUT_RALT						// �E�`�k�s�L�[
KEY_INPUT_SCROLL					// ScrollLock�L�[
KEY_INPUT_SEMICOLON					// �G�L�[
KEY_INPUT_COLON						// �F�L�[
KEY_INPUT_LBRACKET					// �m�L�[
KEY_INPUT_RBRACKET					// �n�L�[
KEY_INPUT_AT						// ���L�[
KEY_INPUT_BACKSLASH					// �_�L�[
KEY_INPUT_COMMA						// �C�L�[
KEY_INPUT_CAPSLOCK					// CaspLock�L�[
KEY_INPUT_PAUSE						// PauseBreak�L�[

KEY_INPUT_NUMPAD0					// �e���L�[�O
KEY_INPUT_NUMPAD1					// �e���L�[�P
KEY_INPUT_NUMPAD2					// �e���L�[�Q
KEY_INPUT_NUMPAD3					// �e���L�[�R
KEY_INPUT_NUMPAD4					// �e���L�[�S
KEY_INPUT_NUMPAD5					// �e���L�[�T
KEY_INPUT_NUMPAD6					// �e���L�[�U
KEY_INPUT_NUMPAD7					// �e���L�[�V
KEY_INPUT_NUMPAD8					// �e���L�[�W
KEY_INPUT_NUMPAD9					// �e���L�[�X
KEY_INPUT_MULTIPLY					// �e���L�[���L�[
KEY_INPUT_ADD						// �e���L�[�{�L�[
KEY_INPUT_SUBTRACT					// �e���L�[�|�L�[
KEY_INPUT_DECIMAL					// �e���L�[�D�L�[
KEY_INPUT_DIVIDE					// �e���L�[�^�L�[
KEY_INPUT_NUMPADENTER				// �e���L�[�̃G���^�[�L�[

KEY_INPUT_F1						// �e�P�L�[
KEY_INPUT_F2						// �e�Q�L�[
KEY_INPUT_F3						// �e�R�L�[
KEY_INPUT_F4						// �e�S�L�[
KEY_INPUT_F5						// �e�T�L�[
KEY_INPUT_F6						// �e�U�L�[
KEY_INPUT_F7						// �e�V�L�[
KEY_INPUT_F8						// �e�W�L�[
KEY_INPUT_F9						// �e�X�L�[
KEY_INPUT_F10						// �e�P�O�L�[
KEY_INPUT_F11						// �e�P�P�L�[
KEY_INPUT_F12						// �e�P�Q�L�[

KEY_INPUT_A							// �`�L�[
KEY_INPUT_B							// �a�L�[
KEY_INPUT_C							// �b�L�[
KEY_INPUT_D							// �c�L�[
KEY_INPUT_E							// �d�L�[
KEY_INPUT_F							// �e�L�[
KEY_INPUT_G							// �f�L�[
KEY_INPUT_H							// �g�L�[
KEY_INPUT_I							// �h�L�[
KEY_INPUT_J							// �i�L�[
KEY_INPUT_K							// �j�L�[
KEY_INPUT_L							// �k�L�[
KEY_INPUT_M							// �l�L�[
KEY_INPUT_N							// �m�L�[
KEY_INPUT_O							// �n�L�[
KEY_INPUT_P							// �o�L�[
KEY_INPUT_Q							// �p�L�[
KEY_INPUT_R							// �q�L�[
KEY_INPUT_S							// �r�L�[
KEY_INPUT_T							// �s�L�[
KEY_INPUT_U							// �t�L�[
KEY_INPUT_V							// �u�L�[
KEY_INPUT_W							// �v�L�[
KEY_INPUT_X							// �w�L�[
KEY_INPUT_Y							// �x�L�[
KEY_INPUT_Z							// �y�L�[
KEY_INPUT_0							// �O�L�[
KEY_INPUT_1							// �P�L�[
KEY_INPUT_2							// �Q�L�[
KEY_INPUT_3							// �R�L�[
KEY_INPUT_4							// �S�L�[
KEY_INPUT_5							// �T�L�[
KEY_INPUT_6							// �U�L�[
KEY_INPUT_7							// �V�L�[
KEY_INPUT_8							// �W�L�[
KEY_INPUT_9							// �X�L�[
*/