# TSP-Travelling-Salesman-Problem
Project created in C++, implementation of Genetic Algorithm in Traveling Slesman problem. 
Program reads from text file graph vertices and using genetic algorithm  designates the shortest path along all vertices.
There are three assumptions:
 - The traveling salesman passes through each vertex only once.
 - Each vertex in the graph is connected to all other vertices.
 - The path determined by the program begins at the selected point, eg "A" and ends there as well. 

This is a main screen with two options, Generating random graph or inserting txt file with prepared vertices. 

![image](https://user-images.githubusercontent.com/44081987/153249835-b213e0ca-0291-42f2-9d01-e11f25f1f277.png)


If user choose option with random graph in next step program will ask how many vertices should be generated, how many generation is needed and what  the mutation rate will be. 


![image](https://user-images.githubusercontent.com/44081987/153258537-5a589f43-c0dd-4936-b597-017798247e8b.png)

After inserting all this data, program will generate random graph with provided values. Photo below shows list of generated graph and connections between vertices: 

![image](https://user-images.githubusercontent.com/44081987/153258674-2034b1a7-2457-4ec4-b65a-780721134504.png)

After this, program shows avaliable paht along all vertices, sorted by its length: 

![image](https://user-images.githubusercontent.com/44081987/153258842-d861d0ac-f9f4-4256-b248-6976d2bad509.png)

Last infomration is number of population in genetic algorithm and shortest path is listed with its lenght.

![image](https://user-images.githubusercontent.com/44081987/153258882-f3319c30-db7d-4895-ac3e-15ed3ddeb950.png)


Error detection is implemented as well in case of entering wrong amounts, user will be informed and program will be waiting for correct input.
Photo below shows example of this situation : 

![image](https://user-images.githubusercontent.com/44081987/153259301-3b729822-3462-4708-b00f-edbb722c0dda.png)



