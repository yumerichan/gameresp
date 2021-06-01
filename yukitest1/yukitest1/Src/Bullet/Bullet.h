#pragma once

#define BULLET_MAX_NUM	(100)	//�e�̍ő吔
#define BULLET_SPD		(10.0f)	//�e�̑��x
#define BLACK_BULLET_MAX_NUM	(500)	//���e�̍ő吔
#define BLACK_BULLET_SPD		(10.0f)	//���e�̊�{���x

#define BULLET_PATH "Data/test.png"	//���@�e�摜
#define BULLET_RADIUS (7)		//�e�̔����T�C�Y
#define BLACK_BULLET_PATH "Data/BlackBullet.png"	//���e�摜
#define BLACK_BULLET_RADIUS (7)	//���e�T�C�Y


//�e���\����
struct BulletInfo
{
	int handle;		//�摜�n���h��
	float x, y;		//���W
	float radius;	//���a
	bool isUse;	//�g�p���t���O

	float angle;	//�p�x
	float moveX;	//���ł��������w
	float moveY;	//���ł��������x
};

//�e�̏�����
void InitBullet();

//�e�̃X�e�b�v
void StepBullet();

//�e�̕`��
void DrawBullet();

//�e�̌㏈��
void FinBullet();

//�e�擾
BulletInfo* GetBulletInfo();

//���̒e�擾
BulletInfo* GetBlackBulletInfo();
