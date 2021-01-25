#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>


#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define offset_x 12
#define offset_y 12

bool GameEnd(int brd[], int colNum); // Gra zakończy się, kiedy zebrany zostanie ostatni kamień
void InitializeBoard(int brd[], int colNum, int colHgt);
void PlayerMove(int brd[], int colNum);
void AIMove(int brd[], int colNum);
void DisplayBoard(int brd[], int colNum);
void ColourMarked(int brd[], int colNum, int x, int y, int colour_id);

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
  InitializeBoard(brd, colNum, colHgt);


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

  srand(time(0));

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

  while(input != '\n'){

    while(brd[y] == 0){
      y++;
      x = brd[y]-1;
    }


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
      if(y > 0){
        y--;
        x = brd[y]-1;
      }
    }else if(input == 'd'){
      if(y < colNum-1){
        y++;
        x = brd[y]-1;
      }
    }
  }

  ColourMarked(brd, colNum, 0, 0, 3);

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
