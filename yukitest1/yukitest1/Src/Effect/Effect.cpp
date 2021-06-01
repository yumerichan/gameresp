
#include <DxLib.h>
#include "Effect.h"
#include "../Common.h"



//一度に表示できるエフェクトの数
#define EFFECT_MAX_NUM (100)

//エフェクトMAX数
#define EFFECT_TYPE_MAX_NUM (256)

//エフェクトアニメMAX数
#define EFFECT_ANIME_MAX_NUM (4)



struct EffectInfo
{
	//=====================================
	//現在のエフェクト番号
	//=====================================
	int effectType;
	//=====================================
	//各エフェクトの最大画像ハンドル
	//↓は handle[4]と書いてあるのと同じ
	//=====================================
	int handle[EFFECT_ANIME_MAX_NUM];
	//=====================================
	//各エフェクトの画像使用数
	//=====================================
	int animeNum;
	//=======================
	//エフェクト使用中
	//=======================
	bool isUse;

	//一枚当たりの表示時間
	float changeTime;
	//今の画像の時間
	float currentChangeTime;
	//出力する座標
	int x,y;
	//今のアニメーション番号
	int currentAnimeIndex;
};



//エフェクト情報
EffectInfo effectinfo[EFFECT_MAX_NUM];

//エフェクトファイルパス
const char effectFilePath[EFFECT_TYPE_NUM][256] =
{
	{"Data/Effect/EffectTest.png"},
	{"Data/Effect/EffectRecovery.png"},
};

//各エフェクトのアニメ数
const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
{
	4,
	4,
};

//各エフェクトの画像サイズ
const int effectImageSize[EFFECT_TYPE_NUM][2] =
{
	{128/2,128/2},
	{64/2,64/2},
};

//各エフェクトのアニメ画像切り替え時間
const float effectChageTime[EFFECT_TYPE_NUM] =
{
	0.05f,
	0.05f,
};

//各エフェクトの画像分割数
const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =		//	[WIDTH]	, [HEIGHT]
{
	{2,2},
	{2,2},
};






//エフェクトの読み込み
//引数	：ファイルパス, エフェクト種類, アニメ総数, 横画像数, 縦画像数, 分割後の横サイズ, 分割後の縦サイズ
void LoadEffect(EFFECT_TYPE type, int create_num)
{
	EffectInfo* EffectInfo = effectinfo;

	//typeエフェクトを画面に出力できる最大数(create_numの数分)
	for (int i = 0; i < create_num; i++)
	{
		//create_numの数分いれる	(EffectInfoをcreate_num個まで)
		for (int j = 0; j < EFFECT_MAX_NUM; j++, EffectInfo++)
		{
			//中身が入っていなかったらこの処理を行う
			if (effectinfo[j].handle[0] == 0)
			{
				//絵をロードする。ロードできたらcheckに0が入る。
				int check = LoadDivGraph(effectFilePath[type],
					effectAnimeImgNum[type],
					effectImageSplitNum[type][0],
					effectImageSplitNum[type][1],
					effectImageSize[type][0],
					effectImageSize[type][1],
					EffectInfo->handle);

				//ロードできてたら
				if (check == 0)
				{

					EffectInfo->animeNum = effectAnimeImgNum[type];
					EffectInfo->changeTime = effectChageTime[type];
					EffectInfo->effectType = type;

				}

				//このブレイクがないとeffectinfo[j].handle[0]以降もループで行われてしまうので、0~100まで同じ処理が行われてしまう
				break;

			}
		}
	}
}



////エフェクト情報
//EffectInfo* EffectInfo = effectinfo;
//
////画面に出力できる最大数
//for (int Create_index = 0; Create_index < create_num; Create_index++)
//{
//	//エフェクト情報を先頭から囘す
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//読み込みしていないエフェクト情報を見つける
//		//（ひとつ目の画像ハンドルがゼロなら読み込みされてない）
//		if (effectinfo[Effect_index].handle[0] == 0)
//		{
//			//分割画像	
//			int Success_Effect_Img_Flag = LoadDivGraph(effectFilePath[type],
//				effectAnimeImgNum[type],
//				effectImageSplitNum[type][0],
//				effectImageSplitNum[type][1],
//				effectImageSize[type][0],
//				effectImageSize[type][1],
//				EffectInfo->handle
//			);
//
//			//成功したなら	LoadDivGraphは、成功したら0を返すので、loadDivGraphに成功した場合、Success_Effect_Img_Flagの中には0が入る
//			if (Success_Effect_Img_Flag == 0)
//			{
//				//アニメ数を格納
//				EffectInfo->animeNum = effectAnimeImgNum[type];
//
//				//１枚当たりの表示時間を設定
//				EffectInfo->changeTime = effectChageTime[type];
//
//				//エフェクトの種類を設定
//				EffectInfo->effectType = type;
//			}
//
//			//成否関わらず抜ける
//			break;
//		}
//	}
//}


//エフェクトの初期化
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

////	//エフェクト情報
//EffectInfo* EffectInfo = effectinfo;
//
////すべてのエフェクト情報の変数を初期化する
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


