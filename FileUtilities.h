#pragma once
#include <filesystem>
#include <iostream>

struct FileUtilities
{
    static bool CopyAFile(const char* SRC, const char* DEST , const char* name);
    static bool FileExist(const char* SRC);
    static std::string GetNameOfDir(const char* SRC);
};

