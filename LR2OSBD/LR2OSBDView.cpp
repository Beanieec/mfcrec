
// LR2OSBDView.cpp: реализация класса CLR2OSBDView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "LR2OSBD.h"
#endif

#include "LR2OSBDDoc.h"
#include "LR2OSBDView.h"
#include <algorithm>
#include <iostream>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.14159265358979323846

// CLR2OSBDView

IMPLEMENT_DYNCREATE(CLR2OSBDView, CView)

BEGIN_MESSAGE_MAP(CLR2OSBDView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// Создание или уничтожение CLR2OSBDView

CLR2OSBDView::CLR2OSBDView() noexcept
{
	// TODO: добавьте код создания

}

CLR2OSBDView::~CLR2OSBDView()
{
}

BOOL CLR2OSBDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CLR2OSBDView::DrawStar(CDC* pDC, int x, int y, int size)
{
	const int numPoints = 10;
	POINT points[numPoints];

	for (int i = 0; i < numPoints; i++)
	{
		double angle = 2 * PI * i / numPoints - PI / 2;
		int radius = (i % 2 == 0) ? size : size / 2;
		points[i].x = x + static_cast<int>(radius * cos(angle));
		points[i].y = y + static_cast<int>(radius * sin(angle));
	}

	pDC->Polygon(points, numPoints);
}

void CLR2OSBDView::DrawHeart(CDC* pDC, int x, int y, int size)
{
	const int numPoints = 50;
	POINT points[numPoints];

	for (int i = 0; i < numPoints; i++) {
		double angle = 2 * PI * i / numPoints - PI;
		double xCoord = 16 * pow(sin(angle), 3);
		double yCoord = -(13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle));
		points[i].x = x + static_cast<int>(xCoord * size * 0.05);
		points[i].y = y + static_cast<int>(yCoord * size * 0.05);
	}
	pDC->Polygon(points, numPoints);
}


// Рисование CLR2OSBDView

void CLR2OSBDView::OnDraw(CDC* pDC)
{
	CLR2OSBDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->Rectangle(5, 5, 275, 115);
	pDC->TextOut(10, 10, L"Клавиша 'P' - режим 'Прямоугольник'");
	pDC->TextOut(10, 30, L"Клавиша 'O' - режим 'Элипс'");
	pDC->TextOut(10, 50, L"Клавиша '{[' - режим 'Звезда'");
	pDC->TextOut(10, 70, L"Клавиша '}]' - режим 'Седрце'");
	if (m_rect)
		pDC->TextOut(10, 90, L"Режим рисования: 'Прямоугольник'");
	if (m_cirk)
		pDC->TextOut(10, 90, L"Режим рисования: 'Элипс'");
	if (m_star)
		pDC->TextOut(10, 90, L"Режим рисования: 'Звезда'");
	if (m_heart)
		pDC->TextOut(10, 90, L"Режим рисования: 'Седрце'");
	

	for (int i = 0; i < pDoc->m_rectangles.GetCount(); i++)
	{
		CPen pen;
		CPen* oldPen = NULL;
		auto r = pDoc->m_rectangles.GetAt(i);
		
		if (i == m_rselected)
		{
			pen.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
			oldPen = pDC->SelectObject(&pen);
		}
		pDC->Rectangle(r.x, r.y, r.x + r.width, r.y + r.height);
		if (oldPen)
		{
			pDC->SelectObject(oldPen);
			oldPen = NULL;
		}
	}

	for (int i = 0; i < pDoc->m_okrs.GetCount(); i++)
	{
		CPen pen;
		CPen* oldPen = NULL;

		auto o = pDoc->m_okrs.GetAt(i);

		if (i == m_cselected)
		{
			pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
			oldPen = pDC->SelectObject(&pen);
		}

		pDC->Ellipse(o.x, o.y, o.x + o.width, o.y + o.height);

		if (oldPen)
		{
			pDC->SelectObject(oldPen);
			oldPen = NULL;
		}
	}

	for (int i = 0; i < pDoc->m_stars.GetCount(); i++)
	{
		CPen pen;
		CPen* oldPen = NULL;

		auto s = pDoc->m_stars.GetAt(i);

		if (i == m_sselected)
		{
			pen.CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
			oldPen = pDC->SelectObject(&pen);
		}
		DrawStar(pDC, s.x, s.y, s.size);
		

		if (oldPen)
		{
			pDC->SelectObject(oldPen);
			oldPen = NULL;
		}
	}

	for (int i = 0; i < pDoc->m_hearts.GetCount(); i++)
	{
		CPen pen;
		CPen* oldPen = NULL;

		auto h = pDoc->m_hearts.GetAt(i);

		if (i == m_hselected)
		{
			pen.CreatePen(PS_SOLID, 3, RGB(255, 192, 203));
			oldPen = pDC->SelectObject(&pen);
		}
		DrawHeart(pDC, h.x, h.y, h.size);


		if (oldPen)
		{
			pDC->SelectObject(oldPen);
			oldPen = NULL;
		}
	}

	if (m_DrawProgress) {
		if (m_rect) {
			pDC->Rectangle(rectProgress.x, rectProgress.y, rectProgress.x + rectProgress.width, rectProgress.y + rectProgress.height);
		}
		if (m_cirk) {
			pDC->Ellipse(okrProgress.x, okrProgress.y, okrProgress.x + okrProgress.width, okrProgress.y + okrProgress.height);
		}
		if (m_star) {
			DrawStar(pDC, starProgress.x, starProgress.y, starProgress.size);
		}
		if (m_heart) {
			DrawHeart(pDC, heartProgress.x, heartProgress.y, heartProgress.size);
		}
	}
}


