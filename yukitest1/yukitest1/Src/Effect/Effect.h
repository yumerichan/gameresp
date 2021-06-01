
#ifndef __EFFECT_H__
#define __EFFECT_H__

//�G�t�F�N�g�̎��
enum EFFECT_TYPE
{
	EFFECT_TYPE_EXPLOSION,	//����
	EFFECT_TYPE_RECOVERY,		//��

	EFFECT_TYPE_NUM,
};





//�G�t�F�N�g�̓ǂݍ���
//����	�F�t�@�C���p�X, �G�t�F�N�g���, �A�j������, ���摜��, �c�摜��, ������̉��T�C�Y, ������̏c�T�C�Y
void LoadEffect(EFFECT_TYPE type, int create_num);

//�G�t�F�N�g�̏�����
void InitEffect();

//�G�t�F�N�g�ʏ폈��
void StepEffect();

//�G�t�F�N�g�`�揈��
void DrawEffect();

//�G�t�F�N�g�̌㏈��
void FinEffect();

//�G�t�F�N�g�̍Đ�
//����	�F�G�t�F�N�g�̎��, �w���W, �x���W, �P��������̕\������
void PlayEffect(EFFECT_TYPE type, int x, int y);


#endif
