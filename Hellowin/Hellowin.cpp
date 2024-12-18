/*------------------------------------------------------------
HELLOWIN.C -- Displays "Hello, Windows!" in client area
------------------------------------------------------------*/
#undef UNICODE
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static char szAppName[] = "HelloWin";
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndclass; // obiectul instantiat din structura WNDCLASSEX
	wndclass.cbSize = sizeof(wndclass);//Dimensiunea structurii
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //Stilul ferestrei

	// Procedura de fereastra care trateaza mesajele
	wndclass.lpfnWndProc = WndProc;

	// Doua câmpuri care permit rezervarea de spatiu suplimentar in structura
	// class, respectiv structura window.
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance; //Identificatorul instantei ferestrei

	//Stabileste o pictograma pentru toate ferestrele create pe baza clasei window
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	//Stabileste o pictograma pentru cursor
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	//Specifica culoarea de fundal a ferestrei
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL; // Specifica meniul feresterei
	wndclass.lpszClassName = szAppName; // Specifica numele feresterei
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//Inregistrarea clasei de fereastra
	RegisterClassEx(&wndclass);

	// Crearea ferestrei pe baza clasei de fereastra
	hwnd = CreateWindow(szAppName, // window class name
		"Un program simplu", // window caption
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT, // initial x position
		CW_USEDEFAULT, // initial y position
		CW_USEDEFAULT, // initial x size
		CW_USEDEFAULT, // initial y size
		NULL, // parent window handle
		NULL, // window menu handle
		hInstance, // program instance handle
		NULL); // creation parameters
	ShowWindow(hwnd, iCmdShow); // afiseaza fereastra pe ecran
	//transmite catre WndProc un mesaj de tip WM_PAINT, care are ca rezultat
	//redesenarea ferestrei, adica reactualizarea zonei client a ferestrei
	UpdateWindow(hwnd); //

	// preia si distribuie mesaje pana se primeste WM_QUIT
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // traduce mesajul
		// transmite mesajul catre procedura de fereastra
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; //contextul grafic
	PAINTSTRUCT ps; // o variabila la structura de desenare
	RECT rect; //obiect dreptunghi

	switch (iMsg)
	{
	case WM_CREATE: //operatii ce se executa la crearea ferestrei
		return 0;
	case WM_PAINT://operatii ce se executa la desenarea ferestrei
		hdc = BeginPaint(hwnd, &ps); //Obtinerea contextului grafic
		GetClientRect(hwnd, &rect); //Obtinerea suprafeţei de desenare
		//Scrierea unui text în fereastră
		DrawText(hdc, "Hello, Windows!", -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps); //Eliberarea contextului grafic
		return 0;
	case WM_DESTROY://operatii ce se executa la distrugerea ferestrei
		// insereaza un mesaj de incheiere in coada de mesaje
		PostQuitMessage(0);
		return 0;
	}
	// Alte mesaje sunt trimise catre functia implicita de tratare
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}