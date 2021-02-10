#include"class.h"
#include <string>
#include <vector>
#include <map>
#include<utility>
#include<time.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include <set>
#include <random>
#include <chrono>

using std::vector;

Path::Path(Graf* graf, int amount_of_population, int generations, int mutation_rate, bool show_population )
{
	if (amount_of_population < 1)//sprawdza czy wielkosc populacji jest mniejsza ni¿ 1
	{
		std::cout << "Error: sieze of population is smaller than 1\n";
		exit(1);
	}
	else if (mutation_rate < 0 || mutation_rate>100)
	{
		std::cout << "Error: mutation rate must be >=0 and <-100\n";
		exit(1);
	}
	this->graf = graf;
	this->num_of_populacji = amount_of_population;
	this->generation = generations;
	this->num_of_mut = mutation_rate;
	this->show_popoulation = show_population;
	this->real_size_population = 0;

}



int Path::Valid_solution(std::vector<int>& solution)// checks if is a valid solution, then return total cost of path else if its wrong return -1
{

	int total_cost = 0;
	std::set<int>set_solution;

	for (int i = 0; i < graf->amount_of_verticles; i++)//checks if not contains repeated elements
	{
		set_solution.insert(solution[i]);
	}
	if (set_solution.size() != (unsigned)graf->amount_of_verticles)//mapa nie zapisuje do siebie wartosci
		//powtórzonych wiec gdy siê powtórzy coœ to bedzie mniejsza d³ugosc tego kontenera
		return -1;
		
	for (int i = 0; i < graf->amount_of_verticles; i++)//checks if connections are valid
	{
		if (i + 1 < graf->amount_of_verticles)
		{
			int cost = graf->Exsist(solution[i], solution[i + 1]);
			if (cost == -1)
			{
				return -1;
			}
			else
				total_cost += cost;
		}
		else
		{
			int cost = graf->Exsist(solution[i], solution[0]);

			if (cost == -1)
			{
				return -1;
			}
			else
				total_cost += cost;
			break;
		}


	}

	return total_cost;
}



bool Path::Exist_chromosome(const std::vector<int>& v)
{
	//checks if exsist in the population 
	for (std::vector<std::pair<std::vector<int>, int>>::iterator it = population.begin(); it != population.end(); ++it)
	{
		const vector<int>& vec = it->first;//gets vector
		if (equal(v.begin(), v.end(), vec.begin()))//compares vectors
			return true;
	}
	return false;
}


void Path::first_population()//generates initial population
{
	vector<int>parent;
	//inserts initial vertex in the parent 
	parent.push_back(graf->first_vertex);

	//creates the parent 
	for (int i = 0; i < graf->amount_of_verticles; i++)
	{
		if (i != graf->first_vertex)
			parent.push_back(i);

	}

	int total_cost = Valid_solution(parent);

	if (total_cost != -1)// checks if the parent is valid
	{
		population.push_back(make_pair(parent, total_cost));//inserts in population
		real_size_population++; // increments real_size_population
	}

	//makes random permutation "generations" times

	for (int i = 0; i < generation; i++)
	{
		//generates random permutation
		unsigned seed2 = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine genx;
		std::uniform_int_distribution<int> distx(1, graf->amount_of_verticles);
		int rand_value = distx(genx);

		std::random_shuffle(parent.begin() + 1, parent.begin() + rand_value);//(rand() % (graf->amount_of_verticles - 1) + 1)

		int total_cost = Valid_solution(parent);//checks if solution is vaild

												//chechks if premutation is vaild solution and if not exist
		if (total_cost != -1 && !Exist_chromosome(parent)) {
			population.push_back(std::make_pair(parent, total_cost));//add in population
			real_size_population++;

		}
		if (real_size_population == num_of_populacji)//checks size of population
			break;
	}

	//chechks if real size is equal to 0
	if (real_size_population == 0) {
		std::cout << "\nEmpty initial population, try again\n";
	}
	else
		std::sort(population.begin(), population.end(), sort_pred());
		//std::stable_sort(population.begin(), population.end());
}


void Path::show()
{
	std::cout << "\nshowing population\n" << std::endl;
	for (vector<std::pair<vector<int>, int>>::iterator it = population.begin(); it != population.end();++it) {
		const vector<int>& vec = it->first;//gets vector

		for (int i = 0; i < graf->amount_of_verticles; i++)
		{
			std::cout << vec[i] << " ";
		}
			std::cout << graf->first_vertex;
			std::cout << " | cost : " << it->second << "\n\n";
	
	}
	std::cout << "\nPopulation size : " << real_size_population << std::endl;

}

