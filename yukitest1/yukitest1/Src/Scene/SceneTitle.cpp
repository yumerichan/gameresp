#include "DxLib.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"
#include "../Sound/Sound.h"




#define ID_GAME_START	(0)	//�Q�[���X�^�[�g��ID
#define ID_QUIT	(1)	//Quit��ID
#define ID_NORMAL_MODE	(100)	//�m�[�}�����[�h��ID
#define ID_VS_BOSS	(101)	//VSBOSS��ID

#define TYPE_ID_TITLE (1000)	//�^�C�g���̃^�C�v��ID
#define TYPE_ID_MODE_SELECT (1001)	//�^�C�g���̃��[�h�Z���N�g��ID




//==================================
//�@�^�C�g���摜�̃n���h���ݒ�
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
//�@�^�C�g���摜�̃n���h���쐬
//==================================
int graphHandle[GRAPH_TYPE_NUM];

//=======================
//	Arrow�̐ݒ�o�^
//=======================
struct ArrowInfo {
	int x, y;	//x.y
	int index;	//index
	int maxIndex;	//�ő�index
	int numIndex;	//�ŏ�index

};
ArrowInfo arrowInfo = { 0 };	//ArrowInfo��arrowInfo�Ƃ��Đ錾

//=======================
//	�^�C�g���^�C�v���쐬
//=======================
int currentTitleType;	//���݂̃^�C�g���^�C�v
int preTitleType;	//�O�̃^�C�g���^�C�v

//==================================
//	�^�C�g��������
//==================================
void InitTitle() 
{

	//�T�E���h������	�����őS�ẴT�E���h�����������Ă�̂ŁA���Ԃ���������V�[�����ɕ����Ă��ǂ���������Ȃ�(05/28	���Ή�)
	InitSound();

	//�K�v�ȃT�E���h�̃��[�h
	LoadSE(SE_TYPE_ARROW_MOVE);	//�₶�邵�����������̉�
	LoadSE(SE_TYPE_SELECT);	//�I�񂾎��̉�


	//�摜������
	for (int graph_index = 0; graph_index < GRAPH_TYPE_NUM; graph_index++)	//�O���t�̐���������������
	{
		graphHandle[graph_index] = LoadGraph(graphFilePath[graph_index]);	//graphFilePath�ɂ���z���ォ�珇�ԂɃ��[�h
	}

	//�₶�邵�̏�����
	arrowInfo.x = 25;	//x���W
	arrowInfo.y = 568;	//y���W
	arrowInfo.index = 0;	//�₶�邵���ǂ��ɂ��邩
	arrowInfo.maxIndex = 1;	//index�̍ő�̐���ݒ�
	arrowInfo.numIndex = 0;	//index�̍ŏ��̐���ݒ�

	//�^�C�g���^�C�v�̏�����
	currentTitleType = TYPE_ID_TITLE;	//���݂�ID�^�C�v���^�C�g���ɐݒ�
	preTitleType = currentTitleType;	//�O��ID�^�C�v���^�C�g���ɐݒ�


	//==================================
	//�@�^�C�g�����[�v��
	//==================================
	g_CurrentSceneID = SCENE_ID_LOOP_TITLE;
}

