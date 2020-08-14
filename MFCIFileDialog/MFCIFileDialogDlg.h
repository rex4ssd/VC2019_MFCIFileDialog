
// MFCIFileDialogDlg.h : header file
//

#pragma once


#include "afxdialogex.h"
#include <new>          // std::nothrow


// CMFCIFileDialogDlg dialog
class CMFCIFileDialogDlg : public CDialogEx
{
// Construction
public:
	CMFCIFileDialogDlg(CWnd* pParent = nullptr);	// standard constructor

	void OnFileOpen();
	void SetDefault(IFileSaveDialog* pfsd);//by rex
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCIFILEDIALOG_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	HRESULT CDialogEventHandler_CreateInstance(REFIID riid, void** ppv);
};



// Indices of file types
#define INDEX_WORDDOC 1
#define INDEX_WEBPAGE 2
#define INDEX_TEXTDOC 3

// Controls
#define CONTROL_GROUP           2000
#define CONTROL_RADIOBUTTONLIST 2
#define CONTROL_RADIOBUTTON1    1
#define CONTROL_RADIOBUTTON2    2       // It is OK for this to have the same ID as CONTROL_RADIOBUTTONLIST,
										// because it is a child control under CONTROL_RADIOBUTTONLIST

// IDs for the Task Dialog Buttons
#define IDC_BASICFILEOPEN                       100
#define IDC_ADDITEMSTOCUSTOMPLACES              101
#define IDC_ADDCUSTOMCONTROLS                   102
#define IDC_SETDEFAULTVALUESFORPROPERTIES       103
#define IDC_WRITEPROPERTIESUSINGHANDLERS        104
#define IDC_WRITEPROPERTIESWITHOUTUSINGHANDLERS 105

const COMDLG_FILTERSPEC c_rgSaveTypes[] =
{
	{L"Setting File (*.ini)",       L"*.ini"},
	/*{L"Web Page (*.htm; *.html)",    L"*.htm;*.html"},
	{L"Text Document (*.txt)",       L"*.txt"},
	{L"All Documents (*.*)",         L"*.*"}*/
};
