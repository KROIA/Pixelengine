#ifndef FILEBROWSER_H
#define FILEBROWSER_H
#include <windows.h>
#include <Commdlg.h>
#include <string>
#include <codecvt>
#include <locale>



namespace FileBrowser {




    std::string getFile(const std::string &startDirectory, const std::string &filter = "*.*");
};
#endif // FILEBROWSER_H
