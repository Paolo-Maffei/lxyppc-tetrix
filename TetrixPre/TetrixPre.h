// TetrixPre.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CTetrixPreApp:
// �йش����ʵ�֣������ TetrixPre.cpp
//

class CTetrixPreApp : public CWinApp
{
public:
	CTetrixPreApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTetrixPreApp theApp;
