
// MFCIFileDialogDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCIFileDialog.h"
#include "MFCIFileDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCIFileDialogDlg dialog



CMFCIFileDialogDlg::CMFCIFileDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCIFILEDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCIFileDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCIFileDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCIFileDialogDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCIFileDialogDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCIFileDialogDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCIFileDialogDlg message handlers

BOOL CMFCIFileDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCIFileDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCIFileDialogDlg::OnPaint()
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
HCURSOR CMFCIFileDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCIFileDialogDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	bool ret = false;

	char starting_dir[] = "H:\\z97x_share\\GitHub_rex4SSD\\MFCIFileDialog\\debug";
	char out[256];
	int max_size = 100;
	IFileDialog* pfd;
	//IFileSaveDialog* pfd;
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pfd));

	if (SUCCEEDED(hr))
	{
		if (starting_dir)
		{
			PIDLIST_ABSOLUTE pidl;
			WCHAR wstarting_dir[MAX_PATH];
			WCHAR* wc = wstarting_dir;
			for (const char* c = starting_dir; *c && wc - wstarting_dir < MAX_PATH - 1; ++c, ++wc)
			{
				*wc = *c == '/' ? '\\' : *c;
			}
			*wc = 0;

			HRESULT hresult = ::SHParseDisplayName(wstarting_dir, 0, &pidl, SFGAO_FOLDER, 0);
			if (SUCCEEDED(hresult))
			{
				IShellItem* psi;
				hresult = ::SHCreateShellItem(NULL, NULL, pidl, &psi);
				if (SUCCEEDED(hresult))
				{
					pfd->SetFolder(psi);//rex
				}
				ILFree(pidl);
			}
		}

		DWORD dwOptions;
		DWORD dwFlags = 0;

		dwFlags |= FOS_FORCEFILESYSTEM;
		dwFlags |= FOS_NOCHANGEDIR;
		dwFlags |= FOS_FORCEFILESYSTEM;
		//dwFlags |= FOS_OVERWRITEPROMPT;
		//dwFlags |= FOS_FORCESHOWHIDDEN;

		hr = pfd->GetOptions(&dwOptions);
		if (SUCCEEDED(hr)) //get option first
		{
			hr = pfd->SetOptions(dwOptions | dwFlags);//rex
	
			if (SUCCEEDED(hr)) //get option first
			{
				// Set the default extension to be ".doc" file.
				hr = pfd->SetDefaultExtension(L"ini");
				if (SUCCEEDED(hr)) //get option first
				{

				}

			}
		}


		if (SUCCEEDED(pfd->Show(NULL)))
		{
			IShellItem* psi;
			if (SUCCEEDED(pfd->GetResult(&psi)))
			{
				WCHAR* tmp;
				if (SUCCEEDED(psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &tmp)))
				{
					char* c = out;
					while (*tmp && c - out < max_size - 1)
					{
						*c = (char)* tmp;
						++c;
						++tmp;
					}
					*c = '\0';
					ret = true;
				}
				psi->Release();
			}
		}
		pfd->Release();
	}
	//return ret;

}

void CMFCIFileDialogDlg::OnFileOpen()
{
	// szFilters is a text string that includes two file name filters:
	// "*.my" for "MyType Files" and "*.*' for "All Files."
	TCHAR szFilters[] = _T("MyType Files (*.my)|*.my|All Files (*.*)|*.*||");

	// Create an Open dialog; the default file name extension is ".my".
	CFileDialog fileDlg(TRUE, _T("my"), _T("*.my"),
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	//fileDlg.SetProperty()
	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();

		// Implement opening and reading file in here.

		//Change the window's title to the opened file's title.
		CString fileName = fileDlg.GetFileTitle();

		SetWindowText(fileName);
	}
}


void CMFCIFileDialogDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	bool ret = false;

	char starting_dir[] = "H:\\z97x_share\\GitHub_rex4SSD\\MFCIFileDialog\\debug";
	char out[256];
	int max_size = 100;

	IFileSaveDialog* pfsd = NULL;
	HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfsd));


	if (SUCCEEDED(hr))
	{
		if (starting_dir)
		{
			PIDLIST_ABSOLUTE pidl;
			WCHAR wstarting_dir[MAX_PATH];
			WCHAR* wc = wstarting_dir;
			for (const char* c = starting_dir; *c && wc - wstarting_dir < MAX_PATH - 1; ++c, ++wc)
			{
				*wc = *c == '/' ? '\\' : *c;
			}
			*wc = 0;

			HRESULT hresult = ::SHParseDisplayName(wstarting_dir, 0, &pidl, SFGAO_FOLDER, 0);
			if (SUCCEEDED(hresult))
			{
				IShellItem* psi;
				hresult = ::SHCreateShellItem(NULL, NULL, pidl, &psi);
				if (SUCCEEDED(hresult))
				{
					pfsd->SetFolder(psi);//rex
				}
				ILFree(pidl);
			}
		}

		DWORD dwOptions;
		DWORD dwFlags = 0;

		dwFlags |= FOS_FORCEFILESYSTEM;
		dwFlags |= FOS_NOCHANGEDIR;
		dwFlags |= FOS_FORCEFILESYSTEM;
		//dwFlags |= FOS_OVERWRITEPROMPT;
		//dwFlags |= FOS_FORCESHOWHIDDEN;

		hr = pfsd->GetOptions(&dwOptions);
		if (SUCCEEDED(hr)) //get option first
		{
			hr = pfsd->SetOptions(dwOptions | dwFlags);//rex

			if (SUCCEEDED(hr)) //get option first
			{
				// Set the default extension to be ".doc" file.
				hr = pfsd->SetDefaultExtension(L"ini");
				if (SUCCEEDED(hr)) //get option first
				{

				}

			}
		}


		if (SUCCEEDED(pfsd->Show(NULL)))
		{
			IShellItem* psi;
			if (SUCCEEDED(pfsd->GetResult(&psi)))
			{
				WCHAR* tmp;
				if (SUCCEEDED(psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &tmp)))
				{
					char* c = out;
					while (*tmp && c - out < max_size - 1)
					{
						*c = (char)* tmp;
						++c;
						++tmp;
					}
					*c = '\0';
					ret = true;
				}
				psi->Release();
			}
		}
		pfsd->Release();
	}
	//return ret;

}


void CMFCIFileDialogDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	OnFileOpen();
}
