#include "stdafx.h"
#include "ScriptCommand.h"
#include "ScriptFile.h"
#include "CommandLexer.h"
#include "SyntaxLibrary.h"
#include <algorithm>

namespace Logic
{
   namespace Scripts
   {
      /// <summary>Gets BranchLogic string</summary>
      /// <param name="l">logic</param>
      /// <returns></returns>
      const WCHAR* GetString(BranchLogic l)
      {
         static const WCHAR* str[] = {L"None", L"NOP", L"If", L"While", L"SkipIf", L"Else", L"ElseIf", L"End", L"Break", L"Continue"};
         return str[l];
      }

      // -------------------------------- CONSTRUCTION --------------------------------

      ScriptCommand::ScriptCommand()
         : Syntax(SyntaxLib.Unknown), RefIndex(0)
      {
      }

      ScriptCommand::ScriptCommand(const wstring& text, const CommandSyntax& syntax, const TokenArray& params)
         : Syntax(syntax), RefIndex(0), Text(text)
      {
      }

      /// <summary>Create a standard command from syntax and parameters (ordered by display index)</summary>
      /// <param name="syntax">The syntax.</param>
      /// <param name="params">The parameters, if any (sorted by display index)</param>
      ScriptCommand::ScriptCommand(const CommandSyntax& syntax, ParameterArray& params)
         : Syntax(syntax), RefIndex(0), Parameters(params) 
      {
      }

      /// <summary>Create an auxiliary command from syntax and parameters (ordered by display index)</summary>
      /// <param name="syntax">The command syntax.</param>
      /// <param name="ref">The index of the associated standard command</param>
      /// <param name="params">The parameters, if any (sorted by display index)</param>
      ScriptCommand::ScriptCommand(const CommandSyntax& syntax, UINT  ref, ParameterArray& params)
         : Syntax(syntax), RefIndex(ref), Parameters(params) 
      {
      }
      
      ScriptCommand::~ScriptCommand()
      {
      }

      // ------------------------------- STATIC METHODS -------------------------------

      // ------------------------------- PUBLIC METHODS -------------------------------

      /// <summary>Identify the type of branching conditional used (if any)</summary>
      /// <returns></returns>
      BranchLogic  ScriptCommand::GetLogic() const
      {
         switch (Syntax.ID)
         {
         case CMD_END:      return BranchLogic::End;
         case CMD_ELSE:     return BranchLogic::Else;
         case CMD_BREAK:    return BranchLogic::Break;
         case CMD_CONTINUE: return BranchLogic::Continue;

         case CMD_COMMAND_COMMENT:
         case CMD_COMMENT: 
         case CMD_NOP:      return BranchLogic::NOP;
         
         default:
            // Find Return parameter, if any
            auto it = find_if(Parameters.begin(), Parameters.end(), [](const ScriptParameter& p) { return p.Syntax.IsRetVar(); });
            
            // RetVar/Discard
            if (it == Parameters.end() || it->Value.Type == ValueType::String)
               return BranchLogic::None;

            // RetVar/Discard
            ReturnValue retVar(it->Value.Int);
            if (retVar.ReturnType == ReturnType::ASSIGNMENT || retVar.ReturnType == ReturnType::DISCARD)
               return BranchLogic::None;
               
            // Conditional
            switch (retVar.Conditional)
            {
            case Conditional::IF:      
            case Conditional::IF_NOT:        return BranchLogic::If;
            case Conditional::WHILE:         
            case Conditional::WHILE_NOT:     return BranchLogic::While;

            case Conditional::ELSE_IF:  
            case Conditional::ELSE_IF_NOT:   return BranchLogic::ElseIf;

            case Conditional::SKIP_IF:  
            case Conditional::SKIP_IF_NOT:   return BranchLogic::SkipIf;

            default:
               return BranchLogic::None;
            }
         }
      }

      void ScriptCommand::Translate(ScriptFile& f)
      {
         CommandLexer lex(Syntax.Text, false);
         bool         Param = false;

         // Translate parameters
         for (ScriptParameter& p : Parameters)
            p.Translate(f);

         // Format command
         for (const ScriptToken& tok : lex.Tokens)
         {
            if (tok.Type == TokenType::Variable || tok.Type == TokenType::Comment)
            {
               int i = (tok.Text[1]-48);
               Text.append( Parameters[i].Text );
            }
            else
               Text.append(tok.Text);
         }

         // Expressions: Print remaining syntax
         if (Syntax.ID == CMD_EXPRESSION)
            for (UINT i = 2; i < Parameters.size(); ++i)
               Text.append(Parameters[i].Text);
      }

		// ------------------------------ PROTECTED METHODS -----------------------------

		// ------------------------------- PRIVATE METHODS ------------------------------

   }
}
