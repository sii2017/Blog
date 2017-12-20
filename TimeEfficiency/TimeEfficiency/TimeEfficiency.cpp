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
	BS_PUSHBUTTON, TEXT("����"),
	BS_PUSHBUTTON, TEXT("ѧϰ"),
};
#define NUM (sizeof button/sizeof button[0])
WNDPROC OldProc[NUM];	//���洰����Ϣ��������ַ
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
	wndclass.hIcon= LoadIcon(NULL, IDI_APPLICATION);	//��ǰʹ�õ���ϵͳ�ı�׼ͼ��
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
		cxChar= LOWORD(GetDialogBaseUnits());	//�ú�������ϵͳ�ĶԻ�������λ���û�����λΪϵͳ�����ַ���ƽ����Ⱥ͸߶�
		cyChar= HIWORD(GetDialogBaseUnits());

		for(int i=0; i<NUM; i++)
		{
			hwndButton[i]= CreateWindow(
			TEXT("button"), //�������
			button[i].szText, //��������
			WS_CHILD| WS_VISIBLE| button[i].iStyle,	//������ʽ
			cxChar, //x����λ��
			cyChar*(1+2*i), //y����λ��
			20*cxChar, //���
			7*cyChar/4, //�߶ȣ�����ť�ĸ߶�Ϊ���ָ߶ȵ�7/4�����������
			hwnd, //������
			(HMENU)i, //�Ӵ���id��������Լ����壬����ֱ��ʹ��12345...
			((LPCREATESTRUCT)lParam)->hInstance,	//**ִ��ʵ����
			NULL);	//���Ӳ���

			OldProc[i]= (WNDPROC)SetWindowLong(hwndButton[i], GWL_WNDPROC, (LONG)ChildProc);	//ͨ��SetWindowLong�ѿؼ����µĴ�����Ϣ�������ScrollProc�ҹ���ͬʱ����ԭ���Ĵ�����Ϣ�������ĵ�ַ
		}

		return 0;
	case WM_SIZE:
		cxClient= LOWORD(lParam);
		cyClient= HIWORD(lParam);
		return 0;
	case WM_COMMAND:
		if (LOWORD(wParam) == 0 && HIWORD(wParam) == BN_CLICKED)	//��ζ�� ������ť �������
		{
			//bClicked= true;

			//time_t rawtime;
			//struct tm * timeinfo;
			//time ( &rawtime );
			//timeinfo = localtime ( &rawtime );
			//nowTime= asctime (timeinfo);
			//MessageBox(hwnd, TEXT("�����˹���"), TEXT("MessageBox"), MB_OK);
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
		if (LOWORD(wParam) == 1 && HIWORD(wParam) == BN_CLICKED)	//��ζ�� ѧϰ��ť �������
		{
			MessageBox(hwnd, TEXT("������ѧϰ"), TEXT("MessageBox"), MB_OK);
		}
		return 0;
	case WM_PAINT:
		hdc= BeginPaint(hwnd, &ps);

		if(bClicked)
		{
			//TCHAR szBuffer[256];
			//int a= wsprintf(szBuffer, TEXT("%s"), nowTime);
			//TextOut(hdc, cxClient/2, 0, szBuffer, wsprintf(szBuffer, TEXT("%s"), nowTime));
			//TextOutA(hdc, cxClient/2, 0, nowTime, strlen(nowTime));	//��һ��Ҫ�ÿ��ֽڵģ�խ�־���TextOutA
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
	return CallWindowProc(OldProc[id], hwnd, message, wParam, lParam);	//����δ�������Ϣ���ظ�ԭ������Ϣ���������д���
}