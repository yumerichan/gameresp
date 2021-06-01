#include "DxLib.h"
#include "Scene/Scene.h"
#include "Scene/SceneTitle.h"
#include "Scene/ScenePlay.h"
#include "common.h"
#include "Scene/SceneClear.h"
#include "Scene/SceneGameOver.h"
#include "Input/Input.h"

//#define WINDOW_WIDTH (1240)	元の値
//#define WINDOW_HEIGHT (720)

//シーン情報


//現在のシーンID
int g_CurrentSceneID = SCENE_ID_INIT_TITLE;
int g_CurrentPlaySceneID ;

//タイトル・クリア・ゲームオーバー情報
//#define TITLE_PATH "Data/BgTitle.png"
#define CLEAR_PATH "Data/BgClear.png"
#define GAMEOVER_PATH "Data/BgGameOver.png"




//フレームレート情報変数
FrameRateInfo frameRateInfo;


//FPS計算
void CalcFPS();

//FPS表示(デバック用)
void DrawFPS();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの状態を設定する
	ChangeWindowMode(true);

	//DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//ウィンドウサイズを変更
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	//描画するスクリーンを設定
	SetDrawScreen(DX_SCREEN_BACK);

	//タイトル画面を初期化
	//int titlehandle = LoadGraph(TITLE_PATH);

	//クリア画面を設定
	int clearhandle = LoadGraph(CLEAR_PATH);

	int gameoverhandle = LoadGraph(GAMEOVER_PATH);

	//================================
	//	入力初期化
	//================================
	InitInput();

	//=====================================
	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		Sleep(1);//システムに処理を返す

		frameRateInfo.currentTime = GetNowCount();

		//最初のループなら
		//現在の時間を、FPSの計算をした時間に設定
		if (frameRateInfo.calcFpsTime == 0.0f)
		{
			frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
			frameRateInfo.fps = (float)FRAME_RATE;
		}
		//現在の時間が、前回のフレーム時より
		//1000/60ミリ秒(1/60秒）以上経過していたら処理を実行する
		if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME)
		{

			//フレーム実行時の時間を更新
			frameRateInfo.lastFrameTime = frameRateInfo.currentTime;

			//フレーム数をカウント
			frameRateInfo.count++;

			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
				//エスケープキーが押されたら終了
			}

			//画面に表示されたものを初期化（１ループの１度だけ行う）
			ClearDrawScreen();

			//==================================
			//	入力ステップ
			//==================================
			StepInput();




			/////////////////////////////////////////////////////////////////////////////
			
			
			//==================================
			//	シーンIDによって処理の振替が行われる
			//==================================

			switch (g_CurrentSceneID)
			{

			case SCENE_ID_INIT_TITLE:
			{
				int g_CurrentPlaySceneID = PLAY_SCENE_NORMAL_ONE;
				//======================
				//	タイトル初期化
				//======================
				InitTitle();

			}//SCENE_ID_INIT_TITLE終わりの括弧
			break;

			case SCENE_ID_LOOP_TITLE:
			{
				//======================
				//	タイトル通常処理
				//======================
				StepTitle();

				//======================
				//	タイトル描画処理
				//======================
				DrawTitle();
			}//SCENE_ID_LOOP_TITLE終わりの括弧
			break;

			case SCENE_ID_FIN_TITLE: 
			{
				//======================
				//	タイトル後処理
				//======================
				FinTitle();
			}
			break;

			case  SCENE_ID_INIT_NORMAL_PLAY:
			{
				//======================
				//	プレイ初期化
				//======================
				InitPlay();
			}//SCENE_ID_INIT_NORMAL_PLAY終わりの括弧
			break;

			case  SCENE_ID_INIT_BOSS_PLAY:
			{
			//======================
			//	プレイ初期化
			//======================
				InitPlay();
			//======================
			//	ボスプレイ初期化
			//======================
				InitBossPlay();
			}//SCENE_ID_INIT_BOSS_PLAY終わりの括弧
			break;

			case  SCENE_ID_LOOP_PLAY:
			{
				//======================
				//	プレイ描画処理
				//======================
				DrawPlay();
				//======================
				//	プレイ通常処理
				//======================
				StepPlay();

			}//SCENE_ID_LOOP_PLAY終わりの括弧
			break;

			case SCENE_ID_FIN_PLAY:
			{
				//======================
				//	プレイ後処理
				//======================
				FinPlay();
			}
			break;

			case SCENE_ID_INIT_CLEAR:
			{
				//======================
				//	クリア初期化
				//======================
				InitClear();
			}//SCENE_ID_INIT_CLEAR終わりの括弧
			break;

			case SCENE_ID_LOOP_CLEAR:
			{
				//======================
				//	クリア描画処理
				//======================
				DrawClear();
				//======================
				//	クリア通常処理
				//======================
				StepClear();
			}//SCENE_ID_LOOP_CLEAR終わりの括弧
			break;

			case SCENE_ID_FIN_CLEAR:
			{
				//======================
				//	クリア後処理
				//======================
				FinClear();
			}
			break;

			case SCENE_ID_INIT_GAMEOVER:
			{
				//======================
				//	ゲームオーバー初期化
				//======================
				InitGameOver();
			}//SCENE_ID_INIT_GAMEOVER終わりの括弧
			break;

			case SCENE_ID_LOOP_GAMEOVER:
			{
				//======================
				//	ゲームオーバー描画処理
				//======================
				DrawGameOver();
				//======================
				//	ゲームオーバー通常処理
				//======================
				StepGameOver();
			}//SCENE_ID_LOOP_GAMEOVER終わりの括弧
			break;

			case SCENE_ID_FIN_GAMEOVER:
			{
				//======================
				//	ゲームオーバー後処理
				//======================
				FinGameOver();
			}
			break;

			}

			//=========================
			//フリップ関数（ループの終わりに１度だけ行う）
			ScreenFlip();
		}
		//FPS計算
		CalcFPS();

		//FPS表示
		DrawFPS();

	}
	//最後に１回だけやる処理をここに書く
	//DXライブラリの後処理

	DxLib_End();

	return 0;
}

//FPS計算
void CalcFPS()
{
	//前回のFPSを計算した時間からの経過時間を求める
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	//前回のFPSを計算した時間から
	//一秒以上経過していたらFPSを計算する
	if (difTime > 1000)
	{
		//フレーム回数をミリ秒に合わせる
		//少数まで出したいのでfloatにキャスト
		float frameCount = (float)(frameRateInfo.count * 1000.0f);

		//FPSを求める
		//理想の数値は 60000/10000で60となる
		frameRateInfo.fps = frameCount / difTime;

		//フレームレートカウントをクリア
		frameRateInfo.count = 0;

		//FPSを計算した時間を更新
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

//FPS表示(デバック用)
void DrawFPS()
{
	unsigned int color = GetColor(255, 30, 30);
	/*DrawFormatString(695, 580, color, "FPS[%.2f]", frameRateInfo.fps);*/
}


//DrawString(200,200, "aaaaaaaaaaaa",GetColor(255,255,255));