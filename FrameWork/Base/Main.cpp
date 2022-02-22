#include <DxLib.h>
#include <stdio.h>
#include <windows.system.h>
#include <windows.system.diagnostics.h>
#include <windows.system.threading.h>

#include "Game.h"
#include "Library/Screen/Screen.h"
#include "Library/NotChangingLibrary/Timer.h"

//
//ここで変数を用意

int TargetFPS = 60; // 目標のFPS(Frame Per Second, 1秒あたりのフレーム数)
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
    SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
    SetWaitVSyncFlag(GetRefreshRate() == TargetFPS ? TRUE : FALSE);
    ChangeWindowMode(!Screen::FullScreen);//非全画面にセット
    SetGraphMode(Screen::Width, Screen::Height, 32);//画面サイズ指定
    SetMainWindowText(Screen::Title.c_str());
    SetAlwaysRunFlag(TRUE);

	if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了
	SetMouseDispFlag(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseTransColor(FALSE);

	//
	//ここで画像・音を読み込み
	Game game;
	game.Init();
    DrawString(0, 100, std::to_string(CurrentFPS).c_str(), GetColor(255, 255, 255));

	MyTimer& timer = MyTimer::GetInstance();
	ScreenFlip();

    timer.Init();
	//

	while (ProcessMessage() == 0)
	{
		// FPSの計測(FPS = 1秒あたりのパラパラ漫画枚数)
		fpsFrameCount++;
		if (fpsFrameCount >= 60)
		{   // 経過時間 1Tick = 100ナノ秒 = 1/10000000秒 (elasped=経過)
			long elapsedTicks = timer.GetElapsedTicks() - fpsTicks;
			float elapsedSec = (float)elapsedTicks / 10000000;
			CurrentFPS = fpsFrameCount / elapsedSec;// 現在のFPS

			fpsFrameCount = 0; // 60枚数えたら0リセット
			// 60枚数えたら現在のFPS(パラパラ速度)を記録
			fpsTicks = timer.GetElapsedTicks();
		}

		game.Update(); //ゲームの更新処理

		//[実験機能]スローモーション、早送り(time.timeScaleが0.5で2倍速2.0で1/2スロー)
		if (timer.isTimeScaleMode && timer.timeScale > 0)
		{   // フレームレートを再計算し早送りやスローモーション
			TargetFPS = (int)(60 / timer.timeScale); // 目標のFPS(Frame Per Second, 1秒あたりのフレーム数)
			MaxAllowSkipTime = 0.2; // フレームスキップする最大間隔（秒）。これ以上の間隔が空いた場合はスキップせずに処理落ちにする。
			IntervalTicks = (long)(1.0 / TargetFPS * 10000000); // フレーム間のTick数。1Tick = 100ナノ秒 = 1/10000000秒
			MaxAllowSkipCount = (int)(TargetFPS * MaxAllowSkipTime);
		}
        // ★垂直同期がDX設定で効いているならDXライブラリにWait処理を任せられる(フレームスキップだけ自分でやる)
        if (GetWaitVSyncFlag() == TRUE && timer.isTimeScaleMode == false)
        {   // ★フレームスキップとは描画処理が重い時にパラパラ漫画を1枚飛ばすか?
            if (EnableFrameSkip)
            {   // ★余った時刻 = 次のパラパラ予定時刻 - 現在の時刻
                long waitTicks = nextFrameTicks - timer.GetElapsedTicks();
                if (waitTicks < 0) // 目標時刻をオーバーしている
                {   //★あまり漫画のパラパラページ数を飛ばすとキャラがワープして見えるので限度をつけてる
                    if (skipCount < MaxAllowSkipCount) // 連続フレームスキップ数が最大スキップ数を超えていなければ
                    {
                        skipCount++; // フレームスキップ（描画処理を飛ばす）
                    }
                    else
                    {   // 最大スキップ数を超えてるので、フレームスキップしないで描画
                        nextFrameTicks = timer.GetElapsedTicks();
                        GameDraw(game); // ★限度越えでスロー描画処理に切替え
                    }
                }
                else
                {   // 目標時刻OKなのでフレームスキップしないで描く
                    // ★DXライブラリが自動で液晶の60Hzとタイミング合わせて描画
                    GameDraw(game); // 描画処理
                }
                // 次のパラパラ予定時刻はIntervalTicks(単位:100ナノ秒)あと
                nextFrameTicks += IntervalTicks;
            }
            else
            {   // ここのelseは何があってもフレームスキップしない設定の時に来る
                GameDraw(game); // ★スロー描画処理
            }
        }
        else
        {   // ★垂直同期がDX設定で【効いてない】ならWait処理を自力でやる(フレームスキップも自分でやる)
            // ↓こちらはフレームスキップ処理(waitTicks = 次のパラパラ予定時刻 - 現在の時刻)
            long waitTicks = nextFrameTicks - timer.GetElapsedTicks(); // 余った時間（待機が必要な時間）
            if (EnableFrameSkip && waitTicks < 0)
            {   // あまり漫画のパラパラページ数を飛ばすとキャラがワープして見えるので限度をつけてる
                if (skipCount < MaxAllowSkipCount)
                {
                    skipCount++; // フレームスキップ（描画処理を飛ばす）
                }
                else
                {   // 次のパラパラ予定時刻を現時刻に設定するので次も絶対遅れてwaitTicks < 0になる
                    nextFrameTicks = timer.GetElapsedTicks();
                    GameDraw(game); //遅れつつもスローモーションで描いてゆく設定の時はここ
                }
            }
            else
            {   // ★自力でWait処理
                if (waitTicks > 20000) // あと2ミリ秒以上待つ必要がある
                {   // ★自作TimeクラスのSleepで一定時間プログラム休止
                    // https://marycore.jp/prog/objective-c/sleep-process/#sleep_for
                    // Sleepは指定した時間でピッタリ戻ってくるわけではないので、
                    // 余裕を持って、「待たなければならない時間-2ミリ秒」Sleepする
                    int waitMillsec = (int)(waitTicks / 10000) - 2;
                    timer.SleepForMilliSec(waitMillsec);
                }

                // 時間が来るまで何もしないループを回して待機する
                while (timer.GetElapsedTicks() < nextFrameTicks)
                {   // 所定の時間になるまで空ループ
                }

                GameDraw(game); // 所定の時間になったら描画処理
            }
            // 次のパラパラ予定時刻はIntervalTicks(単位:100ナノ秒)あと
            nextFrameTicks += IntervalTicks;
        }
    }
	DxLib_End();
	return 0;
}
