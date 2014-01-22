
// MainFrm.h : interface of the MainWnd class
//

#pragma once
#include "ProjectWnd.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "GameDataWnd.h"
#include "GameDataWorker.h"
#include "Logic/Event.h"

/// <summary>User interface</summary>
NAMESPACE_BEGIN(GUI)

   // ------------------------ CLASSES ------------------------

   /// <summary>Main window</summary>
   class MainWnd : public CMDIFrameWndEx
   {
      // ------------------------ TYPES --------------------------

      // --------------------- CONSTRUCTION ----------------------
	   
   public:
	   MainWnd();
      virtual ~MainWnd();

      // ------------------------ STATIC -------------------------
   public:
      DECLARE_DYNAMIC(MainWnd)
   protected:
      DECLARE_MESSAGE_MAP()

   public:
      static FeedbackEvent    GameDataFeedback;

      // --------------------- PROPERTIES ------------------------
	  
      // ---------------------- ACCESSORS ------------------------			
   public:
   #ifdef _DEBUG
	   virtual void AssertValid() const;
	   virtual void Dump(CDumpContext& dc) const;
   #endif 

      // ----------------------- MUTATORS ------------------------
   
   public:
      virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);
	   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   protected:
	   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	   afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
      afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
      afx_msg void OnViewCustomize();
      afx_msg void OnWindowManager();
      afx_msg LRESULT OnWorkerFeedback(WPARAM wParam, LPARAM lParam);

      // -------------------- REPRESENTATION ---------------------

   protected: 
	   CMFCMenuBar       m_wndMenuBar;
	   CMFCToolBar       m_wndToolBar;
	   CMFCStatusBar     m_wndStatusBar;
	   CMFCToolBarImages m_UserImages;
	   CProjectWnd       m_wndProject;
	   COutputWnd        m_wndOutput;
      CGameDataWnd      m_wndGameData;
	   CPropertiesWnd    m_wndProperties;

      GameDataWorker    GameDataThread;
   };



NAMESPACE_END(GUI)



