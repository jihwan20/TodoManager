#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>       // ���� ��¥ Ȯ��
#include <windows.h>    // �ܼ�â ũ�� ����, ȭ�� Ŭ����
#include <conio.h>      // _getch() �Լ� ��� (����Ű �Է� ���� ���� �Է�)
#include "color.h"
#include "calendar.h"
#include "assistant.h"
#include "menu.h"
#include "plan.h"

// (����) ��ǥ �̵� �Լ� (��)
void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// (����) �ؽ�Ʈ �� ���� �Լ� (��)
void textcolor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

// (����) �α��� ȭ�� �簢�� �׸��� �Լ�
void printBOX(void) {
    int i, y = 10;
    gotoxy(34, y);
    printf("��");
    for (i = 0; i < 30; i++)
        printf("��");
    printf("��");
    for (i = 1; i <= 7; i++)
    {
        gotoxy(34, ++y);
        printf("��%30s��", " ");
    }
    gotoxy(34, ++y);
    printf("��");
    for (i = 0; i < 30; i++)
        printf("��");
    printf("��");
}

// (����) �ܼ�â Ŀ�� �� ���̰� �ϴ� �Լ� 0 - ���� 1 - ����
void cursor(int n)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = n;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}