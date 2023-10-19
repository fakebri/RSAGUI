// RSAGUI.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "RSAGUI.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
extern int p, q, n, L, E, D;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RSAGUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RSAGUI));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RSAGUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_RSAGUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 640, 360, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HWND hRaw, hEncrypt, hPubKey, hPrivateKey, hEncryptBtn, hDecryptBtn, hGenerateBtn;

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // 创建一个字体以支持 ClearType 抗锯齿渲染
        HFONT hFont = CreateFontW(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Segoe UI"); // 这里使用了 Segoe UI 字体


        // x y 宽 高

        // 创建"明文"编辑框和标签
        CreateWindowW(L"Static", L"明文:", WS_CHILD | WS_VISIBLE,
            10, 10, 80, 20, hWnd, NULL, NULL, NULL);

        hRaw = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
            100, 10, 520, 50, hWnd, NULL, NULL, NULL);

        // 创建"密文"编辑框和标签
        CreateWindowW(L"Static", L"密文:", WS_CHILD | WS_VISIBLE,
            10, 70, 80, 20, hWnd, NULL, NULL, NULL);

        hEncrypt = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
            100, 70, 520, 50, hWnd, NULL, NULL, NULL);

        // 创建"公密"编辑框和标签
        CreateWindowW(L"Static", L"公密:", WS_CHILD | WS_VISIBLE,
            10, 130, 80, 20, hWnd, NULL, NULL, NULL);

        hPubKey = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
            100, 130, 520, 50, hWnd, NULL, NULL, NULL);

        // 创建"私钥"编辑框和标签
        CreateWindowW(L"Static", L"私钥:", WS_CHILD | WS_VISIBLE,
            10, 190, 80, 20, hWnd, NULL, NULL, NULL);

        hPrivateKey = CreateWindowW(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
            100, 190, 520, 50, hWnd, NULL, NULL, NULL);

        // 加密按钮

        hEncryptBtn = CreateWindowW(L"Button", L"加密", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            100, 250, 80, 30, hWnd, NULL, NULL, NULL);

        // 创建"解密"按钮
        hDecryptBtn = CreateWindowW(L"Button", L"解密", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            200, 250, 80, 30, hWnd, NULL, NULL, NULL);

        hGenerateBtn = CreateWindowW(L"Button", L"生成密钥", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            300, 250, 80, 30, hWnd, NULL, NULL, NULL);

        // 遍历窗口中的子控件，为每个子控件设置相同的字体
        HWND hwndChild = GetWindow(hWnd, GW_CHILD);
        while (hwndChild != NULL) {
            SendMessage(hwndChild, WM_SETFONT, (WPARAM)hFont, TRUE);
            hwndChild = GetWindow(hwndChild, GW_HWNDNEXT); // 获取下一个子控件
        }
    }
    break;
    case WM_COMMAND:
        {
        if (lParam == (LPARAM)hEncryptBtn)
        {
            // 加密操作
            std::wstring raw_text(GetEditText(hRaw));
            std::wstring public_key(GetEditText(hPubKey));

            // excat
            std::vector<int> pubkey = extractNumbers(public_key.c_str());

            E = pubkey[0];
            n = pubkey[1];

            std::wstring encrypt_text = std::to_wstring(RSAEnc(std::stoull(raw_text),E,n));

            SetWindowText(hEncrypt, encrypt_text.c_str());

        }
        else if (lParam == (LPARAM)hDecryptBtn) 
        {
            // 解密操作
            std::wstring encrypt_text(GetEditText(hEncrypt));
            std::wstring private_key(GetEditText(hPrivateKey));

            // excat
            std::vector<int> pubkey = extractNumbers(private_key.c_str());

            bool pause = true;
            D = pubkey[0];
            p = pubkey[1];
            q = pubkey[2];
            n = p * q;

            std::wstring decrypt_text = std::to_wstring(RSAEnc(std::stoull(encrypt_text), D, n));

            SetWindowText(hRaw, decrypt_text.c_str());
            
        }
        else if (lParam == (LPARAM)hGenerateBtn)
        {
            // generate key
            generate_key();
            //p, q, n, L, E, D;
            // 创建一个字符串流对象
            std::wstringstream pubkey;
            std::wstringstream privatekey;
            
            // 将整数转换为字符串并拼接到字符串流中
            pubkey << "{" << E << ", " << n << "}";
            privatekey << "{" << D << ", " << p << ", " << q << "}";

            SetWindowText(hPubKey, pubkey.str().c_str());
            SetWindowText(hPrivateKey, privatekey.str().c_str());

        }
        else {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
