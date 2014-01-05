#pragma once
#include "Stream.h"

namespace Library
{
   namespace IO
   {
      class FileStream : public Stream
      {
      public:
         FileStream(Path path, FileMode mode, FileAccess access, FileShare share);
         ~FileStream();
         
         bool  CanRead()   { return Access == FileAccess::Read || Access == FileAccess::ReadWrite; }
         bool  CanSeek()   { return true; }
         bool  CanWrite()  { return Access == FileAccess::Write || Access == FileAccess::ReadWrite; }

         DWORD GetLength();
         DWORD GetPosition();

         void  Close();
         void  Flush();
         void  Seek(DWORD  offset, SeekOrigin  mode);
         void  SetLength(DWORD  length);

         DWORD Read(BYTE* buffer, DWORD length);
         DWORD Write(BYTE* buffer, DWORD length);
      
      private:
         Path       FullPath;
         FileMode   Mode;
         FileAccess Access;
         FileShare  Share;
         HANDLE     Handle;
      };

   }
}