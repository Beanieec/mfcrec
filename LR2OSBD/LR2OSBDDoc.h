
// LR2OSBDDoc.h: интерфейс класса CLR2OSBDDoc 
//


#pragma once
#include "Rectangle.h"
#include "Okr.h"
#include "Star.h"
#include "Heart.h"

class CLR2OSBDDoc : public CDocument
{
protected: // создать только из сериализации
	CLR2OSBDDoc() noexcept;
	DECLARE_DYNCREATE(CLR2OSBDDoc)

// Атрибуты
public:
	CArray<CRectangle> m_rectangles;
	CArray<Okr> m_okrs;
	CArray<Star> m_stars;
	CArray<Heart> m_hearts;
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS
// Реализация
public:
	virtual ~CLR2OSBDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
};
