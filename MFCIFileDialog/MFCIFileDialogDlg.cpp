
// MFCIFileDialogDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCIFileDialog.h"
#include "MFCIFileDialogDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// CAboutDlg dialog used for App About

char default_dir[] = "H:\\z97x_share\\GitHub_rex4SSD\\MFCIFileDialog\\debug";


class CDialogEventHandler : public IFileDialogEvents,
	public IFileDialogControlEvents
{
public:
	// IUnknown methods
	IFACEMETHODIMP QueryInterface(REFIID riid, void** ppv)
	{
		static const QITAB qit[] = {
			QITABENT(CDialogEventHandler, IFileDialogEvents),
			QITABENT(CDialogEventHandler, IFileDialogControlEvents),
			{ 0 },
#pragma warning(suppress:4838)
		};
		return QISearch(this, qit, riid, ppv);
	}

	IFACEMETHODIMP_(ULONG) AddRef()
	{
		return InterlockedIncrement(&_cRef);
	}

	IFACEMETHODIMP_(ULONG) Release()
	{
		long cRef = InterlockedDecrement(&_cRef);
		if (!cRef)
			delete this;
		return cRef;
	}

	// IFileDialogEvents methods
	IFACEMETHODIMP OnFileOk(IFileDialog*) { return S_OK; };
	IFACEMETHODIMP OnFolderChange(IFileDialog*);
	IFACEMETHODIMP SetDefault(IFileSaveDialog* pfsd);//by rex
	IFACEMETHODIMP OnFolderChanging(IFileDialog*, IShellItem*);
	IFACEMETHODIMP OnHelp(IFileDialog*) { return S_OK; };
	IFACEMETHODIMP OnSelectionChange(IFileDialog*) { return S_OK; };
	IFACEMETHODIMP OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE*) { return S_OK; };
	IFACEMETHODIMP OnTypeChange(IFileDialog* pfd) { return S_OK; };;
	IFACEMETHODIMP OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*) { return S_OK; };


	// IFileDialogControlEvents methods
	IFACEMETHODIMP OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem);
	IFACEMETHODIMP OnButtonClicked(IFileDialogCustomize*, DWORD) { return S_OK; };
	IFACEMETHODIMP OnCheckButtonToggled(IFileDialogCustomize*, DWORD, BOOL) { return S_OK; };
	IFACEMETHODIMP OnControlActivating(IFileDialogCustomize*, DWORD) { return S_OK; };

	CDialogEventHandler() : _cRef(1) { };
private:
	~CDialogEventHandler() { };
	long _cRef;
};


//........................................................................................
//........................................................................................
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
//........................................................................................
//........................................................................................

//........................................................................................
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
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCIFileDialogDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCIFileDialogDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCIFileDialogDlg::OnBnClickedButton6)
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

//........................................................................................
void CMFCIFileDialogDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	bool ret = false;

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
		if (default_dir)
		{
			PIDLIST_ABSOLUTE pidl;
			WCHAR wstarting_dir[MAX_PATH];
			WCHAR* wc = wstarting_dir;
			for (const char* c = default_dir; *c && wc - wstarting_dir < MAX_PATH - 1; ++c, ++wc)
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
}

//........................................................................................
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

//IFileSaveDialog
//........................................................................................
void CMFCIFileDialogDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	bool ret = false;
	char out[256];
	int max_size = 100;

	IFileSaveDialog* pfsd = NULL;
	HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfsd));

	if (SUCCEEDED(hr))
	{
		if (default_dir)
		{
			PIDLIST_ABSOLUTE pidl;
			WCHAR wstarting_dir[MAX_PATH];
			WCHAR* wc = wstarting_dir;
			for (const char* c = default_dir; *c && wc - wstarting_dir < MAX_PATH - 1; ++c, ++wc)
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
}

//........................................................................................
void CMFCIFileDialogDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	OnFileOpen();
}

