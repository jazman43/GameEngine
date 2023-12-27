#pragma once
#include "BaseWindow.h"


class MainWindow : public BaseWindow
{
public:
	MainWindow(int width, int height, const char* title);

	virtual ~MainWindow();
};