#include "DxLib.h"
#include "Sound.h"


#define SE_VOLUME (30)


//���ʉ��t�@�C���p�X
const char seFilePath[SE_TYPE_NUM][256] =
{
	"Data/Sound/Shot.wav",
	"Data/Sound/EnemyDamage.wav",
	"Data/Sound/ArrowMove.wav",
	"Data/Sound/Select.wav",
	"Data/Sound/PlayerDamage.wav",
	"DAta/Sound/Clear.wav",

}; 

////BGM�t�@�C���p�X
//const char bgmFilePath[BGM_TYPE_NUM][256] =
//{
//	"Data/Sound/PlayBGM.mp3",
//};

//���ʉ��n���h��
int seHandle[SE_TYPE_NUM];

//BGM�n���h��
int bgmHandle[BGM_TYPE_NUM];

//�v���C�V�[���̃T�E���h�̏�����
//�e�V�[���̏��������ɌĂ�
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

//�T�E���h�̌㏈��
//�e�V�[���̌㏈�����ɌĂ�
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

//���ʉ��̓ǂݍ���
void LoadSE(SE_TYPE type)
{
	seHandle[type] = LoadSoundMem(seFilePath[type]);
	ChangeVolumeSoundMem(255 * SE_VOLUME / 100, seHandle[type]);	//���ʂ�20%��

}

//���ʉ��̍Đ�
void PlaySE(SE_TYPE type)
{
	PlaySoundMem(seHandle[type], DX_PLAYTYPE_BACK, true);
}

//BGM�̓ǂݍ���
void LoadBGM(BGM_TYPE type)
{
	//bgmHandle[type] = LoadSoundMem(bgmFilePath[type]);
}

//BGM�̍Đ�
void PlayBGM(BGM_TYPE type)
{
	PlaySoundMem(bgmHandle[type], DX_PLAYTYPE_LOOP, 1);
}

//BGM�̒�~
void StopBGM(BGM_TYPE type)
{
	StopSoundMem(bgmHandle[type]);
}

