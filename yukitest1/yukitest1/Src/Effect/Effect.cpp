
#include <DxLib.h>
#include "Effect.h"
#include "../Common.h"



//��x�ɕ\���ł���G�t�F�N�g�̐�
#define EFFECT_MAX_NUM (100)

//�G�t�F�N�gMAX��
#define EFFECT_TYPE_MAX_NUM (256)

//�G�t�F�N�g�A�j��MAX��
#define EFFECT_ANIME_MAX_NUM (4)



struct EffectInfo
{
	//=====================================
	//���݂̃G�t�F�N�g�ԍ�
	//=====================================
	int effectType;
	//=====================================
	//�e�G�t�F�N�g�̍ő�摜�n���h��
	//���� handle[4]�Ə����Ă���̂Ɠ���
	//=====================================
	int handle[EFFECT_ANIME_MAX_NUM];
	//=====================================
	//�e�G�t�F�N�g�̉摜�g�p��
	//=====================================
	int animeNum;
	//=======================
	//�G�t�F�N�g�g�p��
	//=======================
	bool isUse;

	//�ꖇ������̕\������
	float changeTime;
	//���̉摜�̎���
	float currentChangeTime;
	//�o�͂�����W
	int x,y;
	//���̃A�j���[�V�����ԍ�
	int currentAnimeIndex;
};



//�G�t�F�N�g���
EffectInfo effectinfo[EFFECT_MAX_NUM];

//�G�t�F�N�g�t�@�C���p�X
const char effectFilePath[EFFECT_TYPE_NUM][256] =
{
	{"Data/Effect/EffectTest.png"},
	{"Data/Effect/EffectRecovery.png"},
};

//�e�G�t�F�N�g�̃A�j����
const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
{
	4,
	4,
};

//�e�G�t�F�N�g�̉摜�T�C�Y
const int effectImageSize[EFFECT_TYPE_NUM][2] =
{
	{128/2,128/2},
	{64/2,64/2},
};

//�e�G�t�F�N�g�̃A�j���摜�؂�ւ�����
const float effectChageTime[EFFECT_TYPE_NUM] =
{
	0.05f,
	0.05f,
};

//�e�G�t�F�N�g�̉摜������
const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =		//	[WIDTH]	, [HEIGHT]
{
	{2,2},
	{2,2},
};






//�G�t�F�N�g�̓ǂݍ���
//����	�F�t�@�C���p�X, �G�t�F�N�g���, �A�j������, ���摜��, �c�摜��, ������̉��T�C�Y, ������̏c�T�C�Y
void LoadEffect(EFFECT_TYPE type, int create_num)
{
	EffectInfo* EffectInfo = effectinfo;

	//type�G�t�F�N�g����ʂɏo�͂ł���ő吔(create_num�̐���)
	for (int i = 0; i < create_num; i++)
	{
		//create_num�̐��������	(EffectInfo��create_num�܂�)
		for (int j = 0; j < EFFECT_MAX_NUM; j++, EffectInfo++)
		{
			//���g�������Ă��Ȃ������炱�̏������s��
			if (effectinfo[j].handle[0] == 0)
			{
				//�G�����[�h����B���[�h�ł�����check��0������B
				int check = LoadDivGraph(effectFilePath[type],
					effectAnimeImgNum[type],
					effectImageSplitNum[type][0],
					effectImageSplitNum[type][1],
					effectImageSize[type][0],
					effectImageSize[type][1],
					EffectInfo->handle);

				//���[�h�ł��Ă���
				if (check == 0)
				{

					EffectInfo->animeNum = effectAnimeImgNum[type];
					EffectInfo->changeTime = effectChageTime[type];
					EffectInfo->effectType = type;

				}

				//���̃u���C�N���Ȃ���effectinfo[j].handle[0]�ȍ~�����[�v�ōs���Ă��܂��̂ŁA0~100�܂œ����������s���Ă��܂�
				break;

			}
		}
	}
}



