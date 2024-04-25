#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
using namespace std;

int Factorial(int number)
{
    int returnValue = number;
    for (int i = number - 1; i > 1; i--)
    {
        returnValue *= i;
    }
    return returnValue;
}

void InitializeVariables(int **&permutations, short *&arrows, int n)
{
    int permutations_count = Factorial(n);
    permutations = new int *[permutations_count];
    for (int i = 0; i < permutations_count; i++)
    {
        permutations[i] = new int[n];
    }

    arrows = new short[n];
    for (int i = 0; i < n; i++)
    {
        arrows[i] = -1;
        permutations[0][i] = i + 1;
    }
}

int SeekTargetToSwap(int *&permutations, short *&arrows, int n)
{
    int largest_number = 0;
    int index_of_largest_number = -1;

    for (int i = 0; i < n; i++)
    {
        if (i + arrows[i] == n || i + arrows[i] < 0)
        {
            continue;
        }

        if (permutations[i] > permutations[i + arrows[i]] && permutations[i] > largest_number)
        {
            largest_number = permutations[i];
            index_of_largest_number = i;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (permutations[i] > largest_number)
        {
            arrows[i] = -arrows[i];
        }
    }

    return index_of_largest_number;
}

void Swap(int *&permutations, short *&arrows, int target_index)
{
    int temp = permutations[target_index];
    permutations[target_index] = permutations[target_index + arrows[target_index]];
    permutations[target_index + arrows[target_index]] = temp;

    short tempShort = arrows[target_index + arrows[target_index]];
    arrows[target_index + arrows[target_index]] = arrows[target_index];
    arrows[target_index] = tempShort;
}

int **GeneratePermutations(int n)
{
    int **permutations;
    short *arrows;
    InitializeVariables(permutations, arrows, n);

    int index_of_last_permutation = 0;
    int index_of_largest_number = -1;

    while (true)
    {
        index_of_largest_number = SeekTargetToSwap(permutations[index_of_last_permutation], arrows, n);

        if (index_of_largest_number == -1)
        {
            return permutations;
        }

        index_of_last_permutation++;
        for (int i = 0; i < n; i++)
        {
            permutations[index_of_last_permutation][i] = permutations[index_of_last_permutation - 1][i];
        }

        Swap(permutations[index_of_last_permutation], arrows, index_of_largest_number);
    }
}

void PrintPermutations(int **&permutations, int n)
{
    int totalPermutations = Factorial(n);
    for (int i = 0; i < totalPermutations; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << permutations[i][j] << ' ';
        }
        cout << endl;
    }
}

int main()
{
    auto start = chrono::high_resolution_clock::now();
    GeneratePermutations(5);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time taken to generate permutations (n = 5): " << duration.count() << " seconds" << std::endl;

    vector<int> numbers = {1, 2, 3, 4, 5};
    start = chrono::high_resolution_clock::now();
    while (next_permutation(numbers.begin(), numbers.end()))
    {
    }
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Time taken to generate permutations (next_permutation (n = 5)): " << duration.count() << " seconds" << std::endl;

    start = chrono::high_resolution_clock::now();
    GeneratePermutations(10);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Time taken to generate permutations (n = 10): " << duration.count() << " seconds" << std::endl;

    numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    start = chrono::high_resolution_clock::now();
    while (next_permutation(numbers.begin(), numbers.end()))
    {
    }
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Time taken to generate permutations (next_permutation (n = 10)): " << duration.count() << " seconds" << std::endl;
}