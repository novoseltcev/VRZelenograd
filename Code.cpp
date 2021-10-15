#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <clocale>
#include <time.h>

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
		airliner(int _flightNumber, char _secondName[], double _ticketPrice, int _bagWeight) //конструктор с параметрами
		{
			quantity++;
			flightNumber=_flightNumber;
			secondName = new char[strlen(_secondName) + 1];
			strcpy(secondName, _secondName);
			ticketPrice=_ticketPrice;
			bagWeight=_bagWeight;
		}
		airliner() //конструктор без параметров
		{
			quantity++;
			flightNumber=1;
			ticketPrice=0;
			secondName=new char[9];
			strcpy(secondName, "Zolotarev");
			bagWeight=0;
		}
		airliner(const airliner &air) //конструктор копирования
		{
			quantity=air.quantity;
			flightNumber=air.flightNumber;
			ticketPrice=air.ticketPrice;
			bagWeight=air.bagWeight;
			secondName = new char[strlen(air.secondName) + 1];
			strcpy(secondName, air.secondName);
		}
		friend void cinNSD(airliner &air)//Ввод НСД объекта с кл-ры
		{
			char buff[50];
			cout << "Введите номер рейса:\n ";
			cin >> air.flightNumber;
			cout << "Введите фамилию:\n ";
			cin.ignore();
			gets_s(buff);
			air.secondName = new char[strlen(buff) + 1];
			strcpy(air.secondName, buff);
			cout << "Введите цену билета:\n ";
			cin >> air.ticketPrice;
			cout << "Введите вес багажа:\n ";
			cin >> air.bagWeight;
			cout << endl;
		}
		int get_flightNumber() { return flightNumber;}
		int get_ticketPrice() { return ticketPrice;}
		char *get_secondName() {return secondName;}
};

int airliner::quantity = 0; //устанавливаем начальное значение статического поля
void searchByFlight(airliner FirstDB[]);
void searchByPrice(airliner FirstDB[]);
void toTable(airliner FirstDB[], int N);
void DEL(airliner FirstDB[], int count);

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	
	airliner FirstDB[_N]; //Создать массив из 5 объектов,  ввод с кл-ры
	cout << "Создаем ДБ \n";
	for (int i=0;i<_N;i++)
		cinNSD(FirstDB[i]); 

	int count=0; //число записей
	for (int i=0;i<_N;i++)
		if (FirstDB[i].quantity>count)
			count=FirstDB[i].quantity;

	cout << "Количество элементов в БД: " << count << endl;
	
	toTable(FirstDB, _N); //выводим таблицей
	searchByFlight(FirstDB); //Определить общий вес багажа заданного рейса
	searchByPrice(FirstDB); //создать базу пассажиров с билетами дороже заданного
	DEL(FirstDB, _N); //очищаем память
	
	return 0;
}

void searchByFlight(airliner FirstDB[]) //Определить общий вес багажа заданного рейса
{
	bool answer = 1;
	while (answer)
	{
		int count = 0; //число записей
		int overallWeight=0; //общий вес
		int flight; //номер рейса
		cout << "Введите номер рейса, информацию о багаже которого хотите получить\n";
		cin >> flight;
		for (int i=0;i<_N;i++)
			if ( flight == FirstDB[i].get_flightNumber() )
				{
					overallWeight+=FirstDB[i].bagWeight; //определяем вес багажа для определенного рейса
					count ++;
				}
		if (count!=0)
			cout << "Общий вес багажа рейса " << overallWeight << endl;
		else cout << "Данного рейса нет в базе\n";
		cout << "Начать поиск заново? (1/0)" << endl;
		cin >> answer;
	}
}

void searchByPrice(airliner FirstDB[]) //создать базу пассажиров с билетами дороже заданного
{
	bool answer = 1;
	while (answer)
	{
		int count = 0; //число записей
		double price=0; //цена билета
		int k=0; //счетчик нового массива
		cout << "Введите цену билета\n";
		cin >> price;
		
		for (int i=0;i<_N;i++)
			if ( FirstDB[i].get_ticketPrice() > price)
				count ++; //считаем число элементов новой бд
		cout << "Число пассажиров с ценой билета большей, чем " << price << ": " << count << endl;
		if (count !=0)
		{
			airliner *NewDB= new airliner[count]; //создаем бд
			for (int i=0; i<_N; i++) //заполняем бд
				if ( FirstDB[i].get_ticketPrice() > price)
					{
						NewDB[k]=airliner(FirstDB[i]);
						k++;
					} 
			toTable(NewDB, count); //выводим в табличном виде
			
			DEL(NewDB, count); //очищаем память
			delete []NewDB;
		}
		cout << "Начать поиск заново? (1/0)" << endl;
		cin >> answer;
	}
}

void toTable(airliner FirstDB[], int N) //выводим таблицей
{
	printf("%-20s%-20s%-20s%-20s","Номер рейса","Фамилия", "Цена билета", "Вес багажа");
	for (int i=0;i<N;i++)
		FirstDB[i].toTable();
}

void DEL(airliner FirstDB[], int count) //очищаем память
{
	for (int i=0; i<count; i++) 
			FirstDB[i].~airliner();
}