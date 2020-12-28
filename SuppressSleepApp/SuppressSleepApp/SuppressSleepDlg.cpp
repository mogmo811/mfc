
// SuppressSleepDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "SuppressSleepApp.h"
#include "SuppressSleepDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSuppressSleepDlg ダイアログ

CSuppressSleepDlg::CSuppressSleepDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SUPPRESSSLEEPAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuppressSleepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_listLog);
	DDX_Control(pDX, IDC_RADIO_SYSTEM, m_radioSystem);
}

BEGIN_MESSAGE_MAP(CSuppressSleepDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SUPPRESS_TIMER, &CSuppressSleepDlg::OnBnClickedButtonSuppressTimer)
	ON_BN_CLICKED(IDC_BUTTON_SUPPRESS, &CSuppressSleepDlg::OnBnClickedButtonSuppress)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE, &CSuppressSleepDlg::OnBnClickedButtonRelease)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSuppressSleepDlg メッセージ ハンドラー

BOOL CSuppressSleepDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	((CButton*)GetDlgItem(IDC_RADIO_SYSTEM))->SetCheck(1);

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CSuppressSleepDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CSuppressSleepDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CSuppressSleepDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSuppressSleepDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_mode == ESuppressMode::Timer)
	{
		CString message(_T(""));
		if (m_radioSystem.GetCheck() == BST_CHECKED)
		{
			::SetThreadExecutionState(ES_SYSTEM_REQUIRED);
			message = _T("OnTimer() > ::SetThreadExecutionState(ES_SYSTEM_REQUIRED");
		}
		else
		{
			::SetThreadExecutionState(ES_DISPLAY_REQUIRED);
			message = _T("OnTimer() > ::SetThreadExecutionState(ES_DISPLAY_REQUIRED");
		}
		WriteLog(message);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSuppressSleepDlg::OnBnClickedButtonSuppressTimer()
{
	m_mode = ESuppressMode::Timer;
	SetTimer(1, 30000, NULL); // 30000: 30 [sec]

	WriteLog(_T("SetTimer(1, 30000, NULL)"));

	SetControlsEnable(true);
}


void CSuppressSleepDlg::OnBnClickedButtonSuppress()
{
	m_mode = ESuppressMode::OneTime;
	if (m_radioSystem.GetCheck() == BST_CHECKED)
	{
		::SetThreadExecutionState(ES_SYSTEM_REQUIRED | ES_CONTINUOUS);
		WriteLog(_T("::SetThreadExecutionState(ES_SYSTEM_REQUIRED | ES_CONTINUOUS)"));
	}
	else
	{
		::SetThreadExecutionState(ES_DISPLAY_REQUIRED | ES_CONTINUOUS);
		WriteLog(_T("::SetThreadExecutionState(ES_DISPLAY_REQUIRED | ES_CONTINUOUS)"));
	}

	SetControlsEnable(true);
}


void CSuppressSleepDlg::OnBnClickedButtonRelease()
{
	if (m_mode == ESuppressMode::Timer)
	{
		KillTimer(1);
		// 抑止を解除
		::SetThreadExecutionState(ES_CONTINUOUS);
	}
	else if (m_mode == ESuppressMode::OneTime)
	{
		// 抑止を解除
		::SetThreadExecutionState(ES_CONTINUOUS);
	}
	else
	{
		// memo: blank
	}
	m_mode = ESuppressMode::Release;

	WriteLog(_T("OnBnClickedButtonRelease()"));
	SetControlsEnable(false);
}

void CSuppressSleepDlg::WriteLog(const CString& message)
{
	m_listLog.InsertString(0, message);
}

void CSuppressSleepDlg::SetControlsEnable(bool bSuppressingSleep)
{
	GetDlgItem(IDC_BUTTON_SUPPRESS)->EnableWindow(!bSuppressingSleep);
	GetDlgItem(IDC_BUTTON_SUPPRESS_TIMER)->EnableWindow(!bSuppressingSleep);
	GetDlgItem(IDC_BUTTON_RELEASE)->EnableWindow(bSuppressingSleep);
	GetDlgItem(IDC_RADIO_SYSTEM)->EnableWindow(!bSuppressingSleep);
	GetDlgItem(IDC_RADIO_DISPLAY)->EnableWindow(!bSuppressingSleep);
}



