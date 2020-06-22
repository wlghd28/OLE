
// OLE_examView.cpp: COLEexamView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OLE_exam.h"
#endif

#include "OLE_examDoc.h"
#include "OLE_examView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COLEexamView

IMPLEMENT_DYNCREATE(COLEexamView, CScrollView)

BEGIN_MESSAGE_MAP(COLEexamView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, &COLEexamView::OnCancelEditSrvr)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// COLEexamView 생성/소멸

COLEexamView::COLEexamView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

COLEexamView::~COLEexamView()
{
}

BOOL COLEexamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// COLEexamView 그리기

void COLEexamView::OnDraw(CDC* pDC)
{
	COLEexamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFont font;
	font.CreateFont(-500, 0, 0, 0, 400, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "Arial");
	CFont * pFont = pDC->SelectObject(&font);
	CRect rectClient;
	GetClientRect(rectClient);
	CSize sizeClient = rectClient.Size();
	pDC->DPtoHIMETRIC(&sizeClient);

	CRect rectEllipse(sizeClient.cx / 2 - 1000,
		-sizeClient.cy / 2 + 1000,
		sizeClient.cx / 2 + 1000,
		-sizeClient.cy / 2 - 1000);
	pDC->Ellipse(rectEllipse);
	pDC->TextOut(0, 0, pDoc->m_strText);
	pDC->SelectObject(pFont);
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void COLEexamView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// COLEexamView 인쇄

BOOL COLEexamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COLEexamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COLEexamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// OLE 서버 지원

// 다음 명령 처리기는 표준 키보드 사용자 인터페이스를 제공하여
//  내부 편집 세션을 취소합니다.  그러면
//  서버(컨테이너가 아님)가 비활성화됩니다.
void COLEexamView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}


// COLEexamView 진단

#ifdef _DEBUG
void COLEexamView::AssertValid() const
{
	CScrollView::AssertValid();
}

void COLEexamView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

COLEexamDoc* COLEexamView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COLEexamDoc)));
	return (COLEexamDoc*)m_pDocument;
}
#endif //_DEBUG


// COLEexamView 메시지 처리기


void COLEexamView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 여기에 구현 코드 추가.
	pDC->SetMapMode(MM_HIMETRIC);
}
