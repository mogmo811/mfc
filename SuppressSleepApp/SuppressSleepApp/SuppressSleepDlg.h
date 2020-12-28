
// SuppressSleepDlg.h : ヘッダー ファイル
//

#pragma once


// CSuppressSleepDlg ダイアログ
class CSuppressSleepDlg : public CDialogEx
{
// コンストラクション
public:
	CSuppressSleepDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUPPRESSSLEEPAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

// 実装
private:
	enum class ESuppressMode
	{
		Release = 0, Timer, OneTime
	} m_mode = ESuppressMode::Release;
	
	CButton m_radioSystem;
	CListBox m_listLog;

protected:
	HICON m_hIcon;
	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();	
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonSuppressTimer();
	afx_msg void OnBnClickedButtonSuppress();
	afx_msg void OnBnClickedButtonRelease();

	void WriteLog(const CString& message);
	void SetControlsEnable(bool bSuppressSleep);
};