//........................................................................................
void CMFCIFileDialogDlg::OnBnClickedButton4()
{
	IFileSaveDialog* pfsd;
	
	HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfsd));
	if (SUCCEEDED(hr))
	{
		WCHAR szFullPathToTestFile[MAX_PATH] = {};

		if (default_dir)
		{
			PIDLIST_ABSOLUTE pidl;
			WCHAR wstarting_dir[MAX_PATH];
			WCHAR* wc = wstarting_dir;
			for (const char* c = default_dir; *c && wc - wstarting_dir < MAX_PATH - 1; ++c, ++wc)
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

		// For this exercise, let's just support only one file type to make things simpler.
		// Also, let's use the jpg format for sample purpose because the Windows ships with
		// property handlers for jpg files.
		const COMDLG_FILTERSPEC rgSaveTypes[] = { {L"Photo Document (*.jpg)", L"*.jpg"} };

		// Set the file types to display.
		hr = pfsd->SetFileTypes(ARRAYSIZE(rgSaveTypes), rgSaveTypes);
		if (SUCCEEDED(hr))
		{
			hr = pfsd->SetFileTypeIndex(0);
			if (SUCCEEDED(hr))
			{
				// Set default file extension.
				hr = pfsd->SetDefaultExtension(L"jpg");
				if (SUCCEEDED(hr))
				{
					// Ensure the dialog only returns items that can be represented by file system paths.
					DWORD dwFlags;
					hr = pfsd->GetOptions(&dwFlags);
					if (SUCCEEDED(hr))
					{
						hr = pfsd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM | FOS_NOCHANGEDIR);

						// Let's first get the current property set of the file we are replicating
						// and give it to the file dialog object.
						//
						// For simplicity sake, let's just get the property set from a pre-existing jpg file (in the Pictures folder).
						// In the real-world, you would actually add code to get the property set of the file
						// that is currently open and is being replicated.
						if (SUCCEEDED(hr))
						{
							size_t cSize = strlen(default_dir) + 1;
							wchar_t* wc = new wchar_t[cSize];
							mbstowcs(wc, default_dir, cSize);

							hr = PathCombineW(szFullPathToTestFile, wc, L"Flower.jpg") ? S_OK : E_FAIL;
							if (SUCCEEDED(hr))
							{
								IPropertyStore* pps;
								hr = SHGetPropertyStoreFromParsingName(szFullPathToTestFile, NULL, GPS_DEFAULT, IID_PPV_ARGS(&pps));
								if (FAILED(hr))
								{
									// Flower.jpg is probably not in the Pictures folder.
									TaskDialog(NULL, NULL, L"CommonFileDialogApp", L"Create Flower.jpg in the Pictures folder and try again.",
										NULL, TDCBF_OK_BUTTON, TD_ERROR_ICON, NULL);
								}
								else
								{
									// Call SetProperties on the file dialog object for getting back later.
									pfsd->SetCollectedProperties(NULL, TRUE);
									pfsd->SetProperties(pps);
									pps->Release();
								}
							}
						}
					}
				}
			}
		}

		if (SUCCEEDED(hr))
		{
			hr = pfsd->Show(NULL);
			if (SUCCEEDED(hr))
			{
				IShellItem* psiResult;
				hr = pfsd->GetResult(&psiResult);
				if (SUCCEEDED(hr))
				{
					PWSTR pszNewFileName;
					hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszNewFileName);
					if (SUCCEEDED(hr))
					{
						// This is where you add code to write data to your file.
						// For simplicity, let's just copy a pre-existing dummy jpg file.
						//
						// In the real-world, you would actually add code to replicate the data of
						// file that is currently open.
						hr = CopyFileW(szFullPathToTestFile, pszNewFileName, FALSE) ? S_OK : HRESULT_FROM_WIN32(GetLastError());
						if (SUCCEEDED(hr))
						{
							// Now apply the properties.
							//
							// Get the property store first by calling GetPropertyStore and pass it on to ApplyProperties.
							// This will make the registered propety handler for the specified file type (jpg)
							// do all the work of writing the properties for you.
							//
							// Property handlers for the specified file type should be registered for this
							// to work.
							IPropertyStore* pps;

							// When we call GetProperties, we get back all the properties that we originally set
							// (in our call to SetProperties above) plus the ones user modified in the file dialog.
							hr = pfsd->GetProperties(&pps);
							if (SUCCEEDED(hr))
							{
								// Now apply the properties making use of the registered property handler for the file type.
								//
								// hWnd is used as parent for any error dialogs that might popup when writing properties.
								// Pass NULL for IFileOperationProgressSink as we don't want to register any callback for progress notifications.
								hr = pfsd->ApplyProperties(psiResult, pps, NULL, NULL);
								pps->Release();
							}
						}
						CoTaskMemFree(pszNewFileName);
					}
					psiResult->Release();
				}
			}
		}
		pfsd->Release();
	}
}

//........................................................................................
HRESULT CDialogEventHandler::SetDefault(IFileSaveDialog* pfsd)
{
	//set default 
	if (default_dir)
	{
		PIDLIST_ABSOLUTE pidl;
		WCHAR wstarting_dir[MAX_PATH];
		WCHAR* wc = wstarting_dir;
		for (const char* c = default_dir; *c && wc - wstarting_dir < MAX_PATH - 1; ++c, ++wc)
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
				//SetDefault(pfsd);
			}
			ILFree(pidl);
		}
	}
	return S_OK;
}

