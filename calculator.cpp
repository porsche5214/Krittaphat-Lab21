#include <windows.h>
#include <cstdio>
#include <string>

HWND textfield , button , First , Second ;
char textSaved1[20] , textSaved2[20];

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	switch(Message) {
		
		case WM_CREATE:
					textfield = CreateWindow("STATIC","Please input two numbers",
					WS_VISIBLE | WS_CHILD,
				20,20,180,25,hwnd,NULL,NULL,NULL);
					
				CreateWindow("BUTTON","+",
					WS_VISIBLE | WS_CHILD,
				30,120,25,25,hwnd,(HMENU) 1,NULL,NULL);
				CreateWindow("BUTTON","-",
					WS_VISIBLE | WS_CHILD,
				60,120,25,25,hwnd,(HMENU) 2,NULL,NULL);
				CreateWindow("BUTTON","*",
					WS_VISIBLE | WS_CHILD,
				90,120,25,25,hwnd,(HMENU) 3,NULL,NULL);
				CreateWindow("BUTTON","/",
					WS_VISIBLE | WS_CHILD,
				120,120,25,25,hwnd,(HMENU) 4,NULL,NULL);


				First = CreateWindow("EDIT","",
					WS_BORDER|WS_VISIBLE | WS_CHILD,
				30,50,150,20,hwnd,NULL,NULL,NULL);
				Second = CreateWindow("EDIT","",
					WS_BORDER|WS_VISIBLE | WS_CHILD,
				30,80,150,20,hwnd,NULL,NULL,NULL);
					
				break;


		case WM_COMMAND:
				switch(LOWORD(wParam)){
					
					case 1:{
					float firstint = 0,secondint = 0;
					firstint = GetWindowText(First,&textSaved1[0],20);
					secondint= GetWindowText(Second,&textSaved2[0],20);
					float num1 = std::stof(textSaved1);
					float num2 = std::stof(textSaved2);
					num1 = num1 + num2;
					char str[20];
					sprintf(str, "%f", num1);
			

					::MessageBox(hwnd,str,"Result",MB_OK);
					break;
					}
					case 2:{
						float firstint = 0,secondint = 0;
					firstint = GetWindowText(First,&textSaved1[0],20);
					secondint= GetWindowText(Second,&textSaved2[0],20);
					float num1 = std::stof(textSaved1);
					float num2 = std::stof(textSaved2);
					num1 = num1 - num2;
					char str[20];
					sprintf(str, "%f", num1);
					::MessageBox(hwnd,str,"Result",MB_OK);



					}
					break;
					case 3:{
						float firstint = 0,secondint = 0;
					firstint = GetWindowText(First,&textSaved1[0],20);
					secondint= GetWindowText(Second,&textSaved2[0],20);
					float num1 = std::stof(textSaved1);
					float num2 = std::stof(textSaved2);
					num1 = num1 * num2;
					char str[20];
					sprintf(str, "%f", num1);
					::MessageBox(hwnd,str,"Result",MB_OK);



					}

					break;

					case 4:{
						float firstint = 0,secondint = 0;
					firstint = GetWindowText(First,&textSaved1[0],20);
					secondint= GetWindowText(Second,&textSaved2[0],20);
					float num1 = std::stof(textSaved1);
					float num2 = std::stof(textSaved2);
					num1 = num1 / num2;
					char str[20];
					sprintf(str, "%f", num1);
					::MessageBox(hwnd,str,"Result",MB_OK);



					}
				}

				break;
		
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255, 165, 0));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		100, /* x */
		100, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
