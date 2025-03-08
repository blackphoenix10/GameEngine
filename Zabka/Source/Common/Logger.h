#pragma once

#include <string>

class ZABKA_API Logger {

	//Getters and setters for singleton static class
private:
	static Logger* inst;
public:
	static Logger* Instance() { return inst; }

	//Constructor
public:
	Logger();
	~Logger();

	static VOID PrintLog(const WCHAR* fmt, ...);

	static std::wstring LogDirectory();

	static std::wstring LogFile();

	static VOID PrintDebugSeperator();

	static BOOL IsMTailRunning();

	static VOID StartMTail();

};