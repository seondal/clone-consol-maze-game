#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>


#define SIZE 19
//기본 좌표값 설정
#define XP 40
#define YP 5

//키 받아오기
#define LEFT 68
#define RIGHT 67
#define UP 65
#define DOWN 66
#define ARROW 27
#define ARROW2 91

void PrintMazeGame ();
void LoadMaze(char num);
void GotoXY(int x, int y);
char maze[SIZE][SIZE]; //미로 구성
void MoveMaze(int *row, int *col);
int IsBlock(int i, int j);
int IsFinish(int i, int j);

int main(void)
{
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);

    char level;
    GotoXY(XP, YP-3);
    printw("미로 찾기 게임\n");
    refresh();

    GotoXY(XP, YP - 2);
    printw("난이도를 선택하세요 (1,2,3)");
    refresh();
    level = getchar();

    LoadMaze(level);

    int row = 2, col = 1; //시작위치 초기화 (3행2열)
    
    while (1)
    {
        PrintMazeGame();
        MoveMaze(&row, &col);
    }

    addstr("\npress any key to exit...");
    refresh();
    getch();
    endwin();
}

void MoveMaze(int *row, int *col)
{
    if(getchar() == ARROW && getchar() == ARROW2)
    {
        int nkey = getchar();
        switch(nkey)
        {
            case UP:
                if(!(IsBlock(*row-1, *col)))
                {
                    maze[*row][*col] = '0'; //플레이어가 있던 곳을 길로 변경
                    maze[*row-1][*col] = 'x';   //변경된 위치를 플레이어로 변경
                    *row -= 1;  //값을 변경
                }
                else if (IsFinish(*row-1, *col))
                {
                    exit(0);    //임시강제종료 (stlib.h)
                }
                break;
                
            case DOWN:
                if (!(IsBlock(*row + 1, *col)))
                            {
                                maze[*row][*col] = '0';
                                maze[*row + 1][*col] = 'x';
                                *row += 1;
                            }
                            else if (IsFinish(*row + 1, *col))
                            {
                                exit(0);
                            }
                            break;
                
            case RIGHT:
                if (!(IsBlock(*row, *col + 1)))
                            {
                                maze[*row][*col] = '0';
                                maze[*row][*col + 1] = 'x';
                                *col += 1;
                            }
                            else if (IsFinish(*row, *col + 1))
                            {
                                exit(0);
                            }
                            break;
                
            case LEFT:
                if (!(IsBlock(*row, *col - 1)))
                            {
                                maze[*row][*col] = '0';
                                maze[*row][*col - 1] = 'x';
                                *col -= 1;
                            }
                            else if (IsFinish(*row, *col - 1))
                            {
                                exit(0);
                            }
                            break;
        }
        refresh();
    }
}

int IsBlock(int i, int j)
{
    if(maze[i][j] == '1' || maze[i][j] == 'y')
        return 1;
    else
        return 0;
}

int IsFinish(int i, int j)
{
    if(maze[i][j] == 'y')
        return 1;
    else
        return 0;
}

void PrintMazeGame () //콘솔창에 미로 그리기
{
    for(int i=0; i<SIZE; i++)
    {
        GotoXY(XP, YP + i);
        for(int j=0; j<SIZE; j++)
        {
            if (maze[i][j]=='1')
                printw("■");
            else if (maze[i][j] == 'y')
                printw("★");
            else if (maze[i][j] == '0')
                printw("□");
            else
                printw("●");
        }
        refresh();
    }
}


void LoadMaze(char num)//num 이라는 난이도 변수를 받는 함수
{
    
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
    if (f == NULL){
        printw("NULL");
        printw("\n%s\n",path);
        refresh();
    }
    
    for (int i=0;i < SIZE; i++)
    {
        fgets(str_tmp, 50, f); //한줄의 데이터 가져오기
        char* ptr = strtok(str_tmp, "\t"); //탭(t)으로 문자열 분리해서 미로에 저장
        for(int j=0; j<SIZE; j++)
        {
            maze[i][j] = *ptr;
            ptr = strtok(NULL, "\t");
        }
    }
    fclose(f);
}


void GotoXY(int x, int y)
{
    move(y,x);
}
