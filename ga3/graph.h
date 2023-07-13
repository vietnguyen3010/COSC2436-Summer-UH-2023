#ifndef graph_h
#define graph_h

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


struct edge
{
	int start;
	int des;
	int weight;
	
};

class graph
{
private:
	int numVertices;
	vector<vector<int>> matrix;
	
public:
	graph(int numVertices)
	{
		numVertices = numVertices;
		matrix.resize(numVertices, vector<int>(numVertices, 0));
	}
	void inserEdge(int v1, int v2, int weight)
	{
		matrix[v1][v2] = weight;
		matrix[v2][v1] = weight;
	}

	void BFS(int vertex)
	{	
		vector<bool> visited(numVertices, false);
		queue<int> q;
		visited[0] = true;
		q.push(0);

		while(!q.empty())
		{
			int cu = q.front();
			q.pop();

			for (int i = 0; i < numVertices; i++)
			{
				if (matrix[cu][i] != 0 && !visited[i])
				{
					visited[i] = true;
					q.push(i);
				}
			}
		}
		return ()
	}

	int MST() {
		int numEdges = 0;
		visited[0] = true;
		int row, col, span = 0;

		while (numEdges < size - 1) {
			int min = INT_MAX;
			row = col = 0;

			for (int i = 0; i < size; i++) {
				if (visited[i]) {
					for (int j = 0; j < size; j++) {
						if (!visited[j] && matrix[i][j] != -1) {
							if (min > matrix[i][j]) {
								min = matrix[i][j];
								row = i;
								col = j;
							}
						}
					}
				}
			}

			span += matrix[row][col];
			visited[col] = true;
			numEdges++;
		}

		return span;
	}
	
};






#endif