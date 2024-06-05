
// LR2OSBDDoc.cpp: реализация класса CLR2OSBDDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "LR2OSBD.h"
#endif

#include "LR2OSBDDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLR2OSBDDoc

IMPLEMENT_DYNCREATE(CLR2OSBDDoc, CDocument)

BEGIN_MESSAGE_MAP(CLR2OSBDDoc, CDocument)
END_MESSAGE_MAP()
// Создание или уничтожение CLR2OSBDDoc

CLR2OSBDDoc::CLR2OSBDDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CLR2OSBDDoc::~CLR2OSBDDoc()
{
}

BOOL CLR2OSBDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}

// Сериализация CLR2OSBDDoc

void CLR2OSBDDoc::Serialize(CArchive& ar)
{
	INT_PTR rnum = 0;
	INT_PTR cnum = 0;
	INT_PTR snum = 0;
	INT_PTR hnum = 0;

	if (ar.IsStoring())
	{
		rnum = m_rectangles.GetCount();
		ar << rnum;
		for (int i = 0; i < rnum; i++) {
			ar << m_rectangles[i].x;
			ar << m_rectangles[i].y;
			ar << m_rectangles[i].width;
			ar << m_rectangles[i].height;
		}
		cnum = m_okrs.GetCount();
		ar << cnum;
		for (int i = 0; i < cnum; i++) {
			ar << m_okrs[i].x;
			ar << m_okrs[i].y;
			ar << m_okrs[i].width;
			ar << m_okrs[i].height;
		}
		snum = m_stars.GetCount();
		ar << snum;
		for (int i = 0; i < snum; i++) {
			ar << m_stars[i].x;
			ar << m_stars[i].y;
			ar << m_stars[i].size;
		}
		hnum = m_hearts.GetCount();
		ar << hnum;
		for (int i = 0; i < hnum; i++) {
			ar << m_hearts[i].x;
			ar << m_hearts[i].y;
			ar << m_hearts[i].size;
		}
	}
	else
	{
		ar >> rnum;
		for (int i = 0; i < rnum; i++) {
			CRectangle r;
			ar >> r.x;
			ar >> r.y;
			ar >> r.width;
			ar >> r.height;
			m_rectangles.Add(r);
		}

		ar >> cnum;
		for (int i = 0; i < cnum; i++) {
			Okr c;
			ar >> c.x;
			ar >> c.y;
			ar >> c.width;
			ar >> c.height;
			m_okrs.Add(c);
		}

		ar >> snum;
		for (int i = 0; i < snum; i++) {
			Star s;
			ar >> s.x;
			ar >> s.y;
			ar >> s.size;
			m_stars.Add(s);
		}

		ar >> hnum;
		for (int i = 0; i < hnum; i++) {
			Heart h;
			ar >> h.x;
			ar >> h.y;
			ar >> h.size;
			m_hearts.Add(h);
		}
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CLR2OSBDDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CLR2OSBDDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CLR2OSBDDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CLR2OSBDDoc

#ifdef _DEBUG
void CLR2OSBDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLR2OSBDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CLR2OSBDDoc


void CLR2OSBDDoc::DeleteContents()
{
	// TODO: добавьте специализированный код или вызов базового класса
	m_rectangles.RemoveAll();
	m_okrs.RemoveAll();
	m_stars.RemoveAll();
	m_hearts.RemoveAll();
	CDocument::DeleteContents();
}
