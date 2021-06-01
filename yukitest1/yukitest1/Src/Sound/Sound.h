#pragma once


//効果音種類
enum SE_TYPE
{
	SE_TYPE_PLAYER_SHOT,		//プレイヤーの発射音
	SE_TYPE_ENEMY_DAMAGE,		//敵のダメージ
	SE_TYPE_ARROW_MOVE,
	SE_TYPE_SELECT,
	SE_TYPE_PLAYER_DAMAGE,
	SE_TYPE_CLEAR,

	SE_TYPE_NUM
};

//BGM種類
enum BGM_TYPE
{
	BGM_TYPE_PLAY,		//プレイシーンのBGM

	BGM_TYPE_NUM
};

//サウンドの初期化
//各シーンの初期化時に呼ぶ
void InitSound();

//サウンドの後処理
//各シーンの後処理時に呼ぶ
void FinSound();

//効果音の読み込み
void LoadSE(SE_TYPE type);

//効果音の再生
void PlaySE(SE_TYPE type);

//BGMの読み込み
void LoadBGM(BGM_TYPE type);

//BGMの再生
void PlayBGM(BGM_TYPE type);

//BGMの停止
void StopBGM(BGM_TYPE type);
