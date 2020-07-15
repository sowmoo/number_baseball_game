#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define NUM_SIZE 4 //게임숫자
#define USER_BUFFER_SIZE 30 //유저입력버퍼
#define number_counter (computer_num*2)+2
#define GAME_LIFE 10

#define putchxy(x,y,c) {gotoxy(x,y); putch(c);}
#define delay(n) Sleep(n)   

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

struct data
{
	int strike_count;
	int ball_count;
	int user_number[4];
};

struct data data[10];


void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void user_input(struct data *data, int *main_count) //유저 숫자입력 
{
	int count;
	int i, j;
	char number[USER_BUFFER_SIZE];

	while (1)
	{
		gotoxy(2, 18); printf("숫자를 입력해주세요 (%d자리)--> ", NUM_SIZE);



		scanf("%[^\n]s", number); //유저 숫자입력 
		while (getchar() != '\n');	//버퍼 비우기

		if (strcmp(number, "exit") == 0)
		{
			exit(1);
		}


		for (i = 0, count = 0; i < USER_BUFFER_SIZE; i++) // 오류검출 
		{
			if (number[i] >= 48 && number[i] <= 57)
			{
				count++;
			}
		}
		if (count < NUM_SIZE || count > NUM_SIZE)
		{
			gotoxy(2, 19); printf("숫자를 %d개 입력해주세요 (다시입력하세요)\n", NUM_SIZE);
			continue;
		}
		break;
	}
	for (i = 0, j = 0, count = 0; i < USER_BUFFER_SIZE; i++)
	{
		if (number[i] >= 48 && number[i] <= 57)
		{
			data[*main_count].user_number[j] = number[i] - 48;
			j++;
			count++;
		}

		if (count == 4)
		{
			return;
		}
	}
}

void random_computer_number(int computer[])
{
	srand(time(NULL));

	int i, j, counter;
	for (;;)
	{
		counter = 0;

		for (i = 0; i < NUM_SIZE; i++)
		{
			computer[i] = rand() % 10;
		}

		for (i = 0; i < NUM_SIZE; i++)
		{
			for (j = 0; j < NUM_SIZE; j++)
			{
				if (i == j)
				{
					continue;
				}

				if (computer[i] == computer[j])
				{
					counter = 1;
					break;
				}
			}
		}

		if (counter == 0)
		{
			return;
		}
	}
}

void result(struct data *data, int computer[], int main_count)
{
	int i, j;
	for (i = 0; i < NUM_SIZE; i++)
	{
		for (j = 0; j < NUM_SIZE; j++)
		{
			if (computer[i] == data[main_count].user_number[j])
			{
				if (i == j)
				{
					data[main_count].strike_count++;

				}
				else
				{
					data[main_count].ball_count++;
				}
			}
		}
	}
}

void game_loading_screen()
{
	int i;
	for (i = 0; i < 45; i++)
	{
		putchxy(10 + i, 5, '-');
		delay(10);
	}
	for (i = 0; i < 45; i++)
	{
		putchxy(70 - i, 10, '-');
		delay(10);
	}
	delay(800);
	gotoxy(35, 7);
	printf("숫");
	delay(600);
	gotoxy(38, 7);
	printf("자");
	delay(600);
	gotoxy(41, 7);
	printf("야");
	delay(600);
	gotoxy(44, 7);
	printf("구");
	delay(600);
	putchxy(48, 8, 'M');
	delay(40);
	putchxy(49, 8, 'a');
	delay(40);
	putchxy(50, 8, 'd');
	delay(40);
	putchxy(51, 8, 'e');
	delay(40);
	putchxy(53, 8, 'b');
	delay(40);
	putchxy(54, 8, 'y');
	delay(40);
	gotoxy(56, 8);
	printf("B조");
	delay(1000);


	gotoxy(30, 12);
	printf("아무키 누르면 게임진행 가능합니다.");

	system("pause>null");
}

void window_graphic()
{
	int i;
	int y = 0;

	for (i = 0; i < 60; i++)
	{
		putchxy(i, 0, '-');
	}
	for (i = 0; i < 20; i++)
	{
		putchxy(0, i, '|')
	}
	for (i = 0; i < 20; i++)
	{
		putchxy(60, i, '|')
	}
	for (i = 0; i < 60; i++)
	{
		putchxy(i, 20, '-')
	}


}

