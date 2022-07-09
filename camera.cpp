#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "input.h"
#include "player.h"

#define	VALUE_X_ROTATE_CAMERA_MOUSE	(D3DX_PI * 0.0005f)							// �}�E�X���g�p�����J�����̉�]��
#define	VALUE_Y_ROTATE_CAMERA_MOUSE	(D3DX_PI * 0.0003f)							// �}�E�X���g�p�����J�����̉�]��

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 2.0f, -5.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
void Camera::Uninit()
{

}

void Camera::Update()
{
	// �v���C���[�̃r���[�}�g���N�X�擾
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(1);
	D3DXVECTOR3 PlayerPosition = player->GetPosition();
	D3DXVECTOR3 PlayerForward = player->GetForward();

	//// �g�b�v�r���[
	//m_Target = PlayerPosition;
	//m_Position = PlayerPosition + D3DXVECTOR3(0.0f, 2.0f, -5.0f);

	// �T�[�h�p�[�\���r���[
	m_Target = PlayerPosition;
	m_Position = PlayerPosition - PlayerForward * 5.0f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);

	//// �t�@�[�X�g�p�[�\���r���[
	//m_Target = PlayerPosition + PlayerForward;
	//m_Position = PlayerPosition;




	//////////m_Position = D3DXVECTOR3(0.0f, m_Position.y + 0.001f, m_Position.z - 0.001f);
	//////////m_Position = D3DXVECTOR3(0.0f, m_Position.y, m_Position.z);

	//////////float MouseMoveAmount_X = Input::GetMouseX();
	//////////float MouseMoveAmount_Y = Input::GetMouseY();

	//////////// �ق�̏����̈ړ��̓}�E�X�������ĂȂ�����ɂ���(����Ȃ��ƃ}�W�Ő���)
	//////////if (fabsf(MouseMoveAmount_X) < 1.0f)
	//////////	MouseMoveAmount_X = 0.0f;
	//////////if (fabsf(MouseMoveAmount_Y) < 1.0f)
	//////////	MouseMoveAmount_Y = 0.0f;

	//////////// �}�E�X����ł̎��_�ړ��̌v�Z����
	//////////m_Rotation.y += MouseMoveAmount_X * VALUE_X_ROTATE_CAMERA_MOUSE;
	//////////if (m_Rotation.y < -D3DX_PI)
	//////////{
	//////////	m_Rotation.y = D3DX_PI;
	//////////}
	//////////if (m_Rotation.y > D3DX_PI)
	//////////{
	//////////	m_Rotation.y = -D3DX_PI;
	//////////}

	//////////m_Rotation.x -= MouseMoveAmount_Y * VALUE_Y_ROTATE_CAMERA_MOUSE;
	//////////if (m_Rotation.x > D3DX_PI_HARF - 0.1f)
	//////////{
	//////////	m_Rotation.x = D3DX_PI_HARF - 0.1f;
	//////////}
	//////////if (m_Rotation.x < -D3DX_PI_HARF + 0.1f)
	//////////{
	//////////	m_Rotation.x = -D3DX_PI_HARF + 0.1f;
	//////////}
}


void Camera::Draw()
{

	// �r���[�}�g���N�X�ݒ�
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);


	// �v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);	// �A�X�y�N�g�����/�c�ł���Ă�B�ǂ���������^�Ȃ̂Ńt���[�g�ɂ���B

	Renderer::SetProjectionMatrix(&projectionMatrix);
}