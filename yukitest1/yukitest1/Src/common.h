#pragma once


#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (960)

//==================================
//　プレイ画面の縦横サイズ	/61+20	/830 - 20	/21 + 20	/920 - 20
//==================================
#define PLAY_WINDOW_WIDTH_LEFT	(81)
#define PLAY_WINDOW_WIDTH_RIGHT	(810)
#define PLAY_WINDOW_HEIGHT_UP	(41)
#define PLAY_WINDOW_HEIGHT_DOWN	(900)

#define PLAY_WINDOW_WIDTH_SIZE	(729)
#define PLAY_WINDOW_HEIGHT_SIZE	(859)

//設定フレームレート(60FPS)
#define FRAME_RATE (60)

//１フレームの時間 (ミリ秒)
#define FRAME_TIME (1000 / FRAME_RATE )

struct FrameRateInfo
{
	int currentTime; //現在の時間
	int lastFrameTime; //前回のフレーム実行時の時間
	int count; //フレームカウント用
	int calcFpsTime; //FPSを計算した時間
	float fps; //計算したFPS
};

//
////フレームレート情報変数
//FrameRateInfo frameRateInfo;