int game_screen(int *chance, int *main_count, int *computer_number)
{
	window_graphic();
	int y = 0;
	gotoxy(2, 23); printf("test용 컴퓨터숫자 %d %d %d %d", computer_number[0], computer_number[1], computer_number[2], computer_number[3]);

	for (int m = 0; m < *main_count; m++)
	{

		gotoxy(5, m + 3); printf("%d %d %d %d", data[m].user_number[0], data[m].user_number[1], data[m].user_number[2], data[m].user_number[3]);
		gotoxy(15, m + 3); printf("----> strike = %d , ball = %d \n", data[m].strike_count, data[m].ball_count);
		gotoxy(4, 2); printf(" 기  록 ");
		gotoxy(61, y + 1); printf("+-- SCORE BOARD ---+ ");

		if (data[*main_count - 1].strike_count == 0)
		{
			gotoxy(61, y + 2); printf("|  S ○ ○ ○ ○   | ");
		}
		else if (data[*main_count - 1].strike_count == 1)
		{
			gotoxy(61, y + 2); printf("|  S ● ○ ○ ○   | ");
		}
		else if (data[*main_count - 1].strike_count == 2)
		{
			gotoxy(61, y + 2); printf("|  S ● ● ○ ○   | ");
		}
		else if (data[*main_count - 1].strike_count == 3)
		{
			gotoxy(61, y + 2); printf("|  S ● ● ● ○   | ");
		}
		else if (data[*main_count - 1].strike_count == 4)
		{
			gotoxy(61, y + 2); printf("|  S ● ● ● ●   | ");
			return 1; //4스트라이크 종료 
		}

		if (data[*main_count - 1].ball_count == 0)
		{
			gotoxy(61, y + 3); printf("|  B ○ ○ ○ ○   | ");
		}
		if (data[*main_count - 1].ball_count == 1)
		{
			gotoxy(61, y + 3); printf("|  B ● ○ ○ ○   | ");
		}
		if (data[*main_count - 1].ball_count == 2)
		{
			gotoxy(61, y + 3); printf("|  B ● ● ○ ○   | ");
		}
		if (data[*main_count - 1].ball_count == 3)
		{
			gotoxy(61, y + 3); printf("|  B ● ● ● ○   | ");
		}
		if (data[*main_count - 1].ball_count == 4)
		{
			gotoxy(61, y + 3); printf("|  B ● ● ● ●   | ");
		}
	}
	gotoxy(61, y + 4); printf("+------------------+ ");
	gotoxy(61, y + 6); printf("+-  남 은 횟 수  -+ ");
	gotoxy(61, y + 7); printf("|        %d       | ", *chance);
	gotoxy(61, y + 8); printf("+-----------------+ ");

	gotoxy(61, y + 10); printf("+-------게 임 규 칙----------+ ");
	gotoxy(61, y + 11); printf("|                            | ");
	gotoxy(61, y + 12); printf("| 컴퓨터 숫자 중복안나옴     | ");
	gotoxy(61, y + 13); printf("|                            | ");
	gotoxy(61, y + 14); printf("| 사용자 중복숫자입력 무시   | ");
	gotoxy(61, y + 15); printf("|                            | ");
	gotoxy(61, y + 16); printf("| 도전횟수는 총 %d회         | ", GAME_LIFE);
	gotoxy(61, y + 17); printf("|                            | ");
	gotoxy(61, y + 18); printf("| 종료는 exit를 입력해주세요 | ");
	gotoxy(61, y + 19); printf("|                            | ");
	gotoxy(61, y + 20); printf("+----------------------------+ ");

	return 0; //아무변화없음 
}