// Диагностика CLR2OSBDView

#ifdef _DEBUG
void CLR2OSBDView::AssertValid() const
{
	CView::AssertValid();
}

void CLR2OSBDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLR2OSBDDoc* CLR2OSBDView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLR2OSBDDoc)));
	return (CLR2OSBDDoc*)m_pDocument;
}
#endif //_DEBUG

int CLR2OSBDView::findrectFigure(CPoint point)
{
	auto pDoc = GetDocument();
	for (int i = pDoc->m_rectangles.GetCount() - 1; i >= 0; i--) {
		RECT r;
		r.left = pDoc->m_rectangles[i].x;
		r.right = pDoc->m_rectangles[i].x + pDoc->m_rectangles[i].width;
		r.top = pDoc->m_rectangles[i].y;
		r.bottom = pDoc->m_rectangles[i].y + pDoc->m_rectangles[i].height;
		
		if (r.left > r.right)
			std::swap(r.left, r.right);
		if (r.top > r.bottom)
			std::swap(r.top, r.bottom);

		if (PtInRect(&r, point)) {
			return i;
		}
	}
	return -1;
}

int CLR2OSBDView::findcirkFigure(CPoint point)
{
	auto pDoc = GetDocument();
	for (int p = pDoc->m_okrs.GetCount() - 1; p >= 0; p--)
	{
		int center_x = pDoc->m_okrs[p].x + (pDoc->m_okrs[p].width / 2);
		int center_y = pDoc->m_okrs[p].y + (pDoc->m_okrs[p].height / 2);
		int a = abs(pDoc->m_okrs[p].width / 2);
		int b = abs(pDoc->m_okrs[p].height / 2);

		if (pow((point.x - center_x), 2) / pow(a, 2) + pow((point.y - center_y), 2) / pow(b, 2) <= 1)
		{
			return p;
		}
	}
	return -1;
}

