#pragma once

//=============================
//	�^�C�g���V�[����ID
//=============================
#define SCENE_ID_INIT_TITLE (100)	//������
#define SCENE_ID_LOOP_TITLE (101)	//�J��Ԃ�
#define SCENE_ID_FIN_TITLE	(102)	//�㏈��
//=============================
//	�v���C�V�[����ID
//=============================
#define SCENE_ID_INIT_NORMAL_PLAY	(200)	//�m�[�}�����[�h�̏�����
#define SCENE_ID_INIT_BOSS_PLAY	(201)	//���[�hBOSS�̏�����
#define SCENE_ID_LOOP_PLAY	(202)	//�J��Ԃ�
#define SCENE_ID_FIN_PLAY	(203)	//�㏈��
//=============================
//	�N���A�V�[����ID
//=============================
#define SCENE_ID_INIT_CLEAR (300)	//������
#define SCENE_ID_LOOP_CLEAR (301)	//�J��Ԃ�
#define SCENE_ID_FIN_CLEAR	(302)	//�㏈��
//=============================
//	�Q�[���I�[�o�[�V�[����ID
//=============================
#define SCENE_ID_INIT_GAMEOVER	(400)	//������
#define SCENE_ID_LOOP_GAMEOVER	(401)	//�J��Ԃ�
#define SCENE_ID_FIN_GAMEOVER	(402)	//�㏈��


//=======================
//	�v���C�V�[�����̒e��ID
//=======================
#define PLAY_SCENE_BOSS_ONE	(1101)	//�v���C�V�[���{�X1,�����_���ł�
#define PLAY_SCENE_BOSS_TWO	(1102)	//�v���C�V�[���{�X2,
#define PLAY_SCENE_BOSS_THREE	(1103)	//�v���C�V�[���{�X3
#define PLAY_SCENE_BOSS_ENTRANCE	(1104)	//�{�X�̓o��V�[��
#define PLAY_SCENE_NORMAL_ONE	(1105)	//�v���C�V�[���m�[�}��1

//�v���C�V�[������ID
extern int g_CurrentPlaySceneID;


//���݂̃V�[��ID
extern int g_CurrentSceneID;
