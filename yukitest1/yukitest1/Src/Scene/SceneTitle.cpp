#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"
#include "../Sound/Sound.h"




#define ID_GAME_START	(0)	//ゲームスタートのID
#define ID_QUIT	(1)	//QuitのID
#define ID_NORMAL_MODE	(100)	//ノーマルモードのID
#define ID_VS_BOSS	(101)	//VSBOSSのID

#define TYPE_ID_TITLE (1000)	//タイトルのタイプのID
#define TYPE_ID_MODE_SELECT (1001)	//タイトルのモードセレクトのID




//==================================
//　タイトル画像のハンドル設定
//==================================
const char graphFilePath[GRAPH_TYPE_NUM][256] =
{
	"Data/BgTitle.png",
	"Data/Arrow.png",
	"Data/GameStart.png",
	"Data/Quit.png",
	"Data/NormalMode.png",
	"Data/VsBoss.png",

};

//==================================
//　タイトル画像のハンドル作成
//==================================
int graphHandle[GRAPH_TYPE_NUM];

//=======================
//	Arrowの設定登録
//=======================
struct ArrowInfo {
	int x, y;	//x.y
	int index;	//index
	int maxIndex;	//最大index
	int numIndex;	//最小index

};
ArrowInfo arrowInfo = { 0 };	//ArrowInfoをarrowInfoとして宣言

//=======================
//	タイトルタイプを作成
//=======================
int currentTitleType;	//現在のタイトルタイプ
int preTitleType;	//前のタイトルタイプ

