/*
    ������Ʈ : �������� (Ķ����) ���α׷�
    �� : 1�� (A+ ��)
    ���� : ��λ� (202311388)
    ������ : ������ (202311403) ����ȯ (202111679)
    ���� : �賲�� (202311385) ��ƿ� (202311394) ������ (202311409) ������ (202311425) �ֹα� (202111495) ȫ�¹� (202311448)
    �ۼ��� : 2023.11.11 ~ 2023.12.03
*/

/*
    ������Ʈ ����
    1. �޷� ��� (�Ϸ�)
    2. �޷� �� �̵� (�Ϸ�)
    3. ���� ���� ���� (���� �߰�) (�Ϸ�)
    4. ��¥ ���� ��� (�Ϸ�)
    5. ������ ��¥ ���� ��� ��� (��¥ ����) (�Ϸ�)
    6. ���� �߰� ��� (�Ϸ�)
    7. ���� ���� ��� (�Ϸ�)
    8. ���� ���� ��� (�Ϸ�)
     8-1. ���ڻ� ���� ��� (�Ϸ�)
    9. ������ ��� (�Ϸ�)

     5-1. ��� ���� ���� ��� (�н�����)
     6-1. ��� ���� �߰� ���
     8-2. ��� ���� <--> �Ϲ� ���� ��ȯ ���
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>       // ���� ��¥ Ȯ��
#include <windows.h>    // �ܼ�â ũ�� ����, ȭ�� Ŭ����
#include <conio.h>      // _getch() �Լ� ��� (����Ű �Է� ���� ���� �Է�)
#include "color.h"      // ���� �Լ��� ���ǵ� ���� ������ ������� ����
#include "calendar.h"
#include "assistant.h"
#include "menu.h"
#include "plan.h"
#include "login.h"

// 0. ���� �Լ� (��)
int main(void)
{
    // �ܼ�â ũ�� ���� (���� 100�ȼ� ���� 30��)
    system("mode con:cols=100 lines=30");
    int choice, y;

    do 
    {
        system("cls");
        printBOX();                         // �α���â �׸� �ڽ� �׸���
        gotoxy(44, 13);                     
        printf("1. ȸ������\n");
        gotoxy(44, 14);
        printf("2. �α���\n");
        gotoxy(44, 15);
        printf("3. ����\n");

        gotoxy(24, 7);
        printf("  [ ���α׷���2 ");
        textcolor(YELLOW);
        printf("1�� ");
        textcolor(WHITE);
        printf("������Ʈ - ");
        textcolor(darkSkyBlue);
        printf("���� ���� ���α׷�");
        textcolor(WHITE);
        printf("] ");

        cursor(0);                          // Ŀ�� �� ���̰�
        choice = _getch() - '0';            // ���� �Է� ���� ���� �ϳ� �Է¹ޱ�
        cursor(1);                          // Ŀ�� ���̰�

        switch (choice) {
            // ȸ������
        case 1:
            addMember();
            break;

            // �α���
        case 2:
            // �α��� ���� �� ���� ȭ������ �Ѿ (�޷�)
            if (login()) {
                // �ܼ�â �а� �ٲٱ�
                system("mode con:cols=100 lines=50");
                // ���� ��¥ ���ϱ� (���� �ð� �������� tm ����ü ����)
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                // ���� ��¥ ����
                month = tm.tm_mon + 1;      // (0~11)�̹Ƿ� +1
                year = tm.tm_year + 1900;   // 1900�⵵ ���ĺ����̹Ƿ� +1900
                day = tm.tm_mday;

                // ���� ���� �޷� ���
                printCalendar(month, year);

                // �޴� ���
                Menu();
            }
            break;

            // ����
        case 3:
            y = 7;                                      // y��ǥ
            system("cls");
            gotoxy(24, y++);
            printf("  [ ���α׷���2 ");
            textcolor(YELLOW);
            printf("1�� ");
            textcolor(WHITE);
            printf("������Ʈ - ");
            textcolor(darkSkyBlue);
            printf("���� ���� ���α׷�");
            textcolor(WHITE);
            printf("] ");
            y++;
            gotoxy(36, y++);
            printf("[      ]  ��λ� (202311388)");
            gotoxy(35, y++);
            printf("[        ] ������ (202311403)");
            gotoxy(35, y++);
            printf("[        ] ����ȯ (202111679)");
            gotoxy(36, y++);
            printf("[      ]  �賲�� (202311385)");
            gotoxy(36, y++);
            printf("[      ]  ��ƿ� (202311394)");
            gotoxy(36, y++);
            printf("[      ]  ������ (202311409)");
            gotoxy(36, y++);
            printf("[      ]  ������ (202311425)");
            gotoxy(36, y++);
            printf("[      ]  �ֹα� (202111495)");
            gotoxy(36, y++);
            printf("[      ]  ȫ�¹� (202311448)");
            printf("\n");
            textcolor(RED);
            y = 9;
            gotoxy(38, y++);
            printf("����");
            textcolor(SkyBlue);
            gotoxy(37, y++);
            printf("������");
            gotoxy(37, y++);
            printf("������");
            textcolor(YELLOW);
            gotoxy(38, y++);
            printf("����");
            gotoxy(38, y++);
            printf("����");
            gotoxy(38, y++);
            printf("����");
            gotoxy(38, y++);
            printf("����");
            gotoxy(38, y++);
            printf("����");
            gotoxy(38, y++);
            printf("����");
            gotoxy(38, y++);
            textcolor(WHITE);
            gotoxy(38, 25);
            break;

            // ȸ������, �α���, ���� �� �� �ƴϸ�
        default:
            printf("�߸��� �޴��� �����߽��ϴ�.\n");
            Sleep(1000);
        }
    } while (choice != 3);

    return 0;
}