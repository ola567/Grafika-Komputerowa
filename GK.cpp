/******************************************************************
 Grafika komputerowa, �rodowisko MS Windows - program  przyk�adowy
 *****************************************************************/
#define _USE_MATH_DEFINES
#include <windows.h>
#include <gdiplus.h>
#include <math.h>
using namespace Gdiplus;


//deklaracja funkcji obslugi okna
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//funkcja Main - dla Windows
 int WINAPI WinMain(HINSTANCE hInstance,
               HINSTANCE hPrevInstance,
               LPSTR     lpCmdLine,
               int       nCmdShow)
{
	MSG meldunek;		  //innymi slowy "komunikat"
	WNDCLASS nasza_klasa; //klasa g��wnego okna aplikacji
	HWND okno;
	static char nazwa_klasy[] = "Podstawowa";
	
	GdiplusStartupInput gdiplusParametry;// parametry GDI+; domy�lny konstruktor wype�nia struktur� odpowiednimi warto�ciami
	ULONG_PTR	gdiplusToken;			// tzw. token GDI+; warto�� uzyskiwana przy inicjowaniu i przekazywana do funkcji GdiplusShutdown
   
	// Inicjujemy GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusParametry, NULL);

	//Definiujemy klase g��wnego okna aplikacji
	//Okreslamy tu wlasciwosci okna, szczegoly wygladu oraz
	//adres funkcji przetwarzajacej komunikaty
	nasza_klasa.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	nasza_klasa.lpfnWndProc   = WndProc; //adres funkcji realizuj�cej przetwarzanie meldunk�w 
 	nasza_klasa.cbClsExtra    = 0 ;
	nasza_klasa.cbWndExtra    = 0 ;
	nasza_klasa.hInstance     = hInstance; //identyfikator procesu przekazany przez MS Windows podczas uruchamiania programu
	nasza_klasa.hIcon         = 0;
	nasza_klasa.hCursor       = LoadCursor(0, IDC_ARROW);
	nasza_klasa.hbrBackground = (HBRUSH) GetStockObject(GRAY_BRUSH);
	nasza_klasa.lpszMenuName  = "Menu" ;
	nasza_klasa.lpszClassName = nazwa_klasy;

    //teraz rejestrujemy klas� okna g��wnego
    RegisterClass (&nasza_klasa);
	
	/*tworzymy okno g��wne
	okno b�dzie mia�o zmienne rozmiary, listw� z tytu�em, menu systemowym
	i przyciskami do zwijania do ikony i rozwijania na ca�y ekran, po utworzeniu
	b�dzie widoczne na ekranie */
 	okno = CreateWindow(nazwa_klasy, "Grafika komputerowa", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	
	
	/* wyb�r rozmiaru i usytuowania okna pozostawiamy systemowi MS Windows */
   	ShowWindow (okno, nCmdShow) ;
    
	//odswiezamy zawartosc okna
	UpdateWindow (okno) ;

	// G��WNA P�TLA PROGRAMU
	while (GetMessage(&meldunek, NULL, 0, 0))
     /* pobranie komunikatu z kolejki; funkcja GetMessage zwraca FALSE tylko dla
	 komunikatu WM_QUIT; dla wszystkich pozosta�ych komunikat�w zwraca warto�� TRUE */
	{
		TranslateMessage(&meldunek); // wst�pna obr�bka komunikatu
		DispatchMessage(&meldunek);  // przekazanie komunikatu w�a�ciwemu adresatowi (czyli funkcji obslugujacej odpowiednie okno)
	}

	GdiplusShutdown(gdiplusToken);
	
	return (int)meldunek.wParam;
}

/********************************************************************
FUNKCJA OKNA realizujaca przetwarzanie meldunk�w kierowanych do okna aplikacji*/
LRESULT CALLBACK WndProc (HWND okno, UINT kod_meldunku, WPARAM wParam, LPARAM lParam)
{
	HMENU mPlik, mInfo, mGlowne;
    	
/* PONI�SZA INSTRUKCJA DEFINIUJE REAKCJE APLIKACJI NA POSZCZEG�LNE MELDUNKI */
	switch (kod_meldunku) 
	{
	case WM_CREATE:  //meldunek wysy�any w momencie tworzenia okna
		mPlik = CreateMenu();
		AppendMenu(mPlik, MF_STRING, 100, "&Zapiszcz...");
		AppendMenu(mPlik, MF_SEPARATOR, 0, "");
		AppendMenu(mPlik, MF_STRING, 101, "&Koniec");
		mInfo = CreateMenu();
		AppendMenu(mInfo, MF_STRING, 200, "&Autor...");
		mGlowne = CreateMenu();
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR) mPlik, "&Plik");
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR) mInfo, "&Informacja");
		SetMenu(okno, mGlowne);
		DrawMenuBar(okno);

	case WM_COMMAND: //reakcje na wyb�r opcji z menu
		switch (wParam)
		{
		case 100: if(MessageBox(okno, "Zapiszcze�?", "Pisk", MB_YESNO) == IDYES)
					MessageBeep(0);
                  break;
		case 101: DestroyWindow(okno); //wysylamy meldunek WM_DESTROY
        		  break;
		case 200: MessageBox(okno, "Imi� i nazwisko:\nNumer indeksu: ", "Autor", MB_OK);
		}
		return 0;
	
	case WM_LBUTTONDOWN: //reakcja na lewy przycisk myszki
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			return 0;
		}

	case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC kontekst;

			kontekst = BeginPaint(okno, &paint);
		
			// MIEJSCE NA KOD GDI

			//HPEN pioro = CreatePen(PS_SOLID, 20, RGB(255, 0, 0));
			//SelectObject(kontekst, pioro);
			//MoveToEx(kontekst, 50, 50, NULL);
			//LineTo(kontekst, 800, 50);	
			//DeleteObject(pioro);

			//HPEN pioro1 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			POINT punktyN1[] = {{167,150},{177,145},{187,150},{227,250},{207,250},{187,200},{187, 250},{167,250}};
			POINT punktyN2[] = {{207,150},{227,150},{227,250},{207,250}};

			HBRUSH pedzel = CreateSolidBrush(RGB(255, 176, 255));
			HBRUSH pedzel3 = CreateSolidBrush(RGB(255, 100, 0));
			HBRUSH pedzel4 = CreateSolidBrush(RGB(200, 0, 0));
			HBRUSH pedzel5 = CreateSolidBrush(RGB(100, 0, 0));

			int x = 200;
			int y = 200;
			int r = 100;

			SelectObject(kontekst,pedzel);
			Pie(kontekst, 100, 100, 300, 300, x+(r*cos(-20*M_PI/180)), x+(r* sin(-20*M_PI/ 180)),x+(r*cos(-180*M_PI/ 180)),x+(r*sin(-180*M_PI/ 180)));
			DeleteObject(pedzel);

			SelectObject(kontekst, pedzel3);
			Pie(kontekst, 100, 100, 300, 300, x + (r * cos(-180* M_PI / 180)), x + (r * sin(-180* M_PI / 180)), x + (r * cos(160* M_PI / 180)), x + (r * sin(160 * M_PI / 180)));
			DeleteObject(pedzel3);

			SelectObject(kontekst, pedzel4);
			Pie(kontekst, 100, 100, 300, 300, x + (r * cos(160 * M_PI / 180)), x + (r * sin(160 * M_PI / 180)), x + (r * cos(0* M_PI / 180)), x + (r * sin(0 * M_PI / 180)));
			DeleteObject(pedzel4);

			SelectObject(kontekst, pedzel5);
			Pie(kontekst, 100, 100, 300, 300, x + (r * cos(0* M_PI / 180)), x + (r * sin(0 * M_PI / 180)), x + (r * cos(-20 * M_PI / 180)), x + (r * sin(-20* M_PI / 180)));
			DeleteObject(pedzel5);
			
			HBRUSH pedzel1=CreateSolidBrush(RGB(255, 176, 0));
			HBRUSH pedzel2=CreateSolidBrush(RGB(255, 239, 148));

			SelectObject(kontekst, pedzel1);
			Polygon(kontekst, punktyN2, 4);
			DeleteObject(pedzel1);
			SelectObject(kontekst, pedzel2);
			Polygon(kontekst, punktyN1, 8);
			DeleteObject(pedzel2);

			//HBRUSH pedzel6= CreateSolidBrush(RGB(255, 0, 0));
			//SelectObject(kontekst,pedzel6);
			//Ellipse(kontekst,100,100,150,200);
			//Ellipse(kontekst,200,100,250,200);
			//Ellipse(kontekst,150,200,200,230);
			//DeleteObject(pedzel6);

			//HBRUSH pedzel7 = CreateSolidBrush(RGB(255, 255, 0));
			//POINT p1[] = {{50,50},{50,100},{100,100},{100,50}};
			//SelectObject(kontekst, pedzel7);
			//MoveToEx(kontekst, 50, 50, NULL);
			//PolyBezier(kontekst, p1,3);
			//DeleteObject(pedzel7);

			// utworzenie obiektu umo�liwiaj�cego rysowanie przy u�yciu GDI+
			// (od tego momentu nie mo�na u�ywa� funkcji GDI
			Graphics grafika(kontekst);
			
			// MIEJSCE NA KOD GDI+


			// utworzenie czcionki i wypisanie tekstu na ekranie
			FontFamily  fontFamily(L"Times New Roman");
			Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
			PointF      pointF(100.0f, 400.0f);
			SolidBrush  solidBrush(Color(255, 0, 0, 255));

			grafika.DrawString(L"To jest tekst napisany za pomoc� GDI+.", -1, &font, pointF, &solidBrush);

			EndPaint(okno, &paint);

			return 0;
		}
  	
	case WM_DESTROY: //obowi�zkowa obs�uga meldunku o zamkni�ciu okna
		PostQuitMessage (0) ;
		return 0;
    
	default: //standardowa obs�uga pozosta�ych meldunk�w
		return DefWindowProc(okno, kod_meldunku, wParam, lParam);
	}
}
