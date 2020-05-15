/*
雷课堂
图形界面范例程序

本系列课程详细介绍
https://www.zhihu.com/question/389457315/answer/1170354190


作业 5-1
*/

#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <atlstr.h>


using namespace std;


// win32窗口的回调函数
// 函数的定义是固定好的
LRESULT CALLBACK 
windowCallback(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    // 窗口发生不同事件（案件/鼠标移动等）的时候本函数会自动调用
    // msg 代表了事件的类型，WM_DESTROY 表示窗口关闭
    // 在 windows 中，事件被称之为消息
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    // 系统的默认窗口处理函数，这是套路
    return DefWindowProc(hWnd, msg, wp, lp);
}

int
runLoop() {
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    // 窗口进入消息循环
    // 如果窗口没有接收到退出消息的话，就一直循环
    while(msg.message != WM_QUIT) {
        // 检查消息队列，如果消息存在的话，执行消息处理
        // 如果没有任何消息，GetMessage 就会等在这里
        if(GetMessage(&msg, NULL, 0, 0)) {
            // 下面两行是规定，现在不必理解为什么
            // 这两行执行完后，系统就会自动调用 WndProc 函数
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

HWND
kbcCreateWindow(HINSTANCE hInstance) {
    // _T 包起来的字符串才能在里面使用中文
    auto className = _T("kbcWinClass");
    // 设置窗口属性并初始化
    WNDCLASSEX	window = { 0 };
    window.hInstance = hInstance;         // 这个是 WinMain 函数的第一个参数
    window.lpfnWndProc = windowCallback;  // 系统会在窗口事件发生后调用的函数
    window.lpszClassName = className;     // 这个要和下面 CreateWindow 第一个参数一样
    // 下面的属性，不必具体了解，当做规定即可
    // 实际上如果这个 API 设计得稍微用点点点点心，下面很多属性都应该有默认值而不是让人手动去设置
    window.cbSize = sizeof(WNDCLASSEX);
    window.cbClsExtra = 0;
    window.cbWndExtra = 0;
    window.style = CS_CLASSDC;
    window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window.hCursor = LoadCursor(NULL, IDC_ARROW);
    window.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window.lpszMenuName = NULL;
    window.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&window);

    // 创建窗口
    auto windowId = CreateWindow(
        className,                      // 这个要和上面的 wcex 的 lpszClassName 属性一样
        _T("快编程雷课堂 - 作业 5-1"),    // 窗口标题
        WS_OVERLAPPEDWINDOW,            // 窗口样式
        // 下面 4 个参数分别是窗口左上角的 x y 坐标以及窗口的 w h
        100, 100, 800, 600,
        // 下面 4 个现在应当做规定
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // 显示，更新窗口，当做规定
    ShowWindow(windowId, SW_SHOW);
    UpdateWindow(windowId);
    
    return windowId;
}

void
loadImage(HWND windowId) {
    const char* path = "a1.kbcimage";
    FILE *f;
    fopen_s(&f, path, "rb");

    // 读取 3 字节
    // .kbcimage 的前 3 个字节分别是文件版本和图像的 w 和 h
    char *imageInfo = new char[3];
    fread(imageInfo, 1, 3, f);
    int w = (unsigned char)imageInfo[1];
    int h = (unsigned char)imageInfo[2];

    // 用 stringstream 格式化字符串
    // 用 CString 转成 MessageBox 所需参数的格式
    stringstream s;
    s << string("image w and h [") << w << "  " << h <<  string("]");
    CString content(s.str().c_str());
    MessageBox(NULL, content, _T("图像尺寸"), MB_OK);

    const int size = w * h * 3;
    char *data = new char[size];
    fread(data, 1, size, f);
     
    BITMAPINFOHEADER header;
    /*
    作为一个小练习，你需要阅读下面链接的官方文档
    理解文档后正确设置 header 的值
    利用 data 中的像素数据生成正确的包含像素的数组 pixels（下面的代码要用）
    这样就能正常显示图片了

    这会花费你大约 2 小时的时间
    如果你不想做这个或者没能做出来，那么 5 月 13 日下午 18:00 后群里会上传正确的代码
    https://docs.microsoft.com/en-us/windows/win32/wmdm/-bitmapinfoheader
    https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
    */

    auto hdc = GetDC(windowId);
    StretchDIBits(hdc,
        0, 0,
        header.biWidth,
        header.biHeight,
        0, h,
        header.biWidth,
        -header.biHeight,
        pixels,
        (BITMAPINFO*)&header,
        DIB_RGB_COLORS, SRCCOPY
    );
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    auto windowId = kbcCreateWindow(hInstance);

    // 载入图像并画图
    loadImage(windowId);

    return runLoop();
}
