#include "DxLib.h"
#include "Bullet.h"
#include "../common.h"

//==================================
//　弾情報
//==================================


BulletInfo bulletInfo[BULLET_MAX_NUM] = { 0 };

BulletInfo blackBulletInfo[BLACK_BULLET_MAX_NUM] = { 0 };



//弾の初期化
void InitBullet()
{
	//==================================
	//　自機弾の初期化
	//==================================
	BulletInfo* bullet = bulletInfo;

	for (int index = 0; index < BULLET_MAX_NUM; index++, bullet++) 
	{
		bullet->handle = LoadGraph(BULLET_PATH);
		bullet->radius = BULLET_RADIUS;
		bullet->isUse = false;
	}
	//==================================
	//　黒弾の初期化
	//==================================
	BulletInfo* black_bullet = blackBulletInfo;
	for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++) {
		black_bullet->handle = LoadGraph(BLACK_BULLET_PATH);
		black_bullet->radius = BLACK_BULLET_RADIUS;
		black_bullet->isUse = false;
	}
}

//弾のステップ
void StepBullet()
{
	BulletInfo* bullet = bulletInfo;
	//弾の移動処理
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
	//黒弾の移動処理
	for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)
	{

		if (black_bullet->isUse)
		{
			black_bullet->x += black_bullet->moveX;
			black_bullet->y += black_bullet->moveY;
			//もし画面外に行ったら
			if (black_bullet->y <= PLAY_WINDOW_HEIGHT_UP - 30 || black_bullet->y >= PLAY_WINDOW_HEIGHT_DOWN + 30
				|| black_bullet->x <= PLAY_WINDOW_WIDTH_LEFT - 30 || black_bullet->x >= PLAY_WINDOW_WIDTH_RIGHT + 30) {
				black_bullet->isUse = false;
			}
		}
	}
}


//弾の描画
void DrawBullet()
{
	BulletInfo* bullet = bulletInfo;
	//自機の弾の描画
	for (int i = 0; i < BULLET_MAX_NUM; i++, bullet++)
	{
		//弾が使用中なら描画する
		if (bullet->isUse)
		{
			DrawRotaGraph(bullet->x, bullet->y, 1.0, 0.0, bullet->handle, true);
		}
	}

	BulletInfo* black_bullet = blackBulletInfo;
	//敵の弾の描画
	for (int i = 0; i < BLACK_BULLET_MAX_NUM; i++, black_bullet++)
	{
		//弾が使用中なら描画する
		if (black_bullet->isUse)
		{
			DrawRotaGraph(black_bullet->x, black_bullet->y, 1.0, 0.0, black_bullet->handle, true);
		}
	}
}

//弾の後処理
void FinBullet()
{
	BulletInfo* bullet = bulletInfo;
	for (int i = 0; i < BULLET_MAX_NUM; i++, bullet++) {
		DeleteGraph(bullet->handle);	//弾
	}

	BulletInfo* black_bullet = blackBulletInfo;
	for (int i = 0; i < BLACK_BULLET_MAX_NUM; i++, black_bullet++) {
		DeleteGraph(bullet->handle);	//敵の弾
	}
}

//弾取得
BulletInfo* GetBulletInfo()
{
	return bulletInfo;
}

//黒の弾取得
BulletInfo* GetBlackBulletInfo()
{
	return blackBulletInfo;
}
