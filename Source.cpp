#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef struct proccess
{
	int at, bt, ct, ta, wt, btt, ind, mt;
	string pro_id;

	string s;
	/*
at = время прибытия,
bt = время выполнения,
ct = время завершения,
ta = время прибывания,
wt = время ожидания
*/

}Schedule;

bool compare(Schedule a, Schedule b)
{
	return a.at < b.at;
}

bool compare2(Schedule a, Schedule b)
{
	return a.bt < b.bt;
}

bool compare3(Schedule a, Schedule b)
{
	return a.ind < b.ind;

}

void primer(Schedule *pro, int n)
{
	pro[0].pro_id = "P1"; pro[1].pro_id = "P2"; pro[2].pro_id = "P3"; pro[3].pro_id = "P4";
	pro[0].at = 2; pro[1].at = 0; pro[2].at = 1; pro[3].at = 5;
	pro[0].bt = 12; pro[1].bt = 16; pro[2].bt = 8; pro[3].bt = 2;

	pro[0].btt = pro[0].bt;
	pro[0].s = " - ";
	pro[0].ind = 0;

	pro[1].btt = pro[1].bt;
	pro[1].s = " - ";
	pro[1].ind = 1;

	pro[2].btt = pro[2].bt;
	pro[2].s = " - ";
	pro[2].ind = 2;

	pro[3].btt = pro[3].bt;
	pro[3].s = " - ";
	pro[3].ind = 3;
}

void random(Schedule *pro, int n)
{
	for (int i = 0; i < n; i++)
	{
		pro[i].pro_id= i;
		pro[i].at=rand()%10;
		pro[i].bt=rand()%20+1;
		pro[i].btt = pro[i].bt;
		pro[i].s = " - ";
		pro[i].ind = i;
	}
}


void input(Schedule *pro, int n)
{
	for (int i = 0; i < n; i++)
	{
		cin >> pro[i].pro_id;
		cin>>pro[i].at;
		cin >> pro[i].bt;
		pro[i].btt = pro[i].bt;
		pro[i].s = " - ";
		pro[i].ind = i;
	}
}

void print(Schedule* pro, int n) //вывод
{
	cout << "\nProID\tВремя прибытия\tВремя выполнения\tВремя завершения\tВремя прибывания\tВремя ожидания\n";
	sort(pro, pro + n, compare3);
	for (int i = 0; i < n; i++)
	{
		pro[i].ta = pro[i].ct - pro[i].at;
		pro[i].wt = pro[i].ta - pro[i].btt;

		cout << pro[i].pro_id << "\t" << pro[i].at << "\t\t" << pro[i].btt << "\t\t\t" << pro[i].ct << "\t\t\t" << pro[i].ta << "\t\t\t" << pro[i].wt << "\t\t\t";
		cout << endl;
	}
}

void FSJF(Schedule* pro, int n)
{
	int j;
	int pcom = 0;
	int Q = 0;

	sort(pro, pro + n, compare);//сортируем по времени прибытия

	while (pcom < n)
	{
		for (j = 0; j < n; j++)
			if (pro[j].at > Q) break;

		for (int i = 0; i < n; i++)
			if (pro[i].at == Q) pro[i].s = "rea";

		int j2 = j;
		sort(pro, pro + j, compare2);//сортируем по времени выполнения те процессы, которые уже прибыли

		int temp = j;
		if (j > 0)
		{
			for (j = 0; j < n; j++)
				if (pro[j].bt != 0) break;

			pro[j].ct = Q + 1;
			temp = j;
			pro[j].s = "run";

			for (int k = 0; k < n; k++)
				if (j != k && pro[k].s == "run") pro[k].s = " ~ ";
		}

		pcom = 0;
		for (j = 0; j < n; j++)
		{
			if (pro[j].bt == 0)
			{
				pcom++;
				pro[j].s = "done";
			}
		}

		pro[temp].bt--;
		sort(pro, pro + n, compare3);//сортировка для вывода
		cout << Q << " кв.\t";
		for (int i = 0; i < n; i++)
			cout << pro[i].s << "\t";
		cout << "\n";
		Q++;

		sort(pro, pro + j, compare);
		sort(pro, pro + j2, compare2); //сортируем по времени выполнения те процессы, которые уже прибыли

	}
}

int main()
{
	setlocale(LC_ALL, "Ru");
	Schedule pro[10];
	
	int n = 4;
	primer(pro, n);
	FSJF(pro, n);

	print(pro, n);

	cout << "\n\n\n";
	system("pause");
	return 0;
}
