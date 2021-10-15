#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <clocale>
#include <time.h>

#define ABOBA 1488
#define _N 5
using namespace std;


class airliner
{
public: static int quantity;
		int bagWeight;
private: int flightNumber;
		 char* secondName;
		 double ticketPrice;
public:	void toTable()
		{
			printf_s("%-20d%-20s%-20f%-20d",flightNumber,secondName, ticketPrice, bagWeight);
		}
		airliner(int _flightNumber, char _secondName[], double _ticketPrice, int _bagWeight) //����������� � �����������
		{
			quantity++;
			flightNumber=_flightNumber;
			secondName = new char[strlen(_secondName) + 1];
			strcpy(secondName, _secondName);
			ticketPrice=_ticketPrice;
			bagWeight=_bagWeight;
		}
		airliner() //����������� ��� ����������
		{
			quantity++;
			flightNumber=1;
			ticketPrice=0;
			secondName=new char[9];
			strcpy(secondName, "Zolotarev");
			bagWeight=0;
		}
		airliner(const airliner &air) //����������� �����������
		{
			quantity=air.quantity;
			flightNumber=air.flightNumber;
			ticketPrice=air.ticketPrice;
			bagWeight=air.bagWeight;
			secondName = new char[strlen(air.secondName) + 1];
			strcpy(secondName, air.secondName);
		}
		friend void cinNSD(airliner &air)//���� ��� ������� � ��-��
		{
			char buff[50];
			cout << "������� ����� �����:\n ";
			cin >> air.flightNumber;
			cout << "������� �������:\n ";
			cin.ignore();
			gets_s(buff);
			air.secondName = new char[strlen(buff) + 1];
			strcpy(air.secondName, buff);
			cout << "������� ���� ������:\n ";
			cin >> air.ticketPrice;
			cout << "������� ��� ������:\n ";
			cin >> air.bagWeight;
			cout << endl;
		}
		int get_flightNumber() { return flightNumber;}
		int get_ticketPrice() { return ticketPrice;}
		char *get_secondName() {return secondName;}
};

int airliner::quantity = 0; //������������� ��������� �������� ������������ ����
void searchByFlight(airliner FirstDB[]);
void searchByPrice(airliner FirstDB[]);
void toTable(airliner FirstDB[], int N);
void DEL(airliner FirstDB[], int count);

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	
	airliner FirstDB[_N]; //������� ������ �� 5 ��������,  ���� � ��-��
	cout << "������� �� \n";
	for (int i=0;i<_N;i++)
		cinNSD(FirstDB[i]); 

	int count=0; //����� �������
	for (int i=0;i<_N;i++)
		if (FirstDB[i].quantity>count)
			count=FirstDB[i].quantity;

	cout << "���������� ��������� � ��: " << count << endl;
	
	toTable(FirstDB, _N); //������� ��������
	searchByFlight(FirstDB); //���������� ����� ��� ������ ��������� �����
	searchByPrice(FirstDB); //������� ���� ���������� � �������� ������ ���������
	DEL(FirstDB, _N); //������� ������
	
	return 0;
}

void searchByFlight(airliner FirstDB[]) //���������� ����� ��� ������ ��������� �����
{
	bool answer = 1;
	while (answer)
	{
		int count = 0; //����� �������
		int overallWeight=0; //����� ���
		int flight; //����� �����
		cout << "������� ����� �����, ���������� � ������ �������� ������ ��������\n";
		cin >> flight;
		for (int i=0;i<_N;i++)
			if ( flight == FirstDB[i].get_flightNumber() )
				{
					overallWeight+=FirstDB[i].bagWeight; //���������� ��� ������ ��� ������������� �����
					count ++;
				}
		if (count!=0)
			cout << "����� ��� ������ ����� " << overallWeight << endl;
		else cout << "������� ����� ��� � ����\n";
		cout << "������ ����� ������? (1/0)" << endl;
		cin >> answer;
	}
}

void searchByPrice(airliner FirstDB[]) //������� ���� ���������� � �������� ������ ���������
{
	bool answer = 1;
	while (answer)
	{
		int count = 0; //����� �������
		double price=0; //���� ������
		int k=0; //������� ������ �������
		cout << "������� ���� ������\n";
		cin >> price;
		
		for (int i=0;i<_N;i++)
			if ( FirstDB[i].get_ticketPrice() > price)
				count ++; //������� ����� ��������� ����� ��
		cout << "����� ���������� � ����� ������ �������, ��� " << price << ": " << count << endl;
		if (count !=0)
		{
			airliner *NewDB= new airliner[count]; //������� ��
			for (int i=0; i<_N; i++) //��������� ��
				if ( FirstDB[i].get_ticketPrice() > price)
					{
						NewDB[k]=airliner(FirstDB[i]);
						k++;
					} 
			toTable(NewDB, count); //������� � ��������� ����
			
			DEL(NewDB, count); //������� ������
			delete []NewDB;
		}
		cout << "������ ����� ������? (1/0)" << endl;
		cin >> answer;
	}
}

void toTable(airliner FirstDB[], int N) //������� ��������
{
	printf("%-20s%-20s%-20s%-20s","����� �����","�������", "���� ������", "��� ������");
	for (int i=0;i<N;i++)
		FirstDB[i].toTable();
}

void DEL(airliner FirstDB[], int count) //������� ������
{
	for (int i=0; i<count; i++) 
			FirstDB[i].~airliner();
}