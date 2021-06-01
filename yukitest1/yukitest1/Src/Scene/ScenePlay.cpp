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
//　プレイ背景画像のパス
//==================================
#define BG_PLAY_PATH	"Data/BgSky2.png"
#define BG_UI_PATH	"Data/BgTest.png"
//==================================
//　UI画像のパス
//==================================
#define LIFE_PATH "Data/Life.png"
#define LOGO_PATH "Data/Logo.png"
//==================================
//　自機情報
//==================================
#define PLAYER_PATH "Data/MyCharacter.png"
#define PLAYER_RADIUS (32)		//自機画像の半径
#define PLAYER_HIT_SIZE (2)		//自機の当たり判定の半径
#define PLAYER_POWER	(1)		//プレイヤーの火力
#define PLAYER_LOW_SPEED	(2)	//プレイヤーの低速度
#define PLAYER_NORMAL_SPEED	(5)	//プレイヤーの通常速度
//==================================
//　敵毛玉情報
//==================================
#define ENEMY_WOOL_PATH "Data/Wool.png"
#define ENEMY_WOOL_RADIUS (32)		//毛玉の半径
#define ENEMY_WOOL_MAX_NUM	(100)		//敵の最大数
#define ENEMY_WOOL_MAX_HP	(1)		//敵の最大HP
//==================================
//　BOSS情報
//==================================
#define BOSS_PATH "Data/Boss.png"
#define BOSS_RADIUS (64)		//ボスの半径
#define BOSS_MAX_HP (150)		//ボスの最大HP
#define BOSS_DEFAULT_X	(445)		//ボスのデフォルトX
#define BOSS_DEFAULT_Y	(250)		//ボスのデフォルトY
//==================================
//　ゲームオーバーかクリアかの情報
//==================================
#define SCENE_CLEAR	(1)			//クリアシーンの番号
#define SCENE_GAMEOVER	(2)			//ゲームオーバーの番号
//==================================
//　画像ハンドル
//==================================
int bgUI;	//UI画像
int lifeHandle;	//残機画像
int logoHandle;	//ロゴ
//==================================
//　背景画像
//==================================
int bgPlayHandle[2] = { 0 };	//画像ハンドル
int bgSkyY[2] = { 0 };			//Y座標


//自機情報構造体
struct PlayerInfo {
	int handle;	//画像ハンドル
	int x, y;	//xy座標
	int cooltime;	//弾発射のクールタイム
	bool isUse;	//使用中かの判定
	int speed;	//速度
	int life;	//残機
	bool damageCheck;	//被弾判定
	bool invincible;	//無敵判定
	int invincibleTime;	//無敵時間
	bool operation;	//操作可能か
	bool revival;	//復活中
	int revivalTime;	//復活中の現在時間
	bool flash;	//点滅
};
PlayerInfo playerInfo = { 0 };

//毛玉構造体
struct EnemyWoolInfo{
	int handle;	//画像ハンドル
	int x, y;	//x,y座標
	int cooltime;	//弾発射のクールタイム
	bool isUse;	//使用中かどうか
	bool dead;	//倒されたかどうか
	int HP;	//体力
};
int enemyPopCoolTime;

EnemyWoolInfo enemyWoolInfo[ENEMY_WOOL_MAX_NUM] = { 0 };

//ボス構造体
struct BossInfo {
	int handle;	//画像ハンドル
	int x, y;	//x,y座標
	int cooltime;	//弾のクールタイム
	bool isUse;	//使用中かどうか
	int HP;	//体力
	int invincible;	//無敵判定
	int invincibleTime;	//無敵時間
	bool flash;	//点滅
	int life;	//ボスの残機
	int bossThreeCount;	//ボス弾幕3つめの回転度数
	bool entranceFlag;	//登場シーンのフラグ
};
BossInfo bossInfo = { 0 };


//クリアかゲームオーバーかの判定
int scenecheck;



