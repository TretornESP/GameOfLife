#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <assert.h>

int randint(int n);
void imprimir(int resets, clock_t tINICIO, int TAMANO, int SEMILLA);

int main()
{

  system("title SIMULACION ESTADISTICA JUEGO DE LA VIDA");
  int TAMANO;
  int SEMILLA;
  char cmdbuff[256];
  char FILENAME[] ="log.txt";

  printf("TAMAÑO DE CADA EJE: ");
  scanf("%d", &TAMANO);
  printf("SEMILLA: ");
  scanf("%d", &SEMILLA);
  system("cls");

  int MAP_SIZE_X=TAMANO+2;
  int MAP_SIZE_Y=MAP_SIZE_X;

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  CONSOLE_CURSOR_INFO cinfo;
  WORD saved_attributes;

  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes;

  _COORD coord;
  coord.X = 0;
  coord.Y = 0;

  _SMALL_RECT Rect;
  Rect.Top = 0;
  Rect.Left = 0;
  Rect.Bottom = MAP_SIZE_X-3;
  Rect.Right = MAP_SIZE_Y*2-5;

  cinfo.dwSize = 100;
  cinfo.bVisible = false;

  SetConsoleCursorInfo(hConsole, &cinfo);

  ShowCursor(false);

  SetConsoleScreenBufferSize(hConsole, coord);
  SetConsoleWindowInfo(hConsole, TRUE, &Rect);

  bool igual;
  int contador = 0;
  int vivas = 0;
  int generaciones;
  int resets=0;
  clock_t tINICIO;
  tINICIO = clock();

  snprintf(cmdbuff, sizeof(cmdbuff), "start .\\logview.exe -v %s", FILENAME);

  system(cmdbuff);

  restart:

  generaciones=0;

  srand(time(NULL));

  bool universo[MAP_SIZE_X][MAP_SIZE_Y];
  bool universo2[MAP_SIZE_X][MAP_SIZE_Y];

  for (int i = 0; i < MAP_SIZE_X; i++) {
    for (int j = 0; j < MAP_SIZE_Y; j++) {
        universo[i][j]=0;
        universo2[i][j]=0;
    }
  }

  igual=true;

  vivas = randint(MAP_SIZE_X*SEMILLA);
  while (contador < vivas) {
    universo[randint(MAP_SIZE_X-2)][randint(MAP_SIZE_Y-2)]=1;
    contador++;
  }

  contador=0;
  vivas=0;

  system("cls");

  while (true) {
    if (GetAsyncKeyState(VK_SPACE)) {snprintf(cmdbuff, sizeof(cmdbuff), "start .\\logview.exe -c %s %d", FILENAME, SEMILLA); system(cmdbuff);}
    if (GetAsyncKeyState(VK_ESCAPE)) {imprimir(resets, tINICIO, TAMANO, SEMILLA);}
    if (generaciones==100) {imprimir(resets, tINICIO, TAMANO, SEMILLA); tINICIO = clock(); resets=0; goto restart;}
    for (int i = 1; i < MAP_SIZE_X-1; i++) {
      for (int j = 1; j < MAP_SIZE_Y-1; j++) {
        if (universo[i-1][j-1]==1) {vivas++;}
        if (universo[i][j-1]==1) {vivas++;}
        if (universo[i+1][j-1]==1) {vivas++;}
        if (universo[i-1][j]==1) {vivas++;}
        if (universo[i+1][j]==1) {vivas++;}
        if (universo[i-1][j+1]==1) {vivas++;}
        if (universo[i][j+1]==1) {vivas++;}
        if (universo[i+1][j+1]==1) {vivas++;}

        if (universo[i][j]==0) {
          SetConsoleTextAttribute(hConsole, 255 | 255 | 255);
          if (vivas==3) {
            universo[i][j]=1;
          }
        } else if (universo[i][j]==1) {
          SetConsoleTextAttribute(hConsole, 32);
          if (vivas!=2 && vivas!=3) {
            universo[i][j]=0;
          }
        }
        vivas=0;
        printf("  ");
      }
      printf("\n");
    }
    for (int i = 1; i < MAP_SIZE_X-1; i++) {
      for (int j = 1; j < MAP_SIZE_Y-1; j++) {
        if (universo2[i][j]!=universo[i][j]) {igual=false;}
      }
    }
    if (igual==true) {resets++; goto restart;} else {generaciones++;}
    for (int i = 1; i < MAP_SIZE_X-1; i++) {
      for (int j = 1; j < MAP_SIZE_Y-1; j++) {
        universo2[i][j]=universo[i][j];
      }
    }
    igual=true;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coord);
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("%2d",generaciones);
  }
}

int randint(int n)
{
    if ((n - 1) == RAND_MAX) {
        return rand();
    } else {
        // Chop off all of the values that would cause skew...
    long end = RAND_MAX / n; // truncate skew
    assert (end > 0L);
    end *= n;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}

void imprimir(int resets, clock_t tINICIO, int TAMANO, int SEMILLA) {
  clock_t tFIN = clock();
  double segundos = (double)(tFIN - tINICIO) / CLOCKS_PER_SEC;
  FILE * database;
  database = fopen ( "log.txt", "a");
  fprintf(database,"# MALLA: %d SEMILLA: %d INTENTOS: %d @ %.16gS\n", (TAMANO*TAMANO), SEMILLA, resets, segundos);
  fclose(database);
}
