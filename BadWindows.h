#pragma once
#include<Windows.h>
#include<stdio.h>

DWORD WINAPI KeyBroad() {
    while (1) {

        if (GetAsyncKeyState(VK_LWIN) & 0x01) {
            keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
            keybd_event(0x52, 0, KEYEVENTF_KEYUP, 0);
        }

        if (GetAsyncKeyState(VK_TAB) & 0x01) {
            keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
            keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
        }

        if (GetAsyncKeyState(VK_MENU) & 0x01) {
            keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
            keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
        }

        HWND hd = FindWindow("TaskManagerWindow", "任务管理器");
        if (hd != NULL)
        {
            SendMessage(hd, WM_CLOSE, 0, 0);
        }
        hd = NULL;
    }
}

//寻找WorkerW-2窗口并隐藏,同时也隐藏WorkerW-1窗口
/*(按照窗口Z序由下到上,由屏幕里向屏幕外,但子窗口是在父窗口之上的)
    * ""WokerW-1
        * ""SHELLDLL_DefView
            * "FolderView"SysListView32
                * ...
    * ""WokerW-2
    * "Program Manager"Program
        * (视频窗口所在的位置)
*/
BOOL CALLBACK EnumWinProc(HWND hwnd, LPARAM lParam)
{
    HWND hDefView = FindWindowEx(hwnd, 0, "SHELLDLL_DefView", 0);
    //通过父窗口句柄与窗口类名来寻找窗口来获取句柄,如果获取成功,将获取的是SHELLDLL_DefView这个窗口的句柄

    //所以说此时的hwnd为WorkW-1的句柄(获取成功时)

    HWND hSysListView32 = FindWindowEx(hDefView, 0, "SysListView32", 0);

    if (hDefView != NULL) {
        HWND hWorkerw = FindWindowEx(0, hwnd, "WorkerW", 0);
        //因为WorkW-1为WorkerW-2的子窗口,可以通过其来获取WokerW-2的句柄

        ShowWindow(hSysListView32, SW_HIDE);
        ShowWindow(hwnd, SW_SHOW);              //隐藏WorkW-1
        ShowWindow(hDefView, SW_SHOW);   
        ShowWindow(hWorkerw, SW_HIDE);      //隐藏WorkW-2
        return FALSE;
    }
    return TRUE;
}


BOOL CALLBACK HideAll(HWND hwnd, LPARAM lParam)
{
    HWND hDeskTop = FindWindowEx(0, 0, "#32769 (桌面)", 0);
    HWND hProgman = FindWindowA( "Progman", 0);
    HWND hVideo = FindWindowA("mpv", 0);
    if (hwnd != NULL&& hwnd!=hProgman&& hwnd != hVideo)
    {

        //SendMessage(hwnd, WM_CLOSE, 0, 0);
        ShowWindow(hwnd, SW_HIDE);
    }

    if (hDeskTop != NULL) 
    {
        return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK ShowAll(HWND hwnd, LPARAM lParam)
{
    HWND hDeskTop = FindWindowEx(0, 0, "#32769 (桌面)", 0);
    if (hwnd != NULL)
    {

        //SendMessage(hwnd, WM_CLOSE, 0, 0);
        ShowWindow(hwnd, SW_SHOW);
    }

    if (hDeskTop != NULL)
    {
        return FALSE;
    }
    return TRUE;
}


DWORD WINAPI BadApple()
{

    keybd_event(VK_LWIN, 0, 0 , 0);
    keybd_event(0x44, 0, 0, 0);
    Sleep(200);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(0x44, 0, KEYEVENTF_KEYUP, 0);

    STARTUPINFO si{ 0 };
    PROCESS_INFORMATION pi{ 0 };
    //设置显示命令
    while (CreateProcess("src\\mpv.exe", (LPSTR)" src\\vidio.mp4 --fs", 0, 0, 0, CREATE_NO_WINDOW, 0, 0, (LPSTARTUPINFOA)&si, (LPPROCESS_INFORMATION)&pi)) //创建视频窗口进程显示视频
    {
        Sleep(1000);
        //获取桌面窗口的句柄
        HWND hVideoParent = FindWindowA("Progman", 0);
        //发送0x52c消息
        SendMessage(hVideoParent, 0x52c, 0, 0);
        //获取视频窗口的句柄
        HWND hVideo = FindWindowA("mpv", 0);
        //枚举窗口找到WorkerW-2并隐藏它
        
        EnumWindows(HideAll, 0);
        EnumWindows(EnumWinProc, 0);

        HWND hTaksbar = FindWindowA("Shell_TrayWnd", 0);
        ShowWindow(hTaksbar,SW_HIDE);

        //将视频窗口设置为桌面窗口的子窗口
        SetParent(hVideo, hVideoParent);

        ShowWindow(hVideoParent, SW_SHOW);
        ShowWindow(hVideo, SW_SHOW);
        //HWND hSeft = FindWindowA("ConsoleWindowClass", 0);
        //SetParent(hSeft, hVideo);

        Sleep(240);
        break;
    }

    return 0;

}

DWORD WINAPI Mouse() 
{
    HWND hq = FindWindowA("ConsoleWindowClass", 0);
    HWND dh = GetDesktopWindow();

    RECT rect, dhr;
    GetWindowRect(hq, &rect);
    GetWindowRect(dh, &dhr);
    Sleep(100);
    MoveWindow(hq, -20, -50, 100, 100, 1);

    rect.bottom = 10;
    rect.right = 5;
    rect.left = 0;
    rect.top = 0;
    
    while (1) {
        ClipCursor(&rect);
    }
    

    /*
        int t = 200000;
        while (t--) {
            ClipCursor(&rect);
            if (GetAsyncKeyState(VK_TAB) & 0x01) {
                break;
            }
        }*/
    ::Sleep(10000);
    ClipCursor(NULL);//释放
    return 0;
}