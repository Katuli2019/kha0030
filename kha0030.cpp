#include <vector>
#include <random>
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

std::vector<int> shakerSort(std::vector<int> targetToSort)
{
    unsigned int left = 0;
    unsigned int right = targetToSort.size() - 1;
    while (left < right)
    {
        LeftToRight(targetToSort, left, right);
        RightToLeft(targetToSort, left, right);
    }
    return targetToSort;
}

int main()
{
    std::vector<int> array = generateRandomVector(9, 3, 7);
    for (int item : array)
    {
        std::cout << item << ' ';
    }
    std::cout << '\n';
    array = shakerSort(array);
    for (int item : array)
    {
        std::cout << item << ' ';
    }
}