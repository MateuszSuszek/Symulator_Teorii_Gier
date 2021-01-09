#include <stdio.h>

void WriteBoard(int brd[], int colNum, int colHgt){

  for(int i = colHgt-1; i >= 0; i--){
    for(int j = 0; j < colNum; j++){
      if(brd[j] >= i){
        printf("o ");
      }else{
        printf("  ");
      }
    }
    printf("\n");
  }


  /*for(int i = 0; i < colNum; i++){
    printf("%d ", brd[i]);
  }*/

  printf("\n");
}

int PlayNim(int isAI, int colNum, int colHgt){

  //printf("%d\n%d\n%d\n", isAI, colNum, colHgt);

  // Initialize game

  int brd[colNum];

  for(int i = 0; i < colNum; i++){
    brd[i] = colHgt;
  }

  printf("\n");

  WriteBoard(brd, colNum, colHgt);

  //

  int gameEnd = 0;

  while(!gameEnd){
    int o = 0, w = 0;
    printf("Ile oczek z której wieży chcesz zebrać?\n");
    scanf("%d %d", &o, &w);
    while((o != 1 && o != 2) || w < 0 || w >= colNum || brd[w]-o < 0){
      printf("Niepoprawne dane\n");
      WriteBoard(brd, colNum, colHgt);
      scanf("%d %d", &o, &w);
    }

    brd[w] -= o;

    WriteBoard(brd, colNum, colHgt);

  }


  return 0;
}
