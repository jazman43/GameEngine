#pragma once
#include "DragonWin.h"

#include <string>


class BaseWindow
{
public:
    BaseWindow(int width, int height, const char* title);
    virtual ~BaseWindow();

    // Methods to be overridden by derived classes
    virtual void OnMessage(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual void Update();

    virtual void Draw();

protected:
    int width;
    int height;

    HWND handleWin;

    char* title;

private:
    class  WindowClass
    {
    public:
        static const char* GetName() noexcept;
        static HINSTANCE GetInstance() noexcept;

    private:
        WindowClass() noexcept;
        ~WindowClass();

        WindowClass& operator=(const WindowClass&) = delete;

        static constexpr const char* wndClassName = "Dragon Engine";
        static WindowClass wndClass;
        HINSTANCE hInst;
    };


    static LRESULT WINAPI HandleMsgSetup(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    static LRESULT WINAPI HandleMsgThunk(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    LRESULT HandleMsg(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
};



