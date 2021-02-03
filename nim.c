#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>


#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define offset_x 20
#define offset_y 20

bool GameEnd(int brd[], int colNum); // Gra zakończy się, kiedy zebrany zostanie ostatni kamień
void InitializeBoard(int brd[], int colNum, int colHgt);
void PlayerMove(int brd[], int colNum);
void AIMove(int brd[], int colNum);
void DisplayBoard(int brd[], int colNum);
void ColourMarked(int brd[], int colNum, int x, int y, int colour_id);
bool IsWinningPosition(int brd[], int colNum);

int PlayNim(bool isAI, int colNum, int colHgt){ // colHgt - min. wysokość stosu

  initscr();
  cbreak();
  start_color();
  init_pair(1, COLOR_WHITE, 0);  // Domyślny kolor
  init_pair(2, COLOR_RED, 0);   // Kolor zaznaczenia 1
  init_pair(3, COLOR_BLUE, 0); // Kolor zaznaczenia 2
  curs_set(0);
  refresh();

  int brd[colNum];

  do{
    InitializeBoard(brd, colNum, colHgt);
  }while(!isAI && !IsWinningPosition(brd, colNum));

  while(true){

    DisplayBoard(brd, colNum);

    if(!isAI){
      PlayerMove(brd, colNum);
    }else{
      AIMove(brd, colNum);
    }

    if(GameEnd(brd, colNum)){
      break;
    }

    isAI = !isAI;
  }
  clear();
  if(isAI){
    mvprintw(offset_y, offset_x, "The AI won!");
  }else{
    mvprintw(offset_y, offset_x, "The Player won!");
  }
  getch();
  curs_set(1);
  clear();
  endwin();

  return 0;
}

void InitializeBoard(int brd[], int colNum, int colHgt){

  bool ht[50];
  int h = 0;
  int upperbound = colNum + colHgt + 1;
  srand(time(0));

  for(int i = 0; i < colNum; i++){
    ht[i] = 0;
  }

  for(int i = 0; i < colNum; i++){
    int stop = 0;
    do{
      stop++;
      if(stop > 1000){
        stop = 0;
        upperbound++;
      }
      int r = rand()%upperbound;
      h = max(colHgt, r);
    }while(ht[h] != 0);

    ht[h] = 1;
    brd[i] = h;
  }
}

void DisplayBoard(int brd[], int colNum){
  clear();
  move(offset_x, offset_y);
  for(int i = 0; i < colNum; i++){
    for(int j = 0; j < brd[i]; j++){
      attron(COLOR_PAIR(1));
      mvprintw(offset_x - j, offset_y + 2*i, "%c", 'o');
      attroff(COLOR_PAIR(1));
    }
  }
  /*for(int i = 0; i < colNum; i++){
    mvprintw(offset_x + 2, offset_y + 2*i, "%d", brd[i]);
  }*/
  refresh();
}

bool GameEnd(int brd[], int colNum){
  for(int i = 0; i < colNum; i++){
    if(brd[i] > 0){
      return false;
    }
  }
  return true;
}

void ColourMarked(int brd[], int colNum, int x, int y, int colour_id){

  attron(COLOR_PAIR(colour_id));

  for(int i = x; i < brd[y]; i++){
    mvprintw(offset_x - i, offset_y + 2*y, "%c", 'o');
  }
  //mvprintw(offset_x + 1, offset_y, "x:%d y:%d", x, y);

  attroff(COLOR_PAIR(colour_id));

}

void PlayerMove(int brd[], int colNum){
  char input;
  int x = brd[0]-1;
  int y = 0;


  if(brd[y] == 0){
    for(int i = 0; i < colNum; i++){
      if(brd[i] != 0){
        y = i;
        x = brd[y] - 1;
        break;
      }
    }
  }

  while(input != '\n'){

    attron(COLOR_PAIR(1));
    DisplayBoard(brd, colNum);
    attroff(COLOR_PAIR(1));

    ColourMarked(brd, colNum, x, y, 2);
    input = getch();
    //mvprintw(offset_x + 1, offset_y, "%c", input);
    if(input == 'w'){
      x = min(x+1, brd[y]-1);
    }else if(input == 's'){
      x = max(x-1, 0);
    }else if(input == 'a'){
      for(int i = y-1; i >= 0; i--){
        if(brd[i] != 0){
          y = i;
          x = brd[y]-1;
          break;
        }
      }
    }else if(input == 'd'){
      for(int i = y+1; i < colNum; i++){
        if(brd[i] != 0){
          y = i;
          x = brd[y]-1;
          break;
        }
      }
    }
  }

  brd[y] = x;

}

void AIMove(int brd[], int colNum){

  int g = 0;
  for(int i = 0; i < colNum; i++){
    g ^= brd[i];
  }
  if(g == 0){
    for(int i = 0; i < colNum; i++){
      if(brd[i] > 0){
        ColourMarked(brd, colNum, brd[i]-1, i, 3);
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
          ColourMarked(brd, colNum, 0, i, 3);
          return;
        }else{
          for(int j = 1; j < brd[i]; j++){
            if((xor ^ j) == 0){
              brd[i] = j;
              ColourMarked(brd, colNum, j, i, 3);
              return;
            }
          }
        }
      }
    }
  }
}

bool IsWinningPosition(int brd[], int colNum){
  int xor = 0;

  for(int i = 0; i < colNum; i++){
    xor ^= brd[i];
  }

  return xor != 0;
}