void Path::Binary_search(std::vector<int>& child, int total_cost)//inserts the vector using binary search
{
	int imin = 0;
	int imax = real_size_population - 1;

	while (imax >= imin)
	{
		int imid = imin + (imax - imin) / 2;
		if (total_cost == population[imid].second)
		{
			population.insert(population.begin() + imid, std::make_pair(child, total_cost));
			return;
		}
		else if (total_cost > population[imid].second)
			imin = imid + 1;
		else
			imax = imid - 1;

	}
	population.insert(population.begin() + imin, std::make_pair(child, total_cost));
}

void Path::Cross_Over(std::vector<int>& parent1, std::vector<int>& parent2)
{
	vector<int>child1, child2;

	//map of genes, checks if already are selected
	std::map<int, int>genes1, genes2;

	for (int i = 0; i < graf->amount_of_verticles; i++)
	{
		genes1[parent1[i]] = 0;//on the beginning the genes are not used 
		genes2[parent2[i]] = 0;
	}

	//generates random points
	
	//proba----------------------------------
	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//std::default_random_engine gen(seed);
	//std::uniform_int_distribution<int> dist(1, graf->amount_of_verticles-1);
	//int point1 = dist(gen);
	////std::default_random_engine gen2;
	//std::uniform_int_distribution<int> dist2(point1, graf->amount_of_verticles-point1);
	//int point2 = dist2(gen);
	//-----------------------------------
	
	int point1 = rand() % (graf->amount_of_verticles - 1) + 1;//generate random pionts
	int point2 = rand() % (graf->amount_of_verticles - point1) + point1;

	//add points if they are equal
	if (point1 == point2)
	{
		if (point1 - 1 > 1)
			point1--;
		else if (point2 + 1 < graf->amount_of_verticles)
			point2++;
		else
		{
			//choose randomly point 1 or point 2
			//-------------random generator
			//std::default_random_engine gen3;
			//std::uniform_int_distribution<int> dist3(1,10);
			//int point = dist3(gen);
			//-----------------------------
			int point = rand() % 10 + 1;//range 1-10
			
			
			
			if (point <= 5)
				point1--;
			else
				point2++;
		}
	}
	//generates childs

	//point1 child1 receives genes form parent 1
	//child 2 receive genes from parent 2

	for (int i = 0; i < point1; i++)
	{
		//add genes
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
		//marks genes
		genes1[parent1[i]]=1;
		genes2[parent2[i]]=1;
	}

	//marks remaining genes
	for (int i = point2 + 1; i < graf->amount_of_verticles; i++)
	{
		genes1[parent1[i]]=1;
		genes2[parent2[i]]=1;
	}
	//substring here
	//child1 receive form parent 2
	//child 2 form parent 1
	for (int i = point2; i >= point1; i--)
	{
		if(genes1[parent2[i]] == 0) // if the gene is not used
		{
			child1.push_back(parent2[i]);
			genes1[parent2[i]] = 1; // marks the gene	
		}
		else
		{
			// if the gene already is used, chooses gene that is not used
			for (std::map<int, int>::iterator it = genes1.begin(); it != genes1.end(); ++it)
			{
				if (it->second == 0) // checks if is not used
				{
					child1.push_back(it->first);
					genes1[it->first] = 1; // marks as used
					break; // left the loop
				}
			}
		}
		if (genes2[parent1[i]] == 0) // if the gene is not used
		{
			child2.push_back(parent1[i]);
			genes2[parent1[i]] = 1; // marks the gene
		}
		else
		{
			// if the gene already is used, chooses gene that is not used
			for (std::map<int, int>::iterator it = genes2.begin(); it != genes2.end(); ++it)
			{
				if (it->second == 0) // checks if is not used
				{
					child2.push_back(it->first);
					genes2[it->first] = 1; // marks as used
					break; // left the loop
				}
			}
		}

	}
	// ramaining genes: child1 receives genes of the parent1
	// and child2 receives genes of the parent2
	for (int i = point2 + 1; i < graf->amount_of_verticles; i++)
	{
		child1.push_back(parent1[i]);
		child2.push_back(parent2[i]);
	}

	// mutation
	
	//---------------------------------
	//unsigned seed3 = std::chrono::system_clock::now().time_since_epoch().count();
	//std::default_random_engine gen4(seed3);
	//std::uniform_int_distribution<int> dist4(1,100);
	//int mutation = dist4(gen4);
	//-----------------------------------
	
	int mutation = rand() % 100 + 1; // random number in [1,100]
	
	if (mutation <= num_of_mut) // checks if the random number <= mutation rate
	{
		// makes a mutation: change of two genes

		int index_gene1, index_gene2;
		
		//--------------------------------------------
		/*std::default_random_engine gen5;
		std::uniform_int_distribution<int> dist5(1, graf->amount_of_verticles-1 );
		index_gene1 = dist5(gen5);
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine gen6(seed);
		std::uniform_int_distribution<int> dist6(1, graf->amount_of_verticles-1 );
		index_gene2 = dist6(gen6);*/
		//--------------------------------------------
		
		index_gene1 = rand() % (graf->amount_of_verticles - 1) + 1;
		index_gene2 = rand() % (graf->amount_of_verticles -1) + 1;

		//--------------------------------------------

		// makes for child1
		int aux = child1[index_gene1];
		child1[index_gene1] = child1[index_gene2];
		child1[index_gene2] = aux;

		// makes for child2
		aux = child2[index_gene1];
		child2[index_gene1] = child2[index_gene2];
		child2[index_gene2] = aux;
	}


	int total_cost_child1 = Valid_solution(child1);
	int total_cost_child2 = Valid_solution(child2);

	// checks if is a valid solution and not exists in the population
	if (total_cost_child1 != -1 && !Exist_chromosome(child1))
	{
		// add child in the population
		Binary_search(child1, total_cost_child1); // uses binary search to insert
		real_size_population++; // increments the real_size_population
	}

	// checks again...
	if (total_cost_child2 != -1 && !Exist_chromosome(child2))
	{
		// add child in the population
		Binary_search(child2, total_cost_child2); // uses binary search to insert
		real_size_population++; // increments the real_size_population
	}

}



