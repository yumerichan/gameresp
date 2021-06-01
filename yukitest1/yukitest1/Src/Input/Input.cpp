#include "DxLib.h"
#include "Input.h"

#define KEY_BUF_LEN	(256)

//=======================
//	���݃t���[���̃L�[���
//=======================
char currentKeyBuf[KEY_BUF_LEN] = { 0 };

//=======================
//	�O�t���[���̃L�[���
//=======================
char preKeyBuf[KEY_BUF_LEN] = { 0 };

//=======================
//	���͐��䏉����
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
//	���͐��䏉�X�e�b�v
// ����Step��葁���Ă�
//=======================
void StepInput()
{
	//===========================================
	//	�O�t���[���̃L�[���ϐ��ɋL�^���Ă���
	//===========================================
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		preKeyBuf[index] = currentKeyBuf[index];
	}
	//===========================================
	//	���݂̃L�[�����擾
	//===========================================
	GetHitKeyStateAll(currentKeyBuf);
}
//=======================
//	�������ꂽ
//=======================
bool IsKeyPush(int key_code)
{
	if (preKeyBuf[key_code] == 0 && currentKeyBuf[key_code] == 1)
		return true;

	//������ĂȂ��̂�false
	return false;
}

//=======================
//	�����������Ă��邩
//=======================
bool IsKeyKeep(int key_code)
{
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 1)
		return true;

	//������ĂȂ��̂�false
	return false;
}
//=======================
//	���������b���ꂽ��
//=======================
bool IsKeyRelease(int key_code)
{
	if (preKeyBuf[key_code] == 1 && currentKeyBuf[key_code] == 0)
		return true;

	//������ĂȂ��̂�false
	return false;
}
//=======================
//	�P���ɉ�����Ă��邩
//=======================
bool IsKeyDown(int key_code) 
{
	//���t���ŉ�����Ă���(�O�t���̏�Ԃ͊֌W�Ȃ�)
	if (currentKeyBuf[key_code] == 1)
		return true;

	return false;
}