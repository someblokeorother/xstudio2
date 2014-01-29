
// MFC Test 1.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "afxcview.h"
#include "Application.h"
#include "MainWnd.h"

#include "ChildFrm.h"
#include "ScriptDocument.h"
#include "ScriptView.h"
#include "LanguageFrame.h"
#include "LanguageEditView.h"
#include "LanguageDocument.h"

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// --------------------------------- GLOBAL --------------------------------

Application theApp;

// --------------------------------- TYPES ---------------------------------

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

// --------------------------------- APP WIZARD ---------------------------------
  
BEGIN_MESSAGE_MAP(Application, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &Application::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// -------------------------------- CONSTRUCTION --------------------------------

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

Application::Application() : GameDataState(AppState::NoGameData)
{
	SetAppID(_T("BearWare.X-Studio.2"));
}

// ------------------------------- STATIC METHODS -------------------------------

// ------------------------------- PUBLIC METHODS -------------------------------

/// <summary>Exits the instance.</summary>
/// <returns></returns>
int Application::ExitInstance()
{
	//TODO: handle additional resources you may have added
	return CWinAppEx::ExitInstance();
}

/// <summary>Initializes the instance.</summary>
/// <returns></returns>
BOOL Application::InitInstance()
{
	
   //VLDEnable();
   VLDDisable();
   //_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();
   AfxOleInit();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDS_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control	
   AfxInitRichEdit2();
	AfxInitRichEdit5();

	
	// Change the registry key under which our settings are stored
	SetRegistryKey(L"Bearware");
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


   // Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new ScriptDocTemplate(IDR_SCRIPTVIEW,
		RUNTIME_CLASS(GUI::ScriptDocument),
		RUNTIME_CLASS(GUI::CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(GUI::ScriptView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

   pDocTemplate = new LanguageDocTemplate(IDR_LANGUAGEVIEW,
		RUNTIME_CLASS(GUI::LanguageDocument),
		RUNTIME_CLASS(GUI::Views::LanguageFrame),
		nullptr);
   if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// create main MDI Frame window
	MainWnd* pMainFrame = new MainWnd;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// Show window
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/// <summary>Loads an icon.</summary>
/// <param name="nResID">The resource identifier.</param>
/// <param name="iSize">Size of the icon</param>
/// <returns></returns>
HICON  Application::LoadIcon(UINT nResID, UINT iSize) const
{
   return (HICON)::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), IMAGE_ICON, iSize, iSize, 0);
}

/// <summary>Loads a bitmap.</summary>
/// <param name="nResID">The resource identifier.</param>
/// <param name="cx">The width.</param>
/// <param name="cy">The height.</param>
/// <param name="flags">Loading flags.</param>
/// <returns></returns>
CBitmap*  Application::LoadBitmap(UINT nResID, int cx, int cy, UINT flags) const
{
   CBitmap* bmp = new CBitmap();
   HBITMAP h = (HBITMAP)::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), IMAGE_BITMAP, cx, cy, flags);
   bmp->Attach(h);
   return bmp;
}

/// <summary>Dispay about box</summary>
void Application::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/// <summary>Opens the string library.</summary>
/// <returns></returns>
BOOL  Application::OpenStringLibrary()
{
   for (POSITION pos = GetFirstDocTemplatePosition(); pos != NULL; )
   {
      LanguageDocTemplate* doc = dynamic_cast<LanguageDocTemplate*>(GetNextDocTemplate(pos));
      if (doc != nullptr)
         return doc->OpenDocumentFile(L"String Library", FALSE, TRUE) != nullptr;
   }
   return FALSE;
}

/// <summary>Application customization load/save methods</summary>
void Application::PreLoadState()
{
	GetContextMenuManager()->AddMenu(GuiString(IDS_EDIT_MENU).c_str(), IDM_EDIT_POPUP);

	GetContextMenuManager()->AddMenu(GuiString(IDS_EXPLORER).c_str(), IDM_PROJECT_POPUP);
}

void Application::LoadCustomState()
{
}

void Application::SaveCustomState()
{
}

// ------------------------------ PROTECTED METHODS -----------------------------

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// ------------------------------- PRIVATE METHODS ------------------------------