//........................................................................................
HRESULT CDialogEventHandler::OnFolderChange(IFileDialog* pfd)
{
	IFileSaveDialog* pfsd;
	HRESULT hr = pfd->QueryInterface(&pfsd);
	IShellItem* psiResult;

	hr = pfsd->GetCurrentSelection(&psiResult);
	if (SUCCEEDED(hr))
	{
		// We are just going to print out the name of the file for sample sake.
		size_t newsize = strlen(default_dir) + 1;
		wchar_t* wcstring = new wchar_t[newsize];

		// Convert char* string to a wchar_t* string.
		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, wcstring, newsize, default_dir, _TRUNCATE);
		MessageBox(NULL, wcstring, L"Save only in the path:", NULL);
		this->SetDefault(pfsd);
	}

	hr = pfsd->GetFolder(&psiResult);
	if (SUCCEEDED(hr))
	{
		//get displayname
		PWSTR pszFilePath = NULL;
		hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
		if (SUCCEEDED(hr))
		{
			CString s(pszFilePath);
			CString s1(default_dir);
			if (s.CompareNoCase(s1) != 0)
				this->SetDefault(pfsd);

		}
	}
	psiResult->Release();
	pfsd->Release();
	return S_OK;
}

//........................................................................................
//no use right now
HRESULT CDialogEventHandler::OnFolderChanging(IFileDialog* pfd, IShellItem* psiResult)
{
	//........................................................................................


	return S_OK;





	//........................................................................................
	IFileSaveDialog* pfsd;
	HRESULT hr = pfd->QueryInterface(&pfsd);
	
	hr = pfsd->GetCurrentSelection(&psiResult);
	if (SUCCEEDED(hr))
	{
		// We are just going to print out the name of the file for sample sake.
		PWSTR pszFilePath = NULL;
		hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
		if (SUCCEEDED(hr))
		{
			wchar_t starting_dir[] = L"H:\\z97x_share\\GitHub_rex4SSD\\MFCIFileDialog\\Debug";
			wchar_t szTarget[128];
			wcscpy(szTarget, pszFilePath);

			//sprintf(sz, "%s", pszFilePath);
			if (wcscmp(szTarget, starting_dir) != 0)
			{
				TRACE("Diff");
				MessageBox(NULL, starting_dir, L"Warning only", NULL);
				return E_NOTIMPL; ////return S_FALSE;
				
			}
			else
			{
				TRACE("SAME");
				return S_OK;
			}
			TaskDialog(NULL,
				NULL,
				L"CommonFileDialogApp",
				pszFilePath,
				NULL,
				TDCBF_OK_BUTTON,
				TD_INFORMATION_ICON,
				NULL);
			CoTaskMemFree(pszFilePath);
		}
		psiResult->Release();
		return S_FALSE;
	}
	return S_OK;
};

//........................................................................................
// IFileDialogControlEvents
// This method gets called when an dialog control item selection happens (radio-button selection. etc).
// For sample sake, let's react to this event by changing the dialog title.
HRESULT CDialogEventHandler::OnItemSelected(IFileDialogCustomize* pfdc, DWORD dwIDCtl, DWORD dwIDItem)
{
	IFileDialog* pfd = NULL;
	HRESULT hr = pfdc->QueryInterface(&pfd);
	if (SUCCEEDED(hr))
	{
		if (dwIDCtl == CONTROL_RADIOBUTTONLIST)
		{
			switch (dwIDItem)
			{
			case CONTROL_RADIOBUTTON1:
				hr = pfd->SetTitle(L"Longhorn Dialog");
				break;

			case CONTROL_RADIOBUTTON2:
				hr = pfd->SetTitle(L"Vista Dialog");
				break;
			}
		}
		pfd->Release();
	}
	return hr;
}
// IFileDialogEvents methods

//........................................................................................
// Instance creation helper
HRESULT CMFCIFileDialogDlg::CDialogEventHandler_CreateInstance(REFIID riid, void** ppv)
{
	*ppv = NULL;
	
	CDialogEventHandler* pDialogEventHandler = new CDialogEventHandler();
	HRESULT hr = pDialogEventHandler ? S_OK : E_OUTOFMEMORY;
	if (SUCCEEDED(hr))
	{
		hr = pDialogEventHandler->QueryInterface(riid, ppv);
		pDialogEventHandler->Release();
	}
	return hr;
}

