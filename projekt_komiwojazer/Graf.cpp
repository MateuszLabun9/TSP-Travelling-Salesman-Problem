#include "class.h"
#include<algorithm>
#include<iostream>
#include<random>
#include <chrono>

using namespace std;

Graf::Graf(int number, int first, bool random_graph)//konstruktor
{
	if (number < 1)//sprawdzam czy liczba wierzchołków jest mniejsza niż jeden
	{
		cout << "Error : number of vertexses is less than 1" << endl;
		exit(1);
	}

	this->amount_of_verticles = number; // zapisuje liczbę wierzchołków
	this->first_vertex = first;
	this->total_edg = 0;// ustalam długosc krwaedzi na 0 
	if (random_graph)
	{
		GenerateGraf();
	}
}


void Graf::GenerateGraf()
{
	vector<int>vec; // generuje wektor punktow

	for (int i = 0; i < amount_of_verticles; i++)// wygenerowane punkty to wartosci po prostu kolejne
	{
		vec.push_back(i);//dodaje kolejne elementy (na sam koniec)
	}

	random_shuffle(vec.begin(), vec.end());//tutaj mieszam te wartosci zamieniajac je miejscami 

	first_vertex = vec[0];//przypisuje pierwszy element wektora jako wierzcholek poczatkowy

	int weight;// waga 

	for (int i = 0; i < amount_of_verticles; i++)
	{
		weight = rand() % amount_of_verticles + 1;//losowa wartosc z przedzia³u [1,liczba wierzcho³ków];

		if (i + 1 < amount_of_verticles)// na poczatku tworze zamkniety graf 
		{
			Add_Edge(vec[i], vec[i + 1], weight);//biore losowe wspolrzedne
		}
		else // jesli nie to tworze ostatni element 
		{
			Add_Edge(vec[i], vec[0], weight);
			break;
		}
	}

	int limit_edges = amount_of_verticles * (amount_of_verticles - 1);//skonczona ilosc mozliwych kombinacji ulozenia 
	//zmiennych w jednej scierzce
	int size_edges = rand() % (2 * limit_edges) + limit_edges;


	// dodanie pozosta³ych wierzcho³ków w losowy wsposob
	for (int i = 0; i < size_edges; i++)
	{
		int x = rand() % amount_of_verticles;
		int y = rand() % amount_of_verticles;
		weight = rand() % (2 * limit_edges) + limit_edges;
		if (x != y)
		{
			Add_Edge(vec[x], vec[y], weight);
			Add_Edge(vec[y], vec[x], weight);
		}

	}


}

//-----------------------------------------------------------------------------------------------------

void Graf::Add_Edge(int X, int Y, int weight)//dodaje krawedz
{
	map_edges[make_pair(X,Y)] = weight;//dodaje krawedz do mapy
}



void Graf::Show_info_Graf()
{
	cout << "Shows information about graph" << endl;
	cout << "Number of Verticles : " << amount_of_verticles << endl;
	cout << "Number of Edges : " << map_edges.size() << endl;
}

void Graf::show() {
	
	map<pair<int, int>, int>::iterator it;
		for (it = map_edges.begin(); it != map_edges.end(); it++)
		{
			cout << it->first.first << " polaczone do weirzcholka : " << it->first.second << " z waga : " << it->second << endl;
		}
	
}



int Graf::Exsist(int x, int y)//sprawdza czy istnieje taka krawedz
{
	map<pair<int, int>, int>::iterator it = map_edges.find(make_pair(x, y));
	if(it!=map_edges.end())
	{
		return it->second;
	}
	return -1;
}

