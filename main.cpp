#include <iostream>
#include <random>
#include <time.h>
#include <chrono>
#include <math.h>
#include <iomanip>
#include <cstdlib> 

using namespace std;

void printMatrixFandL5(vector<double>& matrix)
{
	for (int i = 0; i < 5 && i < matrix.size(); i++)
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

void choiceMainElement(vector<vector<double>>& matrix, int i, vector<double>& matB)
{
	double MainEl = matrix[i][i];
	int indOfMainEl = i;
	for (int j = i + 1; j < matrix[i].size(); j++)
	{
		if (abs(MainEl) < abs(matrix[j][i]))
		{
			indOfMainEl = j;
			MainEl = matrix[j][i];
		}
	}
	if (i == indOfMainEl && matrix[i][i] == 0.0)
	{
		cerr << "Matrix A inconsistent";
		exit(EXIT_FAILURE);
	}
	swap(matrix[i], matrix[indOfMainEl]);
	swap(matB[i], matB[indOfMainEl]);
}

void gaussMethodWTC(vector<vector<double>>& matrix, vector<double>& solution, vector<double>& matB)
{
	for (int i = 0; i < solution.size(); i++)
	{
		choiceMainElement(matrix, i, matB);
		for (int j = i + 1; j < solution.size(); j++) // j - строка 
		{
			double mulTo = matrix[j][i] / matrix[i][i];
			matrix[j][i] = 0;
			for (int k = i + 1; k < solution.size(); k++) // k - столбец (элемент строки)
			{
				matrix[j][k] -= (matrix[i][k] * mulTo);
			}
			matB[j] -= (matB[i] * mulTo);
		}
	}
	for (int i = solution.size() - 1; i >= 0; i--)
	{
		for (int q = i + 1; q < solution.size(); q++)
		{
			matB[i] -= matrix[i][q] * solution[q];
		}
		solution[i] = matB[i] / matrix[i][i];
	}
}



int main()
{
	srand(time(0));
	//std::cout << std::fixed << std::setprecision(10); //Если надо установить больше знаков после запятой

	int n = 1000;
	vector<vector<double>> matrix(n, vector<double>(n, 0));
	vector<double> solution(n, 0);
	vector<double> impreciseSolution(n, 0);
	vector<double> matB(n, 0);

	for (int i = 0; i < n; i++) // создаем вектор точного решения
	{
		solution[i] = 12.0 + i;
	}
	for (int i = 0; i < n; i++) // создаем матрицу А
	{
		for (int q = 0; q < n; q++)
		{
			matrix[i][q] = rand() % 200 - 100.0;
		}
	}
	for (int i = 0; i < n; i++) // получаем значения b
	{
		for (int q = 0; q < n; q++)
		{
			matB[i] += matrix[i][q] * solution[q];
		}
	}
	
	cout << "A: " << n << "x" << n << ":\n";

	cout << "Exact solution:\n";
	printMatrixFandL5(solution);
	cout << "\n";
	auto start = chrono::high_resolution_clock::now();

	gaussMethodWTC(matrix, impreciseSolution, matB);
	cout << "Imprecise solution:\n";
	printMatrixFandL5(impreciseSolution);

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << "\nTime: " << duration.count() << "\n\n";

	double normSol = 0;
	for (int i = 0; i < solution.size(); i++)
	{
		normSol += abs(solution[i]);
	}
	double normSolImprecise = 0;
	for (int i = 0; i < solution.size(); i++)
	{
		normSolImprecise += abs(solution[i] - impreciseSolution[i]);
	}
	cout << "Relative error: " << normSolImprecise / normSol << "\n";


	n = 10; // 10
	cout << "\n\n";
	cout << "Hilbert matrix: " << n << "x" << n << "\n";
	vector<vector<double>> matrix2(n, vector<double>(n, 0));
	vector<double> solution2(n, 0);
	vector<double> impreciseSolution2(n, 0);
	vector<double> matB2(n, 0);
	for (int i = 0; i < n; i++) // создаем вектор точного решения
	{
		solution2[i] = 1.0 + i;
	}
	for (int i = 0; i < n; i++) // создаем матрицу А
	{
		for (int q = 0; q < n; q++)
		{
			matrix2[i][q] = 1.0 / (i + q + 1.0);
		}
	}
	for (int i = 0; i < n; i++) // получаем значения b
	{
		for (int q = 0; q < n; q++)
		{
			matB2[i] += matrix2[i][q] * solution2[q];
		}
	}

	cout << "Exact solution:\n";
	printMatrixFandL5(solution2);
	cout << "\n";

	gaussMethodWTC(matrix2, impreciseSolution2, matB2);
	cout << "Imprecise solution:\n";
	printMatrixFandL5(impreciseSolution2);
	cout << "\n\n";

	normSol = 0;
	for (int i = 0; i < solution2.size(); i++)
	{
		normSol += abs(solution2[i]);
	}
	normSolImprecise = 0;
	for (int i = 0; i < solution2.size(); i++)
	{
		normSolImprecise += abs(solution2[i] - impreciseSolution2[i]);
	}
	cout << "Relative error: " << normSolImprecise / normSol << "\n";


	n = 22; // 10 + 12
	cout << "\n\n";
	cout << "Hilbert matrix: " << n << "x" << n << "\n";
	vector<vector<double>> matrix3(n, vector<double>(n, 0));
	vector<double> solution3(n, 0);
	vector<double> impreciseSolution3(n, 0);
	vector<double> matB3(n, 0);
	for (int i = 0; i < n; i++) // создаем вектор точного решения
	{
		solution3[i] = 1.0 + i;
	}
	for (int i = 0; i < n; i++) // создаем матрицу А
	{
		for (int q = 0; q < n; q++)
		{
			matrix3[i][q] = 1.0 / (i + q + 1.0);
		}
	}
	for (int i = 0; i < n; i++) // получаем значения b
	{
		for (int q = 0; q < n; q++)
		{
			matB3[i] += matrix3[i][q] * solution3[q];
		}
	}

	cout << "Exact solution:\n";
	printMatrixFandL5(solution3);
	cout << "\n";

	gaussMethodWTC(matrix3, impreciseSolution3, matB3);
	cout << "Imprecise solution:\n";
	printMatrixFandL5(impreciseSolution3);
	cout << "\n\n";

	normSol = 0;
	for (int i = 0; i < solution3.size(); i++)
	{
		normSol += abs(solution3[i]);
	}
	normSolImprecise = 0;
	for (int i = 0; i < solution3.size(); i++)
	{
		normSolImprecise += abs(solution3[i] - impreciseSolution3[i]);
	}
	cout << "Relative error: " << normSolImprecise / normSol << "\n";
	return 0;
}