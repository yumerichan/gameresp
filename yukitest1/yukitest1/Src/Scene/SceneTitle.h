#pragma once


enum TITLE_GRAPH
{
	BG_TITLE_PATH,		//背景
	ARROW_PATH,		//やじるし
	GAME_START_PATH,	//GAME_START
	QUIT_PATH,	//Quit
	NORMAL_MODE_PATH,	//NormalMode
	VS_BOSS_PATH,	//VS_BOSS

	GRAPH_TYPE_NUM
};


//タイトル初期化
void InitTitle();

//タイトル通常処理
void StepTitle();

//タイトル描画処理
void DrawTitle();

//タイトル後処理
void FinTitle();
