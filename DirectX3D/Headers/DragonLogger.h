#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>

#include "BaseWindow.h"

#define MAX_LOG_MESSAGES 50

class TerminalWindow : public BaseWindow
{
public:
	TerminalWindow(int width, int height, const char* title);


	virtual void OnMessage(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam) override;
	virtual ~TerminalWindow() override;

	virtual void Update() override;
	virtual void Draw() override;

	void AddLogMessage(const std::string& message, int r, int g, int b);

private:

	std::vector<std::string> logMessages;

	int logLevel;

	int _r, _g, _b;
};

class Logger
{
public:
	enum class LogLevel
	{
		Message,
		Warning,
		Error
	};
	

	//singleton
	static Logger& Instance()
	{
		static Logger instance;
		return instance;
	}


	void Log(LogLevel level, const std::string& message);

	void SetLogFile(const std::string& filePath);

	void SetTerminalWindow(TerminalWindow* term);

private:

	Logger();

	~Logger();

	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	std::ofstream logFile;


	TerminalWindow* term;
};


//Macros

#define ENGINE_LOG_MESSAGE(message) Logger::Instance().Log(LogLevel::Message, std::string("[Engine Message Log] ") + message)
#define ENGINE_LOG_WARNING(message) Logger::Instance().Log(LogLevel::Warning, std::string("[Engine Warning Log] ") + message)
#define ENGINE_LOG_ERROR(message) Logger::Instance().Log(LogLevel::Error, std::string("[Engine Error Log] ") + message)

#define LOG_MESSAGE(message) Logger::Instance().Log(LogLevel::Message, std::string("[Message Log] ") + message)
#define LOG_WARNING(message) Logger::Instance().Log(LogLevel::Warning, std::string("[Warning Log] ") + message)
#define LOG_ERROR(message) Logger::Instance().Log(LogLevel::Error, std::string("[Error Log!] ") + message)



