#pragma once

#include "gameObject.h"

class Platform : public GameObject	// �p��
{
private:

	static class Model* m_Model;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static void Load();
	static void Unload();

};
