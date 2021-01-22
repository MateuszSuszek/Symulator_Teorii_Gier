#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a, b) (a > b ? a : b)

void WriteBoard(int brd[], int colNum, int maks);
bool GameEnd(int brd[], int colNum); // Gra zakończy się, kiedy zebrany zostanie ostatni kamień
int FindMax(int brd[], int colNum); // Wyszukuję najwyższy stos, przydatne przy wypisywaniu
void InitializeBoard(int brd[], int colNum, int colHgt);
void PlayerMove(int brd[], int colNum);
void AIMove(int brd[], int colNum);

int PlayNim(bool isAI, int colNum, int colHgt){ // colHgt - min. wysokość stosu

  int brd[colNum];
  InitializeBoard(brd, colNum, colHgt);

  WriteBoard(brd, colNum, FindMax(brd, colNum));

  while(true){

    if(!isAI){
      PlayerMove(brd, colNum);
    }else{
      AIMove(brd, colNum);
    }

    WriteBoard(brd, colNum, FindMax(brd, colNum));

    if(GameEnd(brd, colNum)){
      break;
    }

    isAI = !isAI;
  }

  if(isAI){
    printf("Wygrał komputer!\n");
  }else{
    printf("Wygrał gracz!\n");
  }
  return 0;
}

void InitializeBoard(int brd[], int colNum, int colHgt){

  bool ht[50];
  int h = 0;

  for(int i = 0; i < colNum; i++){
    ht[i] = 0;
  }

  for(int i = 0; i < colNum; i++){

    do{
      int r = rand()%((colNum + colHgt)*5/4);  // Dla każdego stosu losuję
      h = max(colHgt, r);                     // jego wysokość w pewnym przedziale

    }while(ht[h] != 0);                     // Wysokość nie może się powtórzyć

    ht[h] = 1;
    brd[i] = h;
  }
}

int FindMax(int brd[], int colNum){
  int maks = 0;
  for(int i = 0; i < colNum; i++){
    maks = max(maks, brd[i]);
  }
  return maks;
}

bool GameEnd(int brd[], int colNum){
  for(int i = 0; i < colNum; i++){
    if(brd[i] > 0){
      return false;
    }
  }
  return true;
}

void WriteBoard(int brd[], int colNum, int maks){ // Tymczasowe rozwiązanie
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

  printf("\n");
}

void PlayerMove(int brd[], int colNum){
  int o = 0, w = 0;
  printf("Ile oczek z której wieży chcesz zebrać?\n");
  scanf("%d %d", &o, &w);
  while(w <= 0 || w > colNum || brd[w-1]-o < 0){
    WriteBoard(brd, colNum, FindMax(brd, colNum));
    printf("Niepoprawne dane\n");
    printf("Ile oczek z której wieży chcesz zebrać?\n");
    scanf("%d %d", &o, &w);
  }
  brd[w-1] -= o;
}

void AIMove(int brd[], int colNum){

  int g = 0;
  for(int i = 0; i < colNum; i++){
    g ^= brd[i];
  }
  if(g == 0){
    for(int i = 0; i < colNum; i++){
      if(brd[i] > 0){
        brd[i]--;
        break;
      }
    }
  }else{
    for(int i = 0; i < colNum; i++){ // a ^ a = 0 i a ^ 0 = a, zatem (a ^ b) ^ b = a
      int xor = g ^ brd[i];         // xor to wartość gry poza rozważanym stosem
      if(brd[i] > 0){
        if(xor == 0){
          brd[i] = 0;
          return;
        }else{
          for(int j = 1; j < brd[i]; j++){
            if((xor ^ j) == 0){
              brd[i] = j;
              return;
            }
          }
        }
      }
    }
  }
}
