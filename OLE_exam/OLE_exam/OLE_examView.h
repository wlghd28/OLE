
// OLE_examView.h: COLEexamView 클래스의 인터페이스
//

#pragma once


class COLEexamView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	COLEexamView() noexcept;
	DECLARE_DYNCREATE(COLEexamView)

// 특성입니다.
public:
	COLEexamDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~COLEexamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnCancelEditSrvr();
	DECLARE_MESSAGE_MAP()
public:
	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
};

#ifndef _DEBUG  // OLE_examView.cpp의 디버그 버전
inline COLEexamDoc* COLEexamView::GetDocument() const
   { return reinterpret_cast<COLEexamDoc*>(m_pDocument); }
#endif

