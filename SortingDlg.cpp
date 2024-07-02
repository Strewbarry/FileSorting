
// SortingDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Sorting.h"
#include "SortingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CSortingDlg 대화 상자



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


// CSortingDlg 메시지 처리기

BOOL CSortingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSortingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSortingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg) {
		// 폴더선택 다이얼로그의 초기화가 끝난 경우
	case BFFM_INITIALIZED:
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
		break;
	}
	return 0;
}

void CSortingDlg::OnBnClickedButtSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ITEMIDLIST  *pidlBrowse;
	WCHAR       pszPathname[MAX_PATH];

	BROWSEINFO  BrInfo;
	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;

	memset(&BrInfo, 0x00, sizeof(BrInfo));
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = _T("Select folder");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	// 이벤트에 대한 사용자정의 함수
	BrInfo.lpfn = BrowseCallbackProc;

	// 사용자정의 함수에 넘겨질 인자로 사용자가 설정하고자 하는 경로를 설정한다.
	// 예를들어 초기폴더경로를 C드라이브로 설정하는 경우
	CString strInitPath = _T("C:\\");
	BrInfo.lParam = (LPARAM)strInitPath.GetBuffer();

	pidlBrowse = ::SHBrowseForFolder(&BrInfo);


	if (pidlBrowse != NULL)
	{
		// 선택된 폴더 경로얻음
		SHGetPathFromIDList(pidlBrowse, pszPathname);

		// 경로(pszPathname)를 이용하여 이후작업 추가
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
			
			// folder 일 경우는 continue
			// if (finder.IsDirectory()) continue;

			// 파일 일때

			//파일의 이름
			CString _fileName = finder.GetFileName();

			// 현재폴더 상위폴더 썸네일파일은 제외
			if (_fileName == _T("Thumbs.db")) continue;

			fileName = finder.GetFileTitle();
			m_ListBox1.AddString(fileName);
			 

			/*debugMsg.Format(_T("fileName : %s\n"), _fileName);
			OutputDebugString(debugMsg);*/
		}
	}
}


void CSortingDlg::OnBnClickedButtSort()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}
