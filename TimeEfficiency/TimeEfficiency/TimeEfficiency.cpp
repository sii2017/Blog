#include <windows.h>
#include <time.h>
#include <vector>
struct
{
	int iStyle;
	TCHAR* szText;
}
button[]= 
{
	BS_PUSHBUTTON, TEXT("工作"),
	BS_PUSHBUTTON, TEXT("学习"),
};
#define NUM (sizeof button/sizeof button[0])
WNDPROC OldProc[NUM];	//保存窗口消息处理程序地址
//struct
//{
//	int type;	//1 means  word, 2 means study
//	char* startTime;
//	char* endTime;
//};
//std::vector<char*, char*> vTimeRecord;
TCHAR szAppName[]= TEXT("TimeEffciency");
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style= CS_HREDRAW|CS_VREDRAW;
	wndclass.lpfnWndProc= WndProc;
	wndclass.cbClsExtra= 0;
	wndclass.cbWndExtra= 0;
	wndclass.hInstance= hInstance;
	wndclass.hIcon= LoadIcon(NULL, IDI_APPLICATION);	//当前使用的是系统的标准图标
	wndclass.hCursor= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName= NULL;
	wndclass.lpszClassName= szAppName;

	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Register Class Failed"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd= CreateWindow(szAppName, TEXT("TimeEffciency"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
		NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

int AskConfirmation(HWND hwnd)
{
	return MessageBox(hwnd, TEXT("Really want to close?"), szAppName, 
		MB_YESNO | MB_ICONQUESTION);  
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int cxClient, cyClient, cxChar, cyChar;
	HWND hwndButton[NUM];
	static bool bClicked= false;
	static char nowTime1[256], nowTime2[256];
	static time_t startTime, endTime;

	switch(message)
	{
	case WM_CREATE:
		cxChar= LOWORD(GetDialogBaseUnits());	//该函数返回系统的对话基本单位，该基本单位为系统字体字符的平均宽度和高度
		cyChar= HIWORD(GetDialogBaseUnits());

		for(int i=0; i<NUM; i++)
		{
			hwndButton[i]= CreateWindow(
			TEXT("button"), //类别名称
			button[i].szText, //窗口文字
			WS_CHILD| WS_VISIBLE| button[i].iStyle,	//窗口样式
			cxChar, //x坐标位置
			cyChar*(1+2*i), //y坐标位置
			20*cxChar, //宽度
			7*cyChar/4, //高度，当按钮的高度为文字高度的7/4倍看起来最好
			hwnd, //父窗口
			(HMENU)i, //子窗口id这个可以自己定义，这里直接使用12345...
			((LPCREATESTRUCT)lParam)->hInstance,	//**执行实体句柄
			NULL);	//附加参数

			OldProc[i]= (WNDPROC)SetWindowLong(hwndButton[i], GWL_WNDPROC, (LONG)ChildProc);	//通过SetWindowLong把控件与新的窗口消息处理程序ScrollProc挂钩，同时保存原来的窗口消息处理程序的地址
		}

		return 0;
	case WM_SIZE:
		cxClient= LOWORD(lParam);
		cyClient= HIWORD(lParam);
		return 0;
	case WM_COMMAND:
		if (LOWORD(wParam) == 0 && HIWORD(wParam) == BN_CLICKED)	//意味着 工作按钮 被点击了
		{
			//bClicked= true;

			//time_t rawtime;
			//struct tm * timeinfo;
			//time ( &rawtime );
			//timeinfo = localtime ( &rawtime );
			//nowTime= asctime (timeinfo);
			//MessageBox(hwnd, TEXT("你点击了工作"), TEXT("MessageBox"), MB_OK);
			//InvalidateRect(hwnd, NULL, FALSE);

			struct tm* timeinfo;
			if(!bClicked)
			{
				bClicked= true;
				startTime= time(NULL);

				timeinfo= localtime(&startTime);
				strcpy(nowTime1, asctime(timeinfo));
				//vTimeRecord[asctime(timeinfo)]="";
			}
			else
			{
				bClicked= false;
				endTime= time(NULL);
				difftime(startTime, endTime);

				timeinfo= localtime(&endTime);
				strcpy(nowTime2, asctime(timeinfo));
			}


		}
		if (LOWORD(wParam) == 1 && HIWORD(wParam) == BN_CLICKED)	//意味着 学习按钮 被点击了
		{
			MessageBox(hwnd, TEXT("你点击了学习"), TEXT("MessageBox"), MB_OK);
		}
		return 0;
	case WM_PAINT:
		hdc= BeginPaint(hwnd, &ps);

		if(bClicked)
		{
			//TCHAR szBuffer[256];
			//int a= wsprintf(szBuffer, TEXT("%s"), nowTime);
			//TextOut(hdc, cxClient/2, 0, szBuffer, wsprintf(szBuffer, TEXT("%s"), nowTime));
			//TextOutA(hdc, cxClient/2, 0, nowTime, strlen(nowTime));	//不一定要用宽字节的，窄字就用TextOutA
		}

		EndPaint(hwnd, &ps);
		return 0;
	case WM_CLOSE:
		if(IDYES== AskConfirmation(hwnd))
			DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK ChildProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int id= GetWindowLong(hwnd, GWL_ID);
	switch(message)
	{
	}
	return CallWindowProc(OldProc[id], hwnd, message, wParam, lParam);	//其余未处理的消息返回给原来的消息处理程序进行处理
}