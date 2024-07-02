
// SortingDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Sorting.h"
#include "SortingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CSortingDlg ��ȭ ����



CSortingDlg::CSortingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SORTING_DIALOG, pParent)
	, m_DrectPath(_T(""))
	, debugMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSortingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DrectPath);
	DDX_Control(pDX, IDC_LIST1, m_ListBox1);
}

BEGIN_MESSAGE_MAP(CSortingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTT_SELECT, &CSortingDlg::OnBnClickedButtSelect)
	ON_BN_CLICKED(IDC_BUTT_SORT, &CSortingDlg::OnBnClickedButtSort)
END_MESSAGE_MAP()


// CSortingDlg �޽��� ó����

BOOL CSortingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSortingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSortingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSortingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg) {
		// �������� ���̾�α��� �ʱ�ȭ�� ���� ���
	case BFFM_INITIALIZED:
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		break;
	}
	return 0;
}

void CSortingDlg::OnBnClickedButtSelect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	ITEMIDLIST  *pidlBrowse;
	WCHAR       pszPathname[MAX_PATH];

	BROWSEINFO  BrInfo;
	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;

	memset(&BrInfo, 0x00, sizeof(BrInfo));
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = _T("Select folder");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	// �̺�Ʈ�� ���� ��������� �Լ�
	BrInfo.lpfn = BrowseCallbackProc;

	// ��������� �Լ��� �Ѱ��� ���ڷ� ����ڰ� �����ϰ��� �ϴ� ��θ� �����Ѵ�.
	// ������� �ʱ�������θ� C����̺�� �����ϴ� ���
	CString strInitPath = _T("C:\\");
	BrInfo.lParam = (LPARAM)strInitPath.GetBuffer();

	pidlBrowse = ::SHBrowseForFolder(&BrInfo);


	if (pidlBrowse != NULL)
	{
		// ���õ� ���� ��ξ���
		SHGetPathFromIDList(pidlBrowse, pszPathname);

		// ���(pszPathname)�� �̿��Ͽ� �����۾� �߰�
		m_DrectPath = pszPathname;
		UpdateData(false);

		CFileFind finder;
		CString exe = _T("/*.*");
		BOOL bWorking = finder.FindFile(pszPathname+ exe);

		CString fileName;
		CString DirName;

		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			
			// folder �� ���� continue
			// if (finder.IsDirectory()) continue;

			//������ �̸�
			CString _fileName = finder.GetFileName();

			// �������� �������� ����������� ����
			if (_fileName == _T("Thumbs.db")) continue;

			fileName = finder.GetFileTitle();
			m_ListBox1.AddString(fileName);
		}
	}
}


void CSortingDlg::OnBnClickedButtSort()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(false);

	CFileFind finder;
	CString exe = _T("/*.*");

	BOOL dWorking = finder.FindFile(m_DrectPath + '/' + _T("original"));
	CreateDirectory(m_DrectPath + '/' + _T("original"), NULL);
	CreateDirectory(m_DrectPath + '/' + _T("overlay"), NULL);

	BOOL bWorking = finder.FindFile(m_DrectPath + exe);

	CString fileName;
	CString DirName;
	CString DirList[100];
	int ListCount = 0;

	while (bWorking)
	{

		bWorking = finder.FindNextFile();

		CString _fileName = finder.GetFileName();
		if (_fileName.GetLength() < 5) continue;

		// �������� �������� ����������� ����
		if (_fileName == _T("Thumbs.db")) continue;

		fileName = finder.GetFileTitle();
		DirList[ListCount] = fileName;
		ListCount++;

	}

	for (int i = 0; i < ListCount; i++)
	{
		if (DirList[i].GetLength() < 10) continue;
		DirName = DirList[i];

		debugMsg.Format(_T("DirName : %s\n\n"), DirName);
		OutputDebugString(debugMsg);

		BOOL bWorking2 = finder.FindFile(m_DrectPath + '/' + DirName + exe);
		while (bWorking2) {
			bWorking2 = finder.FindNextFile();
			CString _fileName2 = finder.GetFileName();
			CString overlay;

			if (_fileName2.GetLength() < 5) continue;
			if (_fileName2 == _T("Thumbs.db")) continue;

			CString View, Sub, ViewV, ViewN, SubS, SubN;
			CString Ov;

			AfxExtractSubString(View, _fileName2, 0, '_');
			AfxExtractSubString(Sub, _fileName2, 1, '_');
			AfxExtractSubString(Ov, _fileName2, 4, '_');
			AfxExtractSubString(Ov, Ov, 0, '.');

			ViewV = View[0];
			ViewN = View[7];
			SubS = Sub[0];
			SubN = Sub[6];

			if (Ov == "Overlay")
				overlay = _T("overlay");
			else
				overlay = _T("original");

			CString vsPath = m_DrectPath + '/' + overlay + '/' + ViewV + ViewN + SubS + SubN;
			CreateDirectory(vsPath, NULL);



			debugMsg.Format(_T("ViewN : %s\n"), ViewN);
			OutputDebugString(debugMsg);
		}
	}
	//MessageBox(_T("success!!"), _T("alert"), NULL);
}
