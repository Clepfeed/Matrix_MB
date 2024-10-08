#include <iostream>
#include <random>
#include <time.h>
#include <chrono>

using namespace std;

void printMatrixFandL5(vector<double>& matrix)
{
	for (int i = 0; i < 5; i++)
	{
		cout << matrix[i] << " ";
	}
	cout << "\n";
	for (int i = matrix.size() - 5; i < matrix.size(); i++)
	{
		cout << matrix[i] << " ";
	}
}

void printMatrix(vector<vector<double>>& matrix)
{
	for (const auto& col : matrix)
	{
		for (const double& el : col)
		{
			cout << el << " ";
		}
		cout << "\n";
	}
}
void printMatrix(vector<double>& matrix)
{
	if (matrix.size() > 10)
	{
		printMatrixFandL5(matrix);
	}
	else
	{
		for (const double& el : matrix)
		{
			cout << el << " ";
		}
		cout << "\n";
	}
}

int main()
{
	srand(time(0));

	int n = 1000;
	vector<vector<double>> matrix(n, vector<double>(n, 0));
	vector<double> solution(n, 0);
	vector<double> matB(n, 0);

	for (int i = 0; i < n; i++)
	{
		solution[i] = 12.0 + i;
	}
	
	while (true)
	{
		for (int i = 0; i < n; i++)
		{
			for (int q = 0; q < n; q++)
			{
				matrix[i][q] = rand() % 200 - 100.0;
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int q = 0; q < n; q++)
			{
				matB[i] += matrix[i][q] * solution[q];
			}
		}
		printMatrix(matB);
		cout << "\n";


		
		break;
	}

	/*auto start = chrono::high_resolution_clock::now();
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << "Time: " << duration.count() << "\n";*/

	return 0;
}