void lose_stage()
{
	int y = 0;
	gotoxy(61, y + 1); printf("+-- SCORE BOARD ---+ ");
	gotoxy(61, y + 2); printf("|  S ○ ○ ○ ○   | ");
	gotoxy(61, y + 3); printf("|  B ○ ○ ○ ○   | ");
	gotoxy(61, y + 4); printf("+------------------+ ");

	gotoxy(61, y + 6); printf("+-  남 은 횟 수  -+ ");
	gotoxy(61, y + 7); printf("|        0        | ");
	gotoxy(61, y + 8); printf("+-----------------+ ");

	gotoxy(61, y + 10); printf("+-------게 임 규 칙----------+ ");
	gotoxy(61, y + 11); printf("|                            | ");
	gotoxy(61, y + 12); printf("| 컴퓨터 숫자 중복안나옴     | ");
	gotoxy(61, y + 13); printf("|                            | ");
	gotoxy(61, y + 14); printf("| 사용자 중복숫자입력 무시   | ");
	gotoxy(61, y + 15); printf("|                            | ");
	gotoxy(61, y + 16); printf("| 도전횟수는 총 10회         | ");
	gotoxy(61, y + 17); printf("|                            | ");
	gotoxy(61, y + 18); printf("| 숫자마다 공백을 넣어주세요 | ");
	gotoxy(61, y + 19); printf("|                            | ");
	gotoxy(61, y + 20); printf("+----------------------------+ ");
	window_graphic();
	delay(800);
	gotoxy(16, 7);
	printf("패");
	delay(600);
	gotoxy(35, 7);
	printf("배");
	delay(600);
	gotoxy(13, 10);
	printf("아무키 누르면 게임진행 가능합니다.");
	system("pause>null");

}

void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}



void win_stage(int *chance)
{
	int y = 0;

	gotoxy(61, y + 1); printf("+-- SCORE BOARD ---+ ");
	gotoxy(61, y + 2); printf("|  S ● ● ● ●   | ");
	gotoxy(61, y + 3); printf("|  B ○ ○ ○ ○   | ");
	gotoxy(61, y + 4); printf("+------------------+ ");

	gotoxy(61, y + 6); printf("+-  남 은 횟 수  -+ ");
	gotoxy(61, y + 7); printf("|        %d       | ", *chance);
	gotoxy(61, y + 8); printf("+-----------------+ ");

	gotoxy(61, y + 10); printf("+-------게 임 규 칙----------+ ");
	gotoxy(61, y + 11); printf("|                            | ");
	gotoxy(61, y + 12); printf("| 컴퓨터 숫자 중복안나옴     | ");
	gotoxy(61, y + 13); printf("|                            | ");
	gotoxy(61, y + 14); printf("| 사용자 중복숫자입력 무시   | ");
	gotoxy(61, y + 15); printf("|                            | ");
	gotoxy(61, y + 16); printf("| 도전횟수는 총 10회         | ");
	gotoxy(61, y + 17); printf("|                            | ");
	gotoxy(61, y + 18); printf("| 숫자마다 공백을 넣어주세요 | ");
	gotoxy(61, y + 19); printf("|                            | ");
	gotoxy(61, y + 20); printf("+----------------------------+ ");
	window_graphic();
	delay(800);
	gotoxy(16, 7);
	printf("승");
	delay(600);
	gotoxy(35, 7);
	printf("리");
	delay(600);
	gotoxy(13, 10);
	printf("아무키 누르면 게임진행 가능합니다.");

	system("pause>null");
}

int main()
{
	int chance;
	int main_count;
	int computer_number[4] = { 0, };
	//game_loading_screen(); //게임시작시 처음한번 로딩화면출력 
	setcursortype(NOCURSOR);
	//system("cls");	

	for (;;)
	{
		chance = GAME_LIFE; //게임라이프 초기화 
		main_count = 0; // 현재라운드		
		int game_over;
		memset(&data, 0, sizeof(struct data)); //게임기록 초기화
		random_computer_number(computer_number); //컴퓨터 랜덤숫자 4개 지정 
		setcursortype(NOCURSOR);
		system("cls");
		window_graphic();
		gotoxy(61, 1); printf("+-- SCORE BOARD ---+ ");
		gotoxy(61, 2); printf("|  S ○ ○ ○ ○   | ");
		gotoxy(61, 3); printf("|  B ○ ○ ○ ○   | ");
		gotoxy(61, 4); printf("+------------------+ ");

		for (;;)
		{
			game_over = game_screen(&chance, &main_count, computer_number);
			if (game_over == 1)
			{
				break;
			}
			user_input(data, &main_count);
			result(data, computer_number, main_count);
			

			main_count++;
			if (--chance == 0)
			{
				break;
			}
			system("cls");
		}
		if (game_over == 1)
		{
			system("cls");
			window_graphic();
			win_stage(&chance);
			gotoxy(16, 20);
		}
		else
		{
			system("cls");
			window_graphic();
			lose_stage();
			gotoxy(16, 20);
		}

	}
}