//==================================
//	プレイ初期化
//==================================
void InitPlay()
{

	//==================================
	//　画像初期化
	//==================================
	 bgUI = LoadGraph(BG_UI_PATH);	//UI画像
	 lifeHandle = LoadGraph(LIFE_PATH);	//残機画像
	 logoHandle = LoadGraph(LOGO_PATH);	//ロゴ
	//==================================
	//　プレイ背景初期化
	//==================================
	for (int i = 0; i < 2; i++)
	{
		bgPlayHandle[i] = LoadGraph(BG_PLAY_PATH);
	}
	//==================================
	//　プレイ背景初期化
	//==================================
	bgSkyY[0] = 0;
	bgSkyY[1] = -WINDOW_HEIGHT;
	//==================================
	//　プレイヤーを初期化
	//==================================
	playerInfo.handle = LoadGraph(PLAYER_PATH);	//画像ハンドル
	playerInfo.x = 445;	//x座標
	playerInfo.y = 850;	//y座標
	playerInfo.isUse = true;	//プレイヤーが使用されているか
	playerInfo.life = 2;	//残機
	playerInfo.invincible = false;	//無敵判定
	playerInfo.invincibleTime = 0;	//残り無敵時間
	playerInfo.damageCheck = false;	//ダメージ判定
	playerInfo.operation = true;
	playerInfo.revival = false;
	playerInfo.revivalTime = 0;
	playerInfo.flash = false;
	//==================================
	//　敵を初期化 座標とcooltimeも初期化
	//==================================
	bossInfo.handle = LoadGraph(BOSS_PATH);	//画像ハンドル
	bossInfo.isUse = false;	//使用中かどうか
	bossInfo.x = BOSS_DEFAULT_X;	//ボスのxを
	bossInfo.y = 0;	//ボスのy(最初は出現していないので0で良い)
	bossInfo.HP = BOSS_MAX_HP;	//ボスのHPを最大HPにする
	bossInfo.invincible = false;	//無敵判定
	bossInfo.invincibleTime = 0;	//残り無敵時間
	bossInfo.flash = false;	//点滅判定
	bossInfo.life = 2;	//ボスの残機
	bossInfo.entranceFlag = false;	//登場シーンを行ったかどうかのフラグ
	bossInfo.bossThreeCount = 0;	//ボス弾幕3を打つために必要な数字
	bossInfo.cooltime = 0;	//弾のクールタイム
	//=======================
	//	ザコ敵の初期化
	//=======================
	for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//雑魚敵の最大数
	{
		enemyWoolInfo[wool_index].x = -100;	//x座標を画面外へ
		enemyWoolInfo[wool_index].y = -100;	//y座標を画面外へ
		enemyWoolInfo[wool_index].handle = LoadGraph(ENEMY_WOOL_PATH);	//画像ハンドル
		enemyWoolInfo[wool_index].isUse = false;	//使用判定
		enemyWoolInfo[wool_index].dead = false;	//死亡判定
		enemyWoolInfo[wool_index].HP = ENEMY_WOOL_MAX_HP;	//HPをMAXHPにする
	}
	enemyPopCoolTime = 0;	//敵が湧く時間のクールタイム

	//クリアかゲームオーバーかの判定
	scenecheck = 0;

	//エフェクト初期化
	InitEffect();

	//エフェクトのロード
	LoadEffect(EFFECT_TYPE_EXPLOSION, 10);
	LoadEffect(EFFECT_TYPE_RECOVERY, 2);

	//SEのロード
	LoadSE(SE_TYPE_PLAYER_SHOT);	//ショットを打った時の音
	LoadSE(SE_TYPE_ENEMY_DAMAGE);	//敵にダメージが入った時の音
	LoadSE(SE_TYPE_PLAYER_DAMAGE);	//自機がやられた時の音

	//弾の初期化
	InitBullet();


	g_CurrentPlaySceneID = PLAY_SCENE_NORMAL_ONE;	//プレイシーンをノーマル・ONEに移行
	//==================================
	//　プレイループへ
	//==================================
	g_CurrentSceneID = SCENE_ID_LOOP_PLAY;
}

