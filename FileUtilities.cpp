#include "FileUtilities.h"

bool FileUtilities::CopyAFile(const char* SRC, const char* DEST, const char* name)
{
    std::filesystem::path sourceFile = SRC;
    std::filesystem::path targetParent = DEST;
    auto target = targetParent / name;
    std::filesystem::copy(sourceFile, target, std::filesystem::copy_options::overwrite_existing);
    return true;
}

bool FileUtilities::FileExist(const char* SRC) {
    std::filesystem::path sourceFile = SRC;
    return std::filesystem::exists(sourceFile);
}

std::string GetNameOfDir(const char* SRC) {
    std::filesystem::path sourceFile = SRC;
    return sourceFile.filename().string();
}