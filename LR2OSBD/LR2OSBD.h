
// LR2OSBD.h: основной файл заголовка для приложения LR2OSBD
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CLR2OSBDApp:
// Сведения о реализации этого класса: LR2OSBD.cpp
//

class CLR2OSBDApp : public CWinApp
{
public:
	CLR2OSBDApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLR2OSBDApp theApp;
