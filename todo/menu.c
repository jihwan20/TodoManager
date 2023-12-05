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

// 2. �޴� ��� �Լ�
int Menu(void)
{
    //�޴� ����_x�� �Է��� ������ ���� �ݺ�
    while (1)
    {
        // �޴� ��� ��ǥ �̵�
        gotoxy(23, 32);
        cursor(0);
        printf("[ -1�� : A,  +1�� : D,  ��¥ ���� : C,  �α׾ƿ� : X ]");

        // �޴� �Է�â ��ǥ �̵�
        choice_menu = _getch(); // _getch() : ����Ű ���� Ű �ϳ��� �Է¹��� �� ����

        // +1�� �̵�
        if (choice_menu == 'd' || choice_menu == 'D')
        {
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
            printCalendar(month, year);
        }

        // -1�� �̵�
        else if (choice_menu == 'a' || choice_menu == 'A')
        {
            month--;
            if (month < 1)
            {
                month = 12;
                year--;
            }
            printCalendar(month, year);
        }

        // ��¥ ����
        else if (choice_menu == 'c' || choice_menu == 'C')
            choice_day();

        // ����
        else if (choice_menu == 'x' || choice_menu == 'X')
        {
            system("mode con:cols=100 lines=30");
            return 0;
        }

        // �ٸ� �Է� => �ٽ� �Է¹ޱ�
        else
            continue;
    }
}

// 2-1. �޴�_��¥ ���� �Լ�
void choice_day(void)
{
    int choiceday;                              // ��¥ ���� ����
    int checkday = numberOfDays(month, year);   // ��¥ ���� Ȯ���ϴ� ����
    int DDay;
    while (1)
    {
        // ȭ�� �ʱ�ȭ & �޷� ���
        printCalendar(month, year);

        cursor(1);
        gotoxy(40, 32);
        printf("[ ��¥ ���� :    ]");
        gotoxy(41, 33);
        printf("[ ���� ��� : 0 ]");

        gotoxy(54, 32);
        scanf("%d", &choiceday);

        // �Է��� ��¥�� �����̰ų�, �ش� ���� ������ ��¥���� ũ��
        if (choiceday > checkday || choiceday < 0)
        {
            gotoxy(35, 33);
            printf("�߸��� ��¥�Դϴ�. (1 ~ %d��)", checkday);
            Sleep(1000);
        }

        // �Է��� ��¥�� 0�̸� ���� ȭ������ ���ư���
        else if (choiceday == 0)
        {
            printCalendar(month, year);
            break;
        }

        // ��¥ ����
        else
        {
            // ���� ���� �޴��� ������ �����ϸ� �ٽ� �̰����� ���ƿ���
        reset:
            printCalendar(month, year);

            gotoxy(38, 32);
            printf("      [ %d�� %d�� ]      ", month, choiceday);

            // ���� ��¥ ���� ���� ����
            gotoxy(59, 32);
            DDay = D_day(year, month, choiceday);
            if (DDay > 0)
                printf("[ D + %2d ]", DDay);
            else if (DDay < 0)
                printf("[ D - %2d ]", -DDay);
            else
                printf("[ D - Day ]");

            cursor(0);
            gotoxy(25, 33);
            printf("[ ���� �߰� : A,  ���� ���� : S,  ���� ���� : D ]");
            gotoxy(27, 34);
            printf("[ ��¥ ���� : C,  ó�� ȭ������ ���ư��� : F ]");

            // ������ ���� ���� ��� �Լ�
            printPlan(year, month, choiceday);

            choice_menu = _getch();

            // �ٸ� ��¥ ����
            if (choice_menu == 'c' || choice_menu == 'C')
                continue;

            // ó�� ȭ������
            else if (choice_menu == 'f' || choice_menu == 'F')
            {
                system("cls");
                printCalendar(month, year);
                break;
            }

            // ���� �߰� �޴�
            else if (choice_menu == 'a' || choice_menu == 'A')
            {
                printCalendar(month, year);                               // ȭ�� �ʱ�ȭ (�޷� ���)
                gotoxy(38, 32);
                printf("      [ %d�� %d�� ]      ", month, choiceday);    // ������ ��¥
                printPlan(year, month, choiceday);                        // ������ ���� ���� ���
                addPlan(year, month, choiceday);                          // ������ ���� ������ �߰�
                goto reset;                                               // reset���� �̵�
            }

            // ���� ���� �޴�
            else if (choice_menu == 's' || choice_menu == 'S')
            {
                printCalendar(month, year);
                gotoxy(38, 32);
                printf("      [ %d�� %d�� ]      ", month, choiceday);
                printPlan(year, month, choiceday);
                editPlan(year, month, choiceday);
                goto reset;
            }

            // ���� ���� �޴�
            else if (choice_menu == 'd' || choice_menu == 'D')
            {
                printCalendar(month, year);
                gotoxy(38, 32);
                printf("      [ %d�� %d�� ]      ", month, choiceday);
                printPlan(year, month, choiceday);
                deletePlan(year, month, choiceday);
                goto reset;
            }

            // �ٸ� �Է� => �ٽ� �Է¹ޱ�
            else
                goto reset;
        }
    }
}