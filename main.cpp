#include <math.h>
#include <stdio.h>
#include <vector>
#include <iostream>

// Do³¹cz definicje biblioteki Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const float FPS = 60;		//obraz bêdzie aktualizowany co 1/FPS sekundy
const int SCREEN_W = 640;	//szerokoœæ okna
const int SCREEN_H = 480;	//wysokoœæ okna

void drawflower(int n, float dx, float dy, float r, float kat)
{
	float x, y;
	for (int i = 0; i < n; i++)
	{
		x = (sin(2 * ALLEGRO_PI / n * i + kat) * r) + dx;
		y = (cos(2 * ALLEGRO_PI / n * i + kat) * r) + dy;

		al_draw_filled_circle(x, y, r, al_map_rgb(255, 255, 0));
	}
}

// Funkcja g³ówna
int main()
{

	ALLEGRO_DISPLAY* display = NULL;			//okno
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;	//kolejka zdarzen
	ALLEGRO_TIMER* timer = NULL;				//timer, od ktorego bêdziemy odbierac zdarzenia (potrzebny do animacji)
	bool redraw = true;

	if (!al_init()) {							//inicjalizacja biblioteki Allegro
		fprintf(stderr, "Nie zainicjalizowano allegro!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);	//utworznie okna
	timer = al_create_timer(1.0 / FPS);					//utworzenie timera
	al_install_keyboard();								//inicjalizacja obs³ugi klawiatury
	event_queue = al_create_event_queue();				//utworzenie kolejki zdarzeñ

	al_init_primitives_addon(); //inicjalizacja obs³ugi prostych elementów (punkty, linie, prostok¹ty, elipsy itd.)
	al_install_mouse();

	//Rejestracja ¿róde³ zdarzeñ (okno, timer, klawiatura ...)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//Kolory rysowania
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);

	//Definicja wielok¹ta
	const int N = 7;
	float dx[N] = { 0.0, -30.0, -10.0, -10.0, 10.0, 10.0, 30.0 };
	float dy[N] = { -60.0, -30.0,-30.0, 60.0, 60.0,-30.0,-30.0 };
	int xm = SCREEN_W / 2;
	int ym = SCREEN_H / 2;
	float rfactor = 1;
	srand(time(NULL));

	//Tablice na przetworzone wspó³rzêdna punktów
	float points[2 * N];

	//Zmienne na potrzeby obracania figury
	double fi = 0.0, dfi = 0.1, sinfi, cosfi;

	//Uruchamiamy timer, który bêdzie z zadan¹ czêstotliwoœci¹ wysy³a³ zdarzenia
	al_start_timer(timer);

	std::vector<int> positions;
	//Pêtla g³ówna programu - obs³uga zdarzeñ.
	//Dzia³amy, dopóki u¿ytkownik nie wciœnie Esc.
	while (true)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {	//zdarzenie timera -> odœwie¿enie obrazu 
			redraw = true;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {	//zdarzenie klawiatury -> jeœli Esc to koñczymy
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				break;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //zdarzenie zamkniêcia okna
			break;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			int n = rand() % 5 + 3;
			int r = rand() % 50 + 30;

			std::cout << r;
			positions.push_back(event.mouse.x);
			positions.push_back(event.mouse.y);
			positions.push_back(n);
			positions.push_back(r);
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(black); //czyszczenie okna na zadany kolor

			//Wyznacz œrodek ekranu


			//Obrót figury
			sinfi = sin(fi);
			cosfi = cos(fi);
			for (int i = 0; i < N; i++)
			{
				points[2 * i] = (dx[i] * cosfi - dy[i] * sinfi + 0.5) + xm;
				points[2 * i + 1] = (dx[i] * sinfi + dy[i] * cosfi + 0.5) + ym;
			}
			fi += dfi;

			int xx = 0;
			int yy = 0;

			//rysowanie kwiatków w danym miejscu po klikniêciu myszk¹
			for (int i = 3; i < positions.size(); i += 4)
			{
				xx = positions[i - 3];
				yy = positions[i - 2];

				positions[i] += rfactor;
				if (positions[i] < 30 || positions[i]> 200)
				{
					rfactor *= -1;
				}

				drawflower(positions[i - 1], xx, yy, positions[i], fi);
				al_draw_filled_circle(xx, yy, positions[i], blue);

			}

			//Wyœwietl w oknie to, co narysowano w buforze
			al_flip_display();
		}
	}

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	return 0;
}





//#include <math.h>
//#include <stdio.h>
//#include <vector>
//
//// Do³¹cz definicje biblioteki Allegro
//#include <allegro5/allegro.h>
//#include <allegro5/allegro_primitives.h>
//
//const float FPS = 60;		//obraz bêdzie aktualizowany co 1/FPS sekundy
//const int SCREEN_W = 640;	//szerokoœæ okna
//const int SCREEN_H = 480;	//wysokoœæ okna
//
//void drawflower(int n, float dx, float dy, float r)
//{
//	float x, y;
//	float refactor = 1;
//	for (int i = 0; i < n; i++)
//	{
//		x = (sin(2 * ALLEGRO_PI / n * i) * r) + dx;
//		y = (cos(2 * ALLEGRO_PI / n * i) * r) + dy;
//
//		al_draw_filled_circle(x, y, r, al_map_rgb(255, 255, 0));
//
//		//x += refactor;
//		//y += refactor;
//		//if ((x < 30 && y < 100) || (x>100 && y > 200))
//		//{
//		//	refactor *= -1;
//		//}
//	}
//}
//
//// Funkcja g³ówna
//int main()
//{
//	ALLEGRO_DISPLAY* display = NULL;			//okno
//	ALLEGRO_EVENT_QUEUE* event_queue = NULL;	//kolejka zdarzen	//kolejka zdarzen
//	ALLEGRO_TIMER* timer = NULL;				//timer, od ktorego bêdziemy odbierac zdarzenia (potrzebny do animacji)
//	bool redraw = true;
//
//	if (!al_init()) {							//inicjalizacja biblioteki Allegro
//		fprintf(stderr, "Nie zainicjalizowano allegro!\n");
//		return -1;
//	}
//
//	display = al_create_display(SCREEN_W, SCREEN_H);	//utworznie okna
//	timer = al_create_timer(1.0 / FPS);					//utworzenie timera
//	al_install_keyboard();
//
//	al_register_event_source(event_queue, al_get_mouse_event_source());//inicjalizacja obs³ugi klawiatury
//	event_queue = al_create_event_queue();				//utworzenie kolejki zdarzeñ
//
//	al_init_primitives_addon();							//inicjalizacja obs³ugi prostych elementów (punkty, linie, prostok¹ty, elipsy itd.)
//
//	//Rejestracja ¿róde³ zdarzeñ (okno, timer, klawiatura ...)
//	al_register_event_source(event_queue, al_get_display_event_source(display));
//	al_register_event_source(event_queue, al_get_timer_event_source(timer));
//
//
//
//	//Kolory rysowania
//	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
//	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
//	ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
//	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
//
//	//Definicja wielok¹ta
//	const int N = 7;
//	float dx[N];
//	float dy[N];
//	int xm = SCREEN_W / 2;
//	int ym = SCREEN_H / 2;
//	int refractor = 1;
//
//
//	//Tablice na przetworzone wspó³rzêdna punktów
//	float points[2 * N];
//
//	//Zmienne na potrzeby obracania figury
//	double fi = 0.0, dfi = 0.1, sinfi, cosfi;
//
//	//Uruchamiamy timer, który bêdzie z zadan¹ czêstotliwoœci¹ wysy³a³ zdarzenia
//	al_start_timer(timer);
//	std::vector<int> positions;
//
//	//Pêtla g³ówna programu - obs³uga zdarzeñ.
//	//Dzia³amy, dopóki u¿ytkownik nie wciœnie Esc.
//	while (true)
//	{
//		ALLEGRO_EVENT event;
//		al_wait_for_event(event_queue, &event);
//
//		if (event.type == ALLEGRO_EVENT_TIMER)
//		{	//zdarzenie timera -> odœwie¿enie obrazu 
//			redraw = true;
//		}
//		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
//		{	//zdarzenie klawiatury -> jeœli Esc to koñczymy
//			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
//				break;
//		}
//		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //zdarzenie zamkniêcia okna
//			break;
//		}
//		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
//		{ //zdarzenie zamkniêcia okna
//			positions.push_back(event.mouse.x);
//			positions.push_back(event.mouse.y);
//
//		}
//		if (redraw && al_is_event_queue_empty(event_queue))
//		{
//			redraw = false;
//			al_clear_to_color(black); //czyszczenie okna na zadany kolor
//
//			//Obrót figury
//			sinfi = sin(fi);
//			cosfi = cos(fi);
//			//for (int i = 0; i < N; i++)
//			//{
//			//	points[2 * i] = (dx[i] * cosfi - dy[i] * sinfi + 0.5) + xm;
//			//	points[2 * i + 1] = (dx[i] * sinfi + dy[i] * cosfi + 0.5) + ym;
//			//}
//			//fi += dfi;
//
//			//al_draw_circle(xm, ym, 50, yellow, 2);
//			//al_draw_arc(xm, ym+50, 20, 0 , ALLEGRO_PI, white,2);
//
//			//Narysuj wype³niony wielokat
//			//al_draw_polygon(points, N, 2,white, 2, 2);
//
//			int xx = 0;
//			int yy = 0;
//
//			for (int i = 3; i < positions.size(); i += 4)
//			{
//				xx = positions[i - 3];
//				yy = positions[i - 2];
//
//				drawflower(positions[i - 1], xx, yy, positions[i]);
//				al_draw_filled_circle(xx, yy, positions[i], white);
//
//			}
//
//			//Wyœwietl w oknie to, co narysowano w buforze
//			al_flip_display();
//
//		}
//	}
//
//	al_destroy_display(display);
//	al_destroy_timer(timer);
//	al_destroy_event_queue(event_queue);
//	return 0;
//}
