
#pragma once
class CLR2OSBDView : public CView
{
protected:
	CLR2OSBDView() noexcept;
	DECLARE_DYNCREATE(CLR2OSBDView)
public:
	CLR2OSBDDoc* GetDocument() const;
public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	int findrectFigure(CPoint point);
	int findcirkFigure(CPoint point);
	int findstarFigure(CPoint point);
	int findheartFigure(CPoint point);
	void DrawHeart(CDC* pDC, int x, int y, int size);
	void DrawStar(CDC* pDC, int x, int y, int size);
public:
	virtual ~CLR2OSBDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	BOOL m_DrawProgress = FALSE;
	CRectangle rectProgress;
	Okr okrProgress;
	Star starProgress;
	Heart heartProgress;
	
	BOOL m_rect = TRUE;
	int m_rdragNum = -1;
	int m_rselected = -1;

	BOOL m_cirk = FALSE;
	int m_cdragNum = -1;
	int m_cselected = -1;

	BOOL m_star = FALSE;
	int m_sdragNum = -1;
	int m_sselected = -1;

	BOOL m_heart = FALSE;
	int m_hdragNum = -1;
	int m_hselected = -1;	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // версия отладки в LR2OSBDView.cpp
inline CLR2OSBDDoc* CLR2OSBDView::GetDocument() const
   { return reinterpret_cast<CLR2OSBDDoc*>(m_pDocument); }
#endif

