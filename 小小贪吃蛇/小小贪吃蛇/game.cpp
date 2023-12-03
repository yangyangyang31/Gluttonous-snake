#include "test.h"

int x=1;
RECT rect;

LRESULT WINAPI Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		initl(map, head);
		randfood();
		MessageBox(hwnd, "游戏开始", "game", MB_YESNO);
		SetTimer(hwnd, 1, 200, NULL);
		break;
	case WM_CLOSE:
		::DestroyWindow(hwnd);
		break;
	case WM_KEYDOWN:	
		if (wParam == 'W' || wParam == 'S')
		{
			if (head != 'W' && head != 'S')
				head = wParam;
		}
		else if (wParam == 'A' || wParam == 'D')
		{
			if (head != 'A' && head != 'D')
				head = wParam;
		}
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_TIMER:
		x=move();
		if (!x)
			KillTimer(hwnd, 1);
		InvalidateRect(hwnd, &rect, false);
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		GetClientRect(hwnd, &rect);
		::BeginPaint(hwnd, &ps);
		display();
		if(x)
			BitBlt(hdc, 0, 0, 815, 815, hTempDc, 0, 0, SRCCOPY);
		if (!x)
		{
			MessageBox(hwnd, "游戏结束", "gameover", MB_OK);
			::PostQuitMessage(0);
		}
		::EndPaint(hwnd, &ps);
		break;
	default:
		return DefWindowProcA(hwnd, msg, wParam, lParam);
		break;
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR cmd, int nshow)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = Proc;
	wc.lpszClassName = "test";
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	srand((unsigned int)time(NULL));

	::RegisterClass(&wc);

	HWND hwnd = ::CreateWindow("test", "test", WS_OVERLAPPEDWINDOW, 200, 50, 815, 800, NULL, NULL, hInstance, NULL);



	DWORD k = GetLastError();
	hdc = GetDC(hwnd);
	hMenDc = CreateCompatibleDC(hdc);
	hTempDc = CreateCompatibleDC(hdc);

	hh = CreateCompatibleBitmap(hdc, 815, 800);


	hw = (HBITMAP)LoadImageA(NULL, "W.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	ha = (HBITMAP)LoadImageA(NULL, "A.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	hs = (HBITMAP)LoadImageA(NULL, "S.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	hd = (HBITMAP)LoadImageA(NULL, "D.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	hf = (HBITMAP)LoadImageA(NULL, "food.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
	hb = (HBITMAP)LoadImageA(NULL, "body.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);

	SelectObject(hTempDc, hh);

	::ShowWindow(hwnd, SW_SHOWNORMAL);
	::UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return 0;
}
