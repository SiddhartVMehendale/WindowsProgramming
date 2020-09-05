#include<windows.h>
#include<tchar.h>
#include<stdio.h>
#include<strsafe.h>

void _tmain(int argc, TCHAR* argv[])
{
    WIN32_FIND_DATA FileData;
    HANDLE hSearch;
    DWORD dwAttrs;
    TCHAR szNewPath[MAX_PATH];

    BOOL fFinished = FALSE;
    TCHAR *szDir = TEXT("D:\\Projects\\Test\\File Finder\\Directory\\DirNew");

    // Create a new directory

    if(!CreateDirectory(szDir, NULL))
    {
        printf("CreateDirectory failed (%d)\n", GetLastError());
        return;
    }

    // Start Searching for the files in the current directory 
    hSearch = FindFirstFile(TEXT("D:\\Projects\\Test\\File Finder\\Directory\\*.txt"), &FileData);
    if(hSearch == INVALID_HANDLE_VALUE)
    {
        printf("No text files found\n");
        return;
    }

    // Copy each file to the new directory and change it to read only
    while(!fFinished)
    {
        StringCchPrintf(szNewPath, sizeof(szNewPath)/ sizeof(szNewPath[0]), TEXT("%s\\%s"), szDir, FileData.cFileName);

        if(CopyFile(FileData.cFileName, szNewPath, FALSE))
        {
            dwAttrs = GetFileAttributes(FileData.cFileName);

            if(dwAttrs == INVALID_FILE_ATTRIBUTES)
            {
                return;
            }

            if(!(dwAttrs & FILE_ATTRIBUTE_READONLY))
            {
                SetFileAttributes(szNewPath, dwAttrs | FILE_ATTRIBUTE_READONLY);
            }
        }    
        else
        {
            printf("Could not copy file. \n");
            return;
        }
        
        if(!FindNextFile(hSearch, &FileData))
        {
            if(GetLastError() == ERROR_NO_MORE_FILES)
            {
                _tprintf(TEXT("Copied *.text to %s\n"), szDir);
                fFinished = TRUE;
            }
            else
            {
                printf("Could not find next file \n");
            }    
        }
    }
    // Close the search handle 
    FindClose(hSearch);
}