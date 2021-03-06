// WinApi.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WinApi.h"
#include <list>

using namespace std;

#define MAX_LOADSTRING 100

enum MOVE_DIR
{
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT
};
typedef struct _tagRectangle
{
	float l, t, r, b;
}RECTANGLE, *PRECTANGLE;

typedef struct _tagMonster
{
	RECTANGLE tRC;
	float fSpeed;
	float fTime;
	float fLimitTime;
	int iDir;
}MONSTER, *PMONSTER;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;
HDC		g_hDC;
bool	g_bLoop = true;
RECTANGLE	g_tPlayerRC = { 100, 100, 200, 200 };
MONSTER g_tMonster;

typedef struct _tagBullet
{
	RECTANGLE rc;
	float fDist;
	float fLimitDist;
}BULLET, *PBULLET;
list<BULLET> g_PlayerBulletList;
list<BULLET> g_MonsterBulletList;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LARGE_INTEGER g_tSecond;
LARGE_INTEGER g_tTime;
float g_fDeltaTime;

void Run();

struct _tagArea
{
	bool	bStart;
	POINT	ptStart;
	POINT	ptEnd;
};

_tagArea	g_tArea;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	g_hDC = GetDC(g_hWnd);

	g_tMonster.tRC.l = 800.f - 100.f;
	g_tMonster.tRC.t = 0.f;
	g_tMonster.tRC.r = 800.f;
	g_tMonster.tRC.b = 100.f;
	g_tMonster.fSpeed = 300.f;
	g_tMonster.fTime = 0.f;
	g_tMonster.fLimitTime = 1.1f;
	g_tMonster.iDir = MD_FRONT;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    MSG msg;

	QueryPerformanceFrequency(&g_tSecond);
	QueryPerformanceCounter(&g_tTime);

    // 기본 메시지 루프입니다:
	while (g_bLoop)// GetMessage(&msg, nullptr, 0, 0))
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))//!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			Run();
		}
    }

	ReleaseDC(g_hWnd, g_hDC);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL; // MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   RECT rc = { 0, 0, 800, 600 };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
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
        break;
	/*case WM_LBUTTONDOWN:
		if (!g_tArea.bStart)
		{
			g_tArea.bStart = true;
			g_tArea.ptStart.x = lParam & 0x0000ffff;
			g_tArea.ptStart.y = lParam >> 16;
			g_tArea.ptEnd = g_tArea.ptStart;

			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_MOUSEMOVE:
		if (g_tArea.bStart)
		{
			g_tArea.ptEnd.x = lParam & 0x0000ffff;
			g_tArea.ptEnd.y = lParam >> 16;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		if (g_tArea.bStart)
		{
			g_tArea.bStart = false;
			g_tArea.ptEnd.x = lParam & 0x0000ffff;
			g_tArea.ptEnd.y = lParam >> 16;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;*/
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}	
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

			/*TextOut(hdc, 50, 50, TEXT("ㅎ"), 1);

			TCHAR	strMouse[64] = {};
			wsprintf(strMouse, TEXT("x : %d y : %d"), g_tArea.ptStart.x, g_tArea.ptStart.y);
			TextOut(hdc, 600, 30, strMouse, lstrlen(strMouse));
			
			Rectangle(hdc, 100, 100, 200, 200);

			Ellipse(hdc, 200, 200, 400, 400);
			MoveToEx(hdc, 200, 200, NULL);
			LineTo(hdc, 300, 300);

			if (g_tArea.bStart)
			{
				Rectangle(hdc, g_tArea.ptStart.x, g_tArea.ptStart.y, g_tArea.ptEnd.x, g_tArea.ptEnd.y);
			}
            EndPaint(hWnd, &ps);
			*/
        }
        break;
    case WM_DESTROY:
		g_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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

