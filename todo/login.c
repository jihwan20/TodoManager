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
#include "login.h"

// ���̵� �ߺ� �˻�
int checkDupID(const char* id)
{
    FILE* file = fopen("member.txt", "r");

    if (file == NULL) {
        perror("���� ���� ����\n");
        return 1;
    }

    MEMBER currentMember;
    
    while (fscanf(file, "%s %s", currentMember.id, currentMember.password) == 2) {
        if (strcmp(id, currentMember.id) == 0) {
            fclose(file);
            return 0; // �ߺ���
        }
    }

    fclose(file);
    return 1; // �ߺ� ����
}

// ȸ������ �Լ�
void addMember()
{
    FILE* file = fopen("member.txt", "a");

    if (file == NULL) {
        gotoxy(44, 20);
        perror("���� ���� ����\n");
        Sleep(1000);
        return;
    }

    MEMBER newMember;

    system("cls");
    printBOX();
    gotoxy(38, 13);
    printf("���̵�: ");
    scanf("%s", newMember.id);

    // �ߺ� �˻� �߰�
    if (!checkDupID(newMember.id)) {
        fclose(file);
        gotoxy(38, 20);
        printf("�̹� �����ϴ� ���̵��Դϴ�.\n");
        Sleep(1000);
        return;
    }

    getchar();
    gotoxy(38, 15);
    printf("��й�ȣ: ");
    scanf("%s", newMember.password);
    getchar();
    fprintf(file, "%s %s\n", newMember.id, newMember.password);

    fclose(file);
    gotoxy(44, 20);
    for (int i = 0; i < 15; i++)
    {
        char addOK[15] = { "ȸ������ ����!" };
        printf("%c", addOK[i]);
        Sleep(100);
    }
    Sleep(1000);
}

// �α��� �Լ�
int login()
{
    FILE* file = fopen("member.txt", "r");

    if (file == NULL) {
        gotoxy(38, 20);
        perror("���� ���� ����");
        return 0;
    }

    char inputUsername[MAX_ID];
    char inputPassword[MAX_PASSWORD];

    system("cls");
    printBOX();

    gotoxy(38, 13);
    printf("���̵�: ");
    scanf("%s", inputUsername);

    gotoxy(38, 15);
    printf("��й�ȣ: ");
    scanf("%s", inputPassword);

    MEMBER currentMember;

    while (fscanf(file, "%s %s", currentMember.id, currentMember.password) == 2) {
        if (strcmp(inputUsername, currentMember.id) == 0 && strcmp(inputPassword, currentMember.password) == 0) {
            fclose(file);
            gotoxy(44, 20);
            for (int i = 0; i < 13; i++)
            {
                char loginOK[13] = { "�α��� ����!" };
                printf("%c", loginOK[i]);
                Sleep(100);
            }
            Sleep(1000);
            return 1; // �α��� ����
        }
    }

    fclose(file);
    gotoxy(44, 20);
    printf("�α��� ����.\n");
    Sleep(1000);
    return 0; // �α��� ����
}