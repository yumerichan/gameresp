#include "DxLib.h"
#include "Bullet.h"
#include "../common.h"

//==================================
//@’eî•ñ
//==================================


BulletInfo bulletInfo[BULLET_MAX_NUM] = { 0 };

BulletInfo blackBulletInfo[BLACK_BULLET_MAX_NUM] = { 0 };



//’e‚Ì‰Šú‰»
void InitBullet()
{
	//==================================
	//@©‹@’e‚Ì‰Šú‰»
	//==================================
	BulletInfo* bullet = bulletInfo;

	for (int index = 0; index < BULLET_MAX_NUM; index++, bullet++) 
	{
		bullet->handle = LoadGraph(BULLET_PATH);
		bullet->radius = BULLET_RADIUS;
		bullet->isUse = false;
	}
	//==================================
	//@•’e‚Ì‰Šú‰»
	//==================================
	BulletInfo* black_bullet = blackBulletInfo;
	for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++) {
		black_bullet->handle = LoadGraph(BLACK_BULLET_PATH);
		black_bullet->radius = BLACK_BULLET_RADIUS;
		black_bullet->isUse = false;
	}
}

//’e‚ÌƒXƒeƒbƒv
void StepBullet()
{
	BulletInfo* bullet = bulletInfo;
	//’e‚ÌˆÚ“®ˆ—
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
	//•’e‚ÌˆÚ“®ˆ—
	for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)
	{

		if (black_bullet->isUse)
		{
			black_bullet->x += black_bullet->moveX;
			black_bullet->y += black_bullet->moveY;
			//‚à‚µ‰æ–ÊŠO‚És‚Á‚½‚ç
			if (black_bullet->y <= PLAY_WINDOW_HEIGHT_UP - 30 || black_bullet->y >= PLAY_WINDOW_HEIGHT_DOWN + 30
				|| black_bullet->x <= PLAY_WINDOW_WIDTH_LEFT - 30 || black_bullet->x >= PLAY_WINDOW_WIDTH_RIGHT + 30) {
				black_bullet->isUse = false;
			}
		}
	}
}


//’e‚Ì•`‰æ
void DrawBullet()
{
	BulletInfo* bullet = bulletInfo;
	//©‹@‚Ì’e‚Ì•`‰æ
	for (int i = 0; i < BULLET_MAX_NUM; i++, bullet++)
	{
		//’e‚ªg—p’†‚È‚ç•`‰æ‚·‚é
		if (bullet->isUse)
		{
			DrawRotaGraph(bullet->x, bullet->y, 1.0, 0.0, bullet->handle, true);
		}
	}

	BulletInfo* black_bullet = blackBulletInfo;
	//“G‚Ì’e‚Ì•`‰æ
	for (int i = 0; i < BLACK_BULLET_MAX_NUM; i++, black_bullet++)
	{
		//’e‚ªg—p’†‚È‚ç•`‰æ‚·‚é
		if (black_bullet->isUse)
		{
			DrawRotaGraph(black_bullet->x, black_bullet->y, 1.0, 0.0, black_bullet->handle, true);
		}
	}
}

//’e‚ÌŒãˆ—
void FinBullet()
{
	BulletInfo* bullet = bulletInfo;
	for (int i = 0; i < BULLET_MAX_NUM; i++, bullet++) {
		DeleteGraph(bullet->handle);	//’e
	}

	BulletInfo* black_bullet = blackBulletInfo;
	for (int i = 0; i < BLACK_BULLET_MAX_NUM; i++, black_bullet++) {
		DeleteGraph(bullet->handle);	//“G‚Ì’e
	}
}

//’eæ“¾
BulletInfo* GetBulletInfo()
{
	return bulletInfo;
}

//•‚Ì’eæ“¾
BulletInfo* GetBlackBulletInfo()
{
	return blackBulletInfo;
}
