#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>
#include <vector>
#include <string>

#include "../Transform/Vec2/Vec2.h"

//ボタン定義時に使うインプットの種類 ※定義しないとバグ有
enum InputType {
	Pad,
	KeyBoard,
	Mouse,
};

//マウス・パッド( XINPUTのみ )・キーボードの入力を管理するクラス
class Input {
public:

	// pad を変更すれば4つのコントローラーに対応 ※キーボード・マウスは増やせない
	Input(int pad = DX_INPUT_PAD1);
	/*///  InputType  /// 上で定義の初期化で使用

	　　　　　　DX_INPUT_KEY_PAD1　　: キー入力とパッド１
　　　　　　　　DX_INPUT_PAD1　　　　: パッド１
　　　　　　　　DX_INPUT_PAD2　　　　: パッド２
　　　　　　　　DX_INPUT_PAD3　　　　: パッド３
　　　　　　　　DX_INPUT_PAD4　　　　: パッド４
　　　　　　　　DX_INPUT_KEY　　　　 : キー入力
	*/
	~Input();

	//インプットの状態を更新
	void update();

	//定義したインプットの名前を InputType 関係なしに使用可能
	bool GetInput(std::string ActionName);		//押している間
	bool GetInputDown(std::string ActionName);	//押した瞬間
	bool GetInputUp(std::string ActionName);	//離された瞬間

	//パッドの各種状態
	bool GetPad(int buttonID);
	bool GetPad(std::string ActionName);
	bool GetPadDown(int buttonID);
	bool GetPadDown(std::string ActionName);
	bool GetPadUp(int buttonID);
	bool GetPadUp(std::string ActionName);
	Vec2 GetPadLeftStick();
	Vec2 GetPadRightStick();
	float GetPadLeftTrigger();	//トリガーボタン設定できるようにしたから不必要かも
	float GetPadRightTrigger();

	//キーボードの各種状態
	bool GetKey(int keyID);
	bool GetKey(std::string ActionName);
	bool GetKeyDown(int keyID);
	bool GetKeyDown(std::string ActionName);
	bool GetKeyUp(int keyID);
	bool GetKeyUp(std::string ActionName);

	//マウスの各種状態
	bool IsMouseMoving(Vec2* velo);
	bool GetMouse(int button);
	bool GetMouse(std::string ActionName);
	bool GetMouseDown(int button);
	bool GetMouseDown(std::string ActionName);
	bool GetMouseUp(int button);
	bool GetMouseUp(std::string ActionName);
	Vec2 GetMousePos();
	float GetMouseWheel();

	//ボタンをStringで定義し、簡易切り替え機能
	void RegisterButton(std::string action, int buttonID, int inputType);
	//マウスを画面内に固定
	void KeepCursorInScreen();
	//マウスを表示するか?
	void IsShowCursor(bool b);
	//どれかのキー入力があるか?
	bool AnyKeyDown();
	//パッドを振動させる
	void PadVibration(int pow, int time, int effectIndex = -1);
	//パッドのスティックに無効範囲( 0.0～1.0 )を設定(default = 0.35)
	void PadStickDeadZone(float zone);

private:

	//定義登録用
	enum {
		ActionName,
		InputID,
		InputType,
	};
	//vectorから登録したボタンを呼び出す
	std::vector<int> InputIDFromList(std::string, int inputType);
	//現在のパッド
	int input_pad_{ 0 };

	//パッドの状態
	int pad_prev_state_[16]{ 0 };    //前回
	int pad_current_state_[16]{ 0 }; //現在

	//キーボードの状態
	char key_prev_state_[256]{ '0' };
	char key_current_state_[256]{ '0' };

	//マウスの状態
	int mouse_prev_state_{ 0 };
	int mouse_current_state_{ 0 };

	//マウスの座標を記録
	Vec2 mouse_prev_pos_{ Vec2{0,0} };
	Vec2 mouse_current_pos_{ Vec2{0,0} };
	int get_mouseX, get_mouseY{ 0 };

	//定義されたボタンの名前を保存するリスト
	std::vector<std::vector<std::string>> buttonName;

	//パッド機能を呼ぶ ( XInputから得られる情報を代入するアドレス )
	XINPUT_STATE input_;
};

#endif // !INPUT_H_
