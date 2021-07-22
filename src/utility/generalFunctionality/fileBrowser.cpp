#include "fileBrowser.h"



std::string FileBrowser::getFile(const std::string &startDirectory, const std::string &filter)
{

    std::wstring w_filter = std::wstring(filter.begin(), filter.end());
    w_filter += '\0';
    std::wstring w_startDirectory = std::wstring(startDirectory.begin(),startDirectory.end());
    w_startDirectory += '\0';
    // LPOPENFILENAME means a (long) pointer to an OPENFILENAME,
    // so we'll make an OPENFILENAME and pass the address to the function
    OPENFILENAME ofn;
    // initialize everything to 0
    ZeroMemory(&ofn, sizeof(ofn));

    // assign the size field
    ofn.lStructSize = sizeof(OPENFILENAME);
    // create a buffer for the filename to be placed into
    ofn.lpstrFile = new wchar_t[MAX_PATH];
    ofn.nMaxFile  = MAX_PATH;

    // set the default filename to a null string
    ofn.lpstrFile[0] = '\0';
    ofn.lpstrFilter = w_filter.c_str();
    ofn.nFilterIndex = 1;

    ofn.lpstrFileTitle  = NULL;
    ofn.nMaxFileTitle   = 0;

    wchar_t *w_initalDir = new wchar_t[w_startDirectory.size()];
    for(size_t i=0; i<w_startDirectory.size();i++)
    {
        w_initalDir[i] = w_startDirectory[i];
    }
    ofn.lpstrInitialDir = w_initalDir;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    std::string filePath;
    if (GetOpenFileName(&ofn) == TRUE)
    {
        std::wstring string(ofn.lpstrFile);
        filePath = std::string(string.begin(), string.end());
        //std::cout << "you chose " << str << std::endl;

    }

    delete[] ofn.lpstrFile;
    return filePath;
}
