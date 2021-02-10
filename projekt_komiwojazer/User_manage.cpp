#include"class.h"
#include<algorithm>
#include<iostream>
#include<random>
#include <chrono>
#include<fstream>
#include<ctime>
#include<string>
#include<stdlib.h>
#include<sstream>


using namespace std;

int Verticles_manual = 0;
int Generations_manual = 0;
int Mutations_manual = 0;
    



void User_manage::open_file(Graf *graf2)
{

	std::ifstream infile;
	string line;
	char path[200];

	cout << endl;
	cout << "                            ENTERING THE DATA FOR GRAPH FROM INPUT .TXT FILE \n";
	cout << "                            ENTER THE PATH TO THE INPUT .TXT FILE \n";
	cin >> path;
	infile.open(path);

	int licznik = 0;
	vector <string> elements;

	if (infile.good()) // Check if the file has been opened correct
	{
		infile.seekg(0, std::ios::end); // Set indicator on the end of the file 
		if (infile.tellg()) { // Check the length of the file to check if the file is empty 
			infile.seekg(0, std::ios::beg);  // Set indicator on the beggining of the file 
			do
			{
				while (getline(infile, line, '\n')) {//read whole line
					std::stringstream sfile(line);
					while (getline(sfile, line, ';')) { // Get a line and save in string 

						elements.push_back(line); // Seperate the elements
					};

					int var = atoi(elements[0].c_str());
					int var2 = atoi(elements[1].c_str());
					int var3 = atoi(elements[2].c_str());
					if (licznik == 0)
					{
						Verticles_manual = var;
						Generations_manual = var2;
						Mutations_manual = var3;
					}
					else
					{
						graf2->Add_Edge(var, var2, var3);
						graf2->Add_Edge(var2, var, var3);
					}
					licznik++;
					elements.clear();
				}

			} while (!infile.eof()); // Perform until end of the file 

			infile.close(); // Close input file 


		}
		else {
			throw string("                            THE FILE IS EMPTY \n");
		
		}
	}
	else {
		throw string("                            THE FILE COULD NOT BE OPENED \n");
		
	}
}

bool choice(int& number)
{
	std::cin >> number;
	while (std::cin.fail())
	{
		std::cout << "		Error : Put A Number Of The Option " << std::endl;//$$$$$$$$$$ poprawic zezby nie dzialalo dla np 1gh zeby pobieral stringa !!!!!!
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> number;
	}

	return true;
}

int digit_check(std::string line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (!(isdigit(line[i])))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits <std::streamsize >::max(), '\n');
			std::cout << "                            ONLY NUMBERS.TRY AGAIN: ";
			std::cin >> line;
			i = 0;
		}
	}

	int i = atoi(line.c_str());//BO TAK 
	return i;

}



