#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>
#include <vector>
#include <string>

#include "../Transform/Vec2/Vec2.h"

//�{�^����`���Ɏg���C���v�b�g�̎�� ����`���Ȃ��ƃo�O�L
enum InputType {
	Pad,
	KeyBoard,
	Mouse,
};

//�}�E�X�E�p�b�h( XINPUT�̂� )�E�L�[�{�[�h�̓��͂��Ǘ�����N���X
class Input {
public:

	// pad ��ύX�����4�̃R���g���[���[�ɑΉ� ���L�[�{�[�h�E�}�E�X�͑��₹�Ȃ�
	Input(int pad = DX_INPUT_PAD1);
	/*///  InputType  /// ��Œ�`�̏������Ŏg�p

	�@�@�@�@�@�@DX_INPUT_KEY_PAD1�@�@: �L�[���͂ƃp�b�h�P
�@�@�@�@�@�@�@�@DX_INPUT_PAD1�@�@�@�@: �p�b�h�P
�@�@�@�@�@�@�@�@DX_INPUT_PAD2�@�@�@�@: �p�b�h�Q
�@�@�@�@�@�@�@�@DX_INPUT_PAD3�@�@�@�@: �p�b�h�R
�@�@�@�@�@�@�@�@DX_INPUT_PAD4�@�@�@�@: �p�b�h�S
�@�@�@�@�@�@�@�@DX_INPUT_KEY�@�@�@�@ : �L�[����
	*/
	~Input();

	//�C���v�b�g�̏�Ԃ��X�V
	void update();

	//��`�����C���v�b�g�̖��O�� InputType �֌W�Ȃ��Ɏg�p�\
	bool GetInput(std::string ActionName);		//�����Ă����
	bool GetInputDown(std::string ActionName);	//�������u��
	bool GetInputUp(std::string ActionName);	//�����ꂽ�u��

	//�p�b�h�̊e����
	bool GetPad(int buttonID);
	bool GetPad(std::string ActionName);
	bool GetPadDown(int buttonID);
	bool GetPadDown(std::string ActionName);
	bool GetPadUp(int buttonID);
	bool GetPadUp(std::string ActionName);
	Vec2 GetPadLeftStick();
	Vec2 GetPadRightStick();
	float GetPadLeftTrigger();	//�g���K�[�{�^���ݒ�ł���悤�ɂ�������s�K�v����
	float GetPadRightTrigger();

	//�L�[�{�[�h�̊e����
	bool GetKey(int keyID);
	bool GetKey(std::string ActionName);
	bool GetKeyDown(int keyID);
	bool GetKeyDown(std::string ActionName);
	bool GetKeyUp(int keyID);
	bool GetKeyUp(std::string ActionName);

	//�}�E�X�̊e����
	bool IsMouseMoving(Vec2* velo);
	bool GetMouse(int button);
	bool GetMouse(std::string ActionName);
	bool GetMouseDown(int button);
	bool GetMouseDown(std::string ActionName);
	bool GetMouseUp(int button);
	bool GetMouseUp(std::string ActionName);
	Vec2 GetMousePos();
	float GetMouseWheel();

	//�{�^����String�Œ�`���A�ȈՐ؂�ւ��@�\
	void RegisterButton(std::string action, int buttonID, int inputType);
	//�}�E�X����ʓ��ɌŒ�
	void KeepCursorInScreen();
	//�}�E�X��\�����邩?
	void IsShowCursor(bool b);
	//�ǂꂩ�̃L�[���͂����邩?
	bool AnyKeyDown();
	//�p�b�h��U��������
	void PadVibration(int pow, int time, int effectIndex = -1);
	//�p�b�h�̃X�e�B�b�N�ɖ����͈�( 0.0�`1.0 )��ݒ�(default = 0.35)
	void PadStickDeadZone(float zone);

private:

	//��`�o�^�p
	enum {
		ActionName,
		InputID,
		InputType,
	};
	//vector����o�^�����{�^�����Ăяo��
	std::vector<int> InputIDFromList(std::string, int inputType);
	//���݂̃p�b�h
	int input_pad_{ 0 };

	//�p�b�h�̏��
	int pad_prev_state_[16]{ 0 };    //�O��
	int pad_current_state_[16]{ 0 }; //����

	//�L�[�{�[�h�̏��
	char key_prev_state_[256]{ '0' };
	char key_current_state_[256]{ '0' };

	//�}�E�X�̏��
	int mouse_prev_state_{ 0 };
	int mouse_current_state_{ 0 };

	//�}�E�X�̍��W���L�^
	Vec2 mouse_prev_pos_{ Vec2{0,0} };
	Vec2 mouse_current_pos_{ Vec2{0,0} };
	int get_mouseX, get_mouseY{ 0 };

	//��`���ꂽ�{�^���̖��O��ۑ����郊�X�g
	std::vector<std::vector<std::string>> buttonName;

	//�p�b�h�@�\���Ă� ( XInput���瓾�������������A�h���X )
	XINPUT_STATE input_;
};

#endif // !INPUT_H_
