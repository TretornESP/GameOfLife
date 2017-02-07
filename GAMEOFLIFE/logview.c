#include <stdio.h>
#include <stdlib.h>

int main() {
  int MALLA, SEMILLA, resets, segundos;
  FILE * log;
  while(1==1) {
    log = fopen("log.txt", "r");
    if (log==NULL) {exit(1);}
    while(feof(log)==0){
      fscanf(log,"MALLA: %d SEMILLA: %d INTENTOS: %d @ %.16g\n", &MALLA, &SEMILLA, &resets, &segundos);
      printf(log,"MALLA: %d SEMILLA: %d INTENTOS: %d @ %.16g\n", MALLA, SEMILLA, resets, segundos);
    }
    fclose(log);
  }
}