void User_manage::start()
{

	cout << endl << "		Welcome in algorithm of Traveling Salesman Problem (TSP)" << endl;
	cout << "		Tell me what do you want to do :" << endl;
	cout << "		(Insert Corresponding numbers 1 or 2)" << endl;
	cout << "		1. -> Generate Random Graph" << endl;
	cout << "		2. -> Insert Verticles Manually" << endl;
	string optio;
	cin >> optio;
	int option = digit_check(optio);

	if (choice)
	{
		while (option != 1 && option != 2)
		{
			cout << "		Error : Put A Number Of The Option (1 or 2)" << std::endl;
			choice(option);

		}
		cout << "		Congrats, Your Choice : " << option << " \n" << endl;
	}

	if (option == 1)
	{
		cout << endl << "		Insert Amount of Verticles :  " << endl;
		string Point_prev;
		cin >> Point_prev;
		int Point = digit_check(Point_prev);
		//choice(Point);
		if (choice)
		{
			while (Point < 5)
			{
				cout << "		Error :  Point Must be Higher Than 4" << std::endl;
				choice(Point);
			}
		}


		cout << endl << "		Insert Amount of Generations :  " << endl;

		string Generations_prev;;
		cin >> Generations_prev;;
		int Generations = digit_check(Generations_prev);


		while (Generations < 10 || Generations >1000)
		{
			cout << "		Error : Number of Generations Must be Higher Than 9" << std::endl;
			cout << "		Error :							 And Lower Than 1000" << std::endl;
			choice(Generations);
		}


		cout << endl << "		Insert Mutation Rate :  " << endl;
		string Mutations_prev;;
		cin >> Mutations_prev;;
		int Mutations = digit_check(Mutations_prev);


		while (Mutations < 3 || Mutations >= 100)
		{
			cout << "		Error : Number of Mutations Must be Higher Than 2" << std::endl;
			cout << "		Error :							And Lower Than 100" << std::endl;
			choice(Mutations);
		}

		int Edges = Point * (Point - 1);
		Graf* graph4 = new Graf(Point, 0, true);
		graph4->Show_info_Graf();
		graph4->show();
		Path Path(graph4, Edges, Generations, Mutations, true);
		const clock_t begin_time = clock(); // gets time
		Path.run(); // runs the genetic algorithm



		cout << "\n\nTime for to run the genetic algorithm: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds."; // shows time in seconds
		cout << endl;
	}
	else
	{
		//tutaj robimy odczyt i jest
		cout << endl << "		Insert Amount of Verticles :  " << endl;
		string Point_prev;
		cin >> Point_prev;
		int Point = digit_check(Point_prev);
		//choice(Point);
		if (choice)
		{
			while (Point < 5)
			{
				cout << "		Error :  Point Must be Higher Than 4" << std::endl;
				choice(Point);
			}
		}

		cout << endl << "		Insert the value of first Point :  " << endl;
		string value_prev;
		cin >> value_prev;
		int value = digit_check(value_prev);
		//choice(Point);
		if (choice)
		{
			while (value < 0)
			{
				cout << "		Error :  Point Must be Higher Than 0" << std::endl;
				choice(value);
			}
		}
		/*cout << endl << "		Insert Amount of Edges :  " << endl;

		string Edges_prev;
		cin >> Edges_prev;
		int Edges = digit_check(Edges_prev);

		while (Edges < 10 || Edges >1000)
		{
			cout << "		Error : Number of Generations Must be Higher Than 9" << std::endl;
			cout << "		Error :							 And Lower Than 1000" << std::endl;
			choice(Edges);
		}
		cout << endl << "		Insert Amount of Generations :  " << endl;

		string Generations_prev;;
		cin >> Generations_prev;;
		int Generations = digit_check(Generations_prev);

		while (Generations < 10 || Generations >1000)
		{
			cout << "		Error : Number of Generations Must be Higher Than 9" << std::endl;
			cout << "		Error :							 And Lower Than 1000" << std::endl;
			choice(Generations);
		}


		cout << endl << "		Insert Mutation Rate :  " << endl;
		string Mutations_prev;;
		cin >> Mutations_prev;;
		int Mutations = digit_check(Mutations_prev);


		while (Mutations < 3 || Mutations >= 100)
		{
			cout << "		Error : Number of Mutations Must be Higher Than 2" << std::endl;
			cout << "		Error :							And Lower Than 100" << std::endl;
			choice(Mutations);
		}*/

		Graf* graf2 = new Graf(Point, value);


		try {
			open_file( graf2);

		}
		catch(string e)
		{
			cout << e;
			cout << "			THE PROGRAM WILL TURN OFF\n";
			exit(EXIT_FAILURE);
		}
	
		graf2->Show_info_Graf();
		graf2->show();
		Path Path(graf2, Verticles_manual, Generations_manual, Mutations_manual);
		const clock_t begin_time = clock(); // gets time
		Path.run(); // runs the genetic algorithm

		cout << "\n\nTime for to run the genetic algorithm: " << float(clock() - begin_time) / CLOCKS_PER_SEC << " seconds."; // shows time in seconds
		cout << endl;

	}

}