//==================================
//	�^�C�g���ʏ폈��
//==================================
void StepTitle() 
{
	//=======================
	//	Arrow�̈ړ�����
	//=======================
	if ((IsKeyPush(KEY_INPUT_DOWN) == 1) || (IsKeyPush(KEY_INPUT_S) == 1))	//���L�[�������ꂽ�ꍇ
	{
		PlaySE(SE_TYPE_ARROW_MOVE);	//SE���Ȃ炷
			arrowInfo.index += 1;	//�J�[�\����index��+1
			if(arrowInfo.index > arrowInfo.maxIndex)	//����index��MAX�̒l���傫���Ȃ�
			arrowInfo.index = arrowInfo.numIndex;	//�ŏ���index�ɂ���
	}

	if ((IsKeyPush(KEY_INPUT_UP) == 1) || (IsKeyPush(KEY_INPUT_W) == 1))	//��L�[�������ꂽ�ꍇ
	{
		PlaySE(SE_TYPE_ARROW_MOVE);	//SE���Ȃ炷
		arrowInfo.index -= 1;	//�J�[�\����index��+1
		if (arrowInfo.index < arrowInfo.numIndex)	//����index��MIN�̒l��菬�����Ȃ�
			arrowInfo.index = arrowInfo.maxIndex;	//�ő��index�ɂ���
	}

	//==================================
	//�@�ǂ�����Enter�L�[������L�[(Z)�������ꂽ�Ȃ�
	//==================================
	if (IsKeyPush(KEY_INPUT_RETURN) == 1 || IsKeyPush(KEY_INPUT_Z) == 1)
	{
		PlaySE(SE_TYPE_SELECT);	//SE���Ȃ炷
		if (arrowInfo.index == ID_GAME_START)	//�Q�[���X�^�[�g��I��ł��鎞�ɉ����ꂽ��
		{
			currentTitleType = TYPE_ID_MODE_SELECT;	//�^�C�v�����[�h�Z���N�g�ɌJ��グ��
		}
		else if (arrowInfo.index == ID_QUIT)	//Quit��I��ł��鎞�ɉ����ꂽ��
		{
			WaitTimer(200);	//0.2�b�܂���
			DxLib_End();	//�Q�[�������
		}
		else if (arrowInfo.index == ID_NORMAL_MODE)	//�m�[�}�����[�h�ŉ�������
		{
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;	//�@�^�C�g���̌㏈���ֈړ�
		}
		else if (arrowInfo.index == ID_VS_BOSS)	//BOSS�ŉ�������
		{
			g_CurrentSceneID = SCENE_ID_FIN_TITLE;	//�@�^�C�g���̌㏈���ֈړ�
		}
	}
	//==================================
	//�@�ǂ�����Esc�L�[���߂�{�^��(x)�������ꂽ�Ȃ�
	//==================================
	if (IsKeyPush(KEY_INPUT_ESCAPE) == 1|| IsKeyPush(KEY_INPUT_X) == 1)
	{
		if (currentTitleType == TYPE_ID_TITLE)	//�^�C�g���ŉ����ꂽ��
			DxLib_End();	//�Q�[�������
		else if (currentTitleType == TYPE_ID_MODE_SELECT)	//���[�h�Z���N�g�ŉ����ꂽ��
			currentTitleType = TYPE_ID_TITLE;	//�^�C�g���ɖ߂�
	}

	//=======================
	//	�������[�h�ύX���N���Ȃ�arrowInfo�̏�������������
	//=======================
	if (currentTitleType != preTitleType)
	{
		if(currentTitleType == TYPE_ID_TITLE)//�����^�C�v���^�C�g����������
		{
			arrowInfo.x = 25;	//x���W
			arrowInfo.y = 568;	//y���W
			arrowInfo.index = ID_GAME_START;	//�₶�邵���^�C�g���̃f�t�H�ʒu��
			arrowInfo.maxIndex = 1;	//index�̍ő�̒l��ݒ�
			arrowInfo.numIndex = 0;	//index�̍ŏ��̒l��ݒ�
			preTitleType = TYPE_ID_TITLE;	//�O��TITLE_ID������������
		}
		else if (currentTitleType == TYPE_ID_MODE_SELECT)
		{
			arrowInfo.x = 25;	//x���W
			arrowInfo.y = 568;	//y���W
			arrowInfo.index = ID_NORMAL_MODE;	//�₶�邵�����[�h�Z���N�g�̃f�t�H�ʒu��
			arrowInfo.maxIndex = 101;	//index�̍ő�̒l��ݒ�
			arrowInfo.numIndex = 100;	//index�̍ŏ��̒l��ݒ�
			preTitleType = TYPE_ID_MODE_SELECT;	//�O��TITLE_ID������������

		}
	}

}

//==================================
//	�^�C�g���`�揈��
//==================================
void DrawTitle() {
	//==================================
	//	�^�C�g���`�揈��
	//==================================
	DrawGraph(0, 0, graphHandle[BG_TITLE_PATH], true);

	//�₶�邵�\��
	if(arrowInfo.index==0|| arrowInfo.index==100)	//�����₶�邵�̔��肪��̈ʒu�Ȃ�
		DrawGraph(arrowInfo.x, arrowInfo.y, graphHandle[ARROW_PATH], true);	//��̈ʒu�ɂ₶�邵������
	else if(arrowInfo.index ==1 || arrowInfo.index == 101)	//�₶�邵�̔��肪���̈ʒu�Ȃ�
		DrawGraph(arrowInfo.x, arrowInfo.y + 100, graphHandle[ARROW_PATH], true);	//���̈ʒu�ɂ₶�邵������

	//=======================
	//	
	//=======================
	if (currentTitleType == TYPE_ID_TITLE)
	{
		DrawGraph(150, 550, graphHandle[GAME_START_PATH], true);	//�Q�[���X�^�[�g
		DrawGraph(150, 650, graphHandle[QUIT_PATH], true);	//Quit
	}
	else if (currentTitleType == TYPE_ID_MODE_SELECT)
	{
		DrawGraph(150, 550, graphHandle[NORMAL_MODE_PATH], true);	//�m�[�}�����[�h
		DrawGraph(150, 650, graphHandle[VS_BOSS_PATH], true);	//VSBOSS
	}





}

//==================================
//	�^�C�g���㏈��
//==================================
void FinTitle() {
	//==================================
	//	�摜�j��
	//==================================
	for (int graph_index = 0; graph_index < GRAPH_TYPE_NUM; graph_index++)
	{
		DeleteGraph(graphHandle[graph_index]);
	}

	//==================================
	//	�^�C�g���㏈���̌�̓v���C��
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