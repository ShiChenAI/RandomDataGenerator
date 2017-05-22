
// RandomDataGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RandomDataGenerator.h"
#include "RandomDataGeneratorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT indicators[] =
{
	ID_STAUTSTIP,           // status line indicator
};
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CRandomDataGeneratorDlg dialog



CRandomDataGeneratorDlg::CRandomDataGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RANDOMDATAGENERATOR_DIALOG, pParent)
	, m_editInputFileName(_T(""))
	, m_editFrames(0)
	, m_editSamples(0)
	, m_editPrjName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRandomDataGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT_FILE_NAME, m_editInputFileName);
	DDX_Text(pDX, IDC_EDIT_FRAMES, m_editFrames);
	DDX_Text(pDX, IDC_EDIT_SAMPLES, m_editSamples);
	DDX_Control(pDX, IDC_CBO_FINGERTIPS, m_cboFingertips);
	DDX_Text(pDX, IDC_EDIT_PRJ_NAME, m_editPrjName);
}

BEGIN_MESSAGE_MAP(CRandomDataGeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEL_INPUT, &CRandomDataGeneratorDlg::OnBnClickedBtnSelInput)
	ON_BN_CLICKED(IDOK, &CRandomDataGeneratorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_CREAT, &CRandomDataGeneratorDlg::OnBnClickedBtnCreat)
END_MESSAGE_MAP()


// CRandomDataGeneratorDlg message handlers

BOOL CRandomDataGeneratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	InitStatusbar();
	InitParameters();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRandomDataGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRandomDataGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRandomDataGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRandomDataGeneratorDlg::InitStatusbar()
{
	m_Statusbar.Create(this);
	m_Statusbar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	CRect rect;
	GetWindowRect(rect);
	m_Statusbar.SetPaneInfo(0, ID_STAUTSTIP, SBPS_STRETCH, rect.Width());

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,
		AFX_IDW_CONTROLBAR_LAST, 0);
}

void CRandomDataGeneratorDlg::InitParameters()
{
	m_editFrames = 10;
	m_editSamples = 10;

	// Add parameters to cbobox
	for (int i = 1; i < 6; i++)
	{
		CString str = CConvertUtility::ToString(i);
		m_cboFingertips.AddString(str);
	}
	m_cboFingertips.SetCurSel(0);

	UpdateData(FALSE);
}


void CRandomDataGeneratorDlg::OnBnClickedBtnSelInput()
{
	m_editInputFileName = CCommonUtility::SelectFile();
	//CCommonUtility::LoadTextFile(m_editInputFileName, m_inputData);
	UpdateData(FALSE);
}


void CRandomDataGeneratorDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	long startRand = 0;
	long endRand = m_editFrames - 1;

	for (int k = 0; k < m_editSamples; k++)
	{
		CString strStatus = TEXT("");
		long sampleNo = k + 1;
		strStatus.Format(TEXT("Samples generating: %d of %d"), sampleNo, m_editSamples);
		m_Statusbar.SetPaneText(0, strStatus);
		vector<long> selFrames;
		while (endRand < m_inputData.size())
		{
			long selFrame = CCommonUtility::GetRandomNumber(startRand, endRand);
			selFrames.push_back(selFrame);
			startRand += m_editFrames;
			endRand += m_editFrames;
		}

		vector<long>::iterator framesIter;
		for (framesIter = selFrames.begin(); framesIter != selFrames.end(); framesIter++)
		{
			long selFrame = *framesIter;
			vector<double> splitResult;
			CCommonUtility::StringSplit(m_inputData[selFrame], splitResult);
			vector<long> randFingertips;
			CString strCurSel = TEXT("");
			m_cboFingertips.GetLBText(m_cboFingertips.GetCurSel(), strCurSel);
			CCommonUtility::GetRandomNumber(0, 4, CConvertUtility::ToLong(strCurSel), randFingertips);

			vector<long>::iterator fingerIter;
			for (fingerIter = randFingertips.begin(); fingerIter != randFingertips.end(); fingerIter++)
			{
				splitResult[(*fingerIter) * 3] = 0;
				splitResult[(*fingerIter) * 3 + 1] = 0;
				splitResult[(*fingerIter) * 3 + 2] = 0;
			}

			CString strFrameResult = TEXT("");
			for (int i = 0; i < splitResult.size(); i++)
			{
				strFrameResult += CConvertUtility::ToString(splitResult[i], 8);
				if (i != splitResult.size() - 1)
				{
					strFrameResult += TEXT(" ");
				}
			}

			m_inputData[selFrame] = strFrameResult;
		}

		SYSTEMTIME sys;
		GetLocalTime(&sys);
		CString saveFileName = TEXT("");
		saveFileName.Format(TEXT("%4d-%02d-%02d-%02d-%02d-%02d-%d.txt"), sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sampleNo);
		CString saveFilePath = m_prjPath;
		saveFilePath += TEXT("\\");
		saveFilePath += saveFileName;
		CCommonUtility::SaveTextFile(saveFilePath, m_inputData);
	}

	m_inputData.clear();
	CCommonUtility::LoadTextFile(m_editInputFileName, m_inputData);
}


void CRandomDataGeneratorDlg::OnBnClickedBtnCreat()
{
	// Get project name
	UpdateData(TRUE);

	if (m_editPrjName.GetLength() <= 0)
	{
		m_Statusbar.SetPaneText(0, TEXT("Please input project name!"));
		return;
	}

	// Create project directory
	m_prjPath = CCommonUtility::GetCurDirectory();
	m_prjPath += TEXT("\\");
	m_prjPath += m_editPrjName;
	if (PathIsDirectory(m_prjPath))
	{
		m_Statusbar.SetPaneText(0, TEXT("Project has already existed!"));
		return;
	}
	if (CreateDirectory(m_prjPath, NULL))
	{
		m_Statusbar.SetPaneText(0, TEXT("Project created successfully!"));
		m_inputData.clear();
		CCommonUtility::LoadTextFile(m_editInputFileName, m_inputData);
		return;
	}
}
