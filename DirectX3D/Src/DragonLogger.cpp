#include "../Headers/DragonLogger.h"





void Logger::LogMessage(const std::string& message)
{
	std::stringstream logStream;


	std::time_t currentTime = std::time(nullptr);
	tm timeInfo;
	localtime_s(&timeInfo, &currentTime);

	char timeBuffer[20];
	strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

	int r, g, b;

	
	logStream << "[MESSSAGE]";
	r = 255;
	g = 255;
	b = 255;
	logStream << " [ " << timeBuffer << " ] " << message << std::endl;

	std::cout << logStream.str();

	if (logFile.is_open()) logFile << logStream.str();

	if (term != nullptr) { term->AddLogMessage(logStream.str(), r, g, b); }
	
	
}

void Logger::LogWarning(const std::string& message)
{
	std::stringstream logStream;


	std::time_t currentTime = std::time(nullptr);
	tm timeInfo;
	localtime_s(&timeInfo, &currentTime);

	char timeBuffer[20];
	strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

	int r, g, b;
	
	logStream << "[WARNING]";
	r = 255;
	g = 255;
	b = 50;
	logStream << " [ " << timeBuffer << " ] " << message << std::endl;

	std::cout << logStream.str();

	if (logFile.is_open()) logFile << logStream.str();

	if (term != nullptr) { term->AddLogMessage(logStream.str(), r, g, b); }
	
	
}

void Logger::LogError( const std::string& message)
{
	std::stringstream logStream;


	std::time_t currentTime = std::time(nullptr);
	tm timeInfo;
	localtime_s(&timeInfo, &currentTime);

	char timeBuffer[20];
	strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &timeInfo);

	int r, g, b;
	
	logStream << "[ERROR]";
	r = 255;
	g = 5;
	b = 5;
	logStream << " [ " << timeBuffer << " ] " << message << std::endl;
	
	std::cout << logStream.str();
	
	if (logFile.is_open()) logFile << logStream.str();
	
	if (term != nullptr) { term->AddLogMessage(logStream.str(), r, g, b); }
	
}

void Logger::SetLogFile(const std::string& filePath)
{
	logFile.open(filePath, std::ios::app);
}

void Logger::SetTerminalWindow(TerminalWindow* term)
{
	this->term = term;
}

Logger::Logger()
{
	logFile.open("log.txt", std::ios::app);
}

Logger::~Logger()
{
	if (logFile.is_open()) logFile.close();
}



//window

TerminalWindow::TerminalWindow(int width, int height, const char* title)
	: BaseWindow(width, height, title)
{
}

void TerminalWindow::OnMessage(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam)
{
	BaseWindow::OnMessage(handleWin, msg, wParam, lParam);
}

TerminalWindow::~TerminalWindow()
{
}

void TerminalWindow::Update()
{
	BaseWindow::Update();

	Draw();
}

void TerminalWindow::Draw()
{
	BaseWindow::Draw();
	// Get the device context for drawing
	HDC hdc = GetDC(handleWin);

	// Set up the font and color for drawing
	HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
	HFONT hOldFont = static_cast<HFONT>(SelectObject(hdc, hFont));


	//SetTextColor(hdc, RGB(_r, _g, _b));
	SetBkColor(hdc, RGB(0, 0, 0));

	// Clear the window
	RECT rect;
	GetClientRect(handleWin, &rect);
	FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	// Draw log messages
	for (size_t i = 0; i < logMessages.size(); ++i) {
		SetTextColor(hdc, RGB(logColors[i].r, logColors[i].g, logColors[i].b));
		TextOutA(hdc, 10, 10 + static_cast<int>(i) * 20, logMessages[i].c_str(), logMessages[i].size());
	}

	// Clean up
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
	ReleaseDC(handleWin, hdc);
}

void TerminalWindow::AddLogMessage(const std::string& message,int r, int g, int b)
{
	logMessages.push_back(message);
	logColors.push_back({r,g,b});
	

	if (logMessages.size() > MAX_LOG_MESSAGES)
	{
		logMessages.erase(logMessages.begin());
		logColors.erase(logColors.begin());
	}


	InvalidateRect(handleWin, nullptr, TRUE);
}
