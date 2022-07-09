#pragma once

#include "gameObject.h"

class Bullet : public GameObject	// �p��
{
private:

	D3DXVECTOR3 m_Velocity;

	static class Model* m_Model;				// ������static

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

public:

	// static�ɂ���ƃC���X�^���X�����Ȃ��Ă��ǂ񂾂�g�����肷�邱�Ƃ��ł���B
	// ����ɂ���ď������̎��Ƃ��A�C���X�^���X�����݂��Ȃ��Ƃ���
	// �ĂԂ��Ƃ��ł���̂�static�͕K�{

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetVelocity(D3DXVECTOR3 vel) { m_Velocity = vel; }




};