void Run()
{
	LARGE_INTEGER tTime;
	QueryPerformanceCounter(&tTime);

	g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / (float)g_tSecond.QuadPart;
	g_tTime = tTime;

	static float fTimeScale = 1.f;

	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		fTimeScale -= g_fDeltaTime;

		if (fTimeScale < 0.f)
			fTimeScale = 0.f;
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		fTimeScale += g_fDeltaTime;

		if (fTimeScale > 1.f)
			fTimeScale = 1.f;
	}

	float fSpeed = 400.f * g_fDeltaTime * fTimeScale;

	if (GetAsyncKeyState('D') & 0x8000)
	{
		g_tPlayerRC.l += fSpeed;
		g_tPlayerRC.r += fSpeed;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		g_tPlayerRC.l -= fSpeed;
		g_tPlayerRC.r -= fSpeed;
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		g_tPlayerRC.t -= fSpeed;
		g_tPlayerRC.b -= fSpeed;
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		
		g_tPlayerRC.t += fSpeed;
		g_tPlayerRC.b += fSpeed;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		BULLET tBullet;

		tBullet.rc.l = g_tPlayerRC.r;
		tBullet.rc.r = g_tPlayerRC.r + 50.f;
		tBullet.rc.t = (g_tPlayerRC.t + g_tPlayerRC.b) / 2.f - 25.f;
		tBullet.rc.b = tBullet.rc.t + 50.f;
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 500.f;

		g_PlayerBulletList.push_back(tBullet);
	}
	RECT rcWindow;
	GetClientRect(g_hWnd, &rcWindow);

	if (g_tPlayerRC.l < rcWindow.left)
	{
		g_tPlayerRC.l = 0;
		g_tPlayerRC.r = rcWindow.left+100;
	}

	if (g_tPlayerRC.r > rcWindow.right)
	{
		g_tPlayerRC.l = rcWindow.right-100;
		g_tPlayerRC.r = rcWindow.right;
	}

	if (g_tPlayerRC.t < rcWindow.top)
	{
		g_tPlayerRC.t = 0;
		g_tPlayerRC.b = rcWindow.top+100;
	}

	if (g_tPlayerRC.b > rcWindow.bottom)
	{
		g_tPlayerRC.t = rcWindow.bottom-100;
		g_tPlayerRC.b = rcWindow.bottom;
	}

	g_tMonster.tRC.t += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;
	g_tMonster.tRC.b += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;

	if (g_tMonster.tRC.b >= 600)
	{
		g_tMonster.iDir = MD_BACK;
		g_tMonster.tRC.b = 600;
		g_tMonster.tRC.t = 500;
	}
	else if (g_tMonster.tRC.t <= 0)
	{
		g_tMonster.iDir = MD_FRONT;
		g_tMonster.tRC.b = 100;
		g_tMonster.tRC.t = 0;
	}

	g_tMonster.fTime += g_fDeltaTime * fTimeScale;

	if (g_tMonster.fTime >= g_tMonster.fLimitTime)
	{
		g_tMonster.fTime -= g_tMonster.fLimitTime;
		
		BULLET tBullet = {};

		tBullet.rc.r = g_tMonster.tRC.l;
		tBullet.rc.l = g_tMonster.tRC.l - 50.f;
		tBullet.rc.t = (g_tMonster.tRC.t + g_tMonster.tRC.b) / 2.f - 25.f;
		tBullet.rc.b = tBullet.rc.t + 50.f;
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 800.f;

		g_MonsterBulletList.push_back(tBullet);
	}

	list<BULLET>::iterator iter;
	list<BULLET>::iterator iterEnd = g_PlayerBulletList.end();

	fSpeed = 600.f * g_fDeltaTime * fTimeScale;

	for (iter = g_PlayerBulletList.begin(); iter != iterEnd;)
	{
		(*iter).rc.l += fSpeed;
		(*iter).rc.r += fSpeed;
		(*iter).fDist += fSpeed;

		if ((*iter).fDist >= (*iter).fLimitDist)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		else if (800 <= (*iter).rc.l)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		else
			++iter;
	}

	iterEnd = g_MonsterBulletList.end();

	for (iter = g_MonsterBulletList.begin(); iter != iterEnd;)
	{
		(*iter).rc.l -= fSpeed;
		(*iter).rc.r -= fSpeed;
		(*iter).fDist += fSpeed;

		if ((*iter).fDist >= (*iter).fLimitDist)
		{
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}
		else if (0 >= (*iter).rc.r)
		{
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}
		else if (g_tPlayerRC.l <= (*iter).rc.r && (*iter).rc.l <= g_tPlayerRC.r &&
			g_tPlayerRC.t <= (*iter).rc.b && g_tPlayerRC.b >= (*iter).rc.t)
		{
			iter = g_MonsterBulletList.erase(iter);
			iterEnd = g_MonsterBulletList.end();
		}
		else
			++iter;
	}

	//Rectangle(g_hDC, 0, 0, 800, 600);
	Rectangle(g_hDC, g_tPlayerRC.l, g_tPlayerRC.t, g_tPlayerRC.r, g_tPlayerRC.b);
	Rectangle(g_hDC, g_tMonster.tRC.l, g_tMonster.tRC.t, g_tMonster.tRC.r, g_tMonster.tRC.b);
	
	iterEnd = g_PlayerBulletList.end();
	for (iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter)
	{
		Rectangle(g_hDC, (*iter).rc.l, (*iter).rc.t, (*iter).rc.r, (*iter).rc.b);
	}

	iterEnd = g_MonsterBulletList.end();
	for (iter = g_MonsterBulletList.begin(); iter != iterEnd; ++iter)
	{
		Rectangle(g_hDC, (*iter).rc.l, (*iter).rc.t, (*iter).rc.r, (*iter).rc.b);
	}

};