
#ifndef __EFFECT_H__
#define __EFFECT_H__

//エフェクトの種類
enum EFFECT_TYPE
{
	EFFECT_TYPE_EXPLOSION,	//爆発
	EFFECT_TYPE_RECOVERY,		//回復

	EFFECT_TYPE_NUM,
};





//エフェクトの読み込み
//引数	：ファイルパス, エフェクト種類, アニメ総数, 横画像数, 縦画像数, 分割後の横サイズ, 分割後の縦サイズ
void LoadEffect(EFFECT_TYPE type, int create_num);

//エフェクトの初期化
void InitEffect();

//エフェクト通常処理
void StepEffect();

//エフェクト描画処理
void DrawEffect();

//エフェクトの後処理
void FinEffect();

//エフェクトの再生
//引数	：エフェクトの種類, Ｘ座標, Ｙ座標, １枚あたりの表示時間
void PlayEffect(EFFECT_TYPE type, int x, int y);


#endif
