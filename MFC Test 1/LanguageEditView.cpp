// LanguageEditView.cpp : implementation file
//

#include "stdafx.h"
#include "LanguageEditView.h"
#include "ListView.h"
#include "afxcview.h"

/// <summary>User interface</summary>
NAMESPACE_BEGIN2(GUI,Views)

   // --------------------------------- APP WIZARD ---------------------------------
  
   // -------------------------------- CONSTRUCTION --------------------------------

   LanguageEditView::LanguageEditView() : CFormView(LanguageEditView::IDD)
   {

   }

   LanguageEditView::~LanguageEditView()
   {
   }

   // ------------------------------- STATIC METHODS -------------------------------

   IMPLEMENT_DYNCREATE(LanguageEditView, CFormView)

   BEGIN_MESSAGE_MAP(LanguageEditView, CFormView)
      ON_WM_SIZE()
      ON_WM_CREATE()
   END_MESSAGE_MAP()

   // ------------------------------- PUBLIC METHODS -------------------------------

   #ifdef _DEBUG
   void LanguageEditView::AssertValid() const
   {
	   CFormView::AssertValid();
   }

   void LanguageEditView::Dump(CDumpContext& dc) const
   {
	   CFormView::Dump(dc);
   }

   LanguageDocument* LanguageEditView::GetDocument() const // non-debug version is inline
   {
	   ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(LanguageDocument)));
	   return (LanguageDocument*)m_pDocument;
   }
   #endif //_DEBUG

   /// <summary>Gets the language string view</summary>
   /// <returns></returns>
   /// <exception cref="Logic::GenericException">View not found</exception>
   LanguageStringView*  LanguageEditView::GetStringView() const
   {
      // Iterate thru views
      for (POSITION pos = GetDocument()->GetFirstViewPosition(); pos != NULL; )
      {
         auto pView = dynamic_cast<LanguageStringView*>(GetDocument()->GetNextView(pos));
         if (pView != nullptr)
            return pView;
      }   

      throw GenericException(HERE, L"Cannot find language string View");
   }

   // ------------------------------ PROTECTED METHODS -----------------------------

   /// <summary>Arrange controls</summary>
   void  LanguageEditView::AdjustLayout()
   {
      // Destroyed/Minimised
	   if (RichEdit.GetSafeHwnd() == nullptr || (AfxGetMainWnd() != nullptr && AfxGetMainWnd()->IsIconic()))
         return;
         
      CRect view;
      GetClientRect(view);

      // Anchor toolbar to top
      int barHeight = ToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	   ToolBar.SetWindowPos(nullptr, view.left, view.top, view.Width(), barHeight, SWP_NOACTIVATE | SWP_NOZORDER);

      // Stretch RichEdit over remainder
      RichEdit.SetWindowPos(nullptr, view.left, view.top+barHeight, view.Width(), view.Height()-barHeight, SWP_NOZORDER | SWP_NOACTIVATE);
   }

   void LanguageEditView::DoDataExchange(CDataExchange* pDX)
   {
      CFormView::DoDataExchange(pDX);
      DDX_Control(pDX, IDC_STRING_EDIT, RichEdit);
   }
   
   int LanguageEditView::OnCreate(LPCREATESTRUCT lpCreateStruct)
   {
      if (CFormView::OnCreate(lpCreateStruct) == -1)
         return -1;

      ToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EDITOR);
	   ToolBar.LoadToolBar(IDR_EDITOR, 0, 0, TRUE /* Is locked */);
	   ToolBar.CleanUpLockedImages();
	   ToolBar.LoadBitmap(IDR_EDITOR, 0, 0, TRUE /* Locked */);

      ToolBar.SetPaneStyle(ToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	   ToolBar.SetPaneStyle(ToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	   ToolBar.SetOwner(this);

      // All commands will be routed via this control , not via the parent frame:
	   ToolBar.SetRouteCommandsViaFrame(FALSE);

      return 0;
   }

   /// <summary>Initialise control</summary>
   void LanguageEditView::OnInitialUpdate()
   {
      CFormView::OnInitialUpdate();

      // Listen for string SelectionChanged
      fnStringSelectionChanged = GetStringView()->SelectionChanged.Register(this, &LanguageEditView::onStringSelectionChanged);
   }

   /// <summary>Populates the text of the currently selected string</summary>
   void LanguageEditView::onStringSelectionChanged()
   {
      // Clear text
      RichEdit.SetWindowTextW(L"");

      try 
      {
         // Re-populate
         if (LanguageString* str = GetStringView()->GetSelectedString())
            RichEdit.SetWindowTextW(str->Text.c_str());
      }
      catch (ExceptionBase& e)
      { Console << e; }
   }
   
   /// <summary>Adjusts layout</summary>
   /// <param name="nType">Type of the resize</param>
   /// <param name="cx">The new width</param>
   /// <param name="cy">The new height</param>
   void LanguageEditView::OnSize(UINT nType, int cx, int cy)
   {
      CFormView::OnSize(nType, cx, cy);
      AdjustLayout();
   }

   // ------------------------------- PRIVATE METHODS ------------------------------

   
NAMESPACE_END2(GUI,Views)


