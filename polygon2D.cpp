#include "main.h"
#include "renderer.h"
#include "polygon2D.h"


// include�̏��ԑ厖�A��{�̂��̂��珇�Ԃ�


void Polygon2D::Init()
{
	VERTEX_3D vertex[4];
																		// ����
	vertex[0].Position	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���W
	vertex[0].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �@��
	vertex[0].Diffuse	 = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);			// �F
	vertex[0].TexCoord	 = D3DXVECTOR2(0.0f, 0.0f);						// �e�N�X�`�����W(��{0.0f~1.0f������10.0f�Ƃ��ɂ����10�\�������B�|���S�����͓���)

	vertex[1].Position	 = D3DXVECTOR3(200.0f, 0.0f, 0.0f);				// �E��
	vertex[1].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	 = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	 = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position	 = D3DXVECTOR3(0.0f, 200.0f, 0.0f);				// ����
	vertex[2].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	 = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	 = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position	 = D3DXVECTOR3(200.0f, 200.0f, 0.0f);			// �E��
	vertex[3].Normal	 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	 = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	 = D3DXVECTOR2(1.0f, 1.0f);


	// �����A�E���A����O�A�E��O�AZ�̎��̌`��

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
											"asset/texture/field004.jpg",
											NULL,
											NULL,
											&m_Texture,
											NULL);
	assert(m_Texture);

	// �V�F�[�_�[�֌W�A�ڂ�����GG��
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

}


void Polygon2D::Uninit()
{
	// �_�C���N�gX�̓����[�X���K�v
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();



}


void Polygon2D::Update()
{


}


void Polygon2D::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// �}�g���N�X�ݒ�
	// �_�C���N�gX�ŃI�u�W�F�N�g����]�����肷��ɂ̓}�g���N�X�ݒ肪�K�v
	Renderer::SetWorldViewProjection2D();


	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	
	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	//���_�o�b�t�@�ɓ����Ă钸�_���ǂ��������ɂȂ��Ă������̐ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	// 4�Ă����̂͒��_���E�̂̓X�^�[�g�ʒu(�قڂق�0�Œ�)
	Renderer::GetDeviceContext()->Draw(4, 0);

}