#pragma once

#include "gameObject.h"

class Polygon2D : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;				// ���_�o�b�t�@��ۑ�����ꏊ
	ID3D11ShaderResourceView* m_Texture = NULL;			// �e�N�X�`����ۑ�����ꏊ

	ID3D11VertexShader* m_VertexShader;					// �V�F�[�_�[�̂��
	ID3D11PixelShader* m_PixelShader;					// �V�F�[�_�[�̂��
	ID3D11InputLayout* m_VertexLayout;					// �V�F�[�_�[�̂��

public:
	// �A�N�Z�X�w�肵���p�u���b�N�ɂ��Ȃ��ƊO������A�N�Z�X�ł��Ȃ�
	void Init();
	void Uninit();
	void Update();
	void Draw();



};

