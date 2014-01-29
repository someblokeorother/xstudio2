#pragma once
#include "Common.h"
#include "XmlReader.h"
#include "ScriptFile.h"

namespace Logic
{
   namespace IO
   {
      
      /// <summary>Reader for MSCI scripts</summary>
      class ScriptFileReader : private XmlReader
      {
      private:
         /// <summary>Base class for MSCI script command readers</summary>
         class ScriptCommandReader
         {
            // --------------------- CONSTRUCTION ----------------------
         protected:
            ScriptCommandReader(ScriptFileReader& r, ScriptFile& s, XmlNodePtr& cmd) : Reader(r), Script(s), Command(cmd), NodeIndex(0) {}
         
            // ----------------------- MUTATORS ------------------------

         public:
            virtual ScriptCommand  ReadCommand() PURE;

         protected:
            wstring         ReadStringNode() { return Reader.ReadString(ReadNode());   }
            int             ReadIntNode()    { return Reader.ReadInt(ReadNode());      }
            ParameterValue  ReadValueNode()  { return Reader.ReadValue(ReadNode());    }
            DataType        ReadTypeNode()   { return (DataType)LOWORD(ReadIntNode()); }

            ScriptParameter ReadParameter(ParameterSyntax s) { 
               DataType dt = ReadTypeNode();
               return ScriptParameter(s, dt, ReadValueNode()); 
            }

         private:
            XmlNodePtr     ReadNode()       { return Command->childNodes->item[NodeIndex++]; }

            // -------------------- REPRESENTATION ---------------------
         protected:
            ScriptFileReader&         Reader;
            ScriptFile&           Script;
            XmlNodePtr&           Command;

         private:
            int                   NodeIndex;
         };


         /// <summary>Reads typical auxiliary commands</summary>
         class AuxiliaryCommandReader : public ScriptCommandReader
         {
            // --------------------- CONSTRUCTION ----------------------
         public:
            AuxiliaryCommandReader(ScriptFileReader& r, ScriptFile& s, XmlNodePtr& cmd) : ScriptCommandReader(r, s, cmd) {}

            // ----------------------- MUTATORS ------------------------

            ScriptCommand  ReadCommand();
         };


         /// <summary>Reads command comments</summary>
         class CommentedCommandReader : public ScriptCommandReader
         {
            // --------------------- CONSTRUCTION ----------------------
         public:
            CommentedCommandReader(ScriptFileReader& r, ScriptFile& s, XmlNodePtr& cmd) : ScriptCommandReader(r, s, cmd) {}

            // ----------------------- MUTATORS ------------------------

            ScriptCommand  ReadCommand();
         };


         /// <summary>Reads variable argument script calls</summary>
         class ScriptCallCommandReader : public ScriptCommandReader
         {
            // --------------------- CONSTRUCTION ----------------------
         public:
            ScriptCallCommandReader(ScriptFileReader& r, ScriptFile& s, XmlNodePtr& cmd) : ScriptCommandReader(r, s, cmd) {}

            // ----------------------- MUTATORS ------------------------

            ScriptCommand  ReadCommand();
         };


         /// <summary>Reads expression commands</summary>
         class ExpressionCommandReader : public ScriptCommandReader
         {
            // --------------------- CONSTRUCTION ----------------------
         public:
            ExpressionCommandReader(ScriptFileReader& r, ScriptFile& s, XmlNodePtr& cmd) : ScriptCommandReader(r, s, cmd) {}

            // ----------------------- MUTATORS ------------------------

            ScriptCommand  ReadCommand();
         };


         /// <summary>Reads typical standard commands</summary>
         class StandardCommandReader : public ScriptCommandReader
         {
            // --------------------- CONSTRUCTION ----------------------
         public:
            StandardCommandReader(ScriptFileReader& r, ScriptFile& s, XmlNodePtr& cmd) : ScriptCommandReader(r, s, cmd) {}

            // ----------------------- MUTATORS ------------------------

            ScriptCommand  ReadCommand();
         };



      private:
         /// <summary>Unique command reader pointer</summary>
         typedef unique_ptr<ScriptCommandReader>  ReaderPtr;

         // --------------------- CONSTRUCTION ----------------------

      public:
         ScriptFileReader(StreamPtr in);
         virtual ~ScriptFileReader();

         // ------------------------ STATIC -------------------------

         // --------------------- PROPERTIES ------------------------
			
		   // ---------------------- ACCESSORS ------------------------
			
		   // ----------------------- MUTATORS ------------------------

      public:
         ScriptFile     ReadFile();

      private:
         ReaderPtr      GetCommandReader(ScriptFile& script, CommandType type, XmlNodePtr& cmdBranch);

         int            ReadArray(XmlNodePtr& node);
         GameVersion    ReadEngineVersion(XmlNodePtr& node);
         int            ReadInt(XmlNodePtr& node);
         wstring        ReadString(XmlNodePtr& node);
         ParameterValue ReadValue(XmlNodePtr& node);

         void  ReadCommands(ScriptFile&  script, XmlNodePtr& stdBranch, XmlNodePtr& auxBranch);
         void  ReadVariables(ScriptFile&  script, XmlNodePtr& varBranch, XmlNodePtr& argBranch);

		   // -------------------- REPRESENTATION ---------------------

      private:
      };

      
   }
}

using namespace Logic::IO;