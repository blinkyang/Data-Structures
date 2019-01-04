// Assigment: Create actor graph and visuzlize with BRIDGES. Also, do some fun stuff with the graph
#include <string>
#include <set>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/ActorMovieIMDB.h"
#include "GraphAdjList.h"
#include <queue>

using namespace std;
using namespace bridges;

string getEnvVar(string const & key);
int BFS(GraphAdjList<string, string> graph, set<string> set, string act1, string act2);
int DSP(GraphAdjList<string, string> graph, set<string> set, string act1, string act2);


int main() {
	Bridges::initialize(1, getEnvVar("BRIDGESUSERNAME"), getEnvVar("BRIDGESKEY"));
	set<string> actors;
	set<string>::iterator it;
	set<string>::iterator it2;




	Bridges::setTitle("Actor Graph: IMDB Data");
	vector<ActorMovieIMDB> actor_list = DataSource::getActorMovieIMDBData(1800);

	// Create a hash table of <actor name, movies acted> more down below
	unordered_multimap<string,string> umap;									//Making Unordered Multimap to store actors
	unordered_multimap<string,string>::iterator mapIt;			//Making map iterators
	unordered_multimap<string,string>::iterator mapIt2;



	// Create a list of actor names with no duplicates (Hint: Use set STL)
	for(int i = 0; i < actor_list.size(); i++)
	{
		string a = actor_list.at(i).getActor();	 			//Extracting Every actor
		actors.insert(a);															//Inputting every actors and letting set handle duplicates
	}

	// Create a GraphAdjList and add vertices corresponding to each actor
	GraphAdjList<string, string> graph;
	for (it = actors.begin(); it != actors.end(); it++)  //Going through the set and inputting all set elements into graph
	{
		graph.addVertex(*it, "");
		graph.getVertex(*it)->getVisualizer()->setOpacity(0.5f);
		graph.getVertex(*it)->getVisualizer()->setColor(Color("red"));  //Change Actors to Red
		if (*it == "Denzel_Washington")
		{
			graph.getVertex(*it)->getVisualizer()->setOpacity(0.5f);
			graph.getVertex(*it)->getVisualizer()->setColor(Color("orange"));  //If Actors is Denzel Washington, use orange for easy identification
		}
	}

	//HASHTABLE STUFF (KY MADE)
	for ( it = actors.begin(); it != actors.end(); it++)  		//Inputting actors hash table made above using set
	{
					for (int j = 0; j < actor_list.size(); j++)  //Going through the IMDB data, and if data actor is the same as list actors, input movie into hashtable
					{
						string actJ = actor_list.at(j).getActor();
						string m = actor_list.at(j).getMovie();

						if (*it == actJ)
						{
								umap.insert({*it,m});
						}
					}
	}


	// For every actor pair, find the movies that they have in common
	// If they have movies in common, insert an edge between the two actor vertices with edge data as number of movies that they have in common
	string act1,act2,mov1,mov2;      //Holders for actors and movies to be compared
	int movCnt;
	for (it = actors.begin(); it != actors.end(); it++)  //For loop to pick static actor to compare rest with
	{
		act1 = *it;
		for (it2 = it; it2 != actors.end();it2++)  //For loop to pick actor to compare with static actor
		{
			act2 = *it2;
			movCnt = 0;											//counter for number of movies
			if(act1 != act2)    										//Ignoring the comparison between same person
				{
					auto range1 = umap.equal_range(act1);
					for (mapIt = range1.first; mapIt != range1.second; mapIt++)   //for loop for picking static movie to compare
					{
								mov1 = (*mapIt).second;
								auto range2 = umap.equal_range(act2);
								for (mapIt2 = range2.first; mapIt2 != range2.second; mapIt2++)  //For loop to pick movies to compare with static movie
								{
									mov2 = (*mapIt2).second;
									if (mov2 == mov1) {movCnt++;}
								}
					}
					if (movCnt > 0){							//Add the edge for any non duplicated actor
						string strCnt = to_string(movCnt);
						if (movCnt > 1) {cout << act1 << " <=> " << act2 << ": " << movCnt << endl;}
						graph.addEdge(act1,act2,movCnt);
						graph.addEdge(act2,act1,movCnt);
					}
				}
		}
	}


	// Display graph
	// provide BRIDGES the  handle to the tree structure
	Bridges::setDataStructure(&graph);				//setting graph and visualizing it
	Bridges::visualize();



	//PROJECT stuff
	//Question 1
	int DOS = 0;
	string projAct1 = "Clark_Gable";
	string projAct2 = "James_Stewart_(I)";
	//string projAct1 = "Yogi_Berra";
	//string projAct1 = "Arnold_Schwarzenegger";
	//string projAct2 = "Denzel_Washington";
	DOS =  BFS(graph, actors, projAct1, projAct2);  						//Function made to do number 1
	cout << projAct1 << " and " << projAct2 << " DOS: " <<  DOS << endl << endl;


	//Question 2
	unordered_multimap<string,int> coMap;								//Making Unordered Multimap to store coActors
	unordered_multimap<string,int>::iterator coIt;				//Iterators for Coactor Map
	string firstCo, secondCo, thirdCo;										//Initializing holders for variables
	int first, second, third;
	first = second = third = INT_MIN;
	for ( it = actors.begin(); it != actors.end(); it++)  		//Loop to iterate through all the vertices (IE Actors)
	{
		int costarCnt = 0;
		SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(*it);  //Make adjacency list for each vertice
		for (SLelement<Edge<string>> *sle = head; sle != nullptr; sle = sle->getNext() ) {   //Loop to pick out all costars and extract num of movies from edge
			costarCnt++;
		}
		coMap.insert({*it,costarCnt});
	}


	for (coIt = coMap.begin(); coIt != coMap.end(); coIt++)   //Loop going through to determine first second and third place
	{
		if(coIt->second > first)
		{
			third = second;
			second = first;
			first = coIt->second;

			thirdCo = secondCo;
			secondCo = firstCo;
			firstCo = coIt->first;
		}
		else if(coIt->second > second)
		{
			third = second;
			second = coIt->second;

			thirdCo = secondCo;
			secondCo = coIt->first;
		}
		else if(coIt->second > third)
		{
			third = coIt->second;

			thirdCo = coIt->first;
		}
	}
	cout << "Top three People with costars!" << endl;
	cout << firstCo << ": " << first << endl;
	cout << secondCo << ": " << second << endl;
	cout << thirdCo << ": " << third << endl;


	//Question 3
	int minMov = DSP(graph, actors, projAct1, projAct2); //Function made to do question 3
	cout << "Minimum Movies: " << minMov << endl;







	return 0;
}

