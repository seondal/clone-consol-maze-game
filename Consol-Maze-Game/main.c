#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

#define SIZE 19

//기본 좌표값 설정
#define XP 40
#define YP 5

void PrintMazeGame();
void LoadMaze(char num);
void GotoXY(int x, int y);

int main(void){
    
    setlocale(LC_ALL, "");
    initscr();
    char level;
    GotoXY(XP, YP-3);
    printw("미로 찾기 게임\n");
    refresh();
    printw("난이도를 선택하세요 (1,2,3)");
    refresh();
    level = getchar();
    
    printw("\n");
    LoadMaze(level);
    
    while (1) {
        
    }
    
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            printw("%c ", maze[i][j]);
        }
        printw("\n");
    }
    refresh();
    
    addstr("\npress any key to exit...");
    refresh();
    getch();
    endwin();
    
    return 0;
}

char maze[SIZE][SIZE]; //미로 구성

//num 이라는 난이도 변수를 받는 함수
void LoadMaze(char num){
    
//    char path[300] = "/Users/guest1/Desktop/seondal/Consol-Maze-Game/Consol-Maze-Game/Maze";
    
    //난이도 변수, 확장자 합치기
//    strcat(path, &num);
//    strcat(path, ".txt");
    
    char path[300];

    if(num == '1'){
        strcpy(path, "/Users/guest1/Desktop/seondal/Consol-Maze-Game/Consol-Maze-Game/Maze1.txt");
    }
    else if(num == '2'){
        strcpy(path, "/Users/guest1/Desktop/seondal/Consol-Maze-Game/Consol-Maze-Game/Maze2.txt");
    }
    else if(num == '3'){
        strcpy(path, "/Users/guest1/Desktop/seondal/Consol-Maze-Game/Consol-Maze-Game/Maze3.txt");
    }
    
    //파일불러오기
    char str_tmp[50] = { 0, };

    FILE* f = fopen(path, "r"); //r(읽기모드)로 파일을 열고 파일포인터를 리턴받음

    for(int i=0;i < SIZE; i++){
        fgets(str_tmp, 49, f); //한줄의 데이터 가져오기
        char* ptr = strtok(str_tmp, "\t"); //탭(t)으로 문자열 분리해서 미로에 저장

        for(int j=0; j<SIZE; j++){
            maze[i][j] = *ptr;
            ptr = strtok(NULL, "\t");
        }
    }

    fclose(f);
}

void GotoXY(int x, int y){
    move(y,x);
}

void PrintMazeGame () {
    for(int i=0; i<SIZE; i++){
        GotoXY(XP, YP+1);
        for(int j=0; j<SIZE; j++){
            if(maze[i][j]=='1')
                printw("■");
            else if(maze[i][j] == 'y')
                printw("★");
            else if(maze[i][j] == '0')
                printw("□");
            else
                printw("·");
        }
        refresh();
    }
}//콘솔창에 미로그리기





