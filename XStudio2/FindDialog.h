#pragma once
#include "afxwin.h"

/// <summary>User interface windows</summary>
NAMESPACE_BEGIN2(GUI,Window)
   
      /// <summary>Find text dialog</summary>
      class FindDialog : public CDialogEx
      {
         // ------------------------ TYPES --------------------------
      public:
         enum { IDD = IDD_FINDREPLACE };

         // --------------------- CONSTRUCTION ----------------------
      public:
	      FindDialog(CWnd* pParent = NULL);   // standard constructor
	      virtual ~FindDialog();

         // ------------------------ STATIC -------------------------

         DECLARE_DYNAMIC(FindDialog)
         DECLARE_MESSAGE_MAP()

         // --------------------- PROPERTIES ------------------------
			
         // ---------------------- ACCESSORS ------------------------			

         // ----------------------- MUTATORS ------------------------
      protected:
	      virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
         
         afx_msg void OnFind();
         afx_msg void OnReplace();
         afx_msg void OnFindAll();
         afx_msg void OnReplaceAll();
         afx_msg void OnOptions();

         // -------------------- REPRESENTATION ---------------------
      
      public:
         BOOL UseRegEx;
         BOOL MatchCase;
         BOOL MatchWholeWord;
         CButton FindButton;
         CButton ReplaceButton;
         CButton FindAllButton;
         CButton ReplaceAllButton;
         CComboBox FindCombo;
         CComboBox ReplaceCombo;
         CComboBox TargetCombo;
      };

/// <summary>User interface windows</summary>
NAMESPACE_END2(GUI,Window)
