#include "DxLib.h"
#include "Input.h"

#define KEY_BUF_LEN	(256)

//=======================
//	現在フレームのキー情報
//=======================
char currentKeyBuf[KEY_BUF_LEN] = { 0 };

//=======================
//	前フレームのキー情報
//=======================
char preKeyBuf[KEY_BUF_LEN] = { 0 };

//=======================
//	入力制御初期化
//=======================
void InitInput()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		currentKeyBuf[index] = '\0';
		preKeyBuf[index] = '\0';
	}
}

//=======================
//	入力制御初ステップ
// 他のStepより早く呼ぶ
//=======================
void StepInput()
{
	//===========================================
	//	前フレームのキー情報変数に記録しておく
	//===========================================
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		preKeyBuf[index] = currentKeyBuf[index];
	}
	//===========================================
	//	現在のキー情報を取得
	//===========================================
	GetHitKeyStateAll(currentKeyBuf);
}
//=======================
//	今押された
//=======================
bool IsKeyPush(int key_code)
{
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
		return true;

	//押されてないのでfalse
	return false;
}

//=======================
//	押し続けられているか
//=======================
bool IsKeyKeep(int key_code)
{
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
		return true;

	//押されてないのでfalse
	return false;
}
//=======================
//	たった今話されたか
//=======================
bool IsKeyRelease(int key_code)
{
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
		return true;

	//押されてないのでfalse
	return false;
}
//=======================
//	単純に押されているか
//=======================
bool IsKeyDown(int key_code) 
{
	//現フレで押されている(前フレの状態は関係なし)
	if (currentKeyBuf[key_code] == 1)
		return true;

	return false;
}