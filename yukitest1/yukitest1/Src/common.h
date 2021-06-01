#pragma once


#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (960)

//==================================
//�@�v���C��ʂ̏c���T�C�Y	/61+20	/830 - 20	/21 + 20	/920 - 20
//==================================
#define PLAY_WINDOW_WIDTH_LEFT	(81)
#define PLAY_WINDOW_WIDTH_RIGHT	(810)
#define PLAY_WINDOW_HEIGHT_UP	(41)
#define PLAY_WINDOW_HEIGHT_DOWN	(900)

#define PLAY_WINDOW_WIDTH_SIZE	(729)
#define PLAY_WINDOW_HEIGHT_SIZE	(859)

//�ݒ�t���[�����[�g(60FPS)
#define FRAME_RATE (60)

//�P�t���[���̎��� (�~���b)
#define FRAME_TIME (1000 / FRAME_RATE )

struct FrameRateInfo
{
	int currentTime; //���݂̎���
	int lastFrameTime; //�O��̃t���[�����s���̎���
	int count; //�t���[���J�E���g�p
	int calcFpsTime; //FPS���v�Z��������
	float fps; //�v�Z����FPS
};

//
////�t���[�����[�g���ϐ�
//FrameRateInfo frameRateInfo;
