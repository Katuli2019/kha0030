#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>

std::vector<int> generateRandomVector(int length, int minVal, int maxVal)
{
    std ::random_device rd;
    std ::mt19937 gen(rd());
    std ::uniform_int_distribution<int> distribution(minVal, maxVal);
    std ::vector<int> result;
    result.reserve(length); // better then series of push_backs
    for (int i = 0; i < length; ++i)
    {
        result.push_back(distribution(gen));
    }
    return result;
}

void Swap(int &first, int &second)
{
    int temp = first;
    first = second;
    second = temp;
}

void LeftToRight(std::vector<int> &targetToSort, unsigned int &left, unsigned int &right)
{
    unsigned int j = 0;
    for (int i = left; i <= right - 1; i++)
    {
        if (targetToSort[i] > targetToSort[i + 1])
        {
            Swap(targetToSort[i], targetToSort[i + 1]);
            j = i;
        }
    }
    right = j;
}

void RightToLeft(std::vector<int> &targetToSort, unsigned int &left, unsigned int &right)
{
    unsigned int j = 0;
    for (int i = right; i >= left + 1; i--)
    {
        if (targetToSort[i - 1] > targetToSort[i])
        {
            Swap(targetToSort[i - 1], targetToSort[i]);
            j = i;
        }
    }
    left = j;
}

void shakerSort(std::vector<int> &targetToSort)
{
    unsigned int left = 0;
    unsigned int right = targetToSort.size() - 1;
    while (left < right)
    {
        LeftToRight(targetToSort, left, right);
        RightToLeft(targetToSort, left, right);
    }
}

int main()
{
    std::vector<int> smallVectorStorage = generateRandomVector(9, 3, 7);
    std::vector<int> bigVectorStorage = generateRandomVector(5000, 3, 387);
    std::vector<int> randomVector = smallVectorStorage;
    auto start = std ::chrono ::high_resolution_clock ::now();
    std ::sort(randomVector.begin(), randomVector.end());
    auto end = std ::chrono ::high_resolution_clock ::now();
    std ::chrono ::duration<double> duration = end - start;
    std ::cout << " Time taken to sort small vector using std::sort: " << duration.count() << " seconds " << std ::endl;

    randomVector = bigVectorStorage;
    start = std ::chrono ::high_resolution_clock ::now();
    std ::sort(randomVector.begin(), randomVector.end());
    end = std ::chrono ::high_resolution_clock ::now();
    duration = end - start;
    std ::cout << " Time taken to sort big vector using std::sort: " << duration.count() << " seconds " << std ::endl;

    randomVector = smallVectorStorage;
    start = std ::chrono ::high_resolution_clock ::now();
    shakerSort(randomVector);
    end = std ::chrono ::high_resolution_clock ::now();
    duration = end - start;
    std ::cout << " Time taken to sort small vector using shakerSort: " << duration.count() << " seconds " << std ::endl;

    randomVector = bigVectorStorage;
    start = std ::chrono ::high_resolution_clock ::now();
    shakerSort(randomVector);
    end = std ::chrono ::high_resolution_clock ::now();
    duration = end - start;
    std ::cout << " Time taken to sort big vector using shakerSort: " << duration.count() << " seconds " << std ::endl;
}
