# TSP-Travelling-Salesman-Problem
Project created in C++, implementation of Genetic Algorithm in Traveling Slesman problem. 
Program reads from text file graph vertices and using genetic algorithm  designates the shortest path along all vertices.
There are three assumptions:
 - The traveling salesman passes through each vertex only once.
 - Each vertex in the graph is connected to all other vertices.
 - The path determined by the program begins at the selected point, eg "A" and ends there as well. 

This is a main screen with two options, Generating random graph or inserting txt file with prepared vertices. 

![image](https://user-images.githubusercontent.com/44081987/153249835-b213e0ca-0291-42f2-9d01-e11f25f1f277.png)

Example text file with vertices below:

![image](https://user-images.githubusercontent.com/44081987/153254554-072e681e-a8eb-4537-be56-114442aabc5b.png)

If user choose option with random graph in next step program will ask how many vertices should be generated: 

![image](https://user-images.githubusercontent.com/44081987/153255111-68167795-5128-4d77-9263-34ff960f5095.png)

In this step user have to insert how many generation of generic algorithm will be used.

![image](https://user-images.githubusercontent.com/44081987/153255254-5f79cba4-e794-41ac-b6f4-9240328fceb2.png)

Last step is to insert mutation rate also used by genetic algorithm. Value should be grater than 2 and smaller than 100. 

![image](https://user-images.githubusercontent.com/44081987/153256004-55ea5e85-0432-4585-b9e2-a334dce0455a.png)

Error detection is implemented as well in case of entering wrong amounts, user will be informed and program will be waiting for correct input.


