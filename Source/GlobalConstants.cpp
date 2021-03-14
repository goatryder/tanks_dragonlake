#include <windows.h>

#include "GlobalConstants.h"


EXTERN_C IMAGE_DOS_HEADER __ImageBase;

std::string GetRootPath()
{
    char Path[FILENAME_MAX];
    GetModuleFileName((HINSTANCE)&__ImageBase, Path, sizeof(Path));

    std::string RootPath(Path);
    
    RootPath.resize(RootPath.size() - std::strlen(EXE_NAME));

    return RootPath;
}


std::string GetResourcePath(const char* RelativePath)
{
    std::string ResourcePath = GetRootPath() + RelativePath;
    
    return ResourcePath;
}