////�G�t�F�N�g���
//EffectInfo* EffectInfo = effectinfo;
//
////��ʂɏo�͂ł���ő吔
//for (int Create_index = 0; Create_index < create_num; Create_index++)
//{
//	//�G�t�F�N�g����擪����d��
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//�ǂݍ��݂��Ă��Ȃ��G�t�F�N�g����������
//		//�i�ЂƂڂ̉摜�n���h�����[���Ȃ�ǂݍ��݂���ĂȂ��j
//		if (effectinfo[Effect_index].handle[0] == 0)
//		{
//			//�����摜	
//			int Success_Effect_Img_Flag = LoadDivGraph(effectFilePath[type],
//				effectAnimeImgNum[type],
//				effectImageSplitNum[type][0],
//				effectImageSplitNum[type][1],
//				effectImageSize[type][0],
//				effectImageSize[type][1],
//				EffectInfo->handle
//			);
//
//			//���������Ȃ�	LoadDivGraph�́A����������0��Ԃ��̂ŁAloadDivGraph�ɐ��������ꍇ�ASuccess_Effect_Img_Flag�̒��ɂ�0������
//			if (Success_Effect_Img_Flag == 0)
//			{
//				//�A�j�������i�[
//				EffectInfo->animeNum = effectAnimeImgNum[type];
//
//				//�P��������̕\�����Ԃ�ݒ�
//				EffectInfo->changeTime = effectChageTime[type];
//
//				//�G�t�F�N�g�̎�ނ�ݒ�
//				EffectInfo->effectType = type;
//			}
//
//			//���ۊւ�炸������
//			break;
//		}
//	}
//}


//�G�t�F�N�g�̏�����
void InitEffect()
{
	EffectInfo* EffectInfo = effectinfo;
	for (int i = 0; i < EFFECT_MAX_NUM; i++, EffectInfo++) {


		for (int j = 0; j < EFFECT_ANIME_MAX_NUM; j++)
		{
			EffectInfo->handle[j] = 0;
		}
		EffectInfo->currentAnimeIndex = 0;
		EffectInfo->changeTime = 0.0f;
		EffectInfo->currentChangeTime = 0.0f;
		EffectInfo->isUse = false;
		EffectInfo->x = 0; EffectInfo->y = 0;
		EffectInfo->animeNum = 0;


	}
}

////	//�G�t�F�N�g���
//EffectInfo* EffectInfo = effectinfo;
//
////���ׂẴG�t�F�N�g���̕ϐ�������������
//for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//{
//	for (int anime_index = 0; anime_index < EFFECT_ANIME_MAX_NUM; anime_index++)
//		EffectInfo->handle[anime_index] = 0;
//
//	EffectInfo->x = EffectInfo->y = 0;
//	EffectInfo->isUse = false;
//	EffectInfo->animeNum = 0;
//	EffectInfo->currentAnimeIndex = 0;
//	EffectInfo->changeTime = 0.0f;
//	EffectInfo->currentChangeTime = 0.0f;
//}


//�G�t�F�N�g�ʏ폈��
void StepEffect()
{
	EffectInfo* EffectInfo = effectinfo;

	for (int i = 0; i < EFFECT_MAX_NUM; i++ , EffectInfo++)
	{
		if (EffectInfo->isUse == true)
		{
			if (EffectInfo->currentChangeTime >= EffectInfo->changeTime)
			{
				EffectInfo->currentAnimeIndex++;
				EffectInfo->currentChangeTime = 0.0f;


				if (EffectInfo->currentAnimeIndex >= EffectInfo->animeNum)
				{

					EffectInfo->isUse = false;
					continue;
				}

			}

			EffectInfo->currentChangeTime += 1.0f / FRAME_RATE;


		}
	}

}

////�G�t�F�N�g���
//EffectInfo* EffectInfo = effectinfo;
//
//DrawFormatString(50, 50, GetColor(255, 255, 255), "x[%.2f]", EffectInfo->x);
//
////���ׂẴG�t�F�N�g���̕ϐ�������������
//for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//{
//	//�g�p���Ȃ�A�j�����Ԃ��o�߂����āA�A�j���ԍ����X�V����
//	if (EffectInfo->isUse == true)
//	{
//		//�摜�؂�ւ��ɕK�v�Ȏ��Ԍo�߂�����
//		if (EffectInfo->currentChangeTime >= EffectInfo->changeTime)
//		{
//			EffectInfo->currentAnimeIndex++;		//���̉摜��
//			EffectInfo->currentChangeTime = 0.0f;	//�v�����ԃ��Z�b�g
//
//			//���̉摜�����������Ȃ�
//			if (EffectInfo->currentAnimeIndex >= EffectInfo->animeNum)
//			{
//				//�g�p���t���O��OFF��
//				EffectInfo->isUse = false;
//
//				//�ȉ��̏����͕s�v
//				continue;
//			}
//		}
//
//		//���ԍX�V
//		EffectInfo->currentChangeTime += 1.0f / FRAME_RATE;
//
//	}
//}




