#ifndef CALENDAR_H
#define CALENDAR_H
void printCalendar(int month, int year);                    // n�� m���� �޷��� ����ϴ� �Լ�
int firstDay_week(int day, int month, int year);            // ���� 1���� ���� �������� �Ǵ��ϴ� �Լ� (ÿ���� ����)
int numberOfDays(int month, int year);                      // n�� m���� ��ĥ���� �ִ��� ��ȯ�ϴ� �Լ�
int totalday(int year, int month, int day);                 // 0����� �ش� ��¥���� �帥 �ϼ��� ��ȯ�ϴ� �Լ�
int D_day(int choiceyear, int choicemonth, int choiceday);  // ���� ��¥ ���� �ش� ��¥�� ��ĥ ���Ҵ��� ��ȯ�ϴ� �Լ�
#endif
