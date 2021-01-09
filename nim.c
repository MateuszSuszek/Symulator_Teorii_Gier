#include <stdio.h>

int PlayNim(int isAI, int colNum, int colHgt){

  //printf("%d\n%d\n%d\n", isAI, colNum, colHgt);

  int brd[10][20];

  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 20; j++){
      brd[i][j] = 0;
    }
  }

  for(int i = 0; i < colNum; i++){
    for(int j = 0; j < colHgt, j++){
      brd[i][j] = 1;
    }
  }

  

  return 0;
}
