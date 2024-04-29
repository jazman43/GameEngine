/*


*/


#include "Headers/BaseWindow.h"
#include "Headers/MainWindow.h"

#include "Headers/DragonException.h"
#include "Headers/DragonLogger.h"




int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{

	try {
		BaseWindow base();
		MainWindow mainWindow(500, 300, "Dragon Engine");
		TerminalWindow terminalWindow(500, 100, "Terminal");

		Logger::Instance().SetLogFile("Logs.txt");

		Logger::Instance().SetTerminalWindow(&terminalWindow);

		LOG_MESSAGE("hello world");
		LOG_WARNING("warning this is not functioning");
		LOG_ERROR("Error in main.cpp line 35");
		LOG_MESSAGE("moving left");

		

		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);

			mainWindow.Update();
			terminalWindow.Update();
		}

		if (gResult == -1)
		{
			return -1;
		}

		return msg.wParam;
	}
	catch (const DragonException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standerd Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details Availble", "Unknown EXception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}