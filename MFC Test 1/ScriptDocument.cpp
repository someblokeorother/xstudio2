
// MFC Test 1Doc.cpp : implementation of the ScriptDocument class
//

#include "stdafx.h"
#include "ScriptDocument.h"
#include <propkey.h>
#include "Logic/FileStream.h"
#include "Logic/GZipStream.h"
#include "Logic/XFileSystem.h"
#include "Logic/LegacySyntaxReader.h"
#include "Logic/SyntaxLibrary.h"
#include "Logic/ScriptFileReader.h"
#include "Logic/StringLibrary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// <summary>User interface</summary>
NAMESPACE_BEGIN(GUI)

   // --------------------------------- APP WIZARD ---------------------------------
  
   IMPLEMENT_DYNCREATE(ScriptDocument, CDocument)
   IMPLEMENT_DYNAMIC(ScriptDocTemplate, CMultiDocTemplate)

   BEGIN_MESSAGE_MAP(ScriptDocument, CDocument)
   END_MESSAGE_MAP()

   // -------------------------------- CONSTRUCTION --------------------------------

   ScriptDocument::ScriptDocument()
   {
	   // TODO: add one-time construction code here

   }

   ScriptDocument::~ScriptDocument()
   {
   }

   // ------------------------------- STATIC METHODS -------------------------------

   // ------------------------------- PUBLIC METHODS -------------------------------

   CDocTemplate::Confidence ScriptDocTemplate::MatchDocType(LPCTSTR lpszPathName, CDocument*& rpDocMatch)
   {
      rpDocMatch = NULL;
      return maybeAttemptNative;
   }

   #ifdef _DEBUG
   void ScriptDocument::AssertValid() const
   {
	   CDocument::AssertValid();
   }

   void ScriptDocument::Dump(CDumpContext& dc) const
   {
	   CDocument::Dump(dc);
   }
   #endif //_DEBUG

   
   BOOL ScriptDocument::OnNewDocument()
   {
	   if (!CDocument::OnNewDocument())
		   return FALSE;

	   // TODO: add reinitialization code here
	   // (SDI documents will reuse this document)

	   return TRUE;
   }


   BOOL ScriptDocument::OnOpenDocument(LPCTSTR lpszPathName)
   {
      /*if (!CDocument::OnOpenDocument(lpszPathName))
         return FALSE;*/
      
      try
      {
         // Parse script
         Console << ENDL << Colour::Cyan << L"Parsing MSCI script: " << lpszPathName << ENDL;

         StreamPtr fs2( new FileStream(lpszPathName, FileMode::OpenExisting, FileAccess::Read) );
         Script = ScriptFileReader(fs2).ReadFile();

         Console << Colour::Green << L"Script loaded successfully" << ENDL;
      
         //UpdateAllViews(NULL);
         return TRUE;
      }
      catch (ExceptionBase&  e)
      {
         CString sz;
         sz.Format(L"Unable to load '%s' : %s\n\n" L"Source: %s()", lpszPathName, e.Message.c_str(), e.Source.c_str());
         AfxMessageBox(sz);
         return FALSE;
      }
   }



   void ScriptDocument::Serialize(CArchive& ar)
   {
	   if (ar.IsStoring())
	   {
		   // TODO: add storing code here
	   }
	   else
	   {
		   // TODO: add loading code here
	   }
   }

   // ------------------------------ PROTECTED METHODS -----------------------------

   // ------------------------------- PRIVATE METHODS ------------------------------


NAMESPACE_END(GUI)

