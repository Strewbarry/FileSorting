
// SortingDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CSortingDlg ��ȭ ����
class CSortingDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSortingDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SORTING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtSelect();
	CString m_DrectPath;
	CListBox m_ListBox1;
	CString debugMsg;
	afx_msg void OnBnClickedButtSort();
	BOOL PreTranslateMessage(MSG * pMsg);
	CString strInitPath;
};
