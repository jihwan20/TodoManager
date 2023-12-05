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

// 2-1-1. ���� ��� �Լ� 
void printPlan(int year, int month, int day)
{
    FILE* fp = NULL;                                    // ���� ������

    char str[BUFSIZ], title[BUFSIZ], content[BUFSIZ];   // ���Ͽ� ����� ������ ����, ������ �����ϴ� ����
    int i = 36;                                         // Ŀ�� Y ��ǥ
    int count = 1;                                      // ���Ͽ��� ���� �о���� ��
    int fpYear, fpMonth, fpDay;                         // ���Ͽ� ����� ������ ��¥�� �����ϴ� ����
    int color;                                          // ���Ͽ� ����� ���� ������ ������ �����ϴ� ����

    fp = fopen("Plan.txt", "r+");                       // ����¿� ���� ���� (���� ����)

    // ���� ������ ã�� ���ϸ�
    if (fp == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    gotoxy(28, i);
    while (fgets(str, sizeof(str), fp) != NULL)         // �� �پ� �о����, NULL�� ���� ������
    {
        sscanf(str, "%d/%d/%d, %[^,], %[^,], %d", &fpYear, &fpMonth, &fpDay, title, content, &color);   // ��¥, ����, ����, ���� ����
        if (fpYear == year && fpMonth == month && fpDay == day)                                         // ���Ͽ� ����� ��¥�� ������ ��¥�� ������
        {
            // ��ȣ. [����] : ���� �������� ���
            printf("%2d. [", count);
            textcolor(color);
            printf("%7s", title);
            textcolor(WHITE);
            printf("] : %s\n", content);
            count++;
            i++;
            gotoxy(28, i);
        }
    }
    fclose(fp);                                         // ���� �ݱ�
}

// 2-1-2. ���� �߰� �Լ�
void addPlan(int year, int month, int day)
{
    FILE* fp;
    char title[9], content[40];             // ����, ����

    getchar();
    // ���� �Է�
    cursor(1);
    gotoxy(28, 33);
    printf("���� (�ѱ� 3���ڱ���) : ");
    fgets(title, sizeof(title), stdin);
    title[strlen(title) - 1] = '\0';        // ���� ���� ����

    // ���� �Է�
    gotoxy(28, 34);
    printf("���� : ");
    fgets(content, sizeof(content), stdin);
    content[strlen(content) - 1] = '\0';

    fp = fopen("Plan.txt", "a+");           // Plan.txt ���� ���� (������ ����)

    if (fp == NULL)                         // ���� ���� ����
    {
        gotoxy(28, 35);
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ���� �߰�
    fprintf(fp, "%04d/%02d/%02d, %s, %s, %d\n", year, month, day, title, content, WHITE);
    fclose(fp);

    // ���� �߰��� �Ϸ�Ǹ� �ٽ� ���� �޴��� (2-1�� reset����)
    gotoxy(38, 35);
    printf("������ �߰��Ǿ����ϴ�.\n");
    Sleep(1000);
}

// 2-1-3. ���� ���� �Լ�
void editPlan(int year, int month, int day) {
    FILE* fp, * tempFile;
    char str[256], title[7], content[40], newTitle[7], newContent[40];      // ����, ����, ���ο� ����, ���ο� ����
    int fileYear, fileMonth, fileDay, color;                                // ��/��/��, ���� ����
    int count = 1, choice, number, newYear, newMonth, newDay, newColor;     // ���� �� ��, ������ �׸� ����, ������ ���� ��ȣ, ���ο� ��/��/��, ���ο� ���� ����
    int found = 0;                                                          // �ٲٷ��� ������ ���� �ִ���, ������ �Ǿ����� Ȯ��

    // ������ ���� ��ȣ ����
    cursor(1);
    gotoxy(38, 33);
    printf("������ ������ ��ȣ : ");
    scanf("%d", &number);
    getchar();                              // ���� ����

    fp = fopen("Plan.txt", "r+");           // Plan ���� ����
    tempFile = fopen("temp.txt", "w+");     // �ӽ� ���� (�ӽ� ���Ͽ� ���� ������ ���� ��, �ӽ� ������ �̸��� Plan���� �ٲ� �� ���� Plan ���� ����) ����

    if (fp == NULL || tempFile == NULL)
    {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // �� �پ� ���� (�ٲ� ���� ã��)
    while (fgets(str, sizeof(str), fp))
    {
        sscanf(str, "%d/%d/%d, %[^,], %[^,], %d", &fileYear, &fileMonth, &fileDay, title, content, &color); // ��¥, ����, ����, ���� ���� ����

        // ��/��/���� ���� ������ ã���� ��
        if (fileYear == year && fileMonth == month && fileDay == day)
        {
            // ���� ���� Ƚ�� == ���� �ٲٷ� �ϴ� ������ ��ȣ �� ��
            if (count == number)
            {
                gotoxy(24, 34);
                printf("������ �׸� (1. ��¥, 2. ����, 3. ����, 4. ���� ����)");
                choice = _getch() - '0';    // ���� �ϳ��� ����Ű ���� �Է¹���. - '0'�� �� ������ �Է¹��� ���ڸ� ���ڷ� �ٲٱ� ����

                switch (choice)
                {
                    // ��¥ ����
                case 1:
                    gotoxy(28, 35);
                    printf("���ο� ��¥ (yyyy mm dd): ");
                    scanf("%d %d %d", &newYear, &newMonth, &newDay);
                    getchar();                                          // ���� �����

                    // ���ο� ��/��/��, �������� �״�� �����ϱ�
                    fprintf(tempFile, "%04d/%02d/%02d, %s, %s, %d\n", newYear, newMonth, newDay, title, content, color);

                    // ã�Ҵ� & �����ߴٴ� ǥ��
                    found = 1;

                    break;

                    // ���� ����
                case 2:
                    gotoxy(28, 35);
                    printf("���ο� ���� (�ѱ� 3���� ����): ");
                    fgets(newTitle, sizeof(newTitle), stdin);
                    newTitle[strlen(newTitle) - 1] = '\0';
                    fprintf(tempFile, "%04d/%02d/%02d, %s, %s, %d\n", year, month, day, newTitle, content, color);
                    found = 1;
                    break;

                    // ���� ����
                case 3:
                    gotoxy(28, 35);
                    printf("���ο� ����: ");
                    fgets(newContent, sizeof(newContent), stdin);
                    newContent[strlen(newContent) - 1] = '\0';
                    fprintf(tempFile, "%04d/%02d/%02d, %s, %s, %d\n", year, month, day, title, newContent, color);
                    // ã�Ҵٴ� ǥ��
                    found = 1;
                    break;

                    // ���� ���� ����
                case 4:
                    gotoxy(28, 35);
                    printf("���ο� ���� (0~15): ");
                    scanf("%d", &newColor);
                    getchar();

                    // ����ü�� �ִ� ��ȣ (0~15)�� ����� ���(15)���� �ڵ� ���� 
                    if (newColor > 15 || newColor < 0)
                    {
                        gotoxy(28, 35);
                        printf("�߸��� �����Դϴ�. ������� �����մϴ�.");
                        newColor = 15;
                    }

                    fprintf(tempFile, "%04d/%02d/%02d, %s, %s, %d\n", year, month, day, title, content, newColor);
                    // ã�Ҵٴ� ǥ��
                    found = 1;
                    break;

                    // �ٸ� ���� �Է½�
                default:
                    gotoxy(28, 35);
                    printf("�߸��� �����Դϴ�.\n");
                    break;
                }
            }
            // ���� ��/��/�������� ���� �����Ϸ��� ������ �ƴ� ��
            else
                fputs(str, tempFile);   // �������� �ʴ� ���� �״�� ����
            count++;
        }
        // �ٸ� ��/��/���̰� ���� �����Ϸ��� ������ �ƴ� ��
        else
            fputs(str, tempFile);       // �ٸ� ��¥�� ���� �״�� ����
    }

    fclose(fp);
    fclose(tempFile);

    if (found == 0)
    {
        gotoxy(25, 35);
        printf("��ȣ�� �ش��ϴ� ������ ���ų� �������� ���߽��ϴ�.");
        Sleep(1000);
        return;
    }

    remove("Plan.txt");             // ���� ���� ����
    rename("temp.txt", "Plan.txt"); // �ӽ� ������ ���� ���Ϸ� �̸� ����

    gotoxy(28, 35);
    printf("                                                                                        ");
    gotoxy(38, 35);
    printf("������ �����Ǿ����ϴ�.");
    Sleep(1000);
    // �ٲ� ������ �ٽ� ����ϰ� 2-1�� reset���� �̵�
    printPlan(year, month, day);

}

// 2-1-4. ���� ���� �Լ�
void deletePlan(int year, int month, int day) {
    FILE* fp, * tempFile;
    char str[256], title[7], content[40];
    int fileYear, fileMonth, fileDay, color;
    int count = 1, number;
    int found = 0;

    cursor(1);
    gotoxy(38, 33);
    printf("������ ������ ��ȣ : ");
    scanf("%d", &number);
    getchar(); // ���� ���� ����

    fp = fopen("Plan.txt", "r+"); // ���� ����
    tempFile = fopen("temp.txt", "w+"); // �ӽ� ���� ����

    if (fp == NULL || tempFile == NULL)
    {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    while (fgets(str, sizeof(str), fp))
    {
        sscanf(str, "%d/%d/%d, %[^,], %[^,], %d", &fileYear, &fileMonth, &fileDay, title, content, &color); // ��¥, ����, ���� ����

        if (fileYear == year && fileMonth == month && fileDay == day)
        {
            if (count != number)
                fputs(str, tempFile); // �������� �ʴ� ���� �״�� ����
            if (count == number)
                found = 1;
            count++;
        }
        else {
            fputs(str, tempFile); // �ٸ� ��¥�� ���� �״�� ����
        }
    }

    fclose(fp);
    fclose(tempFile);

    remove("Plan.txt"); // ���� ���� ����
    rename("temp.txt", "Plan.txt"); // �ӽ� ������ ���� ���Ϸ� �̸� ����

    if (found == 0)
    {
        gotoxy(32, 35);
        printf("��ȣ�� �ش��ϴ� ������ �����ϴ�.");
        Sleep(1000);
        return;
    }

    gotoxy(28, 35);
    printf("                                                                                        ");
    gotoxy(38, 35);
    printf("������ �����Ǿ����ϴ�.");
    Sleep(1000);
    printPlan(year, month, day);
}