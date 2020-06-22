
// SrvrItem.cpp: COLEexamSrvrItem 클래스의 구현
//

#include "stdafx.h"
#include "OLE_exam.h"

#include "OLE_examDoc.h"
#include "SrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COLEexamSrvrItem 구현

IMPLEMENT_DYNAMIC(COLEexamSrvrItem, COleServerItem)

COLEexamSrvrItem::COLEexamSrvrItem(COLEexamDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	//  (예: 항목의 데이터 소스에 추가 클립보드 형식 추가)
}

COLEexamSrvrItem::~COLEexamSrvrItem()
{
	// TODO: 여기에 정리 코드를 추가합니다.
}

void COLEexamSrvrItem::Serialize(CArchive& ar)
{
	// 항목이 클립보드에 복사되면 프레임워크에서 COLEexamSrvrItem::Serialize를
	//  호출합니다.  이러한 호출은
	//  OLE 콜백 OnGetClipboardData를 통해 자동으로 발생시킬 수 있습니다.
	//  포함 항목의 경우 기본적으로 해당 문서의 Serialize 함수에 위임하는 것이
	//  좋습니다.  연결을 지원할 경우에는 문서의 일부만
	//  serialization할 수 있습니다.

	if (!IsLinkedItem())
	{
		COLEexamDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc)
			pDoc->Serialize(ar);
	}
}

BOOL COLEexamSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	// 이 응용 프로그램과 같은 대부분의 응용 프로그램은 항목의
	//  내용 모양 그리기만 처리합니다.
	//  OnDrawEx를 재정의하여 DVASPECT_THUMBNAIL과 같은 다른 모양을 지원하려면
	//  이 OnGetExtent의 구현을 수정하여 추가 모양을 처리하도록
	//  해야 합니다.

	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	// COLEexamSrvrItem::OnGetExtent를 호출합니다.
	//  전체 항목의 범위를 HIMETRIC 단위로 가져오기 위해서입니다.  여기에서의 기본 구현은 단순히
	//  하드 코드된 단위 수를 반환하는 것입니다.

	// TODO: 이 임의의 크기를 바꿉니다.

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC 단위

	return TRUE;
}

BOOL COLEexamSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	if (!pDC)
		return FALSE;

	// rSize를 사용할 경우 이 줄을 제거하십시오.
	UNREFERENCED_PARAMETER(rSize);

	COLEexamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: set mapping mode and extent
	//  (The extent is usually the same as the size returned from OnGetExtent)
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0, 0);
	pDC->SetWindowExt(3000, -3000);

	CFont font;
	font.CreateFont(-500, 0, 0, 0, 400, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, "Arial");
	CFont* pFont = pDC->SelectObject(&font);
	CRect rectEllipse(CRect(500, -500, 2500, -2500));
	pDC->Ellipse(rectEllipse);
	pDC->TextOut(0, 0, pDoc->m_strText);
	pDC->SelectObject(pFont);

	return TRUE;
}


// COLEexamSrvrItem 진단

#ifdef _DEBUG
void COLEexamSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void COLEexamSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

