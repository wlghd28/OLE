
// OLE_examDoc.h: COLEexamDoc 클래스의 인터페이스
//


#pragma once


class COLEexamSrvrItem;

class COLEexamDoc : public COleServerDoc
{
protected: // serialization에서만 만들어집니다.
	COLEexamDoc() noexcept;
	DECLARE_DYNCREATE(COLEexamDoc)

// 특성입니다.
public:
	COLEexamSrvrItem* GetEmbeddedItem()
		{ return reinterpret_cast<COLEexamSrvrItem*>(COleServerDoc::GetEmbeddedItem()); }

// 작업입니다.
public:

// 재정의입니다.
protected:
	virtual COleServerItem* OnGetEmbeddedItem();
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~COLEexamDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	CString m_strText;
	void OnModify();
};