//==================================
//	ボスプレイ初期化
//==================================
void InitBossPlay()
{
	playerInfo.life = 1;	//残機を減らす
	g_CurrentPlaySceneID = PLAY_SCENE_BOSS_ENTRANCE;	//プレイシーンをボス登場に移行
}

//==================================
//	プレイ通常処理
//==================================
void StepPlay()
{
	//弾の処理
	StepBullet();

	//弾のロード
	BulletInfo* bullet = GetBulletInfo();
	BulletInfo* black_bullet = GetBlackBulletInfo();

	//=======================
	//	自機操作の処理
	//=======================
	if (playerInfo.operation == true)	//操作可能なら下の処理を行う
	{

		//=======================
		//	自機の移動速度処理
		//=======================
		if ((IsKeyDown(KEY_INPUT_LSHIFT) == 1))	//シフトが押されていたら
		{
			playerInfo.speed = PLAYER_LOW_SPEED;	//速度を下げる
		}
		else if ((IsKeyDown(KEY_INPUT_LSHIFT) == 0))	//シフトが押されていなかったら
		{
			playerInfo.speed = PLAYER_NORMAL_SPEED;	//速度を通常に戻す
		}
		//=======================
		// 自機移動処理
		//=======================
		if ((IsKeyDown(KEY_INPUT_RIGHT) == 1))	//右が押されていたら
		{
			playerInfo.x += playerInfo.speed;	//右に移動する
			if (playerInfo.x > PLAY_WINDOW_WIDTH_RIGHT)	//画面端なら
				playerInfo.x = PLAY_WINDOW_WIDTH_RIGHT;	//画面端に戻す
		}
		if ((IsKeyDown(KEY_INPUT_LEFT) == 1))	//左が押されていたら
		{
			playerInfo.x -= playerInfo.speed;	//右に移動する
			if (playerInfo.x < PLAY_WINDOW_WIDTH_LEFT)	//画面端なら
				playerInfo.x = PLAY_WINDOW_WIDTH_LEFT;	//画面端に戻す
		}
		if ((IsKeyDown(KEY_INPUT_DOWN) == 1))	//下が押されていたら
		{
			playerInfo.y += playerInfo.speed;	//下に移動する
			if (playerInfo.y > PLAY_WINDOW_HEIGHT_DOWN)	//画面端なら
				playerInfo.y = PLAY_WINDOW_HEIGHT_DOWN;	//画面端に戻す
		}
		if ((IsKeyDown(KEY_INPUT_UP) == 1))	//上が押されていたら
		{
			playerInfo.y -= playerInfo.speed;	//上に移動する
			if (playerInfo.y < PLAY_WINDOW_HEIGHT_UP)	//画面端なら
				playerInfo.y = PLAY_WINDOW_HEIGHT_UP;	//画面端に戻す
		}
		//=======================
		//	自機弾発射処理
		//=======================
		if ((IsKeyDown(KEY_INPUT_Z) == true) && (playerInfo.cooltime == 0))	//Zが押されていて、弾のクールタイムが0の時
		{
			int count = 0;	//実行回数カウントを作成、0にする
			for (int index = 0; index < BULLET_MAX_NUM; index++, bullet++)	//バレットの最大数分回す。バレットも増える
			{
				if (bullet->isUse == false)	//バレットが未使用なら
				{
					bullet->isUse = true;	//弾を使用中にする
					bullet->x = playerInfo.x;	//x座標
					bullet->y = playerInfo.y - 23;	//y座標を自機の少し前に
					PlaySE(SE_TYPE_PLAYER_SHOT);	//SEを鳴らす

					playerInfo.cooltime = 5;	//弾のクールタイムをセット

					if (count == 0)	//一回目の処理なら
					{
						bullet->moveX = 0.0f;	//毎秒真っ直ぐに移動
						bullet->moveY = -BULLET_SPD;	//BULLET_SPDの分、上に進む
					}
					else if (count == 1)	//二回目の処理なら
					{
						bullet->moveX = 2;	//毎秒右に移動
						bullet->moveY = -BULLET_SPD;	//BULLET_SPDの分、上に進む
					}
					else if (count == 2)	//三回目の処理なら
					{
						bullet->moveX = -2;	//毎秒左に移動
						bullet->moveY = -BULLET_SPD;	//BULLET_SPDの分、上に進む
					}

					count++;//実行回数を1増やす
					if (count >= 3)	//もし実行回数が三回目以降なら
						break;
				}
			}
		}
	}//自機操作の処理、終了

	//=======================
	// 	敵の挙動
	//=======================
	switch (g_CurrentPlaySceneID)	//g_CurrentPlaySceneIDの中身を見る
	{
	case PLAY_SCENE_NORMAL_ONE:	//NORMAL1の挙動
	{
		if (enemyPopCoolTime <= 0)	//敵が湧く時間のクールタイムがゼロなら
		{
			for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//敵の最大数だけ動く
			{
				if (enemyWoolInfo[wool_index].isUse == false && enemyWoolInfo[wool_index].dead == false)	//使用中ではなくて、死んでいないなら
				{
					enemyWoolInfo[wool_index].isUse = true;	//使用中にする
					enemyWoolInfo[wool_index].x = PLAY_WINDOW_WIDTH_LEFT + GetRand(PLAY_WINDOW_WIDTH_SIZE);	//画面内のランダムなx座標に移動
					enemyWoolInfo[wool_index].y = PLAY_WINDOW_HEIGHT_UP - ENEMY_WOOL_RADIUS;	//画面上部より少し上に移動
					enemyPopCoolTime = GetRand(30);	//敵の湧く時間のクールタイムをランダムに決定
					break;
				}
				continue;
			}
		}
		enemyPopCoolTime--;	//敵の湧く時間を減らす

		for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//敵の最大数だけ動く
		{
			if (enemyWoolInfo[wool_index].isUse == true)	//使用中なら
			{
				enemyWoolInfo[wool_index].y += 3;	//敵の位置を下に移動する
				if (enemyWoolInfo[wool_index].y >= WINDOW_HEIGHT)	//画面外に行ったら
				{
					enemyWoolInfo[wool_index].isUse = false;	//未使用にする
				}
			}
		}

		//=======================
		//	敵が全員倒されたら次のシーンに進む
		//=======================
		for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//敵の最大数だけ動く
		{
			if (enemyWoolInfo[wool_index].dead == false)	//もし誰かが死んでいなかったら何もしない
			{
				break;
			}
			if(wool_index == ENEMY_WOOL_MAX_NUM -1)	//もし最後まで行ったなら
			g_CurrentPlaySceneID = PLAY_SCENE_BOSS_ENTRANCE;	//次のプレイシーンに行く
		}
	}
	break;
	case PLAY_SCENE_BOSS_ENTRANCE:	//ボス登場シーン
		{
		if (bossInfo.entranceFlag == false)	//ボス登場初回の設定
		{
			bossInfo.entranceFlag = true;
			bossInfo.isUse = true;	//ボスを使用中に
			bossInfo.invincible = true;	//無敵判定
			bossInfo.invincibleTime = 1000;	//無敵時間を雑に設定(後で消すので何でも良い)
		}
		bossInfo.y += (BOSS_DEFAULT_Y/100) ;	//ボスのyにBOSS_DEFAULT_Yの100分の一を足す
			if (bossInfo.y >= BOSS_DEFAULT_Y)	//もしボスのy座標が指定の位置に行ったら
			{
				bossInfo.invincible = false;	//無敵を解く
				bossInfo.invincibleTime = 0;	//無敵時間を0
				bossInfo.flash = false;	//点滅を解く
				bossInfo.y = BOSS_DEFAULT_Y;	//ボスのyを定位置に移動
				g_CurrentPlaySceneID = PLAY_SCENE_BOSS_ONE;	//次のプレイシーンに移動
			}
		}
		break;
	case PLAY_SCENE_BOSS_ONE:	//ボス弾幕1
	{
		if (bossInfo.invincible == false)	//無敵じゃないなら
		{
			//敵弾発射処理
			if ((bossInfo.cooltime == 0) && (bossInfo.isUse == true))
			{
				//BulletInfo* black_bullet = GetBulletInfo();
				int count = 0;	//動いた数

				for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)
				{
					if (black_bullet->isUse == false)
					{

						//発射間隔をリセット
						bossInfo.cooltime = 1;


						black_bullet->x = bossInfo.x;
						black_bullet->y = bossInfo.y + 10;

						black_bullet->isUse = true;


						double angle = 0;

						angle = atan2(rand() - rand(), rand() - rand());	//角度


						//求めたベクトルを使用して、プレイヤーの方向への移動量を求める
						black_bullet->moveX = cos(angle) * BLACK_BULLET_SPD;
						black_bullet->moveY = sin(angle) * BLACK_BULLET_SPD;

						count += 1;

						if (count >= 2)	//もし二回動いたら
							break;
					}
				}
			}
		}
	}
	break;
	case PLAY_SCENE_BOSS_TWO:
	{
		if (bossInfo.invincible == false)	//無敵じゃないなら
		{
			//敵弾発射処理
			if ((bossInfo.cooltime == 0) && (bossInfo.isUse == true))
			{
				//BulletInfo* black_bullet = GetBulletInfo();
				int count = 0;

				for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)
				{
					if (black_bullet->isUse == false)
					{

						//発射間隔をリセット
						bossInfo.cooltime = 6;


						black_bullet->x = bossInfo.x;
						black_bullet->y = bossInfo.y + 10;

						black_bullet->isUse = true;

						double angle = 0;

						if (count == 0)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x);	//角度

						if (count == 1)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x) + 0.3;	//角度

						if (count == 2)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x) - 0.3;	//角度

						if (count == 3)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x) + 0.6;	//角度

						if (count == 4)
							angle = atan2(playerInfo.y - black_bullet->y, playerInfo.x - black_bullet->x) - 0.6;	//角度


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
		if (bossInfo.invincible == false)	//無敵じゃないなら
		{
			//敵弾発射処理
			if ((bossInfo.cooltime == 0) && (bossInfo.isUse == true))
			{
				//BulletInfo* black_bullet = GetBulletInfo();
				int count = 0;

				for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)
				{
					if (black_bullet->isUse == false)
					{

						//発射間隔をリセット
						bossInfo.cooltime = 2;


						black_bullet->x = bossInfo.x;
						black_bullet->y = bossInfo.y + 10;

						black_bullet->isUse = true;

						double angle = 0;

						if (count == 0)
							angle = atan2(1, 0) + (00.2 * bossInfo.bossThreeCount);	//角度
						else if (count == 1)
							angle = atan2(0, -1) + (00.2 * bossInfo.bossThreeCount);	//角度
						else if (count == 2)
							angle = atan2(-1, 0) + (00.2 * bossInfo.bossThreeCount);	//角度
						else if (count == 3)
							angle = atan2(0, 1) + (00.2 * bossInfo.bossThreeCount);	//角度

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
	// 敵の弾発射クールタイム
	//=======================
	//弾発射のクールタイム
	if (playerInfo.cooltime > 0)
		playerInfo.cooltime -= 1;
	//BOSS弾発射のクールタイム
	if (bossInfo.cooltime > 0)
		bossInfo.cooltime -= 1;

	//=======================
	//	自機弾の処理
	//=======================
	bullet = GetBulletInfo();	//弾のロード
	for (int index = 0; index < BULLET_MAX_NUM; index++,bullet++)
	{

		if (bullet->isUse == false)//弾が未使用なら
		{
			continue;//次の玉の確認
		}

		//=======================
		// 	自機弾が雑魚woolに当たっているかの判定
		//=======================
		for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)	//雑魚の数だけ
		{
			if (enemyWoolInfo[wool_index].isUse == 1)	//もしwoolが存在していたら
			{
				if ((atari(bullet->x, bullet->y, BULLET_RADIUS, enemyWoolInfo[wool_index].x, enemyWoolInfo[wool_index].y, ENEMY_WOOL_RADIUS)))	//弾が当たっていたら
				{
					enemyWoolInfo[wool_index].HP-= PLAYER_POWER;	//HPをへらす
					bullet->isUse = false;	//当たった弾を消す
					PlaySE(SE_TYPE_ENEMY_DAMAGE);	//SEを鳴らせる
					PlayEffect(EFFECT_TYPE_EXPLOSION, enemyWoolInfo[wool_index].x, enemyWoolInfo[wool_index].y );	//爆破エフェクトを表示する
					if (enemyWoolInfo[wool_index].HP <= 0)	//HPが0以下だったら
					{
						enemyWoolInfo[wool_index].isUse = false;	//woolを消す
						enemyWoolInfo[wool_index].dead = true;	//woolを死んだ判定にする

						//=======================
						// 死んだら弾を飛ばす処理
						//=======================
						black_bullet = GetBlackBulletInfo();	//黒弾の取得(リセット)
						int count = 0;	//実行回数を数えるためのint
						for (int death_index = 0; death_index < BLACK_BULLET_MAX_NUM; death_index++, black_bullet++)	//黒弾の最大分回す
						{
							if (black_bullet->isUse == false)	//もし使用中ではなかったら
							{
								black_bullet->isUse = true;//黒弾を使用中にする

								//woolの位置に弾を出現
								black_bullet->x = enemyWoolInfo[wool_index].x;
								black_bullet->y = enemyWoolInfo[wool_index].y;

								double angle = atan2(rand() - rand(), rand() - rand());	//ランダムな角度を設定

								//求めたベクトルを使用して、プレイヤーの方向への移動量を求める
								black_bullet->moveX = cos(angle) * BLACK_BULLET_SPD;	//角度 * 速度
								black_bullet->moveY = sin(angle) * BLACK_BULLET_SPD;	//角度 * 速度

								count++;	//実行回数を増やす

								if (count >= 6)	//もし6回実行していたら
									break;
							}
						}
					}
				}
			}
		}//敵woolの判定終わり

		//=======================
		// 自機球がボスに当たっているか
		//=======================
		if (bossInfo.isUse == true)	//もしボスが出現していたら
		{
			if ((atari(bullet->x, bullet->y, BULLET_RADIUS, bossInfo.x, bossInfo.y, BOSS_RADIUS)) && bossInfo.invincible == false)	//もしボスに攻撃が当たったら　無敵ならパス
			{
				bullet->isUse = false;//弾を消す

				bossInfo.HP -= PLAYER_POWER;	//ボスのHPを消す
				PlaySE(SE_TYPE_ENEMY_DAMAGE);	//SEを鳴らせる

				//=======================
				// ボス死亡後処理
				//=======================
				if (bossInfo.HP <= 0)	//ボスのHPが0以下なら
				{
					g_CurrentPlaySceneID++;	//次のシーンへ
					bossInfo.life -= 1;	//ボスの残機を減らす
					bossInfo.invincible = true;	//無敵にする
					bossInfo.invincibleTime = 80;	//無敵時間を設定する
					bossInfo.HP = BOSS_MAX_HP;	//HPをMAXにする

					//=======================
					// 弾を全て消す
					//=======================
					BulletInfo* black_bullet = GetBlackBulletInfo();	//黒弾の取得(リセット)
					for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)	//黒弾の数だけ
					{
						if (black_bullet->isUse == true)	//黒弾が使われていたら
						{
							black_bullet->isUse = false;	//黒弾を消す
						}
					}
					//=======================
					// ボスの残機がなくなった後の処理
					//=======================
					if (bossInfo.life < 0)	//ボスの残機が無かったら
					{
						bossInfo.isUse = false;	//ボスを消滅
						scenecheck = SCENE_CLEAR;	//クリアフラグを立てる
					}
				}
				PlayEffect(EFFECT_TYPE_EXPLOSION, bossInfo.x + GetRand(30) - GetRand(30), bossInfo.y + GetRand(30) - GetRand(30));	//弾が当たったらボス近くに爆破エフェクト
				break;
			}
		}
	}

	//=======================
	// 	自機の当たり判定
	//=======================
	if (playerInfo.invincible == false)	//もし無敵じゃないなら敵の当たり判定を使用する
	{
		//=======================
		// 黒弾の当たり判定チェック
		//=======================
		BulletInfo* black_bullet = GetBlackBulletInfo();	//黒弾の取得(リセット)
		for (int index = 0; index < BLACK_BULLET_MAX_NUM; index++, black_bullet++)	//黒弾の数だけ
		{
			if (black_bullet->isUse == false)	//弾が未使用なら
			{
				continue;	//次を見る
			}
			if (atari(black_bullet->x, black_bullet->y, BLACK_BULLET_RADIUS, playerInfo.x, playerInfo.y, PLAYER_HIT_SIZE))	//当たっているなら
			{
				black_bullet->isUse = false;	//黒弾を消す
				playerInfo.damageCheck = true;	//プレイヤーにダメージを入れる
				break;
			}
		}
		//=======================
		//	ボスと自機が当たった処理
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
	// 	自機のダメージ判定
	//=======================
	if (playerInfo.damageCheck == true)	//もし自機がダメージ食らっていたら
	{
		PlayEffect(EFFECT_TYPE_EXPLOSION, playerInfo.x , playerInfo.y);
		PlaySE(SE_TYPE_PLAYER_DAMAGE);
		playerInfo.life -= 1;	//残機を一減らす
		playerInfo.invincible = true;	//無敵にする
		playerInfo.invincibleTime = 150;	//無敵時間の設定
		playerInfo.operation = false;	//操作不能にする
		playerInfo.x = 445;
		playerInfo.y = 850 + 300;
		playerInfo.damageCheck = false;	//ダメージ食らっていたフラグを消す
		playerInfo.revival = true;	//復活中にする
		playerInfo.revivalTime = 100;	//復活時間を設定
	}
	//=======================
	// 	自機の無敵判定
	//=======================
	if (playerInfo.invincible == true)	//もし無敵なら
	{
		playerInfo.invincibleTime -= 1;	//無敵時間を1へらす
		if (playerInfo.flash == true)
			playerInfo.flash = false;
		else if (playerInfo.flash == false)
			playerInfo.flash = true;
		if (playerInfo.invincibleTime <= 0)	//無敵時間が0になったら
		{
			playerInfo.invincible = false;	//無敵を終わらせる
			playerInfo.flash = false;
		}
	}
	//=======================
	// 	自機の復活判定
	//=======================
	if (playerInfo.revival == true)	//もし自機が復活中なら
	{
		playerInfo.y -= 3;	//上昇する
		playerInfo.revivalTime -= 1;	//復活時間をカウント
		if (playerInfo.revivalTime <= 0)	//時間が0になったら
		{
			playerInfo.operation = true;
			playerInfo.revival = false;	//復活時間を終わらせる
		}
	}
	//=======================
	// 	敵の無敵判定
	//=======================
	if (bossInfo.invincible == true)	//もし敵が無敵なら
	{
		bossInfo.invincibleTime -= 1;	//無敵時間を1へらす
		if (bossInfo.flash == true)
			bossInfo.flash = false;
		else if (bossInfo.flash == false)
			bossInfo.flash = true;
		if (bossInfo.invincibleTime <= 0)	//無敵時間が0になったら
		{
			bossInfo.invincible = false;	//無敵を終わらせる
			bossInfo.flash == false;	//点滅を止める
		}
	}


	//ゲームオーバー処理
	if (playerInfo.life < 0) {
		scenecheck = SCENE_GAMEOVER;
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;

	}


	//DrawRotaGraph(CircleA_x, CircleA_y, 1.0, angle, CircleA_Graph, true);

	DrawFormatString(890, 90, GetColor(255, 255, 255), "x = %d ,y = %d", playerInfo.x, playerInfo.y);


	if (scenecheck == SCENE_CLEAR) {	//シーンチェックがクリアなら
		g_CurrentSceneID = SCENE_ID_FIN_PLAY;
	}

	if (IsKeyPush(KEY_INPUT_ESCAPE) == 1)	//エスケープ押されたら
	{
			DxLib_End();	//ゲームを閉じる
	}

	StepEffect();
}




//==================================
//	プレイ描画処理
//==================================
void DrawPlay() {
	//==================================
	//	背景描画処理
	//==================================
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(0, bgSkyY[i], bgPlayHandle[0], true);
	}
	//背景の移動処理
	for (int i = 0; i < 2; i++)
	{
		bgSkyY[i] += 3;
		if (bgSkyY[i] == WINDOW_HEIGHT)
		{
			bgSkyY[i] = -WINDOW_HEIGHT;
		}

	}

	//プレイヤーの描画
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

	//弾の描画処理
	DrawBullet();


	//敵の描画
	//敵が使用中なら描画する
	if (bossInfo.isUse && bossInfo.flash == false)
	{
		DrawRotaGraph(bossInfo.x, bossInfo.y, 1.0, 0.0, bossInfo.handle, true);
	}
	

	DrawEffect();//エフェクトの描画

	//==================================
	//	UI描画処理
	//==================================
	DrawGraph(0, 0, bgUI, true);

	//==================================
	//	残機描画処理
	//==================================
	DrawString(938, 150,"残機", GetColor(255, 255, 255));
	for (int life_index = 0; life_index < playerInfo.life; life_index++)
	{
		DrawRotaGraph(950 + (30 * life_index), 200, 1.0, 0.0, lifeHandle, true);
	}

	DrawGraph(800, 500, logoHandle, true);	//ロゴの表示
	

	////BOSSのHPを描画
	if(bossInfo.isUse)	//もしBOSS戦なら(BOSSが存在していたら)
	DrawBox(100, PLAY_WINDOW_HEIGHT_UP + 10, 100 + (bossInfo.HP * 4), PLAY_WINDOW_HEIGHT_UP + 25 ,GetColor(255,0,0), true);


}

//==================================
//	プレイ後処理
//==================================
void FinPlay() {

	//弾の後処理
	FinBullet();

	//==================================
	//	プレイ画像破棄
	//==================================
	for (int i = 0; i < 2; i++)
	{
	DeleteGraph(bgPlayHandle[i]);	//背景
	}
	DeleteGraph(playerInfo.handle);	//キャラクター
	DeleteGraph(bossInfo.handle);	//敵
	DeleteGraph(bgUI);	//UI
	DeleteGraph(lifeHandle);	//残機
	DeleteGraph(logoHandle);	//ロゴ

	for (int wool_index = 0; wool_index < ENEMY_WOOL_MAX_NUM; wool_index++)
	{
		DeleteGraph(enemyWoolInfo[wool_index].handle);
	}

	//エフェクトの後処理
	FinEffect();
	
	if (scenecheck == SCENE_GAMEOVER) {
		g_CurrentSceneID = SCENE_ID_INIT_GAMEOVER;
	}
	else if (scenecheck == SCENE_CLEAR) {
		g_CurrentSceneID = SCENE_ID_INIT_CLEAR;
	}
}