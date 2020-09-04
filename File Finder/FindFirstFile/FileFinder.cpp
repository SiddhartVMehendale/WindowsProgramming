#include<windows.h>
#include<tchar.h>
#include<stdio.h>

void _tmain(int argc, TCHAR *argv[])
{
    // Loacl variable
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    TCHAR szFile[] = TEXT("D:\\Projects\\Test\\File Finder\\FindNextFile\\test.txt");
    

    // To find the file and directory
    _tprintf(TEXT("\n The Target file is in %s \n"), szFile);
    hFind = FindFirstFile(szFile, &FindFileData);

    // To check if the handle FindFirstFile has failed
    if(hFind == INVALID_HANDLE_VALUE)
    {
        _tprintf(TEXT(" Find First File Failed  (%d)\n"), GetLastError());
        return;
    }
    else
    {
        _tprintf(TEXT(" The first file found is %s \n"), FindFileData.cFileName);
        FindClose(hFind);
    }
}