//�G�t�F�N�g�`�揈��
void DrawEffect()
{
	EffectInfo* EffectInfo = effectinfo;

	for (int i = 0; i < EFFECT_MAX_NUM; i++, EffectInfo++)
	{
		if (EffectInfo->isUse)
		{
			DrawRotaGraph(EffectInfo->x, EffectInfo->y, 1.0, 0.0, EffectInfo->handle[EffectInfo->currentAnimeIndex], true);
		}
	}
}

////�G�t�F�N�g���
//EffectInfo* EffectInfo = effectinfo;
////���ׂẴG�t�F�N�g���̕ϐ�������������
//for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//{
//	//�g�p���Ȃ猻�݂̃A�j���ԍ��ŕ`�悷��
//	if (EffectInfo->isUse == true)
//	{
//		/*if(EffectInfo->effectType != 1)*/
//		DrawRotaGraph(EffectInfo->x, EffectInfo->y, 1.0, 0.0, EffectInfo->handle[EffectInfo->currentAnimeIndex], true);
//		/*else
//			DrawRotaGraph(EffectInfo->x, EffectInfo->y, 1.5, 0.0, EffectInfo->handle[EffectInfo->currentAnimeIndex], true);*/
//	}
//}



//�G�t�F�N�g�̌㏈��
void FinEffect()
{
	EffectInfo* EffectInfo = effectinfo;

	for (int i = 0; i < EFFECT_MAX_NUM; i++, EffectInfo++)
	{
		for (int j = 0; j < EFFECT_ANIME_MAX_NUM; j++)
		{
			if (EffectInfo->handle[j] != 0)
			{
			
			DeleteGraph(EffectInfo->handle[j]);

			EffectInfo->handle[j] = 0;
			}
		}


	}


}

////	//�G�t�F�N�g���
//EffectInfo* EffectInfo = effectinfo;
//7
////���ׂẴG�t�F�N�g���폜
//for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//{
//	//���ׂč폜����
//	for (int anime_index = 0; anime_index < EFFECT_ANIME_MAX_NUM; anime_index++)
//	{
//		//�[���ȊO��������폜����
//		if (EffectInfo->handle[anime_index] != 0)
//		{
//			//�摜�폜
//			DeleteGraph(EffectInfo->handle[anime_index]);
//
//			//the�쏜������O������
//			EffectInfo->handle[anime_index] = 0;
//		}
//	}
//}


//�G�t�F�N�g�̍Đ�
//����	�F�G�t�F�N�g�̎��, �w���W, �x���W, �P��������̕\������
void PlayEffect(EFFECT_TYPE type, int x, int y)
{
	EffectInfo* EffectInfo = effectinfo;
	for (int i = 0; i < EFFECT_MAX_NUM; i++, EffectInfo++)
	{
		//�g�p���Ȃ�
		if (EffectInfo->isUse)
		{
			continue;
		}
		if(EffectInfo->effectType == type)
		{
			EffectInfo->x = x;
			EffectInfo->y = y;

			EffectInfo->currentChangeTime = 0;
			EffectInfo->currentAnimeIndex = 0;

			EffectInfo->isUse = true;

			break;
		}
	}
}

////�G�t�F�N�g���
//EffectInfo* EffectInfo = effectinfo;
//
////���g�p�G�t�F�N�g��T���čĐ�
//for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//{
//	//�g�p���Ȃ�ȉ��s��Ȃ�
//	if (EffectInfo->isUse == true)
//		continue;
//
//	//�^�C�v����v����
//	if (EffectInfo->effectType == type)
//	{
//		//���W������
//		EffectInfo->x = x;
//		EffectInfo->y = y;
//
//		//�v���p�̕ϐ����N���A
//		EffectInfo->currentAnimeIndex = 0;
//		EffectInfo->currentChangeTime = 0.0f;
//
//		//�g�p���ɂ���
//		EffectInfo->isUse = true;
//
//		//������
//		break;
//	}
//}



