#pragma once

//=============================
//	タイトルシーンのID
//=============================
#define SCENE_ID_INIT_TITLE (100)	//初期化
#define SCENE_ID_LOOP_TITLE (101)	//繰り返し
#define SCENE_ID_FIN_TITLE	(102)	//後処理
//=============================
//	プレイシーンのID
//=============================
#define SCENE_ID_INIT_NORMAL_PLAY	(200)	//ノーマルモードの初期化
#define SCENE_ID_INIT_BOSS_PLAY	(201)	//モードBOSSの初期化
#define SCENE_ID_LOOP_PLAY	(202)	//繰り返し
#define SCENE_ID_FIN_PLAY	(203)	//後処理
//=============================
//	クリアシーンのID
//=============================
#define SCENE_ID_INIT_CLEAR (300)	//初期化
#define SCENE_ID_LOOP_CLEAR (301)	//繰り返し
#define SCENE_ID_FIN_CLEAR	(302)	//後処理
//=============================
//	ゲームオーバーシーンのID
//=============================
#define SCENE_ID_INIT_GAMEOVER	(400)	//初期化
#define SCENE_ID_LOOP_GAMEOVER	(401)	//繰り返し
#define SCENE_ID_FIN_GAMEOVER	(402)	//後処理


//=======================
//	プレイシーン中の弾幕ID
//=======================
#define PLAY_SCENE_BOSS_ONE	(1101)	//プレイシーンボス1,ランダム打ち
#define PLAY_SCENE_BOSS_TWO	(1102)	//プレイシーンボス2,
#define PLAY_SCENE_BOSS_THREE	(1103)	//プレイシーンボス3
#define PLAY_SCENE_BOSS_ENTRANCE	(1104)	//ボスの登場シーン
#define PLAY_SCENE_NORMAL_ONE	(1105)	//プレイシーンノーマル1

//プレイシーン中のID
extern int g_CurrentPlaySceneID;


//現在のシーンID
extern int g_CurrentSceneID;
