﻿
// SuppressSleepApp.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CSuppressSleepAppApp:
// このクラスの実装については、SuppressSleepApp.cpp を参照してください
//

class CSuppressSleepAppApp : public CWinApp
{
public:
	CSuppressSleepAppApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CSuppressSleepAppApp theApp;
