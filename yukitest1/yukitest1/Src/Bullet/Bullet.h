#pragma once

#define BULLET_MAX_NUM	(100)	//弾の最大数
#define BULLET_SPD		(10.0f)	//弾の速度
#define BLACK_BULLET_MAX_NUM	(500)	//黒弾の最大数
#define BLACK_BULLET_SPD		(10.0f)	//黒弾の基本速度

#define BULLET_PATH "Data/test.png"	//自機弾画像
#define BULLET_RADIUS (7)		//弾の半分サイズ
#define BLACK_BULLET_PATH "Data/BlackBullet.png"	//黒弾画像
#define BLACK_BULLET_RADIUS (7)	//黒弾サイズ


//弾情報構造体
struct BulletInfo
{
	int handle;		//画像ハンドル
	float x, y;		//座標
	float radius;	//半径
	bool isUse;	//使用中フラグ

	float angle;	//角度
	float moveX;	//飛んでいく方向Ｘ
	float moveY;	//飛んでいく方向Ｙ
};

//弾の初期化
void InitBullet();

//弾のステップ
void StepBullet();

//弾の描画
void DrawBullet();

//弾の後処理
void FinBullet();

//弾取得
BulletInfo* GetBulletInfo();

//黒の弾取得
BulletInfo* GetBlackBulletInfo();
