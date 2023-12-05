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

// 1. �޷� ��� �Լ� (��)
void printCalendar(int month, int year) {
    // ȭ�� Ŭ����
    system("cls");

    // n�� n�� ���
    gotoxy(45, 1);
    printf("%d�� %d��", year, month);

    // �޷� ���� ���
    gotoxy(20, 3);
    printf("============================================================");
    gotoxy(25, 4);
    printf("��      ��      ȭ      ��      ��      ��      ��");
    gotoxy(20, 5);
    printf("============================================================");

    int set_y = 7;                                  // Ŀ�� �̵� y��ǥ
    int day;                                        // ��¥ (n��)
    int startDay = firstDay_week(1, month, year);   // �Ŵ� 1���� ���� [ ��(0) ��(1) ȭ(2) ��(3) ��(4) ��(5) ��(6) ]

    // �Ͽ��� ��¥�� �������� ��� ��ǥ ���� (24 + 8ĭ ���� * ����, set_y)
    gotoxy(24 + 8 * startDay, set_y);

    // n�� ��� (1�Ϻ��� n���� ������������)
    for (day = 1; day <= numberOfDays(month, year); day++)
    {
        // ��¥ + ���� ������ 7�� ���� �������� ���� ���� ���� [ 0(��), 1(��), 2(��), 3(ȭ), 4(��), 5(��), 6(��) ]

        // �Ͽ����� ���������� ���
        if ((day + startDay) % 7 == 1)
        {
            textcolor(RED);
            printf("%3d     ", day);
            textcolor(WHITE);
        }

        // ������� �ϴû����� ����� �� �Ͽ��Ϸ� �Ѿ�� ���� �� �ٲٱ�
        else if ((day + startDay) % 7 == 0)
        {
            textcolor(darkSkyBlue);
            printf("%3d     ", day);
            textcolor(WHITE);
            set_y += 4;
            gotoxy(24, set_y);
        }

        // �������� ������� ��� (8ĭ ���� - �۾� 3ĭ + ��ĭ 5ĭ)
        else
            printf("%3d     ", day);
    }
    gotoxy(20, 31);
    printf("============================================================");
}

// (����) n�� n�� 1���� ���� �������� ��ȯ�ϴ� �Լ� (��)
int firstDay_week(int day, int month, int year) {
    // ÿ���� ���� ��� -> 1��, 2���� ���⵵ 13, 14���� ���
    if (month < 3)
    {
        month += 12;
        year -= 1;
    }

    // ÿ���� ������ ���� ����� - [ ��(0) ��(1) ��(2) ȭ(3) ��(4) ��(5) ��(6) ]
    int h = (day + 13 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;

    // �Ͽ����� 0���� �ϱ� ���� h - 1 ���� (�� ĭ�� �����)
    h--;

    // ������� -1�� �ǹǷ� 6���� �ٲ��ֱ�
    if (h == -1)
        return 6;

    // ���������� [ ��(0) ��(1) ȭ(2) ��(3) ��(4) ��(5) ��(6) ]
    else
        return h;
}

// (����) n�� n���� ��ĥ���� �ִ��� ����ϴ� �Լ� (���� ����) (��)
int numberOfDays(int month, int year) {
    if (month == 2)
    {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            return 29;
        else
            return 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

// (����) 0����� �ش� ��¥���� �ϼ��� ��ȯ�ϴ� �ϼ� (��)
int totalday(int year, int month, int day)
{
    int month_day[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (numberOfDays(2, year) == 29)
        month_day[1] = 29;

    int total = 365 * (year - 1);

    total += (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;

    for (int i = 0; i < month - 1; i++)
        total += month_day[i];

    total += day;
    return total;
}

// (����) ������ ��¥�� ���� ��¥�κ��� ��ĥ ���Ҵ���/�������� ��ȯ�ϴ� �Լ�
int D_day(int choiceyear, int choicemonth, int choiceday)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // ���� ��¥ ����
    int t_month = tm.tm_mon + 1;      // (0~11)�̹Ƿ� +1
    int t_year = tm.tm_year + 1900;   // 1900�⵵ ���ĺ����̹Ƿ� +1900
    int t_day = tm.tm_mday;

    int todayTotal = totalday(t_year, t_month, t_day);
    int selectTotal = totalday(choiceyear, choicemonth, choiceday);

    return (todayTotal - selectTotal);
}