//........................................................................................
void CMFCIFileDialogDlg::SetDefault(IFileSaveDialog* pfsd)
{
	if (default_dir)
	{
		PIDLIST_ABSOLUTE pidl;
		WCHAR wstarting_dir[MAX_PATH];
		WCHAR* wc = wstarting_dir;
		for (const char* c = default_dir; *c && wc - wstarting_dir < MAX_PATH - 1; ++c, ++wc)
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
	//.............................
}

//........................................................................................
void CMFCIFileDialogDlg::OnBnClickedButton5() 
{
	// TODO: Add your control notification handler code here

	HRESULT hr;
	IFileSaveDialog* pfsd;
	// Create an event handling object, and hook it up to the dialog.
	IFileDialogEvents* pfde = NULL;
	DWORD               dwCookie = 0;

	hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfsd));
	if (SUCCEEDED(hr))
	{
		hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));

		if (SUCCEEDED(hr))
		{
			SetDefault(pfsd);

			// Hook up the event handler.
			DWORD dwCookie;
			hr = pfsd->Advise(pfde, &dwCookie);
			if (SUCCEEDED(hr))
			{
				// Set the options on the dialog.
				DWORD dwFlags;

				// Before setting, always get the options first in order not to override existing options.
				hr = pfsd->GetOptions(&dwFlags);
				if (SUCCEEDED(hr))
				{
					// In this case, get shell items only for file system items.
					hr = pfsd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
					if (SUCCEEDED(hr))
					{
						// Set the file types to display only. Notice that, this is a 1-based array.
						hr = pfsd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
						if (SUCCEEDED(hr))
						{
							// Set the selected file type index to Word Docs for this example.
							hr = pfsd->SetFileTypeIndex(INDEX_WORDDOC);
							if (SUCCEEDED(hr))
							{
								// Set the default extension to be ".doc" file.
								hr = pfsd->SetDefaultExtension(L"ini");
								if (SUCCEEDED(hr))
								{
									// Show the dialog
									hr = pfsd->Show(NULL);
									if (SUCCEEDED(hr))
									{
										
										//HRESULT hr = pfd->QueryInterface(&pfsd);
										//hr = pfsd->GetCurrentSelection(&psiResult);

										// Obtain the result, once the user clicks the 'Open' button.
										// The result is an IShellItem object.
										IShellItem* psiResult;
										//hr = pfsd->GetCurrentSelection(&psiResult);
										hr = pfsd->GetResult(&psiResult);
										if (SUCCEEDED(hr))
										{	
											// We are just going to print out the name of the file for sample sake.
											PWSTR pszFilePath = NULL;
											hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
											if (SUCCEEDED(hr))
											{
												TaskDialog(NULL,
													NULL,
													L"CommonFileDialogApp",
													pszFilePath,
													NULL,
													TDCBF_OK_BUTTON,
													TD_INFORMATION_ICON,
													NULL);
												
											}
											CoTaskMemFree(pszFilePath);
											psiResult->Release();
										}
									}
								}
							}
						}
					}
				}
				// Unhook the event handler.
				pfsd->Unadvise(dwCookie);
			}
			pfde->Release();
		}
		pfsd->Release();
		
	}// end if CoCreateInstance ok
	CoUninitialize();
}

///.....................................................................................
void CMFCIFileDialogDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	PCWSTR paths[] = {
		TEXT("C:\\"),
		TEXT("C:\\Windows"),
		TEXT(""),
		TEXT("This PC"),
		TEXT("MyComputerFolder"), // Canonical KF name
		TEXT("Recycle Bin"),
		TEXT("RecycleBinFolder"), // Canonical KF name
		TEXT("Libraries"),
		TEXT("OneDrive"),
		TEXT("Libraries\\Documents"),
		TEXT("Network"),
		TEXT("NetworkPlacesFolder"), // Canonical KF name
		TEXT("Startup"),
	};

	OleInitialize(0);
	INT pad = 0, fill, i;
	for (i = 0; i < ARRAYSIZE(paths); ++i) pad = max(pad, lstrlen(paths[i]));
	for (i = 1, fill = printf("%-*s | Original | shell:   |\n", pad, ""); i < fill; ++i) printf("-"); printf("\n");
	for (i = 0; i < ARRAYSIZE(paths); ++i)
	{
		WCHAR buf[MAX_PATH], * p1 = NULL, * p2 = NULL;
		IShellItem* pSI;
		HRESULT hr = SHCreateItemFromParsingName(paths[i], NULL, IID_IShellItem, (void**)& pSI);
		if (SUCCEEDED(hr)) pSI->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &p1), pSI->Release();
		wsprintf(buf, L"shell:%s", paths[i]);
		HRESULT hr2 = SHCreateItemFromParsingName(buf, NULL, IID_IShellItem, (void**)& pSI);
		if (SUCCEEDED(hr2)) pSI->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &p2), pSI->Release();
		wprintf(L"%-*s | %.8x | %.8x | %s\n", pad, paths[i], hr, hr2, p2 && *p2 ? p2 : p1 ? p1 : L"");
		CoTaskMemFree(p1), CoTaskMemFree(p2);
	}
}
