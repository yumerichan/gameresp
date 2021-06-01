#include <math.h>
#include "DxLib.h"
#include "Scene.h"
#include "ScenePlay.h"
#include "../common.h"
#include "../Collision/Collision.h"
#include "../Input/Input.h"
#include "../Effect/Effect.h"
#include "../Sound/Sound.h"
#include "../Bullet/Bullet.h"

//==================================
//�@�v���C�w�i�摜�̃p�X
//==================================
#define BG_PLAY_PATH	"Data/BgSky2.png"
#define BG_UI_PATH	"Data/BgTest.png"
//==================================
//�@UI�摜�̃p�X
//==================================
#define LIFE_PATH "Data/Life.png"
#define LOGO_PATH "Data/Logo.png"
//==================================
//�@���@���
//==================================
#define PLAYER_PATH "Data/MyCharacter.png"
#define PLAYER_RADIUS (32)		//���@�摜�̔��a
#define PLAYER_HIT_SIZE (2)		//���@�̓����蔻��̔��a
#define PLAYER_POWER	(1)		//�v���C���[�̉Η�
#define PLAYER_LOW_SPEED	(2)	//�v���C���[�̒ᑬ�x
#define PLAYER_NORMAL_SPEED	(5)	//�v���C���[�̒ʏ푬�x
//==================================
//�@�G�ыʏ��
//==================================
#define ENEMY_WOOL_PATH "Data/Wool.png"
#define ENEMY_WOOL_RADIUS (32)		//�ыʂ̔��a
#define ENEMY_WOOL_MAX_NUM	(100)		//�G�̍ő吔
#define ENEMY_WOOL_MAX_HP	(1)		//�G�̍ő�HP
//==================================
//�@BOSS���
//==================================
#define BOSS_PATH "Data/Boss.png"
#define BOSS_RADIUS (64)		//�{�X�̔��a
#define BOSS_MAX_HP (150)		//�{�X�̍ő�HP
#define BOSS_DEFAULT_X	(445)		//�{�X�̃f�t�H���gX
#define BOSS_DEFAULT_Y	(250)		//�{�X�̃f�t�H���gY
//==================================
//�@�Q�[���I�[�o�[���N���A���̏��
//==================================
#define SCENE_CLEAR	(1)			//�N���A�V�[���̔ԍ�
#define SCENE_GAMEOVER	(2)			//�Q�[���I�[�o�[�̔ԍ�
//==================================
//�@�摜�n���h��
//==================================
int bgUI;	//UI�摜
int lifeHandle;	//�c�@�摜
int logoHandle;	//���S
//==================================
//�@�w�i�摜
//==================================
int bgPlayHandle[2] = { 0 };	//�摜�n���h��
int bgSkyY[2] = { 0 };			//Y���W


//���@���\����
struct PlayerInfo {
	int handle;	//�摜�n���h��
	int x, y;	//xy���W
	int cooltime;	//�e���˂̃N�[���^�C��
	bool isUse;	//�g�p�����̔���
	int speed;	//���x
	int life;	//�c�@
	bool damageCheck;	//��e����
	bool invincible;	//���G����
	int invincibleTime;	//���G����
	bool operation;	//����\��
	bool revival;	//������
	int revivalTime;	//�������̌��ݎ���
	bool flash;	//�_��
};
PlayerInfo playerInfo = { 0 };

//�ыʍ\����
struct EnemyWoolInfo{
	int handle;	//�摜�n���h��
	int x, y;	//x,y���W
	int cooltime;	//�e���˂̃N�[���^�C��
	bool isUse;	//�g�p�����ǂ���
	bool dead;	//�|���ꂽ���ǂ���
	int HP;	//�̗�
};
int enemyPopCoolTime;

EnemyWoolInfo enemyWoolInfo[ENEMY_WOOL_MAX_NUM] = { 0 };

//�{�X�\����
struct BossInfo {
	int handle;	//�摜�n���h��
	int x, y;	//x,y���W
	int cooltime;	//�e�̃N�[���^�C��
	bool isUse;	//�g�p�����ǂ���
	int HP;	//�̗�
	int invincible;	//���G����
	int invincibleTime;	//���G����
	bool flash;	//�_��
	int life;	//�{�X�̎c�@
	int bossThreeCount;	//�{�X�e��3�߂̉�]�x��
	bool entranceFlag;	//�o��V�[���̃t���O
};
BossInfo bossInfo = { 0 };