int CLR2OSBDView::findstarFigure(CPoint point)
{
	auto pDoc = GetDocument();
	const int numPoints = 10;
	POINT points[numPoints];

	for (int p = pDoc->m_stars.GetCount() - 1; p >= 0; p--)
	{
		int x = pDoc->m_stars[p].x;
		int y = pDoc->m_stars[p].y;
		int size = pDoc->m_stars[p].size;

		for (int i = 0; i < numPoints; i++)
		{
			double angle = 2 * PI * i / numPoints - PI / 2;
			int radius = (i % 2 == 0) ? size : size / 2;
			points[i].x = x + static_cast<int>(radius * cos(angle));
			points[i].y = y + static_cast<int>(radius * sin(angle));
		}

		bool inside = false;
		for (int i = 0, j = numPoints - 1; i < numPoints; j = i++)
		{
			if (((points[i].y > point.y) != (points[j].y > point.y)) && (point.x < (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
			{
				inside = !inside;
			}
		}
		
		if (inside)
		{
			return p;
		}
	}
	return -1;
}

int CLR2OSBDView::findheartFigure(CPoint point)
{
	auto pDoc = GetDocument();
	const int numPoints = 50;
	POINT points[numPoints];

	for (int p = pDoc->m_hearts.GetCount() - 1; p >= 0; p--)
	{
		int x = pDoc->m_hearts[p].x;
		int y = pDoc->m_hearts[p].y;
		int size = pDoc->m_hearts[p].size;

		for (int i = 0; i < numPoints; i++)
		{
			double angle = 2 * PI * i / numPoints - PI;
			double xCoord = 16 * pow(sin(angle), 3);
			double yCoord = -(13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle));
			points[i].x = x + static_cast<int>(xCoord * size * 0.05);
			points[i].y = y + static_cast<int>(yCoord * size * 0.05);
		}

		bool inside = false;
		for (int i = 0, j = numPoints - 1; i < numPoints; j = i++)
		{
			if (((points[i].y > point.y) != (points[j].y > point.y)) && (point.x < (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
			{
				inside = !inside;
			}
		}
		if (inside)
		{
			return p;
		}
	}
	return -1;
}

void CLR2OSBDView::OnLButtonDown(UINT nFlags, CPoint point)
{
	auto pDoc = GetDocument();
	auto rectNum = findrectFigure(point);
	auto cirkNum = findcirkFigure(point);
	auto starNum = findstarFigure(point);
	auto heartNum = findheartFigure(point);
	if (rectNum > -1) {
		m_rdragNum = rectNum;
		rectProgress.x = point.x;
		rectProgress.y = point.y;	
	}
	else if(cirkNum > -1) {
		m_cdragNum = cirkNum;
		okrProgress.x = point.x;
		okrProgress.y = point.y;
	}
	else if (starNum > -1) {
		m_sdragNum = starNum;
		starProgress.x = point.x;
		starProgress.y = point.y;
	}
	else if (heartNum > -1) {
		m_hdragNum = heartNum;
		heartProgress.x = point.x;
		heartProgress.y = point.y;
	}
	else {
		if (m_rect) {
			rectProgress.x = point.x;
			rectProgress.y = point.y;
		}
		if (m_cirk) {
			okrProgress.x = point.x;
			okrProgress.y = point.y;
		}
		if (m_star) {
			starProgress.x = point.x;
			starProgress.y= point.y;
		}
		if (m_heart) {
			heartProgress.x = point.x;
			heartProgress.y = point.y;
		}
		m_DrawProgress = TRUE;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CLR2OSBDView::OnLButtonUp(UINT nFlags, CPoint point)
{
	auto pDoc = GetDocument();
	if (m_rdragNum > -1) 
		m_rdragNum = -1;
	if (m_cdragNum > -1)
		m_cdragNum = -1;
	if (m_sdragNum > -1) 
		m_sdragNum = -1;
	if (m_hdragNum > -1)
		m_hdragNum = -1;
	if (m_DrawProgress) {
		if (m_rect) {
			rectProgress.width = point.x - rectProgress.x;
			rectProgress.height = point.y - rectProgress.y;
			pDoc->m_rectangles.Add(rectProgress);
		}
		if (m_cirk) {
			okrProgress.width = point.x - okrProgress.x;
			okrProgress.height = point.y - okrProgress.y;	
			pDoc->m_okrs.Add(okrProgress);
		}
		if (m_star) {
			starProgress.size = sqrt(pow(point.x, 2) + pow(point.y, 2)) - sqrt(pow(starProgress.x, 2) + pow(starProgress.y, 2));
			pDoc->m_stars.Add(starProgress);
		}
		if (m_heart) {
			heartProgress.size = sqrt(pow(point.x, 2) + pow(point.y, 2)) - sqrt(pow(heartProgress.x, 2) + pow(heartProgress.y, 2));
			pDoc->m_hearts.Add(heartProgress);
		}
		pDoc->SetModifiedFlag();
		m_DrawProgress = FALSE;
	}
	InvalidateRect(NULL);
	CView::OnLButtonUp(nFlags, point);
}


void CLR2OSBDView::OnMouseMove(UINT nFlags, CPoint point)
{
	auto pDoc = GetDocument();
	if (m_DrawProgress) {
		if (m_rect) {
			rectProgress.width = point.x - rectProgress.x;
			rectProgress.height = point.y - rectProgress.y;
		}
		if (m_cirk) {
			okrProgress.width = point.x - okrProgress.x;
			okrProgress.height = point.y - okrProgress.y;
		}
		if (m_star) {
			starProgress.size = sqrt(pow(point.x, 2) + pow(point.y, 2)) - sqrt(pow(starProgress.x, 2) + pow(starProgress.y, 2));
		}
		if (m_heart) {
			heartProgress.size = sqrt(pow(point.x, 2) + pow(point.y, 2)) - sqrt(pow(heartProgress.x, 2) + pow(heartProgress.y, 2));
		}
		InvalidateRect(NULL);
	}
	if (m_rdragNum > -1) {
		int roffsetX = point.x - rectProgress.x;
		int roffsetY = point.y - rectProgress.y;
		rectProgress.x = point.x;
		rectProgress.y = point.y;

		CRectangle r = pDoc->m_rectangles[m_rdragNum];
		r.x += roffsetX;
		r.y += roffsetY;
		pDoc->m_rectangles.SetAt(m_rdragNum, r);
		InvalidateRect(NULL);
	}
	if (m_cdragNum > -1) {
		int ooffsetX = point.x - okrProgress.x;
		int ooffsetY = point.y - okrProgress.y;
		okrProgress.x = point.x;
		okrProgress.y = point.y;

		Okr o = pDoc->m_okrs[m_cdragNum];
		o.x += ooffsetX;
		o.y += ooffsetY;
		pDoc->m_okrs.SetAt(m_cdragNum, o);
		InvalidateRect(NULL);
	}
	if (m_sdragNum > -1) {
		int offsetX = point.x - starProgress.x;
		int offsetY = point.y - starProgress.y;
		starProgress.x = point.x;
		starProgress.y = point.y;

		Star s = pDoc->m_stars[m_sdragNum];
		s.x += offsetX;
		s.y += offsetY;
		pDoc->m_stars.SetAt(m_sdragNum, s);
		InvalidateRect(NULL);
	}
	if (m_hdragNum > -1) {
		int offsetX = point.x - heartProgress.x;
		int offsetY = point.y - heartProgress.y;

		heartProgress.x = point.x;
		heartProgress.y = point.y;

		Heart h = pDoc->m_hearts[m_hdragNum];
		h.x += offsetX;
		h.y += offsetY;
		pDoc->m_hearts.SetAt(m_hdragNum, h);
		InvalidateRect(NULL);
	}
	CView::OnMouseMove(nFlags, point);
}

void CLR2OSBDView::OnRButtonDown(UINT nFlags, CPoint point)
{
	auto pDoc = GetDocument();
	auto rselected = findrectFigure(point);
	auto cselected = findcirkFigure(point);
	auto sselected = findstarFigure(point);
	auto hselected = findheartFigure(point);
	if (m_rselected == rselected) 
		m_rselected = -1;
	else
		m_rselected = rselected;
	if (m_cselected == cselected) 
		m_cselected = -1;
	else 
		m_cselected = cselected;
	if (m_sselected == sselected) 
		m_sselected = -1;
	else 
		m_sselected = sselected;
	if (m_hselected == hselected) 
		m_hselected = -1;
	else 
		m_hselected = hselected;
	InvalidateRect(NULL);
	CView::OnRButtonDown(nFlags, point);
}


void CLR2OSBDView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE)
	{
		auto pDoc = GetDocument();
		if (m_rselected > -1) {
			pDoc->m_rectangles.RemoveAt(m_rselected);
		}
		if (m_cselected > -1) {
			pDoc->m_okrs.RemoveAt(m_cselected);
		}
		if (m_sselected > -1) {
			pDoc->m_stars.RemoveAt(m_sselected);
		}
		if (m_hselected > -1) {
			pDoc->m_hearts.RemoveAt(m_hselected);
		}
		pDoc->SetModifiedFlag();
		m_rselected = -1;
		m_cselected = -1;
		m_sselected = -1;
		m_hselected = -1;
	}
	if (nChar == 0x4F) 
	{
		m_cirk = TRUE;
		m_rect = FALSE;
		m_star = FALSE;
		m_heart = FALSE;
		m_rselected = -1;
		m_cselected = -1;
		m_sselected = -1;
		m_hselected = -1;
		m_rdragNum = -1;
		m_cdragNum = -1;
		m_sdragNum = -1;
		m_hdragNum = -1;
		m_DrawProgress = FALSE;	
	}
	if (nChar == 0x50)
	{
		m_cirk = FALSE;
		m_rect = TRUE;
		m_star = FALSE;
		m_heart = FALSE;
		m_rselected = -1;
		m_cselected = -1;
		m_sselected = -1;
		m_hselected = -1;
		m_rdragNum = -1;
		m_cdragNum = -1;
		m_sdragNum = -1;
		m_hdragNum = -1;
		m_DrawProgress = FALSE;
	}
	if (nChar == VK_OEM_4)
	{
		m_cirk = FALSE;
		m_rect = FALSE;
		m_star = TRUE;
		m_heart = FALSE;
		m_rselected = -1;
		m_cselected = -1;
		m_sselected = -1;
		m_hselected = -1;
		m_rdragNum = -1;
		m_cdragNum = -1;
		m_sdragNum = -1;
		m_hdragNum = -1;
		m_DrawProgress = FALSE;
	}
	if (nChar == VK_OEM_6)
	{
		m_cirk = FALSE;
		m_rect = FALSE;
		m_star = FALSE;
		m_heart = TRUE;
		m_rselected = -1;
		m_cselected = -1;
		m_sselected = -1;
		m_hselected = -1;
		m_rdragNum = -1;
		m_cdragNum = -1;
		m_sdragNum = -1;
		m_hdragNum = -1;
		m_DrawProgress = FALSE;
	}
	Invalidate();
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