//エフェクト通常処理
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

////エフェクト情報
//EffectInfo* EffectInfo = effectinfo;
//
//DrawFormatString(50, 50, GetColor(255, 255, 255), "x[%.2f]", EffectInfo->x);
//
////すべてのエフェクト情報の変数を初期化する
//for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//{
//	//使用中ならアニメ時間を経過させて、アニメ番号を更新する
//	if (EffectInfo->isUse == true)
//	{
//		//画像切り替わるに必要な時間経過したら
//		if (EffectInfo->currentChangeTime >= EffectInfo->changeTime)
//		{
//			EffectInfo->currentAnimeIndex++;		//次の画像へ
//			EffectInfo->currentChangeTime = 0.0f;	//計測時間リセット
//
//			//次の画像がもし無いなら
//			if (EffectInfo->currentAnimeIndex >= EffectInfo->animeNum)
//			{
//				//使用中フラグをOFFに
//				EffectInfo->isUse = false;
//
//				//以下の処理は不要
//				continue;
//			}
//		}
//
//		//時間更新
//		EffectInfo->currentChangeTime += 1.0f / FRAME_RATE;
//
//	}
//}




//エフェクト描画処理
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

////エフェクト情報
//EffectInfo* EffectInfo = effectinfo;
////すべてのエフェクト情報の変数を初期化する
//for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//{
//	//使用中なら現在のアニメ番号で描画する
//	if (EffectInfo->isUse == true)
//	{
//		/*if(EffectInfo->effectType != 1)*/
//		DrawRotaGraph(EffectInfo->x, EffectInfo->y, 1.0, 0.0, EffectInfo->handle[EffectInfo->currentAnimeIndex], true);
//		/*else
//			DrawRotaGraph(EffectInfo->x, EffectInfo->y, 1.5, 0.0, EffectInfo->handle[EffectInfo->currentAnimeIndex], true);*/
//	}
//}



//エフェクトの後処理
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

////	//エフェクト情報
//EffectInfo* EffectInfo = effectinfo;
//7
////すべてのエフェクトを削除
//for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//{
//	//すべて削除する
//	for (int anime_index = 0; anime_index < EFFECT_ANIME_MAX_NUM; anime_index++)
//	{
//		//ゼロ以外だったら削除する
//		if (EffectInfo->handle[anime_index] != 0)
//		{
//			//画像削除
//			DeleteGraph(EffectInfo->handle[anime_index]);
//
//			//the駆除したら０を入れる
//			EffectInfo->handle[anime_index] = 0;
//		}
//	}
//}