//�N���A���Q�[���I�[�o�[���̔���
int scenecheck;



//==================================
//	�v���C������
//==================================
void InitPlay()
{

	//==================================
	//�@�摜������
	//==================================
	 bgUI = LoadGraph(BG_UI_PATH);	//UI�摜
	 lifeHandle = LoadGraph(LIFE_PATH);	//�c�@�摜
	 logoHandle = LoadGraph(LOGO_PATH);	//���S
	//==================================
	//�@�v���C�w�i������
	//==================================
	for (int i = 0; i < 2; i++)
	{
		bgPlayHandle[i] = LoadGraph(BG_PLAY_PATH);
	}
	//==================================
	//�@�v���C�w�i������
	//==================================
	bgSkyY[0] = 0;
	bgSkyY[1] = -WINDOW_HEIGHT;
	//==================================
	//�@�v���C���[��������
	//==================================
	playerInfo.handle = LoadGraph(PLAYER_PATH);	//�摜�n���h��
	playerInfo.x = 445;	//x���W
	playerInfo.y = 850;	//y���W
	playerInfo.isUse = true;	//�v���C���[���g�p����Ă��邩
	playerInfo.life = 2;	//�c�@
	playerInfo.invincible = false;	//���G����
	playerInfo.invincibleTime = 0;	//�c�薳�G����
	playerInfo.damageCheck = false;	//�_���[�W����
	playerInfo.operation = true;
	playerInfo.revival = false;
	playerInfo.revivalTime = 0;
	playerInfo.flash = false;
	//==================================
	//�@�G�������� ���W��cooltime��������
	//==================================
	bossInfo.handle = LoadGraph(BOSS_PATH);	//�摜�n���h��
	bossInfo.isUse = false;	//�g�p�����ǂ���
	bossInfo.x = BOSS_DEFAULT_X;	//�{�X��x��
	bossInfo.y = 0;	//�{�X��y(�ŏ��͏o�����Ă��Ȃ��̂�0�ŗǂ�)
	bossInfo.HP = BOSS_MAX_HP;	//�{�X��HP���ő�HP�ɂ���
	bossInfo.invincible = false;	//���G����
	bossInfo.invincibleTime = 0;	//�c�薳�G����
	bossInfo.flash = false;	//�_�Ŕ���
	bossInfo.life = 2;	//�{�X�̎c�@
	bossInfo.entranceFlag = false;	//�o��V�[�����s�������ǂ����̃t���O
	bossInfo.bossThreeCount = 0;	//�{�X�e��3��ł��߂ɕK�v�Ȑ���
	bossInfo.cooltime = 0;	//�e�̃N�[���^�C��
	//=======================
	//	�U�R�G�̏�����
	//=======================
	for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//�G���G�̍ő吔
	{
		enemyWoolInfo[wool_index].x = -100;	//x���W����ʊO��
		enemyWoolInfo[wool_index].y = -100;	//y���W����ʊO��
		enemyWoolInfo[wool_index].handle = LoadGraph(ENEMY_WOOL_PATH);	//�摜�n���h��
		enemyWoolInfo[wool_index].isUse = false;	//�g�p����
		enemyWoolInfo[wool_index].dead = false;	//���S����
		enemyWoolInfo[wool_index].HP = ENEMY_WOOL_MAX_HP;	//HP��MAXHP�ɂ���
	}
	enemyPopCoolTime = 0;	//�G���N�����Ԃ̃N�[���^�C��

	//�N���A���Q�[���I�[�o�[���̔���
	scenecheck = 0;

	//�G�t�F�N�g������
	InitEffect();

	//�G�t�F�N�g�̃��[�h
	LoadEffect(EFFECT_TYPE_EXPLOSION, 10);
	LoadEffect(EFFECT_TYPE_RECOVERY, 2);

	//SE�̃��[�h
	LoadSE(SE_TYPE_PLAYER_SHOT);	//�V���b�g��ł������̉�
	LoadSE(SE_TYPE_ENEMY_DAMAGE);	//�G�Ƀ_���[�W�����������̉�
	LoadSE(SE_TYPE_PLAYER_DAMAGE);	//���@�����ꂽ���̉�

	//�e�̏�����
	InitBullet();


	g_CurrentPlaySceneID = PLAY_SCENE_NORMAL_ONE;	//�v���C�V�[�����m�[�}���EONE�Ɉڍs
	//==================================
	//�@�v���C���[�v��
	//==================================
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//==================================
//	�{�X�v���C������
//==================================
void InitBossPlay()
{
	playerInfo.life = 1;	//�c�@�����炷
	g_CurrentPlaySceneID = PLAY_SCENE_BOSS_ENTRANCE;	//�v���C�V�[�����{�X�o��Ɉڍs
}

//==================================
//	�v���C�ʏ폈��
//==================================
void StepPlay()
{
	//�e�̏���
	StepBullet();

	//�e�̃��[�h
	BulletInfo* bullet = GetBulletInfo();
	BulletInfo* black_bullet = GetBlackBulletInfo();

	//=======================
	//	���@����̏���
	//=======================
	if (playerInfo.operation == true)	//����\�Ȃ牺�̏������s��
	{

		//=======================
		//	���@�̈ړ����x����
		//=======================
		if ((IsKeyDown(KEY_INPUT_LSHIFT) == 1))	//�V�t�g��������Ă�����
		{
			playerInfo.speed = PLAYER_LOW_SPEED;	//���x��������
		}
		else if ((IsKeyDown(KEY_INPUT_LSHIFT) == 0))	//�V�t�g��������Ă��Ȃ�������
		{
			playerInfo.speed = PLAYER_NORMAL_SPEED;	//���x��ʏ�ɖ߂�
		}
		//=======================
		// ���@�ړ�����
		//=======================
		if ((IsKeyDown(KEY_INPUT_RIGHT) == 1))	//�E��������Ă�����
		{
			playerInfo.x += playerInfo.speed;	//�E�Ɉړ�����
			if (playerInfo.x > PLAY_WINDOW_WIDTH_RIGHT)	//��ʒ[�Ȃ�
				playerInfo.x = PLAY_WINDOW_WIDTH_RIGHT;	//��ʒ[�ɖ߂�
		}
		if ((IsKeyDown(KEY_INPUT_LEFT) == 1))	//����������Ă�����
		{
			playerInfo.x -= playerInfo.speed;	//�E�Ɉړ�����
			if (playerInfo.x < PLAY_WINDOW_WIDTH_LEFT)	//��ʒ[�Ȃ�
				playerInfo.x = PLAY_WINDOW_WIDTH_LEFT;	//��ʒ[�ɖ߂�
		}
		if ((IsKeyDown(KEY_INPUT_DOWN) == 1))	//����������Ă�����
		{
			playerInfo.y += playerInfo.speed;	//���Ɉړ�����
			if (playerInfo.y > PLAY_WINDOW_HEIGHT_DOWN)	//��ʒ[�Ȃ�
				playerInfo.y = PLAY_WINDOW_HEIGHT_DOWN;	//��ʒ[�ɖ߂�
		}
		if ((IsKeyDown(KEY_INPUT_UP) == 1))	//�オ������Ă�����
		{
			playerInfo.y -= playerInfo.speed;	//��Ɉړ�����
			if (playerInfo.y < PLAY_WINDOW_HEIGHT_UP)	//��ʒ[�Ȃ�
				playerInfo.y = PLAY_WINDOW_HEIGHT_UP;	//��ʒ[�ɖ߂�
		}
		//=======================
		//	���@�e���ˏ���
		//=======================
		if ((IsKeyDown(KEY_INPUT_Z) == true) && (playerInfo.cooltime == 0))	//Z��������Ă��āA�e�̃N�[���^�C����0�̎�
		{
			int count = 0;	//���s�񐔃J�E���g���쐬�A0�ɂ���
			for (int index = 0; index < BULLET_MAX_NUM; index++, bullet++)	//�o���b�g�̍ő吔���񂷁B�o���b�g��������
			{
				if (bullet->isUse == false)	//�o���b�g�����g�p�Ȃ�
				{
					bullet->isUse = true;	//�e���g�p���ɂ���
					bullet->x = playerInfo.x;	//x���W
					bullet->y = playerInfo.y - 23;	//y���W�����@�̏����O��
					PlaySE(SE_TYPE_PLAYER_SHOT);	//SE��炷

					playerInfo.cooltime = 5;	//�e�̃N�[���^�C�����Z�b�g

					if (count == 0)	//���ڂ̏����Ȃ�
					{
						bullet->moveX = 0.0f;	//���b�^�������Ɉړ�
						bullet->moveY = -BULLET_SPD;	//BULLET_SPD�̕��A��ɐi��
					}
					else if (count == 1)	//���ڂ̏����Ȃ�
					{
						bullet->moveX = 2;	//���b�E�Ɉړ�
						bullet->moveY = -BULLET_SPD;	//BULLET_SPD�̕��A��ɐi��
					}
					else if (count == 2)	//�O��ڂ̏����Ȃ�
					{
						bullet->moveX = -2;	//���b���Ɉړ�
						bullet->moveY = -BULLET_SPD;	//BULLET_SPD�̕��A��ɐi��
					}

					count++;//���s�񐔂�1���₷
					if (count >= 3)	//�������s�񐔂��O��ڈȍ~�Ȃ�
						break;
				}
			}
		}
	}//���@����̏����A�I��

	//=======================
	// 	�G�̋���
	//=======================
	switch (g_CurrentPlaySceneID)	//g_CurrentPlaySceneID�̒��g������
	{
	case PLAY_SCENE_NORMAL_ONE:	//NORMAL1�̋���
	{
		if (enemyPopCoolTime <= 0)	//�G���N�����Ԃ̃N�[���^�C�����[���Ȃ�
		{
			for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//�G�̍ő吔��������
			{
				if (enemyWoolInfo[wool_index].isUse == false && enemyWoolInfo[wool_index].dead == false)	//�g�p���ł͂Ȃ��āA����ł��Ȃ��Ȃ�
				{
					enemyWoolInfo[wool_index].isUse = true;	//�g�p���ɂ���
					enemyWoolInfo[wool_index].x = PLAY_WINDOW_WIDTH_LEFT + GetRand(PLAY_WINDOW_WIDTH_SIZE);	//��ʓ��̃����_����x���W�Ɉړ�
					enemyWoolInfo[wool_index].y = PLAY_WINDOW_HEIGHT_UP - ENEMY_WOOL_RADIUS;	//��ʏ㕔��菭����Ɉړ�
					enemyPopCoolTime = GetRand(30);	//�G�̗N�����Ԃ̃N�[���^�C���������_���Ɍ���
					break;
				}
				continue;
			}
		}
		enemyPopCoolTime--;	//�G�̗N�����Ԃ����炷

		for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//�G�̍ő吔��������
		{
			if (enemyWoolInfo[wool_index].isUse == true)	//�g�p���Ȃ�
			{
				enemyWoolInfo[wool_index].y += 3;	//�G�̈ʒu�����Ɉړ�����
				if (enemyWoolInfo[wool_index].y >= WINDOW_HEIGHT)	//��ʊO�ɍs������
				{
					enemyWoolInfo[wool_index].isUse = false;	//���g�p�ɂ���
				}
			}
		}

		//=======================
		//	�G���S���|���ꂽ�玟�̃V�[���ɐi��
		//=======================
		for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//�G�̍ő吔��������
		{
			if (enemyWoolInfo[wool_index].dead == false)	//�����N��������ł��Ȃ������牽�����Ȃ�
			{
				break;
			}
			if(wool_index == ENEMY_WOOL_MAX_NUM -1)	//�����Ō�܂ōs�����Ȃ�
			g_CurrentPlaySceneID = PLAY_SCENE_BOSS_ENTRANCE;	//���̃v���C�V�[���ɍs��
		}
	}
	break;
	case PLAY_SCENE_BOSS_ENTRANCE:	//�{�X�o��V�[��
		{
		if (bossInfo.entranceFlag == false)	//�{�X�o�ꏉ��̐ݒ�
		{
			bossInfo.entranceFlag = true;
			bossInfo.isUse = true;	//�{�X���g�p����
			bossInfo.invincible = true;	//���G����
			bossInfo.invincibleTime = 1000;	//���G���Ԃ��G�ɐݒ�(��ŏ����̂ŉ��ł��ǂ�)
		}
		bossInfo.y += (BOSS_DEFAULT_Y/100) ;	//�{�X��y��BOSS_DEFAULT_Y��100���̈�𑫂�
			if (bossInfo.y >= BOSS_DEFAULT_Y)	//�����{�X��y���W���w��̈ʒu�ɍs������
			{
				bossInfo.invincible = false;	//���G������
				bossInfo.invincibleTime = 0;	//���G���Ԃ�0
				bossInfo.flash = false;	//�_�ł�����
				bossInfo.y = BOSS_DEFAULT_Y;	//�{�X��y���ʒu�Ɉړ�
				g_CurrentPlaySceneID = PLAY_SCENE_BOSS_ONE;	//���̃v���C�V�[���Ɉړ�
			}
		}
		break;
	case PLAY_SCENE_BOSS_ONE:	//�{�X�e��1
	{
		if (bossInfo.invincible == false)	//���G����Ȃ��Ȃ�
		{
			//�G�e���ˏ���
			if ((bossInfo.cooltime == 0) && (bossInfo.isUse == true))
			{
				//BulletInfo* black_bullet = GetBulletInfo();
				int count = 0;	//��������

				for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)
				{
					if (black_bullet->isUse == false)
					{

						//���ˊԊu�����Z�b�g
						bossInfo.cooltime = 1;


						black_bullet->x = bossInfo.x;
						black_bullet->y = bossInfo.y + 10;

						black_bullet->isUse = true;


						double angle = 0;

						angle = atan2(rand() - rand(), rand() - rand());	//�p�x


						//���߂��x�N�g�����g�p���āA�v���C���[�̕����ւ̈ړ��ʂ����߂�
						black_bullet->moveX = cos(angle) * BLACK_BULLET_SPD;
						black_bullet->moveY = sin(angle) * BLACK_BULLET_SPD;

						count += 1;

						if (count >= 2)	//������񓮂�����
							break;
					}
				}
			}
		}
	}
	break;
	case PLAY_SCENE_BOSS_TWO:
	{
		if (bossInfo.invincible == false)	//���G����Ȃ��Ȃ�
		{
			//�G�e���ˏ���
			if ((bossInfo.cooltime == 0) && (bossInfo.isUse == true))
			{
				//BulletInfo* black_bullet = GetBulletInfo();
				int count = 0;

				for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)
				{
					if (black_bullet->isUse == false)
					{

						//���ˊԊu�����Z�b�g
						bossInfo.cooltime = 6;


						black_bullet->x = bossInfo.x;
						black_bullet->y = bossInfo.y + 10;

						black_bullet->isUse = true;

						double angle = 0;

						if (count == 0)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x);	//�p�x

						if (count == 1)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x) + 0.3;	//�p�x

						if (count == 2)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x) - 0.3;	//�p�x

						if (count == 3)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x) + 0.6;	//�p�x

						if (count == 4)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x) - 0.6;	//�p�x


						black_bullet->moveX = cos(angle) * BLACK_BULLET_SPD;
						black_bullet->moveY = sin(angle) * BLACK_BULLET_SPD;


						count++;

						if (count >= 5)
							break;

					}
				}
			}
		}
	}
	break;
	case PLAY_SCENE_BOSS_THREE:
	{
		if (bossInfo.invincible == false)	//���G����Ȃ��Ȃ�
		{
			//�G�e���ˏ���
			if ((bossInfo.cooltime == 0) && (bossInfo.isUse == true))
			{
				//BulletInfo* black_bullet = GetBulletInfo();
				int count = 0;

				for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)
				{
					if (black_bullet->isUse == false)
					{

						//���ˊԊu�����Z�b�g
						bossInfo.cooltime = 2;


						black_bullet->x = bossInfo.x;
						black_bullet->y = bossInfo.y + 10;

						black_bullet->isUse = true;

						double angle = 0;

						if (count == 0)
							angle = atan2(1, 0) + (00.2 * bossInfo.bossThreeCount);	//�p�x
						else if (count == 1)
							angle = atan2(0, -1) + (00.2 * bossInfo.bossThreeCount);	//�p�x
						else if (count == 2)
							angle = atan2(-1, 0) + (00.2 * bossInfo.bossThreeCount);	//�p�x
						else if (count == 3)
							angle = atan2(0, 1) + (00.2 * bossInfo.bossThreeCount);	//�p�x

						bossInfo.bossThreeCount++;

						black_bullet->moveX = cos(angle) * (BLACK_BULLET_SPD / 2);
						black_bullet->moveY = sin(angle) * (BLACK_BULLET_SPD / 2);

						count++;
						if (count > 3)
							break;

					}
				}
			}
		}
	}
	break;
	}
	
	//=======================
	// �G�̒e���˃N�[���^�C��
	//=======================
	//�e���˂̃N�[���^�C��
	if (playerInfo.cooltime > 0)
		playerInfo.cooltime -= 1;
	//BOSS�e���˂̃N�[���^�C��
	if (bossInfo.cooltime > 0)
		bossInfo.cooltime -= 1;

	//=======================
	//	���@�e�̏���
	//=======================
	bullet = GetBulletInfo();	//�e�̃��[�h
	for (int index = 0; index < BULLET_MAX_NUM; index++,bullet++)
	{

		if (bullet->isUse == false)//�e�����g�p�Ȃ�
		{
			continue;//���̋ʂ̊m�F
		}

		//=======================
		// 	���@�e���G��wool�ɓ������Ă��邩�̔���
		//=======================
		for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//�G���̐�����
		{
			if (enemyWoolInfo[wool_index].isUse == 1)	//����wool�����݂��Ă�����
			{
				if ((atari(bullet->x, bullet->y, BULLET_RADIUS, enemyWoolInfo[wool_index].x, enemyWoolInfo[wool_index].y, ENEMY_WOOL_RADIUS)))	//�e���������Ă�����
				{
					enemyWoolInfo[wool_index].HP-= PLAYER_POWER;	//HP���ւ炷
					bullet->isUse = false;	//���������e������
					PlaySE(SE_TYPE_ENEMY_DAMAGE);	//SE��点��
					PlayEffect(EFFECT_TYPE_EXPLOSION, enemyWoolInfo[wool_index].x, enemyWoolInfo[wool_index].y );	//���j�G�t�F�N�g��\������
					if (enemyWoolInfo[wool_index].HP <= 0)	//HP��0�ȉ���������
					{
						enemyWoolInfo[wool_index].isUse = false;	//wool������
						enemyWoolInfo[wool_index].dead = true;	//wool�����񂾔���ɂ���

						//=======================
						// ���񂾂�e���΂�����
						//=======================
						black_bullet = GetBlackBulletInfo();	//���e�̎擾(���Z�b�g)
						int count = 0;	//���s�񐔂𐔂��邽�߂�int
						for (int death_index = 0; death_index < BLACK_BULLET_MAX_NUM; death_index++, black_bullet++)	//���e�̍ő啪��
						{
							if (black_bullet->isUse == false)	//�����g�p���ł͂Ȃ�������
							{
								black_bullet->isUse = true;//���e���g�p���ɂ���

								//wool�̈ʒu�ɒe���o��
								black_bullet->x = enemyWoolInfo[wool_index].x;
								black_bullet->y = enemyWoolInfo[wool_index].y;

								double angle = atan2(rand() - rand(), rand() - rand());	//�����_���Ȋp�x��ݒ�

								//���߂��x�N�g�����g�p���āA�v���C���[�̕����ւ̈ړ��ʂ����߂�
								black_bullet->moveX = cos(angle) * BLACK_BULLET_SPD;	//�p�x * ���x
								black_bullet->moveY = sin(angle) * BLACK_BULLET_SPD;	//�p�x * ���x

								count++;	//���s�񐔂𑝂₷

								if (count >= 6)	//����6����s���Ă�����
									break;
							}
						}
					}
				}
			}
		}//�Gwool�̔���I���

		//=======================
		// ���@�����{�X�ɓ������Ă��邩
		//=======================
		if (bossInfo.isUse == true)	//�����{�X���o�����Ă�����
		{
			if ((atari(bullet->x, bullet->y, BULLET_RADIUS, bossInfo.x, bossInfo.y, BOSS_RADIUS)) && bossInfo.invincible == false)	//�����{�X�ɍU��������������@���G�Ȃ�p�X
			{
				bullet->isUse = false;//�e������

				bossInfo.HP -= PLAYER_POWER;	//�{�X��HP������
				PlaySE(SE_TYPE_ENEMY_DAMAGE);	//SE��点��

				//=======================
				// �{�X���S�㏈��
				//=======================
				if (bossInfo.HP <= 0)	//�{�X��HP��0�ȉ��Ȃ�
				{
					g_CurrentPlaySceneID++;	//���̃V�[����
					bossInfo.life -= 1;	//�{�X�̎c�@�����炷
					bossInfo.invincible = true;	//���G�ɂ���
					bossInfo.invincibleTime = 80;	//���G���Ԃ�ݒ肷��
					bossInfo.HP = BOSS_MAX_HP;	//HP��MAX�ɂ���

					//=======================
					// �e��S�ď���
					//=======================
					BulletInfo* black_bullet = GetBlackBulletInfo();	//���e�̎擾(���Z�b�g)
					for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)	//���e�̐�����
					{
						if (black_bullet->isUse == true)	//���e���g���Ă�����
						{
							black_bullet->isUse = false;	//���e������
						}
					}
					//=======================
					// �{�X�̎c�@���Ȃ��Ȃ�����̏���
					//=======================
					if (bossInfo.life < 0)	//�{�X�̎c�@������������
					{
						bossInfo.isUse = false;	//�{�X������
						scenecheck = SCENE_CLEAR;	//�N���A�t���O�𗧂Ă�
					}
				}
				PlayEffect(EFFECT_TYPE_EXPLOSION, bossInfo.x + GetRand(30) - GetRand(30), bossInfo.y + GetRand(30) - GetRand(30));	//�e������������{�X�߂��ɔ��j�G�t�F�N�g
				break;
			}
		}
	}

	//=======================
	// 	���@�̓����蔻��
	//=======================
	if (playerInfo.invincible == false)	//�������G����Ȃ��Ȃ�G�̓����蔻����g�p����
	{
		//=======================
		// ���e�̓����蔻��`�F�b�N
		//=======================
		BulletInfo* black_bullet = GetBlackBulletInfo();	//���e�̎擾(���Z�b�g)
		for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)	//���e�̐�����
		{
			if (black_bullet->isUse == false)	//�e�����g�p�Ȃ�
			{
				continue;	//��������
			}
			if (atari(black_bullet->x, black_bullet->y, BLACK_BULLET_RADIUS, playerInfo.x, playerInfo.y, PLAYER_HIT_SIZE))	//�������Ă���Ȃ�
			{
				black_bullet->isUse = false;	//���e������
				playerInfo.damageCheck = true;	//�v���C���[�Ƀ_���[�W������
				break;
			}
		}
		//=======================
		//	�{�X�Ǝ��@��������������
		//=======================
		if ((bossInfo.isUse) && atari(playerInfo.x, playerInfo.y, PLAYER_HIT_SIZE, bossInfo.x, bossInfo.y, BOSS_RADIUS)) {
			playerInfo.damageCheck = true;
		}

		for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)
		{

			if ((enemyWoolInfo[wool_index].isUse) && atari(playerInfo.x, playerInfo.y, PLAYER_HIT_SIZE, enemyWoolInfo[wool_index].x, enemyWoolInfo[wool_index].y, ENEMY_WOOL_RADIUS)) {
				playerInfo.damageCheck = true;
			}

		}

	}

	//=======================
	// 	���@�̃_���[�W����
	//=======================
	if (playerInfo.damageCheck == true)	//�������@���_���[�W�H����Ă�����
	{
		PlayEffect(EFFECT_TYPE_EXPLOSION, playerInfo.x , playerInfo.y);
		PlaySE(SE_TYPE_PLAYER_DAMAGE);
		playerInfo.life -= 1;	//�c�@���ꌸ�炷
		playerInfo.invincible = true;	//���G�ɂ���
		playerInfo.invincibleTime = 150;	//���G���Ԃ̐ݒ�
		playerInfo.operation = false;	//����s�\�ɂ���
		playerInfo.x = 445;
		playerInfo.y = 850 + 300;
		playerInfo.damageCheck = false;	//�_���[�W�H����Ă����t���O������
		playerInfo.revival = true;	//�������ɂ���
		playerInfo.revivalTime = 100;	//�������Ԃ�ݒ�
	}
	//=======================
	// 	���@�̖��G����
	//=======================
	if (playerInfo.invincible == true)	//�������G�Ȃ�
	{
		playerInfo.invincibleTime -= 1;	//���G���Ԃ�1�ւ炷
		if (playerInfo.flash == true)
			playerInfo.flash = false;
		else if (playerInfo.flash == false)
			playerInfo.flash = true;
		if (playerInfo.invincibleTime <= 0)	//���G���Ԃ�0�ɂȂ�����
		{
			playerInfo.invincible = false;	//���G���I��点��
			playerInfo.flash = false;
		}
	}
	//=======================
	// 	���@�̕�������
	//=======================
	if (playerInfo.revival == true)	//�������@���������Ȃ�
	{
		playerInfo.y -= 3;	//�㏸����
		playerInfo.revivalTime -= 1;	//�������Ԃ��J�E���g
		if (playerInfo.revivalTime <= 0)	//���Ԃ�0�ɂȂ�����
		{
			playerInfo.operation = true;
			playerInfo.revival = false;	//�������Ԃ��I��点��
		}
	}
	//=======================
	// 	�G�̖��G����
	//=======================
	if (bossInfo.invincible == true)	//�����G�����G�Ȃ�
	{
		bossInfo.invincibleTime -= 1;	//���G���Ԃ�1�ւ炷
		if (bossInfo.flash == true)
			bossInfo.flash = false;
		else if (bossInfo.flash == false)
			bossInfo.flash = true;
		if (bossInfo.invincibleTime <= 0)	//���G���Ԃ�0�ɂȂ�����
		{
			bossInfo.invincible = false;	//���G���I��点��
			bossInfo.flash == false;	//�_�ł��~�߂�
		}
	}


	//�Q�[���I�[�o�[����
	if (playerInfo.life < 0) {
		scenecheck = SCENE_GAMEOVER;
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;

	}


	//DrawRotaGraph(CircleA_x, CircleA_y, 1.0, angle, CircleA_Graph, true);

	DrawFormatString(890, 90, GetColor(255, 255, 255), "x = %d ,y = %d", playerInfo.x, playerInfo.y);


	if (scenecheck == SCENE_CLEAR) {	//�V�[���`�F�b�N���N���A�Ȃ�
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}

	if (IsKeyPush(KEY_INPUT_ESCAPE) == 1)	//�G�X�P�[�v�����ꂽ��
	{
			DxLib_End();	//�Q�[�������
	}

	StepEffect();
}




