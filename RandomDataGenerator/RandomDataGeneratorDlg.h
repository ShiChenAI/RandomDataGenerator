
// RandomDataGeneratorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ConvertUtility.h"
#include "CommonUtility.h"
#include <vector>

using namespace std;

// CRandomDataGeneratorDlg dialog
class CRandomDataGeneratorDlg : public CDialogEx
{
// Construction
public:
	CRandomDataGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RANDOMDATAGENERATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_editInputFileName;
	CStatusBar m_Statusbar;

private:
	void InitStatusbar();
	void InitParameters();

public:
	long m_editFrames;
	long m_editSamples;
	CString m_prjPath;
	vector<CString> m_inputData;
	CComboBox m_cboFingertips;
	afx_msg void OnBnClickedBtnSelInput();
	afx_msg void OnBnClickedOk();
	CString m_editPrjName;
	afx_msg void OnBnClickedBtnCreat();
};
