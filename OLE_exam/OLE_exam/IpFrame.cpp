
// IpFrame.cpp: CInPlaceFrame 클래스의 구현
//

#include "stdafx.h"
#include "OLE_exam.h"

#include "IpFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInPlaceFrame

IMPLEMENT_DYNCREATE(CInPlaceFrame, COleIPFrameWnd)

BEGIN_MESSAGE_MAP(CInPlaceFrame, COleIPFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CInPlaceFrame 생성/소멸

CInPlaceFrame::CInPlaceFrame()
{
}

CInPlaceFrame::~CInPlaceFrame()
{
}

int CInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleIPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CResizeBar는 내부 크기 조정을 구현합니다.
	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // 만들지 못했습니다.
	}

	// 기본적으로, 놓기 대상이 사용자의 창 프레임과 관련이 없는 것으로
	//  등록하는 것이 좋습니다.  이렇게 하면 끌어서 놓기를 지원하는
	//  컨테이너에 놓는 작업이 "실패"하지 않습니다.
	m_dropTarget.Register(this);

	return 0;
}

// 컨테이너 응용 프로그램의 창에 컨트롤 모음을 만들기 위해 프레임워크에서 OnCreateControlBars를
//  호출합니다.  pWndFrame은 컨테이너의 최상위 수준 프레임 창이며
//  항상 null이 아닌 값을 가집니다. pWndDoc는 문서 수준 프레임 창으로서
//  컨테이너가 SDI 응용 프로그램일 경우 null이 됩니다.
//  서버 응용 프로그램은 두 창 중 하나에 MFC 컨트롤 모음을 배치할 수 있습니다.
BOOL CInPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// pWndDoc를 사용할 경우에는 이 줄을 제거하십시오.
	UNREFERENCED_PARAMETER(pWndDoc);

	// 이 창에 대한 소유자를 설정하므로 메시지가 올바른 응용 프로그램에 전달됩니다.
	m_wndToolBar.SetOwner(this);


	// 클라이언트의 프레임 창에 도구 모음을 만듭니다.
	if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_SRVR_INPLACE))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	pWndFrame->DockControlBar(&m_wndToolBar);

	return TRUE;
}

BOOL CInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서 Window 클래스 또는 스타일을 수정합니다.

	return COleIPFrameWnd::PreCreateWindow(cs);
}


// CInPlaceFrame 진단

#ifdef _DEBUG
void CInPlaceFrame::AssertValid() const
{
	COleIPFrameWnd::AssertValid();
}

void CInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleIPFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CInPlaceFrame 명령

