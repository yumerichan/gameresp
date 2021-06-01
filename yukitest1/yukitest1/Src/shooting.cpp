#include "DxLib.h"
#include "Scene/Scene.h"
#include "Scene/SceneTitle.h"
#include "Scene/ScenePlay.h"
#include "common.h"
#include "Scene/SceneClear.h"
#include "Scene/SceneGameOver.h"
#include "Input/Input.h"

//#define WINDOW_WIDTH (1240)	���̒l
//#define WINDOW_HEIGHT (720)

//�V�[�����


//���݂̃V�[��ID
int g_CurrentSceneID = SCENE_ID_INIT_TITLE;
int g_CurrentPlaySceneID ;

//�^�C�g���E�N���A�E�Q�[���I�[�o�[���
//#define TITLE_PATH "Data/BgTitle.png"
#define CLEAR_PATH "Data/BgClear.png"
#define GAMEOVER_PATH "Data/BgGameOver.png"




//�t���[�����[�g���ϐ�
FrameRateInfo frameRateInfo;


//FPS�v�Z
void CalcFPS();

//FPS�\��(�f�o�b�N�p)
void DrawFPS();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�̏�Ԃ�ݒ肷��
	ChangeWindowMode(true);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//�E�B���h�E�T�C�Y��ύX
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	//�`�悷��X�N���[����ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	//�^�C�g����ʂ�������
	//int titlehandle = LoadGraph(TITLE_PATH);

	//�N���A��ʂ�ݒ�
	int clearhandle = LoadGraph(CLEAR_PATH);

	int gameoverhandle = LoadGraph(GAMEOVER_PATH);

	//================================
	//	���͏�����
	//================================
	InitInput();

	//=====================================
	//�Q�[�����C�����[�v
	while (ProcessMessage() != -1)
	{
		Sleep(1);//�V�X�e���ɏ�����Ԃ�

		frameRateInfo.currentTime = GetNowCount();

		//�ŏ��̃��[�v�Ȃ�
		//���݂̎��Ԃ��AFPS�̌v�Z���������Ԃɐݒ�
		if (frameRateInfo.calcFpsTime == 0.0f)
		{
			frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
			frameRateInfo.fps = (float)FRAME_RATE;
		}
		//���݂̎��Ԃ��A�O��̃t���[�������
		//1000/60�~���b(1/60�b�j�ȏ�o�߂��Ă����珈�������s����
		if (frameRateInfo.currentTime - frameRateInfo.lastFrameTime >= FRAME_TIME)
		{

			//�t���[�����s���̎��Ԃ��X�V
			frameRateInfo.lastFrameTime = frameRateInfo.currentTime;

			//�t���[�������J�E���g
			frameRateInfo.count++;

			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
				//�G�X�P�[�v�L�[�������ꂽ��I��
			}

			//��ʂɕ\�����ꂽ���̂��������i�P���[�v�̂P�x�����s���j
			ClearDrawScreen();

			//==================================
			//	���̓X�e�b�v
			//==================================
			StepInput();




			/////////////////////////////////////////////////////////////////////////////
			
			
			//==================================
			//	�V�[��ID�ɂ���ď����̐U�ւ��s����
			//==================================

			switch (g_CurrentSceneID)
			{

			case SCENE_ID_INIT_TITLE:
			{
				int g_CurrentPlaySceneID = PLAY_SCENE_NORMAL_ONE;
				//======================
				//	�^�C�g��������
				//======================
				InitTitle();

			}//SCENE_ID_INIT_TITLE�I���̊���
			break;

			case SCENE_ID_LOOP_TITLE:
			{
				//======================
				//	�^�C�g���ʏ폈��
				//======================
				StepTitle();

				//======================
				//	�^�C�g���`�揈��
				//======================
				DrawTitle();
			}//SCENE_ID_LOOP_TITLE�I���̊���
			break;

			case SCENE_ID_FIN_TITLE: 
			{
				//======================
				//	�^�C�g���㏈��
				//======================
				FinTitle();
			}
			break;

			case  SCENE_ID_INIT_NORMAL_PLAY:
			{
				//======================
				//	�v���C������
				//======================
				InitPlay();
			}//SCENE_ID_INIT_NORMAL_PLAY�I���̊���
			break;

			case  SCENE_ID_INIT_BOSS_PLAY:
			{
			//======================
			//	�v���C������
			//======================
				InitPlay();
			//======================
			//	�{�X�v���C������
			//======================
				InitBossPlay();
			}//SCENE_ID_INIT_BOSS_PLAY�I���̊���
			break;

			case  SCENE_ID_LOOP_PLAY:
			{
				//======================
				//	�v���C�`�揈��
				//======================
				DrawPlay();
				//======================
				//	�v���C�ʏ폈��
				//======================
				StepPlay();

			}//SCENE_ID_LOOP_PLAY�I���̊���
			break;

			case SCENE_ID_FIN_PLAY:
			{
				//======================
				//	�v���C�㏈��
				//======================
				FinPlay();
			}
			break;

			case SCENE_ID_INIT_CLEAR:
			{
				//======================
				//	�N���A������
				//======================
				InitClear();
			}//SCENE_ID_INIT_CLEAR�I���̊���
			break;

			case SCENE_ID_LOOP_CLEAR:
			{
				//======================
				//	�N���A�`�揈��
				//======================
				DrawClear();
				//======================
				//	�N���A�ʏ폈��
				//======================
				StepClear();
			}//SCENE_ID_LOOP_CLEAR�I���̊���
			break;

			case SCENE_ID_FIN_CLEAR:
			{
				//======================
				//	�N���A�㏈��
				//======================
				FinClear();
			}
			break;

			case SCENE_ID_INIT_GAMEOVER:
			{
				//======================
				//	�Q�[���I�[�o�[������
				//======================
				InitGameOver();
			}//SCENE_ID_INIT_GAMEOVER�I���̊���
			break;

			case SCENE_ID_LOOP_GAMEOVER:
			{
				//======================
				//	�Q�[���I�[�o�[�`�揈��
				//======================
				DrawGameOver();
				//======================
				//	�Q�[���I�[�o�[�ʏ폈��
				//======================
				StepGameOver();
			}//SCENE_ID_LOOP_GAMEOVER�I���̊���
			break;

			case SCENE_ID_FIN_GAMEOVER:
			{
				//======================
				//	�Q�[���I�[�o�[�㏈��
				//======================
				FinGameOver();
			}
			break;

			}

			//=========================
			//�t���b�v�֐��i���[�v�̏I���ɂP�x�����s���j
			ScreenFlip();
		}
		//FPS�v�Z
		CalcFPS();

		//FPS�\��
		DrawFPS();

	}
	//�Ō�ɂP�񂾂���鏈���������ɏ���
	//DX���C�u�����̌㏈��

	DxLib_End();

	return 0;
}

//FPS�v�Z
void CalcFPS()
{
	//�O���FPS���v�Z�������Ԃ���̌o�ߎ��Ԃ����߂�
	int difTime = frameRateInfo.currentTime - frameRateInfo.calcFpsTime;

	//�O���FPS���v�Z�������Ԃ���
	//��b�ȏ�o�߂��Ă�����FPS���v�Z����
	if (difTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�������̂�float�ɃL���X�g
		float frameCount = (float)(frameRateInfo.count * 1000.0f);

		//FPS�����߂�
		//���z�̐��l�� 60000/10000��60�ƂȂ�
		frameRateInfo.fps = frameCount / difTime;

		//�t���[�����[�g�J�E���g���N���A
		frameRateInfo.count = 0;

		//FPS���v�Z�������Ԃ��X�V
		frameRateInfo.calcFpsTime = frameRateInfo.currentTime;
	}
}

//FPS�\��(�f�o�b�N�p)
void DrawFPS()
{
	unsigned int color = GetColor(255, 30, 30);
	/*DrawFormatString(695, 580, color, "FPS[%.2f]", frameRateInfo.fps);*/
}


//DrawString(200,200, "aaaaaaaaaaaa",GetColor(255,255,255));