#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>

void printProcessInfo() {
    DWORD processId = GetCurrentProcessId();
    DWORD parentProcessId = 0;

    // Get the parent process ID
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(snapshot, &processEntry)) {
            do {
                if (processEntry.th32ProcessID == processId) {
                    parentProcessId = processEntry.th32ParentProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &processEntry));
        }
        CloseHandle(snapshot);
    }

    printf("Process ID: %lu\n", processId);
    printf("Parent Process ID: %lu\n", parentProcessId);
}

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Initialize memory for structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Command line for the new process
    char commandLine[] = "C:\\Windows\\System32\\notepad.exe";

    // Create a child process
    if (CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Parent process:\n");
        printProcessInfo();

        // Wait until child process exits.
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Close process and thread handles.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("CreateProcess failed (%lu).\n", GetLastError());
    }

    return 0;
}

