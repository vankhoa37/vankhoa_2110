// Code (kết nối tới 1 phần mềm AI ) tham khảo từ FamTrinli , đã chỉnh sửa để phù hợp với game
#ifndef CONNECTOR1_H
#define CONNECTOR1_H

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

STARTUPINFO startupInfo = {0};
SECURITY_ATTRIBUTES securityAttributes = {0};
PROCESS_INFORMATION processInfo = {0};
HANDLE inputWritePipe, inputReadPipe, outputWritePipe, outputReadPipe;
BYTE buffer[2048];
DWORD bytesWritten, exitCode, bytesRead, availableBytes;

void ConnectToEngine(char* enginePath)
{
    inputWritePipe = inputReadPipe = outputWritePipe = outputReadPipe = NULL;
    securityAttributes.nLength = sizeof(securityAttributes);
    securityAttributes.bInheritHandle = TRUE;
    securityAttributes.lpSecurityDescriptor = NULL;

    CreatePipe(&outputReadPipe, &outputWritePipe, &securityAttributes, 0);
    CreatePipe(&inputReadPipe, &inputWritePipe, &securityAttributes, 0);

    startupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    startupInfo.wShowWindow = SW_HIDE;
    startupInfo.hStdInput = inputReadPipe;
    startupInfo.hStdOutput = outputWritePipe;
    startupInfo.hStdError = outputWritePipe;

    CreateProcess(NULL, enginePath, NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInfo);
}

std::string getNextMove(std::string currentPosition)
{
    //std::cout << "Connected successfully." << std::endl;
    std::string result;
    currentPosition = "position startpos moves " + currentPosition + "\ngo\n";

    WriteFile(inputWritePipe, currentPosition.c_str(), currentPosition.length(), &bytesWritten, NULL);
    Sleep(500);

    PeekNamedPipe(outputReadPipe, buffer, sizeof(buffer), &bytesRead, &availableBytes, NULL);
    do
    {
        ZeroMemory(buffer, sizeof(buffer));
        if (!ReadFile(outputReadPipe, buffer, sizeof(buffer), &bytesRead, NULL) || !bytesRead)
            break;
        buffer[bytesRead] = 0;
        result += (char*)buffer;
    } while (bytesRead >= sizeof(buffer));

    int index = result.find("bestmove");
    //std::cout << "Stockfish: " << result.substr(index + 9, 5) << std::endl;
    if (index >= 0)
        return result.substr(index + 9, 4);

    return "error";
}
std::string getNextMovePromote(std::string currentPosition)
{
    //std::cout << "Connected successfully." << std::endl;
    std::string result;
    currentPosition = "position startpos moves " + currentPosition + "\ngo\n";

    WriteFile(inputWritePipe, currentPosition.c_str(), currentPosition.length(), &bytesWritten, NULL);
    Sleep(500);

    PeekNamedPipe(outputReadPipe, buffer, sizeof(buffer), &bytesRead, &availableBytes, NULL);
    do
    {
        ZeroMemory(buffer, sizeof(buffer));
        if (!ReadFile(outputReadPipe, buffer, sizeof(buffer), &bytesRead, NULL) || !bytesRead)
            break;
        buffer[bytesRead] = 0;
        result += (char*)buffer;
    } while (bytesRead >= sizeof(buffer));

    int index = result.find("bestmove");
   // std::cout << "Stockfish: " << result.substr(index + 9, 5) << std::endl;
    if (index >= 0)
        return result.substr(index + 9, 5);

    return "error";
}

void CloseConnection()
{
    WriteFile(inputWritePipe, "quit\n", 5, &bytesWritten, NULL);
    if (inputWritePipe != NULL) CloseHandle(inputWritePipe);
    if (inputReadPipe != NULL) CloseHandle(inputReadPipe);
    if (outputWritePipe != NULL) CloseHandle(outputWritePipe);
    if (outputReadPipe != NULL) CloseHandle(outputReadPipe);
    if (processInfo.hProcess != NULL) CloseHandle(processInfo.hProcess);
    if (processInfo.hThread != NULL) CloseHandle(processInfo.hThread);
}

#endif  CONNECTOR1_H

