#include<windows.h>
#include<stdio.h>

#define THREADCOUNT 2

HANDLE ghMutex;
DWORD WINAPI WriteToDatabase(LPVOID);

int main()
{
	HANDLE aThread[THREADCOUNT];
	DWORD ThreadID;
	int i;

	// create mutex with no initial owner
	ghMutex = CreateMutex(
		NULL,					// Default security attribute
		FALSE,					// initially not owned
		NULL);				// unamed mutex

	if (ghMutex == NULL)
	{
		printf("\n Create Mutex error: %d\n", GetLastError());
		return 1;
	}

	// Create worker threads
	for (i = 0; i < THREADCOUNT; i++)
	{
		aThread[i] = CreateThread(
									NULL,  // default security attributes
									0,	   // default stack size
									(LPTHREAD_START_ROUTINE)WriteToDatabase,
									NULL,    //No thread function arguments
									0,		 //Default creationg flags
									&ThreadID); //Recive thread Identfier

		if (aThread[i] == NULL)
		{
			printf("CreateThread error: %d\n",GetLastError());
			return 1;
		}
	}
	// wait for all the threads to terminate

	WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

	// close thread and mutex handles
	for (i = 0; i < THREADCOUNT; i++)
	{
		CloseHandle(aThread[i]);
	}
	CloseHandle(ghMutex);

	return 0;
}

DWORD WINAPI WriteToDatabase(LPVOID lpParam)
{
	UNREFERENCED_PARAMETER(lpParam);

	DWORD dwCount = 0, dwWaitResult;

	// Request ownership of mutex

	while (dwCount < 20)
	{
		dwWaitResult = WaitForSingleObject(ghMutex,   // handle to mutex  
											INFINITE); // no time-out interval

		switch (dwWaitResult)
		{
		case WAIT_OBJECT_0:
			__try{
				//TODO: Write to database
				printf("Thread %d writing to database...\n",GetCurrentThreadId());
				dwCount++;
			}
			__finally {
				// Release ownership of the mutex object
				if (!ReleaseMutex(ghMutex))
				{
					// handle error
				}
			}
			break;

			// The thread got ownership of an abandonded mutex 
			// The database is in a indeterminante state
		case WAIT_ABANDONED:
			return FALSE;
		}
	}
	return TRUE;
}
