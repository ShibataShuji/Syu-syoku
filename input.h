#pragma once


class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	static long GetMouseX(void);               // �}�E�X��X�����ɓ��������Βl
	static long GetMouseY(void);               // �}�E�X��Y�����ɓ��������Βl
	static long GetMouseZ(void);               // �}�E�X�z�C�[�������������Βl

};
