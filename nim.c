#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a, b) (a > b ? a : b)

void WriteBoard(int brd[], int colNum, int maks){
  printf("\n");
  for(int i = maks; i >= 1; i--){
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

bool GameEnd(int brd[], int colNum){
  for(int i = 0; i < colNum; i++){
    if(brd[i] > 0){
      return false;
    }
  }
  return true;
}

int ZnajdzMaks(int brd[], int colNum){
  int maks = 0;
  for(int i = 0; i < colNum; i++){
    maks = max(maks, brd[i]);
  }
  return maks;
}

int PlayNim(int isAI, int colNum, int colHgt){

  //printf("%d\n%d\n%d\n", isAI, colNum, colHgt);

  // Initialize game

  int brd[colNum];
  bool ht[50];
  int h = 0;
  int najwyzsza = (colNum + colHgt)*3/2;
  int maks = 0;

  for(int i = 0; i < najwyzsza; i++){
    ht[i] = 0;
  }

  for(int i = 0; i < colNum; i++){

    do{
    int r = rand()%najwyzsza;
    h = max(colHgt, r);

    }while(ht[h] != 0);

    ht[h] = 1;
    brd[i] = h;
    maks = max(maks, h);
  }

  printf("\n");

  WriteBoard(brd, colNum, maks);

  //

  while(true){
    int o = 0, w = 0;
    printf("Ile oczek z której wieży chcesz zebrać?\n");
    scanf("%d %d", &o, &w);
    while(w <= 0 || w > colNum || brd[w-1]-o < 0){
      printf("Niepoprawne dane\n");
      //WriteBoard(brd, colNum, maks);
      scanf("%d %d", &o, &w);
    }
    brd[w-1] -= o;

    maks = ZnajdzMaks(brd, colNum);

    WriteBoard(brd, colNum, maks);

    if(GameEnd(brd, colNum)){
      printf("Koniec!\n");
      break;
    }

  }


  return 0;
}
