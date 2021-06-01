#pragma once


//���ʉ����
enum SE_TYPE
{
	SE_TYPE_PLAYER_SHOT,		//�v���C���[�̔��ˉ�
	SE_TYPE_ENEMY_DAMAGE,		//�G�̃_���[�W
	SE_TYPE_ARROW_MOVE,
	SE_TYPE_SELECT,
	SE_TYPE_PLAYER_DAMAGE,
	SE_TYPE_CLEAR,

	SE_TYPE_NUM
};

//BGM���
enum BGM_TYPE
{
	BGM_TYPE_PLAY,		//�v���C�V�[����BGM

	BGM_TYPE_NUM
};

//�T�E���h�̏�����
//�e�V�[���̏��������ɌĂ�
void InitSound();

//�T�E���h�̌㏈��
//�e�V�[���̌㏈�����ɌĂ�
void FinSound();

//���ʉ��̓ǂݍ���
void LoadSE(SE_TYPE type);

//���ʉ��̍Đ�
void PlaySE(SE_TYPE type);

//BGM�̓ǂݍ���
void LoadBGM(BGM_TYPE type);

//BGM�̍Đ�
void PlayBGM(BGM_TYPE type);

//BGM�̒�~
void StopBGM(BGM_TYPE type);
