#pragma once


enum TITLE_GRAPH
{
	BG_TITLE_PATH,		//�w�i
	ARROW_PATH,		//�₶�邵
	GAME_START_PATH,	//GAME_START
	QUIT_PATH,	//Quit
	NORMAL_MODE_PATH,	//NormalMode
	VS_BOSS_PATH,	//VS_BOSS

	GRAPH_TYPE_NUM
};


//�^�C�g��������
void InitTitle();

//�^�C�g���ʏ폈��
void StepTitle();

//�^�C�g���`�揈��
void DrawTitle();

//�^�C�g���㏈��
void FinTitle();