void Path::run()
{
	first_population(); // gets initial population

	if (real_size_population == 0)
		return;

	for (int i = 0; i < generation; i++)
	{


		int  old_size_population = real_size_population;

		/* selects two parents (if exists) who will participate
			of the reproduction process */
		if (real_size_population >= 2)
		{
			if (real_size_population == 2)
			{
				// applying crossover in the parents
				Cross_Over(population[0].first, population[1].first);
			}
			else
			{
				// real_size_population > 2

				int parent1, parent2;

				do
				{
					// select two random parents
					//------------------------------------------------------------
					unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
					std::default_random_engine gen9(seed);
					std::uniform_int_distribution<int> dist9(0,real_size_population-1);
					parent1 = dist9(gen9);
					std::default_random_engine gen10;
					std::uniform_int_distribution<int> dist10(0, real_size_population-1);
					parent2 = dist9(gen10);
					//-------------------------------------

					//parent1 = rand() % real_size_population;
					//parent2 = rand() % real_size_population;
				} while (parent1 == parent2);

				// applying crossover in the two parents
				Cross_Over(population[parent1].first, population[parent2].first);
			}

			// gets difference to check if the population grew 
			int diff_population = real_size_population - old_size_population;

			if (diff_population == 2)
			{
				if (real_size_population > num_of_populacji)
				{
					// removes the two worst parents of the population
					population.pop_back();
					population.pop_back();

					// decrements the real_size_population in 2 units
					real_size_population -= 2;
				}
			}
			else if (diff_population == 1)
			{
				if (real_size_population > num_of_populacji)
				{
					population.pop_back(); // removes the worst parent of the population
					real_size_population--; // decrements the real_size_population in the unit
				}
			}
		}
		else // population contains only 1 parent
		{
			// applying crossover in the parent
			Cross_Over(population[0].first, population[0].first);

			if (real_size_population > num_of_populacji)
			{
				population.pop_back(); // removes the worst parent of the population
				real_size_population--; // decrements the real_size_population in the unit
			}
		}
	}

	if (show_popoulation == true)
		show(); // shows the population

	std::cout << "\nBest solution: ";
	const vector<int>& vec = population[0].first;
	for (int i = 0; i < graf->amount_of_verticles; i++)
		std::cout << vec[i] << " ";
	std::cout << graf->first_vertex;
	std::cout << " | Cost: " << population[0].second;

}

int Path::Best_Solution()
{
	if (real_size_population > 0)
		return population[0].second;
	return -1;
}