//エフェクトの再生
//引数	：エフェクトの種類, Ｘ座標, Ｙ座標, １枚あたりの表示時間
void PlayEffect(EFFECT_TYPE type, int x, int y)
{
	EffectInfo* EffectInfo = effectinfo;
	for (int i = 0; i < EFFECT_MAX_NUM; i++, EffectInfo++)
	{
		//使用中なら
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

////エフェクト情報
//EffectInfo* EffectInfo = effectinfo;
//
////未使用エフェクトを探して再生
//for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//{
//	//使用中なら以下行わない
//	if (EffectInfo->isUse == true)
//		continue;
//
//	//タイプが一致した
//	if (EffectInfo->effectType == type)
//	{
//		//座標を入れる
//		EffectInfo->x = x;
//		EffectInfo->y = y;
//
//		//計測用の変数をクリア
//		EffectInfo->currentAnimeIndex = 0;
//		EffectInfo->currentChangeTime = 0.0f;
//
//		//使用中にする
//		EffectInfo->isUse = true;
//
//		//抜ける
//		break;
//	}
//}



//
//EffectInfo* GetEffect()
//{
//	return effectinfo;
//}



////一度に表示できるエフェクトの数
//#define EFFECT_MAX_NUM (100)
//
////エフェクトMAX数
//#define EFFECT_TYPE_MAX_NUM (256)
//
////エフェクト情報
//EffectInfo effectinfo[EFFECT_MAX_NUM];
//
////エフェクトファイルパス
//const char effectFilePath[EFFECT_TYPE_NUM][256] =
//{
//	{"Data/Effect/ほし.png"},
//	{"Data/Effect/羽使用時.png"},
//	{"Data/Effect/ヘイスト.png"},
//};
//
////各エフェクトのアニメ数
//const int effectAnimeImgNum[EFFECT_TYPE_NUM] =
//{
//	14,
//	25,
//	15,
//};
//
////各エフェクトの画像サイズ
//const int effectImageSize[EFFECT_TYPE_NUM][2] =
//{
//	{64,64},
//	{64,64},
//	{64,64},
//};
//
////各エフェクトのアニメ画像切り替え時間
//const float effectChageTime[EFFECT_TYPE_NUM] =
//{
//	0.05f,
//	0.05f,
//	0.1f,
//};
//
////各エフェクトの画像分割数
//const int effectImageSplitNum[EFFECT_TYPE_NUM][2] =
//{
//	{5,3},
//	{5,5},
//	{5,3},
//};
//
////---------------------------------------------
////	エフェクトの読み込み
////---------------------------------------------
////引数  :ファイルパス, エフェクト種類, アニメ総数, 横画像数, 縦画像数, 分割後の横サイズ, 分割後の縦サイズ
//void LoadEffect(EFFECT_TYPE type, int create_num)
//{
//	//エフェクト情報
//	EffectInfo* EffectInfo = effectinfo;
//
//	//?
//	for (int Create_index = 0; Create_index < create_num; Create_index++)
//	{
//		//エフェクト情報を先頭から囘す
//		for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//		{
//			//読み込みしていないエフェクト情報を見つける
//			//（ひとつ目の画像ハンドルがゼロなら読み込みされてない）
//			if (effectinfo[Effect_index].handle[0] == 0)
//			{
//				//分割画像
//				int Success_Effect_Img_Flag = LoadDivGraph(effectFilePath[type],
//					effectAnimeImgNum[type],
//					effectImageSplitNum[type][0],
//					effectImageSplitNum[type][1],
//					effectImageSize[type][0],
//					effectImageSize[type][1],
//					EffectInfo->handle);
//
//				//サクセス！！
//				if (Success_Effect_Img_Flag == 0)
//				{
//					//アニメ数を格納
//					EffectInfo->animeNum = effectAnimeImgNum[type];
//
//					//１枚当たりの表示時間を設定
//					EffectInfo->changeTime = effectChageTime[type];
//
//					//エフェクトの種類を設定
//					EffectInfo->effectType = type;
//				}
//
//				//成否関わらず抜ける
//				break;
//			}
//		}
//	}
//}
//
////---------------------------------
////	エフェクト初期化
////---------------------------------
//void InitEffect()
//{
//	//エフェクト情報
//	EffectInfo* EffectInfo = effectinfo;
//
//	//すべてのエフェクト情報の変数を初期化する
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
////	エフェクト通常処理
////----------------------------------
//void StepEffect()
//{
//	//エフェクト情報
//	EffectInfo* EffectInfo = effectinfo;
//
//	//すべてのエフェクト情報の変数を初期化する
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//使用中ならアニメ時間を経過させて、アニメ番号を更新する
//		if (EffectInfo->isUse == true)
//		{
//			//画像切り替わるに必要な時間経過したら
//			if (EffectInfo->currentChangeTime >= EffectInfo->changeTime)
//			{
//				EffectInfo->currentAnimeIndex++;		//次の画像へ
//				EffectInfo->currentChangeTime = 0.0f;	//計測時間リセット
//
//				//次の画像がもし無いなら
//				if (EffectInfo->currentAnimeIndex >= EffectInfo->animeNum)
//				{
//					//使用中フラグをOFFに
//					EffectInfo->isUse = false;
//
//					//以下の処理は不要
//					continue;
//				}
//			}
//
//			//時間更新
//			EffectInfo->currentChangeTime += 1.0f / (60 / GameSpeed);
//
//		}
//	}
//}
//
////--------------------------------------
////	エフェクト描画処理
////--------------------------------------
//void DrawEffect()
//{
//	//エフェクト情報
//	EffectInfo* EffectInfo = effectinfo;
//
//	//すべてのエフェクト情報の変数を初期化する
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//使用中なら現在のアニメ番号で描画する
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
////	エフェクト後処理
////----------------------------------------
//void FinEffect()
//{
//	//エフェクト情報
//	EffectInfo* EffectInfo = effectinfo;
//
//	//すべてのエフェクトを削除
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//すべて削除する
//		for (int anime_index = 0; anime_index < EFFECT_ANIME_MAX_NUM; anime_index++)
//		{
//			//ゼロ以外だったら削除する
//			if (EffectInfo->handle[anime_index] != 0)
//			{
//				//画像削除
//				DeleteGraph(EffectInfo->handle[anime_index]);
//
//				//the駆除したら０を入れる
//				EffectInfo->handle[anime_index] = 0;
//			}
//		}
//	}
//}
//
////---------------------------------------
////	エフェクト再生
////---------------------------------------
////引数  :エフェクトの種類, X座標, Y座標, 1枚あたりの表示時間
//void PlayEffect(EFFECT_TYPE type, int x, int y)
//{
//	//エフェクト情報
//	EffectInfo* EffectInfo = effectinfo;
//
//	//未使用エフェクトを探して再生
//	for (int Effect_index = 0; Effect_index < EFFECT_MAX_NUM; Effect_index++, EffectInfo++)
//	{
//		//使用中なら以下行わない
//		if (EffectInfo->isUse == true)
//			continue;
//
//		//タイプが一致した
//		if (EffectInfo->effectType == type)
//		{
//			//座標を入れる
//			EffectInfo->x = x;
//			EffectInfo->y = y;
//
//			//計測用の変数をクリア
//			EffectInfo->currentAnimeIndex = 0;
//			EffectInfo->currentChangeTime = 0.0f;
//
//			//使用中にする
//			EffectInfo->isUse = true;
//
//			//抜ける
//			break;
//		}
//	}
//}
//
//EffectInfo* GetEffect()
//{
//	return effectinfo;
//}