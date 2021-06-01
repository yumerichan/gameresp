#include "DxLib.h"
#include "Sound.h"


#define SE_VOLUME (30)


//効果音ファイルパス
const char seFilePath[SE_TYPE_NUM][256] =
{
	"Data/Sound/Shot.wav",
	"Data/Sound/EnemyDamage.wav",
	"Data/Sound/ArrowMove.wav",
	"Data/Sound/Select.wav",
	"Data/Sound/PlayerDamage.wav",
	"DAta/Sound/Clear.wav",

}; 

////BGMファイルパス
//const char bgmFilePath[BGM_TYPE_NUM][256] =
//{
//	"Data/Sound/PlayBGM.mp3",
//};

//効果音ハンドル
int seHandle[SE_TYPE_NUM];

//BGMハンドル
int bgmHandle[BGM_TYPE_NUM];

//プレイシーンのサウンドの初期化
//各シーンの初期化時に呼ぶ
void InitSound()
{
	for (int se_index = 0; se_index < SE_TYPE_NUM; se_index++)
	{
		seHandle[se_index] = 0;
	}

	for (int bgm_index = 0; bgm_index < BGM_TYPE_NUM; bgm_index++)
	{
		bgmHandle[bgm_index] = 0;
	}
}

//サウンドの後処理
//各シーンの後処理時に呼ぶ
void FinSound()
{
	for (int se_index = 0; se_index < SE_TYPE_NUM; se_index++)
	{
		DeleteSoundMem(seHandle[se_index]);
	}

	for (int bgm_index = 0; bgm_index < BGM_TYPE_NUM; bgm_index++)
	{
		DeleteSoundMem(seHandle[bgm_index]);
	}
}

//効果音の読み込み
void LoadSE(SE_TYPE type)
{
	seHandle[type] = LoadSoundMem(seFilePath[type]);
	ChangeVolumeSoundMem(255 * SE_VOLUME / 100, seHandle[type]);	//音量を20%に

}

//効果音の再生
void PlaySE(SE_TYPE type)
{
	PlaySoundMem(seHandle[type], DX_PLAYTYPE_BACK, true);
}

//BGMの読み込み
void LoadBGM(BGM_TYPE type)
{
	//bgmHandle[type] = LoadSoundMem(bgmFilePath[type]);
}

//BGMの再生
void PlayBGM(BGM_TYPE type)
{
	PlaySoundMem(bgmHandle[type], DX_PLAYTYPE_LOOP, 1);
}

//BGMの停止
void StopBGM(BGM_TYPE type)
{
	StopSoundMem(bgmHandle[type]);
}