//==================================
//	�v���C�`�揈��
//==================================
void DrawPlay() {
	//==================================
	//	�w�i�`�揈��
	//==================================
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(0, bgSkyY[i], bgPlayHandle[0], true);
	}
	//�w�i�̈ړ�����
	for (int i = 0; i < 2; i++)
	{
		bgSkyY[i] += 3;
		if (bgSkyY[i] == WINDOW_HEIGHT)
		{
			bgSkyY[i] = -WINDOW_HEIGHT;
		}

	}

	//�v���C���[�̕`��
	if (playerInfo.isUse && playerInfo.flash ==false) {
		DrawRotaGraph(playerInfo.x, playerInfo.y, 1.0, 0.0, playerInfo.handle, true);
	}

	for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)
	{
		if (enemyWoolInfo[wool_index].isUse == true)
		{
			DrawRotaGraph(enemyWoolInfo[wool_index].x, enemyWoolInfo[wool_index].y, 1.0, 0.0, enemyWoolInfo[wool_index].handle, true);
		}
	}

	//�e�̕`�揈��
	DrawBullet();


	//�G�̕`��
	//�G���g�p���Ȃ�`�悷��
	if (bossInfo.isUse && bossInfo.flash == false)
	{
		DrawRotaGraph(bossInfo.x, bossInfo.y, 1.0, 0.0, bossInfo.handle, true);
	}
	

	DrawEffect();//�G�t�F�N�g�̕`��

	//==================================
	//	UI�`�揈��
	//==================================
	DrawGraph(0, 0, bgUI, true);

	//==================================
	//	�c�@�`�揈��
	//==================================
	DrawString(938, 150,"�c�@", GetColor(255, 255, 255));
	for (int life_index = 0; life_index < playerInfo.life; life_index++)
	{
		DrawRotaGraph(950 + (30 * life_index), 200, 1.0, 0.0, lifeHandle, true);
	}

	DrawGraph(800, 500, logoHandle, true);	//���S�̕\��
	

	////BOSS��HP��`��
	if(bossInfo.isUse)	//����BOSS��Ȃ�(BOSS�����݂��Ă�����)
	DrawBox(100, PLAY_WINDOW_HEIGHT_UP + 10, 100 + (bossInfo.HP * 4), PLAY_WINDOW_HEIGHT_UP + 25 ,GetColor(255,0,0), true);


}

//==================================
//	�v���C�㏈��
//==================================
void FinPlay() {

	//�e�̌㏈��
	FinBullet();

	//==================================
	//	�v���C�摜�j��
	//==================================
	for (int i = 0; i < 2; i++)
	{
	DeleteGraph(bgPlayHandle[i]);	//�w�i
	}
	DeleteGraph(playerInfo.handle);	//�L�����N�^�[
	DeleteGraph(bossInfo.handle);	//�G
	DeleteGraph(bgUI);	//UI
	DeleteGraph(lifeHandle);	//�c�@
	DeleteGraph(logoHandle);	//���S

	for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)
	{
		DeleteGraph(enemyWoolInfo[wool_index].handle);
	}

	//�G�t�F�N�g�̌㏈��
	FinEffect();
	
	if (scenecheck == SCENE_GAMEOVER) {
		g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
	}
	else if (scenecheck == SCENE_CLEAR) {
		g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
	}
}