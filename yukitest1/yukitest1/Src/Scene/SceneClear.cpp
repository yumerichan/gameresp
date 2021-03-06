#include "DxLib.h"
#include "Scene.h"
#include "SceneClear.h"
#include "../Input/Input.h"
#include "../Sound/Sound.h"

//==================================
//　クリア背景画像のパス
//==================================
#define BG_CLEAR_PATH	"Data/BgClear.png"

//==================================
//　クリア画像のハンドル
//==================================
int bgClearHandle;

int seCheck;

//==================================
//	クリア初期化
//==================================
void InitClear()
{
	//==================================
	//　クリア背景初期化
	//==================================
	bgClearHandle = LoadGraph(BG_CLEAR_PATH);
	//=======================
	//	クリアした時の音をロード、初期化
	//=======================
	LoadSE(SE_TYPE_CLEAR);
	seCheck = false;

	//==================================
	//　クリアループへ
	//==================================
	g_CurrentSceneID = SCENE_ID_LOOP_CLEAR;
}

//==================================
//	クリア通常処理
//==================================
void StepClear()
{
	if (seCheck == false)
	{
		seCheck = true;
		PlaySE(SE_TYPE_CLEAR);
	}
	//==================================
	//　EnterキーかZキーを押されたなら
	//==================================
	if (IsKeyPush(KEY_INPUT_RETURN) == 1 || IsKeyPush(KEY_INPUT_Z) == 1)
	{
		//==================================
		//　クリア後処理へ移動
		//==================================
		g_CurrentSceneID = SCENE_ID_FIN_CLEAR;//プレイシーンのID
	}
}

//==================================
//	クリア描画処理
//==================================
void DrawClear() {
	//==================================
	//	クリア描画処理
	//==================================
	DrawGraph(0, 0, bgClearHandle, true);
}


//==================================
//	クリア後処理
//==================================
void FinClear() {
	//==================================
	//	クリア画像破棄
	//==================================
	DeleteGraph(bgClearHandle);
	//==================================
	//サウンドの後処理
	//==================================
	//サウンドの後処理
	FinSound();
	//==================================
	//	タイトルシーン初期化へ
	//==================================
	g_CurrentSceneID = SCENE_ID_INIT_TITLE;
}
