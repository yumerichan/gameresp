#include "DxLib.h"
#include "Bullet.h"
#include "../common.h"

//==================================
//�@�e���
//==================================


BulletInfo bulletInfo[BULLET_MAX_NUM] = { 0 };

BulletInfo blackBulletInfo[BLACK_BULLET_MAX_NUM] = { 0 };



//�e�̏�����
void InitBullet()
{
	//==================================
	//�@���@�e�̏�����
	//==================================
	BulletInfo* bullet = bulletInfo;

	for (int index = 0; index < BULLET_MAX_NUM; index++, bullet++) 
	{
		bullet->handle = LoadGraph(BULLET_PATH);
		bullet->radius = BULLET_RADIUS;
		bullet->isUse = false;
	}
	//==================================
	//�@���e�̏�����
	//==================================
	BulletInfo* black_bullet = blackBulletInfo;
	for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++) {
		black_bullet->handle = LoadGraph(BLACK_BULLET_PATH);
		black_bullet->radius = BLACK_BULLET_RADIUS;
		black_bullet->isUse = false;
	}
}

//�e�̃X�e�b�v
void StepBullet()
{
	BulletInfo* bullet = bulletInfo;
	//�e�̈ړ�����
	for (int index = 0; index < BULLET_MAX_NUM; index++,bullet++)
	{
		if (bullet->isUse)
		{
			bullet->x += bullet->moveX;
			bullet->y += bullet->moveY;
			if (bullet->y <= 0) {
				bullet->isUse = false;
			}
		}
	}

	BulletInfo* black_bullet = blackBulletInfo;
	//���e�̈ړ�����
	for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)
	{

		if (black_bullet->isUse)
		{
			black_bullet->x += black_bullet->moveX;
			black_bullet->y += black_bullet->moveY;
			//������ʊO�ɍs������
			if (black_bullet->y <= PLAY_WINDOW_HEIGHT_UP - 30 || black_bullet->y >= PLAY_WINDOW_HEIGHT_DOWN + 30
				|| black_bullet->x <= PLAY_WINDOW_WIDTH_LEFT - 30 || black_bullet->x >= PLAY_WINDOW_WIDTH_RIGHT + 30) {
				black_bullet->isUse = false;
			}
		}
	}
}


//�e�̕`��
void DrawBullet()
{
	BulletInfo* bullet = bulletInfo;
	//���@�̒e�̕`��
	for (int i = 0; i < BULLET_MAX_NUM; i++, bullet++)
	{
		//�e���g�p���Ȃ�`�悷��
		if (bullet->isUse)
		{
			DrawRotaGraph(bullet->x, bullet->y, 1.0, 0.0, bullet->handle, true);
		}
	}

	BulletInfo* black_bullet = blackBulletInfo;
	//�G�̒e�̕`��
	for (int i = 0; i < BLACK_BULLET_MAX_NUM; i++, black_bullet++)
	{
		//�e���g�p���Ȃ�`�悷��
		if (black_bullet->isUse)
		{
			DrawRotaGraph(black_bullet->x, black_bullet->y, 1.0, 0.0, black_bullet->handle, true);
		}
	}
}

//�e�̌㏈��
void FinBullet()
{
	BulletInfo* bullet = bulletInfo;
	for (int i = 0; i < BULLET_MAX_NUM; i++, bullet++) {
		DeleteGraph(bullet->handle);	//�e
	}

	BulletInfo* black_bullet = blackBulletInfo;
	for (int i = 0; i < BLACK_BULLET_MAX_NUM; i++, black_bullet++) {
		DeleteGraph(bullet->handle);	//�G�̒e
	}
}

//�e�擾
BulletInfo* GetBulletInfo()
{
	return bulletInfo;
}

//���̒e�擾
BulletInfo* GetBlackBulletInfo()
{
	return blackBulletInfo;
}