string getEnvVar(string const & key) {
    char * val = getenv( key.c_str() );
    return val == NULL ? string("") : string(val);
}


int BFS(GraphAdjList<string, string> graph, set<string> set, string act1, string act2){

	unordered_map<string,int> DOSMap;				//Initializing Parameters
	queue<string> actQ;
	int DOS = 0;
	string tarAct;
	int snapSize = 1;

	for (auto it = set.begin(); it != set.end(); it++) //Initializing all Vertexs as unseen
	{
		DOSMap.insert({*it, -1});
	}

	actQ.push(act1);					//Initializing actor 1 art beginning point
	DOSMap[act1] = 0;
	while(tarAct != act2)     //While Loop to find Degree of Separation (Until actor 2 is found)
	{
		snapSize = actQ.size();  //Incrementor to finish layer then progress
		DOS++;
		while(snapSize > 0)  //Finish queue layer then progress
		{
			SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(actQ.front());
			for (SLelement<Edge<string>> *sle = head; sle != nullptr; sle = sle->getNext() )
			{
				string currAct = sle->getValue().getVertex();
				if(DOSMap[currAct] == -1)
				{
					if (currAct == act2) {tarAct = act2;}   //Setting exit parameter
					DOSMap[currAct] = DOS;
					actQ.push(currAct);       //Pushing layer elements into queue
				}
			}
			actQ.pop();
			snapSize--;
		}
	}
	return DOSMap[act2];
}





int DSP(GraphAdjList<string, string> graph, set<string> set, string act1, string act2){
	int minMov = 0;


	/*
	SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(act1);									Initial check to check for 1st layer costar, and return their movies
	for (SLelement<Edge<string>> *sle = head; sle != nullptr; sle = sle->getNext() )
	{
		string term_vertex = sle->getValue().getVertex();
		if (term_vertex == act2) {
			minMov = sle->getValue().getWeight();
			return minMov;
		}
	} */


	unordered_map<string,int> distMap;
	unordered_map<string,string> pathMap;
	queue<string> actQ;
	queue<string> pathQ;

	for (auto it = set.begin(); it != set.end(); it++) //Initializing all Vertexs as unseen
	{
		distMap.insert({*it, -1});
	}

	actQ.push(act1);																	//intialize actor 1 as start point
	while( actQ.size() > 0)														//While loop that continues until queue is clear
	{
			SLelement<Edge<string>>  *head = graph.getAdjacencyList().at(actQ.front());
			for (SLelement<Edge<string>> *sle = head; sle != nullptr; sle = sle->getNext() )  //Loop to go through each first layer of head of queue
			{
				string currAct = sle->getValue().getVertex();																		//Getting actors being analyzed
				int thisWeight = distMap[actQ.front()] + sle->getValue().getWeight();  					//Finding the new potential movie count of the current Actor
				int bestWeight = distMap[currAct];																							//Finding the actual "best" movie count of current
				if(bestWeight == -1)																														//Assigning "best" movie Count if this is first time
				{
						bestWeight = sle->getValue().getWeight();
						distMap[currAct] = bestWeight;
						actQ.push(currAct);																						//Pushing actors into queue
						pathMap.emplace(actQ.front(),currAct);												//Putting actors into hashmap to for graph visualization
				}
				else if (thisWeight < bestWeight)
					{
						bestWeight = thisWeight;
						distMap[currAct] = bestWeight;
						actQ.push(currAct);
						pathMap.emplace(actQ.front(),currAct);
					}

			}
			actQ.pop();							//Removing analyzed actor after finishing
	}

	string tarActor = act1;
	pathQ.push(act2);
	while(pathQ.size() > 0 && tarActor != act1)      //Reverse Tracking path of DSP
	{
		string temp = pathQ.front();
		graph.getVertex(pathQ.front())->getVisualizer()->setColor(Color("green"));
		pathQ.pop();
		for (auto pathIt = pathMap.begin(); pathIt != pathMap.end(); pathIt++)
		{
			if ((*pathIt).second == act2) {tarActor = act1; }
			if ((*pathIt).second == temp) { pathQ.push((*pathIt).first); }
		}
	}

	Bridges::setDataStructure(&graph);				//setting graph and visualizing it
	Bridges::visualize();


	return distMap[act2];





}


























//