//==================================
//	タイトル初期化
//==================================
void InitTitle() 
{

	//サウンド初期化	ここで全てのサウンドを初期化してるので、時間があったらシーン毎に分けても良いかもしれない(05/28	未対応)
	InitSound();

	//必要なサウンドのロード
	LoadSE(SE_TYPE_ARROW_MOVE);	//やじるしが動いた時の音
	LoadSE(SE_TYPE_SELECT);	//選んだ時の音


	//画像初期化
	for (int graph_index = 0; graph_index < GRAPH_TYPE_NUM; graph_index++)	//グラフの数だけ初期化する
	{
		graphHandle[graph_index] = LoadGraph(graphFilePath[graph_index]);	//graphFilePathにある奴を上から順番にロード
	}

	//やじるしの初期化
	arrowInfo.x = 25;	//x座標
	arrowInfo.y = 568;	//y座標
	arrowInfo.index = 0;	//やじるしがどこにあるか
	arrowInfo.maxIndex = 1;	//indexの最大の数を設定
	arrowInfo.numIndex = 0;	//indexの最小の数を設定

	//タイトルタイプの初期化
	currentTitleType = TYPE_ID_TITLE;	//現在のIDタイプをタイトルに設定
	preTitleType = currentTitleType;	//前のIDタイプをタイトルに設定


	//==================================
	//　タイトルループへ
	//==================================
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//==================================
//	タイトル通常処理
//==================================
void StepTitle() 
{
	//=======================
	//	Arrowの移動処理
	//=======================
	if ((IsKeyPush(KEY_INPUT_DOWN) == 1) || (IsKeyPush(KEY_INPUT_S) == 1))	//下キーが押された場合
	{
		PlaySE(SE_TYPE_ARROW_MOVE);	//SEをならす
			arrowInfo.index += 1;	//カーソルのindexを+1
			if(arrowInfo.index > arrowInfo.maxIndex)	//もしindexがMAXの値より大きいなら
			arrowInfo.index = arrowInfo.numIndex;	//最小のindexにする
	}

	if ((IsKeyPush(KEY_INPUT_UP) == 1) || (IsKeyPush(KEY_INPUT_W) == 1))	//上キーが押された場合
	{
		PlaySE(SE_TYPE_ARROW_MOVE);	//SEをならす
		arrowInfo.index -= 1;	//カーソルのindexを+1
		if (arrowInfo.index < arrowInfo.numIndex)	//もしindexがMINの値より小さいなら
			arrowInfo.index = arrowInfo.maxIndex;	//最大のindexにする
	}

	//==================================
	//　どこかでEnterキーか決定キー(Z)を押されたなら
	//==================================
	if (IsKeyPush(KEY_INPUT_RETURN) == 1 || IsKeyPush(KEY_INPUT_Z) == 1)
	{
		PlaySE(SE_TYPE_SELECT);	//SEをならす
		if (arrowInfo.index == ID_GAME_START)	//ゲームスタートを選んでいる時に押されたら
		{
			currentTitleType = TYPE_ID_MODE_SELECT;	//タイプをモードセレクトに繰り上げる
		}
		else if (arrowInfo.index == ID_QUIT)	//Quitを選んでいる時に押されたら
		{
			WaitTimer(200);	//0.2秒まって
			DxLib_End();	//ゲームを閉じる
		}
		else if (arrowInfo.index == ID_NORMAL_MODE)	//ノーマルモードで押したら
		{
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;	//　タイトルの後処理へ移動
		}
		else if (arrowInfo.index == ID_VS_BOSS)	//BOSSで押したら
		{
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;	//　タイトルの後処理へ移動
		}
	}
	//==================================
	//　どこかでEscキーか戻るボタン(x)を押されたなら
	//==================================
	if (IsKeyPush(KEY_INPUT_ESCAPE) == 1|| IsKeyPush(KEY_INPUT_X) == 1)
	{
		if (currentTitleType == TYPE_ID_TITLE)	//タイトルで押されたら
			DxLib_End();	//ゲームを閉じる
		else if (currentTitleType == TYPE_ID_MODE_SELECT)	//モードセレクトで押されたら
			currentTitleType = TYPE_ID_TITLE;	//タイトルに戻る
	}

	//=======================
	//	もしモード変更が起きならarrowInfoの情報を書き換える
	//=======================
	if (currentTitleType != preTitleType)
	{
		if(currentTitleType == TYPE_ID_TITLE)//もしタイプがタイトルだったら
		{
			arrowInfo.x = 25;	//x座標
			arrowInfo.y = 568;	//y座標
			arrowInfo.index = ID_GAME_START;	//やじるしをタイトルのデフォ位置に
			arrowInfo.maxIndex = 1;	//indexの最大の値を設定
			arrowInfo.numIndex = 0;	//indexの最小の値を設定
			preTitleType = TYPE_ID_TITLE;	//前のTITLE_IDを書き換える
		}
		else if (currentTitleType == TYPE_ID_MODE_SELECT)
		{
			arrowInfo.x = 25;	//x座標
			arrowInfo.y = 568;	//y座標
			arrowInfo.index = ID_NORMAL_MODE;	//やじるしをモードセレクトのデフォ位置に
			arrowInfo.maxIndex = 101;	//indexの最大の値を設定
			arrowInfo.numIndex = 100;	//indexの最小の値を設定
			preTitleType = TYPE_ID_MODE_SELECT;	//前のTITLE_IDを書き換える

		}
	}

}

//==================================
//	タイトル描画処理
//==================================
void DrawTitle() {
	//==================================
	//	タイトル描画処理
	//==================================
	DrawGraph(0, 0, graphHandle[BG_TITLE_PATH], true);

	//やじるし表示
	if(arrowInfo.index==0|| arrowInfo.index==100)	//もしやじるしの判定が上の位置なら
		DrawGraph(arrowInfo.x, arrowInfo.y, graphHandle[ARROW_PATH], true);	//上の位置にやじるしを書く
	else if(arrowInfo.index ==1 || arrowInfo.index == 101)	//やじるしの判定が下の位置なら
		DrawGraph(arrowInfo.x, arrowInfo.y + 100, graphHandle[ARROW_PATH], true);	//下の位置にやじるしを書く

	//=======================
	//	
	//=======================
	if (currentTitleType == TYPE_ID_TITLE)
	{
		DrawGraph(150, 550, graphHandle[GAME_START_PATH], true);	//ゲームスタート
		DrawGraph(150, 650, graphHandle[QUIT_PATH], true);	//Quit
	}
	else if (currentTitleType == TYPE_ID_MODE_SELECT)
	{
		DrawGraph(150, 550, graphHandle[NORMAL_MODE_PATH], true);	//ノーマルモード
		DrawGraph(150, 650, graphHandle[VS_BOSS_PATH], true);	//VSBOSS
	}





}

//==================================
//	タイトル後処理
//==================================
void FinTitle() {
	//==================================
	//	画像破棄
	//==================================
	for (int graph_index = 0; graph_index < GRAPH_TYPE_NUM; graph_index++)
	{
		DeleteGraph(graphHandle[graph_index]);
	}

	//==================================
	//	タイトル後処理の後はプレイへ
	//==================================
	if (arrowInfo.index == ID_NORMAL_MODE)
	{
		g_CurrentSceneID = SCENE_ID_INIT_NORMAL_PLAY;
	}
	else if (arrowInfo.index == ID_VS_BOSS)
	{
		g_CurrentSceneID = SCENE_ID_INIT_BOSS_PLAY;
	}
}