//
//EffectInfo* GetEffect()
//{
//	return effectinfo;
//}



////��x�ɕ\���ł���G�t�F�N�g�̐�
//#define EFFECT_MAX_NUM (100)
//
////�G�t�F�N�gMAX��
//#define EFFECT_TYPE_MAX_NUM (256)
//
////�G�t�F�N�g���
//EffectInfo effectinfo[EFFECT_MAX_NUM];
//
////�G�t�F�N�g�t�@�C���p�X
//const char effectFilePath[EFFECT_TYPE_NUM][256] =
//{
//	{"Data/Effect/�ق�.png"},
//	{"Data/Effect/�H�g�p��.png"},
//	{"Data/Effect/�w�C�X�g.png"},
//};
//
////�e�G�t�F�N�g�̃A�j����
//const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
//{
//	14,
//	25,
//	15,
//};
//
////�e�G�t�F�N�g�̉摜�T�C�Y
//const int effectImageSize[EFFECT_TYPE_NUM][2] =
//{
//	{64,64},
//	{64,64},
//	{64,64},
//};
//
////�e�G�t�F�N�g�̃A�j���摜�؂�ւ�����
//const float effectChageTime[EFFECT_TYPE_NUM] =
//{
//	0.05f,
//	0.05f,
//	0.1f,
//};
//
////�e�G�t�F�N�g�̉摜������
//const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =
//{
//	{5,3},
//	{5,5},
//	{5,3},
//};
//
////---------------------------------------------
////	�G�t�F�N�g�̓ǂݍ���
////---------------------------------------------
////����  :�t�@�C���p�X, �G�t�F�N�g���, �A�j������, ���摜��, �c�摜��, ������̉��T�C�Y, ������̏c�T�C�Y
//void LoadEffect(EFFECT_TYPE type, int create_num)
//{
//	//�G�t�F�N�g���
//	EffectInfo* EffectInfo = effectinfo;
//
//	//?
//	for (int Create_index = 0; Create_index < create_num; Create_index++)
//	{
//		//�G�t�F�N�g����擪����d��
//		for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//		{
//			//�ǂݍ��݂��Ă��Ȃ��G�t�F�N�g����������
//			//�i�ЂƂڂ̉摜�n���h�����[���Ȃ�ǂݍ��݂���ĂȂ��j
//			if (effectinfo[Effect_index].handle[0] == 0)
//			{
//				//�����摜
//				int Success_Effect_Img_Flag = LoadDivGraph(effectFilePath[type],
//					effectAnimeImgNum[type],
//					effectImageSplitNum[type][0],
//					effectImageSplitNum[type][1],
//					effectImageSize[type][0],
//					effectImageSize[type][1],
//					EffectInfo->handle);
//
//				//�T�N�Z�X�I�I
//				if (Success_Effect_Img_Flag == 0)
//				{
//					//�A�j�������i�[
//					EffectInfo->animeNum = effectAnimeImgNum[type];
//
//					//�P��������̕\�����Ԃ�ݒ�
//					EffectInfo->changeTime = effectChageTime[type];
//
//					//�G�t�F�N�g�̎�ނ�ݒ�
//					EffectInfo->effectType = type;
//				}
//
//				//���ۊւ�炸������
//				break;
//			}
//		}
//	}
//}
//
////---------------------------------
////	�G�t�F�N�g������
////---------------------------------
//void InitEffect()
//{
//	//�G�t�F�N�g���
//	EffectInfo* EffectInfo = effectinfo;
//
//	//���ׂẴG�t�F�N�g���̕ϐ�������������
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		for (int anime_index = 0; anime_index < EFFECT_ANIME_MAX_NUM; anime_index++)
//			EffectInfo->handle[anime_index] = 0;
//
//		EffectInfo->x = EffectInfo->y = 0;
//		EffectInfo->isUse = false;
//		EffectInfo->animeNum = 0;
//		EffectInfo->currentAnimeIndex = 0;
//		EffectInfo->changeTime = 0.0f;
//		EffectInfo->currentChangeTime = 0.0f;
//	}
//}
//
////----------------------------------
////	�G�t�F�N�g�ʏ폈��
////----------------------------------
//void StepEffect()
//{
//	//�G�t�F�N�g���
//	EffectInfo* EffectInfo = effectinfo;
//
//	//���ׂẴG�t�F�N�g���̕ϐ�������������
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//�g�p���Ȃ�A�j�����Ԃ��o�߂����āA�A�j���ԍ����X�V����
//		if (EffectInfo->isUse == true)
//		{
//			//�摜�؂�ւ��ɕK�v�Ȏ��Ԍo�߂�����
//			if (EffectInfo->currentChangeTime >= EffectInfo->changeTime)
//			{
//				EffectInfo->currentAnimeIndex++;		//���̉摜��
//				EffectInfo->currentChangeTime = 0.0f;	//�v�����ԃ��Z�b�g
//
//				//���̉摜�����������Ȃ�
//				if (EffectInfo->currentAnimeIndex >= EffectInfo->animeNum)
//				{
//					//�g�p���t���O��OFF��
//					EffectInfo->isUse = false;
//
//					//�ȉ��̏����͕s�v
//					continue;
//				}
//			}
//
//			//���ԍX�V
//			EffectInfo->currentChangeTime += 1.0f / (60 / GameSpeed);
//
//		}
//	}
//}
//
////--------------------------------------
////	�G�t�F�N�g�`�揈��
////--------------------------------------
//void DrawEffect()
//{
//	//�G�t�F�N�g���
//	EffectInfo* EffectInfo = effectinfo;
//
//	//���ׂẴG�t�F�N�g���̕ϐ�������������
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//�g�p���Ȃ猻�݂̃A�j���ԍ��ŕ`�悷��
//		if (EffectInfo->isUse == true)
//		{
//			/*if(EffectInfo->effectType != 1)*/
//			DrawRotaGraph(EffectInfo->x, EffectInfo->y, 1.0, 0.0, EffectInfo->handle[EffectInfo->currentAnimeIndex], true);
//			/*else
//				DrawRotaGraph(EffectInfo->x, EffectInfo->y, 1.5, 0.0, EffectInfo->handle[EffectInfo->currentAnimeIndex], true);*/
//
//		}
//	}
//}
//
////----------------------------------------
////	�G�t�F�N�g�㏈��
////----------------------------------------
//void FinEffect()
//{
//	//�G�t�F�N�g���
//	EffectInfo* EffectInfo = effectinfo;
//
//	//���ׂẴG�t�F�N�g���폜
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//���ׂč폜����
//		for (int anime_index = 0; anime_index < EFFECT_ANIME_MAX_NUM; anime_index++)
//		{
//			//�[���ȊO��������폜����
//			if (EffectInfo->handle[anime_index] != 0)
//			{
//				//�摜�폜
//				DeleteGraph(EffectInfo->handle[anime_index]);
//
//				//the�쏜������O������
//				EffectInfo->handle[anime_index] = 0;
//			}
//		}
//	}
//}
//
////---------------------------------------
////	�G�t�F�N�g�Đ�
////---------------------------------------
////����  :�G�t�F�N�g�̎��, X���W, Y���W, 1��������̕\������
//void PlayEffect(EFFECT_TYPE type, int x, int y)
//{
//	//�G�t�F�N�g���
//	EffectInfo* EffectInfo = effectinfo;
//
//	//���g�p�G�t�F�N�g��T���čĐ�
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//�g�p���Ȃ�ȉ��s��Ȃ�
//		if (EffectInfo->isUse == true)
//			continue;
//
//		//�^�C�v����v����
//		if (EffectInfo->effectType == type)
//		{
//			//���W������
//			EffectInfo->x = x;
//			EffectInfo->y = y;
//
//			//�v���p�̕ϐ����N���A
//			EffectInfo->currentAnimeIndex = 0;
//			EffectInfo->currentChangeTime = 0.0f;
//
//			//�g�p���ɂ���
//			EffectInfo->isUse = true;
//
//			//������
//			break;
//		}
//	}
//}
//
//EffectInfo* GetEffect()
//{
//	return effectinfo;
//}