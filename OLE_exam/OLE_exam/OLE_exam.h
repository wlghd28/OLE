
// OLE_exam.h: OLE_exam 응용 프로그램의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// COLEexamApp:
// 이 클래스의 구현에 대해서는 OLE_exam.cpp을(를) 참조하세요.
//

class COLEexamApp : public CWinApp
{
public:
	COLEexamApp() noexcept;


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	COleTemplateServer m_server;
		// 문서 만들기에 대한 서버 개체입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COLEexamApp theApp;
