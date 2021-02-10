#pragma once
#include <string>
#include <vector>
#include <map>
#include<utility>
#include<time.h>
#include<stdlib.h>



class Obiekt
{
public:
	
	virtual void show()=0;// wypisz
	virtual void delet() = 0;//usun
	
	// tutaj jeszcze zrobic dekonstruktor
	virtual ~Obiekt() {};
};


class Graf : public Obiekt
{
protected:

	//std::vector<Point>punkty;

	int amount_of_verticles; // liczba wierzcholkow
	int total_edg; // ilosc krawedzi
	int first_vertex; //pierwszy wierzcholek
	std::map<std::pair<int, int>, int>map_edges;
	void Add_Edge(int X, int Y, int weight);// dodaje krawÍdü   dodaj do protected
	void GenerateGraf();// generuje losowy graf
	int Exsist(int x, int y);//sprawdza czy istnieje juø jakis graf

public:
	Graf(int number, int first, bool random_graph = false); //konstruktor

	 virtual void show(); 
	 void Show_info_Graf();//pokazuje informacje o grafie 
	 void delet() override {};
	 ~Graf() {};
	
	friend class Path; //przyjaün po to øeby sciezka mia≥a dostep do prywatnych zmiennych
	friend class User_manage;
};

typedef std::pair<std::vector<int>, int>pary_elem;

struct sort_pred
{
	bool operator()(const pary_elem& firstElem, const pary_elem& secondElem)
	{
		return firstElem.second < secondElem.second;
	}
};

//class sort//sortuje wektor parami 
//{
//public: 
//	
//	bool operator()(const pary_elem& firstElem, const pary_elem& secondElem)
//	{
//		return firstElem.second < secondElem.second;
//	}
//
//};

class Path : public Obiekt
{
	Graf* graf;//obiekt typu graf
	std::vector<pary_elem>population; // kaødy element pary to jeden punkt vector i koszt(odleglosc)
	int num_of_populacji;//size of population
	int real_size_population;//real sizee
	int generation;//amount of generations
	int num_of_mut;//mutiation rate
	bool show_popoulation;//flag to show population

	void first_population();//p
	int Valid_solution(std::vector<int>& solution);
	void Cross_Over(std::vector<int>& parent1, std::vector<int>& parent2);
	void Binary_search(std::vector<int>& child, int total_cost);
	void run();
	int Best_Solution();
	bool Exist_chromosome(const std::vector<int>& v);
public:

	Path(Graf* graf, int amount_of_population, int generations, int mutation_rate, bool show_population = true);
	
	
	virtual void show() ;
	void delet() override {};
	~Path() {};
	friend class Graf;
	friend class User_manage;
};


class User_manage
{
	void open_file(Graf* graf2);
public:
	User_manage() {};
	void start();
	friend class Graf;
	friend class Path;
	~User_manage() {};
};

bool choice(int& number);
int digit_check(std::string line);


