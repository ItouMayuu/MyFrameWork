#include <DxLib.h>
#include <stdio.h>
#include <windows.system.h>
#include <windows.system.diagnostics.h>
#include <windows.system.threading.h>

#include "Game.h"
#include "Library/Screen/Screen.h"
#include "Library/NotChangingLibrary/Timer.h"

//
//�����ŕϐ���p��

int TargetFPS = 60; // �ڕW��FPS(Frame Per Second, 1�b������̃t���[����)
static bool EnableFrameSkip = true;
double MaxAllowSkipTime = 0.2;
long IntervalTicks = (long)(1.0 / TargetFPS * 10000000);
int MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);

static long nextFrameTicks = IntervalTicks;
static int skipCount = 0;
static long fpsTicks = 0;
static int fpsFrameCount = 0;

///<summary>
///Current FPS
///</summary>
static float CurrentFPS;

static void GameDraw(Game &game)
{
	ClearDrawScreen();
	game.Draw();
	ScreenFlip();
	skipCount = 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
    SetWaitVSyncFlag(GetRefreshRate() == TargetFPS ? TRUE : FALSE);
    ChangeWindowMode(!Screen::FullScreen);//��S��ʂɃZ�b�g
    SetGraphMode(Screen::Width, Screen::Height, 32);//��ʃT�C�Y�w��
    SetMainWindowText(Screen::Title.c_str());
    SetAlwaysRunFlag(TRUE);

	if (DxLib_Init() == 1) { return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��
	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseTransColor(FALSE);

	//
	//�����ŉ摜�E����ǂݍ���
	Game game;
	game.Init();
    DrawString(0, 100, std::to_string(CurrentFPS).c_str(), GetColor(255, 255, 255));

	MyTimer& timer = MyTimer::GetInstance();
	ScreenFlip();

    timer.Init();
	//

	while (ProcessMessage() == 0)
	{
		// FPS�̌v��(FPS = 1�b������̃p���p�����文��)
		fpsFrameCount++;
		if (fpsFrameCount >= 60)
		{   // �o�ߎ��� 1Tick = 100�i�m�b = 1/10000000�b (elasped=�o��)
			long elapsedTicks = timer.GetElapsedTicks() - fpsTicks;
			float elapsedSec = (float)elapsedTicks / 10000000;
			CurrentFPS = fpsFrameCount / elapsedSec;// ���݂�FPS

			fpsFrameCount = 0; // 60����������0���Z�b�g
			// 60���������猻�݂�FPS(�p���p�����x)���L�^
			fpsTicks = timer.GetElapsedTicks();
		}

		game.Update(); //�Q�[���̍X�V����

		//[�����@�\]�X���[���[�V�����A������(time.timeScale��0.5��2�{��2.0��1/2�X���[)
		if (timer.isTimeScaleMode && timer.timeScale > 0)
		{   // �t���[�����[�g���Čv�Z���������X���[���[�V����
			TargetFPS = (int)(60 / timer.timeScale); // �ڕW��FPS(Frame Per Second, 1�b������̃t���[����)
			MaxAllowSkipTime = 0.2; // �t���[���X�L�b�v����ő�Ԋu�i�b�j�B����ȏ�̊Ԋu���󂢂��ꍇ�̓X�L�b�v�����ɏ��������ɂ���B
			IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // �t���[���Ԃ�Tick���B1Tick = 100�i�m�b = 1/10000000�b
			MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);
		}
        // ������������DX�ݒ�Ō����Ă���Ȃ�DX���C�u������Wait������C������(�t���[���X�L�b�v���������ł��)
        if (GetWaitVSyncFlag() == TRUE && timer.isTimeScaleMode == false)
        {   // ���t���[���X�L�b�v�Ƃ͕`�揈�����d�����Ƀp���p�������1����΂���?
            if (EnableFrameSkip)
            {   // ���]�������� = ���̃p���p���\�莞�� - ���݂̎���
                long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
                if (waitTicks < 0) // �ڕW�������I�[�o�[���Ă���
                {   //�����܂薟��̃p���p���y�[�W�����΂��ƃL���������[�v���Č�����̂Ō��x�����Ă�
                    if (skipCount < MaxAllowSkipCount) // �A���t���[���X�L�b�v�����ő�X�L�b�v���𒴂��Ă��Ȃ����
                    {
                        skipCount++; // �t���[���X�L�b�v�i�`�揈�����΂��j
                    }
                    else
                    {   // �ő�X�L�b�v���𒴂��Ă�̂ŁA�t���[���X�L�b�v���Ȃ��ŕ`��
                        nextFrameTicks = timer.GetElapsedTicks();
                        GameDraw(game); // �����x�z���ŃX���[�`�揈���ɐؑւ�
                    }
                }
                else
                {   // �ڕW����OK�Ȃ̂Ńt���[���X�L�b�v���Ȃ��ŕ`��
                    // ��DX���C�u�����������ŉt����60Hz�ƃ^�C�~���O���킹�ĕ`��
                    GameDraw(game); // �`�揈��
                }
                // ���̃p���p���\�莞����IntervalTicks(�P��:100�i�m�b)����
                nextFrameTicks += IntervalTicks;
            }
            else
            {   // ������else�͉��������Ă��t���[���X�L�b�v���Ȃ��ݒ�̎��ɗ���
                GameDraw(game); // ���X���[�`�揈��
            }
        }
        else
        {   // ������������DX�ݒ�Ły�����ĂȂ��z�Ȃ�Wait���������͂ł��(�t���[���X�L�b�v�������ł��)
            // ��������̓t���[���X�L�b�v����(waitTicks = ���̃p���p���\�莞�� - ���݂̎���)
            long waitTicks = nextFrameTicks - timer.GetElapsedTicks(); // �]�������ԁi�ҋ@���K�v�Ȏ��ԁj
            if (EnableFrameSkip && waitTicks < 0)
            {   // ���܂薟��̃p���p���y�[�W�����΂��ƃL���������[�v���Č�����̂Ō��x�����Ă�
                if (skipCount < MaxAllowSkipCount)
                {
                    skipCount++; // �t���[���X�L�b�v�i�`�揈�����΂��j
                }
                else
                {   // ���̃p���p���\�莞�����������ɐݒ肷��̂Ŏ�����Βx���waitTicks < 0�ɂȂ�
                    nextFrameTicks = timer.GetElapsedTicks();
                    GameDraw(game); //�x����X���[���[�V�����ŕ`���Ă䂭�ݒ�̎��͂���
                }
            }
            else
            {   // �����͂�Wait����
                if (waitTicks > 20000) // ����2�~���b�ȏ�҂K�v������
                {   // ������Time�N���X��Sleep�ň�莞�ԃv���O�����x�~
                    // https://marycore.jp/prog/objective-c/sleep-process/#sleep_for
                    // Sleep�͎w�肵�����ԂŃs�b�^���߂��Ă���킯�ł͂Ȃ��̂ŁA
                    // �]�T�������āA�u�҂��Ȃ���΂Ȃ�Ȃ�����-2�~���b�vSleep����
                    int waitMillsec = (int)(waitTicks / 10000) - 2;
                    timer.SleepForMilliSec(waitMillsec);
                }

                // ���Ԃ�����܂ŉ������Ȃ����[�v���񂵂đҋ@����
                while (timer.GetElapsedTicks() < nextFrameTicks)
                {   // ����̎��ԂɂȂ�܂ŋ󃋁[�v
                }

                GameDraw(game); // ����̎��ԂɂȂ�����`�揈��
            }
            // ���̃p���p���\�莞����IntervalTicks(�P��:100�i�m�b)����
            nextFrameTicks += IntervalTicks;
        }
    }
	DxLib_End();
	return 0;
}
