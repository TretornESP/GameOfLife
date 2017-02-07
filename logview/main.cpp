#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[]) {
  system("title LOG VIEWER");
  int MALLA, SEMILLA, resets;
  int seed=atoi(argv[3]);
  float segundos;
  char cursor;
  int contador=0;
  int intentos_total=0;
  float segundos_total=0;
  double intentos_percent=0;
  float intentos_segundo=0;
  float intentos_media=0;
  float segundos_media=0;

  FILE * log;
  if (!strcmp(argv[1], "-v")){
    while(1==1) {
      Sleep(10);
      system("cls");
      log = fopen(argv[2], "r");
      if (log==NULL) {printf("FILE NOT FOUND %s", argv[2]); system("pause"); exit(1);}
      while(feof(log)==0){
        cursor = fgetc(log);
        if (cursor=='#') {
          fscanf(log," MALLA: %d SEMILLA: %d INTENTOS: %d @ %gS\n", &MALLA, &SEMILLA, &resets, &segundos);
          printf("MALLA: %d SEMILLA: %d INTENTOS: %d @ %gS\n", MALLA, SEMILLA, resets, segundos);
        }
      }
      fclose(log);
    }
  } else if (!strcmp(argv[1], "-c")) {
    log = fopen("log.txt", "r");
    if (log==NULL) {printf("FILE NOT FOUND %s", argv[2]); system("pause"); exit(1);}
    while (feof(log)==0) {
      cursor = fgetc(log);
      if (cursor=='#') {
        fscanf(log," MALLA: %d SEMILLA: %d INTENTOS: %d @ %gS\n", &MALLA, &SEMILLA, &resets, &segundos);
        if (seed==SEMILLA) {
          contador++;
          intentos_total=intentos_total+resets;
          segundos_total=segundos_total+segundos;
          intentos_segundo=intentos_segundo+(resets/segundos);
        }
      }
    }
    fclose(log);
    intentos_media=intentos_total/contador;
    segundos_media=segundos_total/contador;
    intentos_percent=contador*100;
    intentos_percent=intentos_percent/intentos_total;
    printf("+-------------------------------------------------------------------------+\n");
    printf("CONFIGURACION, SEMILLA: %d\n", seed);
    printf("TIEMPO DE EJECUCION %10g MUESTRAS OBTENIDAS: %10d @ %g INTENTOS/SEGUNDO\n", segundos_total, intentos_total, intentos_segundo);
    printf("+-------------------------------------------------------------------------+\n");
    printf("INTENTOS EXITOSOS: %d\n", contador);
    printf("MEDIA INTENTOS/EXITO: %g\n", intentos_media);
    printf("MEDIA SEGUNDOS/EXITO: %g\n", segundos_media);
    printf("PORCENTAJE EXITO: %lf\n", intentos_percent);
    printf("+-------------------------------------------------------------------------+\n");
    system("pause");
  } else {
    printf("USAGE: logview.exe [MODE] [FILE] [SEED]\n");
    printf("MODES: -v (MONITOR LOG FILE)\n");
    printf("       -c (COMPUTE LOG FILE)\n");
    printf("SEED: seed to compute\n");
    exit(1);
  }
}
