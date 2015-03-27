#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

//	following transitions occur:
//	Any live cell with fewer than two live neighbours dies, as if caused by under-population.
//	Any live cell with two or three live neighbours lives on to the next generation.
//	Any live cell with more than three live neighbours dies, as if by overcrowding.
//	Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
//
//	created by Tekami on 2013.06.21

#define HEIGHT 40
#define WIDTH 41

#define FALSE 0
#define TRUE 1

#define DEAD 10
#define LIVE 11
#define WALL 12

typedef struct Cell_{
	int state;
	int neighbor;
	int display;
}Cell;

void Cellinit(Cell* C);
void Display(Cell* C);
void NeighborCheck(Cell* C);
void CellStateCheck(Cell* C);
void CellNextGeneration(Cell* C);
void SetCursorPosition(int x, int y);

int main()
{
	char key_input = 0;
	int x = 0, y = 0;
	Cell cell[HEIGHT][WIDTH];
	Cellinit(cell);

	while(1)
	{
		//system("cls");
		SetCursorPosition(0, 0);
		switch(key_input)
		{
		case 'a':
			cell[y][x--].display = 0;
			cell[y][x].display = 1;
			break;
		case 'd':
			cell[y][x++].display = 0;
			cell[y][x].display = 1;
			break;
		case 's':
			cell[y++][x].display = 0;
			cell[y][x].display = 1;
			break;
		case 'w':
			cell[y--][x].display = 0;
			cell[y][x].display = 1;
			break;
		case 'n':
			CellNextGeneration(cell);
			break;
		case 'i':
			Cellinit(cell);
			break;
		case 'm':
			if(cell[y][x].state == WALL)
				break;
			if(cell[y][x].state == LIVE)
				cell[y][x].state = DEAD;
			else
				cell[y][x].state = LIVE;
			break;
		default:
			break;
		}
		
		
		CellStateCheck(cell);
		Display(cell);
		printf("%d %d neighbor : %d                      \n", x, y, cell[y][x].neighbor);
		printf("by Tekami / Park Sung-Kyoung 2010180020\n");
		printf("KPU Department of Game & Multimedia Engineering\n");
		printf("Crescendo Studio");
		key_input = getch();
		
	}
	
}

void Cellinit(Cell* C)
{
	int i;
	Cell* temp = C;
	srand((unsigned)time(NULL));
	for(i = 0; i < HEIGHT * WIDTH; i++)
	{
		C->state = DEAD;
		C->neighbor = 0;
		C->display = 0;
		if((C + 1) != NULL)
			C++;
		else
			break;
	}
	C = temp;
	for(i = 0; i< WIDTH - 1; i++)
	{
		C->state = WALL;
		(C + (WIDTH - 1))->state = WALL;
		if((C + WIDTH) != NULL)
			C += WIDTH;
		else
			return;
	}
	C = temp;
	for(i = 0; i< WIDTH; i++)
	{
		C->state = WALL;
		(C + (WIDTH * (HEIGHT-1)))->state = WALL;

		if((C + 1) != NULL)
			C ++;
		else
			return;
	}

}

void Display(Cell* C)
{
	int i, j;
	char display[HEIGHT][(WIDTH+1)*2];
	char *cp;
	for(i = 0; i < HEIGHT; i++)
	{
		for(j = 0; j < WIDTH; j++)
		{
			/*display[i][j*2] = ' ';
			display[i][(j*2)+1] = ' ';*/
			switch(C->state)
			{
			case DEAD:
				cp = "бр";
				display[i][j*2] = cp[0];
				display[i][(j*2)+1] = cp[1];
				//printf("бр");
				break;
			case LIVE:
				cp = "бс";
				display[i][j*2] = cp[0];
				display[i][(j*2)+1] = cp[1];
				//printf("бс");
				break;
			case WALL:
				cp = "в╞";
				display[i][j*2] = cp[0];
				display[i][(j*2)+1] = cp[1];
				//printf("в╞");
				break;
			default:
				cp = "??";
				display[i][j*2] = cp[0];
				display[i][(j*2)+1] = cp[1];
				//printf("?");
				break;
			}
			if(C->display){
				cp = "в╤";
				display[i][j*2] = cp[0];
				display[i][(j*2)+1] = cp[1];
			}
			if((C + 1) != NULL)
				C++;
			else
				return;
		}
		display[i][(j*2)+0] = ' ';
		display[i][(j*2)+1] = '\n';
		//printf("\n");
	}
	display[HEIGHT-1][((WIDTH)*2)+1] = NULL;

	printf("%s\n", display);
}

void CellStateCheck(Cell* C)
{
	int i;

	for(i = 0; i < HEIGHT * WIDTH; i++)
	{
		NeighborCheck(C);

		if((C + 1) != NULL)
			C++;
		else
			return;
	}
}

void NeighborCheck(Cell* C)
{
	int i;
	C->neighbor = 0;
	for(i = -1; i <= 1; i++){
		if((C - (WIDTH) + (i))->state == LIVE && (C - (WIDTH) + (i))->state != WALL)
			C->neighbor++;
		if((C + (WIDTH) + (i))->state == LIVE && (C + (WIDTH) + (i))->state != WALL)
			C->neighbor++;
		if(((C + (i))->state == LIVE) && i != 0 && ((C + (i))->state != WALL))
			C->neighbor++;
	}	
}

void CellNextGeneration(Cell* C)
{
	int i;

	for(i = 0; i < HEIGHT * WIDTH; i++)
	{
		if(C->state != WALL){
			switch(C->neighbor)
			{
			case 0:
			case 1:
				C->state = DEAD;
				break;
			case 2:
				break;
			case 3:
				if(C->state == DEAD)
					C->state = LIVE;
				break;
			default:
				C->state = DEAD;
				break;
			}
		}
		if((C + 1) != NULL)
			C++;
		else
			return;
	}
}

void SetCursorPosition(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}