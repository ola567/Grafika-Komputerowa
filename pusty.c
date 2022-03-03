
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int red, green, blue, yellow,grey;
unsigned long foreground, background;


//*************************************************************************************************************************
//funkcja przydzielania kolorow

int AllocNamedColor(char *name, Display* display, Colormap colormap)
  {
    XColor col;
    XParseColor(display, colormap, name, &col);
    XAllocColor(display, colormap, &col);
    return col.pixel;
  } 

//*************************************************************************************************************************
// inicjalizacja zmiennych globalnych okreslajacych kolory

int init_colors(Display* display, int screen_no, Colormap colormap)
{
  background = WhitePixel(display, screen_no);  //niech tlo bedzie biale
  foreground = BlackPixel(display, screen_no);  //niech ekran bedzie czarny
  red=AllocNamedColor("red", display, colormap);
  green=AllocNamedColor("green", display, colormap);
  blue=AllocNamedColor("blue", display, colormap);
  yellow=AllocNamedColor("yellow", display, colormap);
  grey=AllocNamedColor("grey", display, colormap);
}

//*************************************************************************************************************************
// Glowna funkcja zawierajaca petle obslugujaca zdarzenia */

int main(int argc, char *argv[])
{
  char            icon_name[] = "Grafika";
  char            title[]     = "Grafika komputerowa";
  Display*        display;    //gdzie bedziemy wysylac dane (do jakiego X servera)
  Window          window;     //nasze okno, gdzie bedziemy dokonywac roznych operacji
  GC              gc;         //tu znajduja sie informacje o parametrach graficznych
  XEvent          event;      //gdzie bedziemy zapisywac pojawiajace sie zdarzenia
  KeySym          key;        //informacja o stanie klawiatury 
  Colormap        colormap;
  int             screen_no;
  XSizeHints      info;       //informacje typu rozmiar i polozenie ok
  
  char            buffer[8];  //gdzie bedziemy zapamietywac znaki z klawiatury
  int             hm_keys;    //licznik klawiszy
  int             to_end;

  display    = XOpenDisplay("");                //otworz polaczenie z X serverem pobierz dane od zmiennej srodowiskowej DISPLAY ("")
  screen_no  = DefaultScreen(display);          //pobierz domyslny ekran dla tego wyswietlacza (0)
  colormap = XDefaultColormap(display, screen_no);
  init_colors(display, screen_no, colormap);

  //okresl rozmiar i polozenie okna
  info.x = 100;
  info.y = 150;
  info.width = 500;
  info.height = 300;
  info.flags = PPosition | PSize;

  XPoint tarczaA[]={{50,50},{450,50},{450,250},{50,250},{50,50}};
  XPoint literaAa[]={{140,60},{160,60},{180,160},{160,160},{150,110},{140,160},{120,160},{140,60}};
  XPoint literaA1[]={{140,60},{135,55},{165,55},{160,60},{140,60}};
  XPoint literaA2[]={{120,160},{115,165},{145,165},{140,160},{120,160}};
  XPoint literaAb[]={{140,130},{160,130},{160,140},{140,140},{140,130}};
  XPoint literaA3[]={{180,160},{185,165},{155,165},{160,160},{180,160}};
  XPoint literaH[]={{310,60},{315,55},{285,55},{290,60},{290,160},{285,165},{315,165},{310,160},{310,60}};
  XPoint literaHa[]={{350,60},{355,55},{325,55},{330,60},{330,160},{325,165},{355,165},{350,160},{350,60}};
  XPoint literaHb[]={{310,110},{330,110},{330,120},{310,120},{310,110}};

  XPoint obwodka[]={{48,48},{452,48},{452,252},{48,252},{48,48}};
  XPoint obwodkaH[]={{313,60},{318,52},{282,52},{287,60},{287,160},{282,168},{318,168},{313,160},{313,60}};
  XPoint obwodkaHa[]={{353,60},{358,52},{322,52},{328,60},{328,160},{322,168},{322,168},{353,160},{353,60}};
  XPoint obwodkaHb[]={{310,107},{330,107},{330,123},{310,123},{310,107}};

  //majac wyswietlacz, stworz okno - domyslny uchwyt okna
  window = XCreateSimpleWindow(display, DefaultRootWindow(display),info.x, info.y, info.width, info.height, 7/* grubosc ramki */, foreground, background);
  XSetStandardProperties(display, window, title, icon_name, None, argv, argc, &info);
  //utworz kontekst graficzny do zarzadzania parametrami graficznymi (0,0) domyslne wartosci
  gc = XCreateGC(display, window, 0, 0);
  XSetBackground(display, gc, background);
  XSetForeground(display, gc, foreground);

  //okresl zdarzenia jakie nas interesuja, np. nacisniecie klawisza
  XSelectInput(display, window, (KeyPressMask | ExposureMask | ButtonPressMask| ButtonReleaseMask | Button1MotionMask));
  XMapRaised(display, window);  //wyswietl nasze okno na samym wierzchu wszystkich okien
      
  to_end = FALSE;

 /* petla najpierw sprawdza, czy warunek jest spelniony
     i jesli tak, to nastepuje przetwarzanie petli
     a jesli nie, to wyjscie z petli, bez jej przetwarzania */
  while (to_end == FALSE)
  {
    XNextEvent(display, &event);  // czekaj na zdarzenia okreslone wczesniej przez funkcje XSelectInput

    switch(event.type)
    {
      case Expose:
        if (event.xexpose.count == 0)
        {
           XSetForeground(display,gc,foreground);
		   XFillPolygon(display, window, gc, obwodka, 5, 0, 0);
           XSetForeground(display,gc,grey);
		   XFillPolygon(display, window, gc, tarczaA, 5, 0, 0);
           XSetForeground(display,gc,foreground);
           XFillArc(display,window, gc, 48,228,404,44,180*64,180*64);
           XSetForeground(display,gc,grey);
           XFillArc(display,window, gc, 50,230,400,40,180*64,180*64);
           XSetForeground(display,gc,foreground);
           XFillArc(display,window, gc, 48,27,404,44,180*64,-180*64);
           XSetForeground(display,gc,grey);
           XFillArc(display,window, gc, 50,29,400,40,180*64,360*64);

		   XSetForeground(display,gc,blue);
		   XFillPolygon(display, window, gc, literaAa, 8, 0, 0);
           XSetForeground(display,gc,blue);
		   XFillPolygon(display, window, gc, literaAb, 5, 0, 0);
           XSetForeground(display,gc,blue);
		   XFillPolygon(display, window, gc, literaA1, 5, 0, 0);
           XSetForeground(display,gc,blue);
		   XFillPolygon(display, window, gc, literaA2, 5, 0, 0);
           XSetForeground(display,gc,blue);
		   XFillPolygon(display, window, gc, literaA3, 5, 0, 0);
           XSetForeground(display,gc,green);

           XSetForeground(display,gc,foreground);
		   XFillPolygon(display, window, gc, obwodkaH, 9, 0, 0);
		   XSetForeground(display,gc,green);
		   XFillPolygon(display, window, gc, literaH, 9, 0, 0);
		 
		   XSetForeground(display,gc,foreground);
		   XFillPolygon(display, window, gc, obwodkaHa, 9, 0, 0);
		   XSetForeground(display,gc,green);
		   XFillPolygon(display, window, gc, literaHa, 9, 0, 0);
			
		   XSetForeground(display,gc,foreground);
		   XFillPolygon(display, window, gc, obwodkaHb, 5, 0, 0);
           XSetForeground(display,gc,green);
		   XFillPolygon(display, window, gc, literaHb, 5, 0, 0);
		   
        }
        break;

      case MappingNotify:
        XRefreshKeyboardMapping(&event.xmapping); // zmiana ukladu klawiatury - w celu zabezpieczenia sie przed taka zmiana trzeba to wykonac
        break;

      case ButtonPress:
        if (event.xbutton.button == Button1)  // sprawdzenie czy wcisnieto lewy przycisk		
        {
   		              
    
        }
        break;


      case KeyPress:
        hm_keys = XLookupString(&event.xkey, buffer, 8, &key, 0);
        if (hm_keys == 1)
        {
          if (buffer[0] == 'q') to_end = TRUE;        // koniec programu
          
        }

      default:
        break;
    }
  }

  XFreeGC(display, gc);
  XDestroyWindow(display, window);
  XCloseDisplay(display);

  return 0;
}
