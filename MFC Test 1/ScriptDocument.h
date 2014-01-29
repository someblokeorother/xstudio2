// MFC Test 1Doc.h : interface of the ScriptDocument class
//
#pragma once
#include "Logic/ScriptFile.h"

/// <summary>User interface</summary>
NAMESPACE_BEGIN(GUI)

   /// <summary>MSCI Script document template</summary>
   class ScriptDocTemplate : public CMultiDocTemplate
   {
      // --------------------- CONSTRUCTION ----------------------
   public:
      ScriptDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
         : CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
      {}

      // ------------------------ STATIC -------------------------

      DECLARE_DYNAMIC(ScriptDocTemplate)

      // ---------------------- ACCESSORS ------------------------	
      virtual Confidence MatchDocType(LPCTSTR lpszPathName, CDocument*& rpDocMatch);
   };

   /// <summary>MSCI Script document</summary>
   class ScriptDocument : public CDocument
   {
      // ------------------------ TYPES --------------------------
   private:
	  
      // --------------------- CONSTRUCTION ----------------------

   protected: // create from serialization only
	   ScriptDocument();
   public:
	   virtual ~ScriptDocument();

      // ------------------------ STATIC -------------------------

   protected:
      DECLARE_DYNCREATE(ScriptDocument)
	   DECLARE_MESSAGE_MAP()

      // --------------------- PROPERTIES ------------------------
			
      // ---------------------- ACCESSORS ------------------------			

      // ----------------------- MUTATORS ------------------------
   public:
   #ifdef _DEBUG
	   virtual void AssertValid() const;
	   virtual void Dump(CDumpContext& dc) const;
   #endif

	   virtual BOOL OnNewDocument();
      virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	   virtual void Serialize(CArchive& ar);
   
      // -------------------- REPRESENTATION ---------------------
   public:
      ScriptFile  Script;

   

   };


NAMESPACE_END(GUI)
