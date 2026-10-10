#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include <chrono>
#include <limits>
#include <iomanip>

using namespace std;

struct PhotoEntry 
{
    int id;
    int32_t lat_e6;
    int32_t lon_e6;
    int32_t key;
};

// Функція заповнює 3 масиви з одного файлу
void load_file(const string& filename,
    vector<PhotoEntry>& rand_arr,
    vector<PhotoEntry>& sorted_arr,
    vector<PhotoEntry>& rev_arr)
{
    ifstream file(filename);
    string line;

    // Вказівник який вказує в який з трьох масивів ми зараз додаємо дані
    vector<PhotoEntry>* targets[] = { &rand_arr, &sorted_arr, &rev_arr };
    int current_idx = -1;

    while (getline(file, line))
    {
        // Пропускаємо непотрібні рядки
        if (line.empty() || line[0] == '#') continue;
        // Якщо рядок починається з '=' це заголовок секції - перемикаємо масив
        if (line[0] == '=')
        {
            current_idx++;
            continue;
        }

        if (current_idx >= 0 && current_idx < 3) {
            std::istringstream iss(line);
            PhotoEntry p;
            if (iss >> p.id >> p.lat_e6 >> p.lon_e6 >> p.key)
                targets[current_idx]->push_back(p);
        }
    }
}

// Структура збереження результатів замірів
struct SortMetrics
{
    unsigned long long comparisons = 0;
    unsigned long long swaps = 0;
    double time_ms = 0.0;
};

// =========================================
// =========================================
//     М Е Т О Д И   С О Р Т У В А Н Н Я  
// =========================================
// =========================================

// СОРТУВАННЯ ШЕЛЛА
void shell_sort(std::vector<PhotoEntry>& arr,
    unsigned long long& comparisons,
    unsigned long long& swaps)
{
    comparisons = 0;
    swaps = 0;
    size_t n = arr.size();

    for (size_t gap = n / 2; gap > 0; gap /= 2) 
    {
        for (size_t i = gap; i < n; ++i) 
        {
            PhotoEntry temp = arr[i];
            size_t j = i;

            while (j >= gap) 
            {
                comparisons++;
                if (arr[j - gap].key > temp.key) 
                {
                    arr[j] = arr[j - gap];
                    swaps++;
                    j -= gap;
                }
                else
                    break;
            }
            arr[j] = temp;
        }
    }
}

// СПРОЩЕНИЙ TIMSORT
const int RUN = 32;

void insertion_sort_range(std::vector<PhotoEntry>& arr, int left, int right,
    unsigned long long& comparisons,
    unsigned long long& swaps)
{
    for (int i = left + 1; i <= right; ++i) 
    {
        PhotoEntry temp = arr[i];
        int j = i - 1;
        while (j >= left) 
        {
            comparisons++;
            if (arr[j].key > temp.key) 
            {
                arr[j + 1] = arr[j];
                swaps++;
                j--;
            }
            else
                break;
        }
        arr[j + 1] = temp;
    }
}

void merge_runs(std::vector<PhotoEntry>& arr, int l, int m, int r,
    unsigned long long& comparisons,
    unsigned long long& swaps)
{
    int len1 = m - l + 1;
    int len2 = r - m;

    std::vector<PhotoEntry> left(len1);
    std::vector<PhotoEntry> right(len2);

    for (int i = 0; i < len1; ++i) left[i] = arr[l + i];
    for (int i = 0; i < len2; ++i) right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) 
    {
        comparisons++;
        if (left[i].key <= right[j].key)
            arr[k] = left[i++];
        else 
            arr[k] = right[j++];
        swaps++;
        k++;
    }

    while (i < len1) 
    {
        arr[k++] = left[i++];
        swaps++;
    }
    while (j < len2) 
    {
        arr[k++] = right[j++];
        swaps++;
    }
}

// СОРТУВАННЯ ТІМА
void timsort(std::vector<PhotoEntry>& arr,
    unsigned long long& comparisons,
    unsigned long long& swaps)
{
    comparisons = 0;
    swaps = 0;
    int n = static_cast<int>(arr.size());

    // Сортування блоків розміром RUN вставками
    for (int i = 0; i < n; i += RUN) 
    {
        int right = (i + RUN - 1 < n - 1) ? (i + RUN - 1) : (n - 1);
        insertion_sort_range(arr, i, right, comparisons, swaps);
    }

    // Ітеративне злиття відсортованих підмасивів
    for (int size = RUN; size < n; size = 2 * size) 
    {
        for (int left = 0; left < n; left += 2 * size) 
        {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

            if (mid < right) 
                merge_runs(arr, left, mid, right, comparisons, swaps);
        }
    }
}

// БУЛЬБАШКОВЕ СОРТУВАННЯ
void bubble_sort(std::vector<PhotoEntry>& arr,
    unsigned long long& comparisons,
    unsigned long long& swaps)
{
    comparisons = 0;
    swaps = 0;
    size_t n = arr.size();

    for (size_t i = 0; i < n - 1; ++i) 
    {
        bool swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) 
        {
            comparisons++;
            if (arr[j].key > arr[j + 1].key) 
            {
                std::swap(arr[j], arr[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ЗАМІР ЧАСУ
SortMetrics measure_sort(void (*sort_func)
    (vector<PhotoEntry>&, unsigned long long&, unsigned long long&),
    vector<PhotoEntry> arr_copy)
{
    SortMetrics m;

    auto t1 = chrono::high_resolution_clock::now();
    sort_func(arr_copy, m.comparisons, m.swaps);

    auto t2 = chrono::high_resolution_clock::now();
    m.time_ms = chrono::duration<double, milli>(t2 - t1).count();

    return m;
}

void run_test(const string& filename)
{
    vector<PhotoEntry> r, s, rev;
    load_file(filename, r, s, rev);

    string names[] = { "Random", "Sorted", "Reversed" };
    vector<PhotoEntry> sets[] = { r, s, rev};

    cout << "\n=== Measurement file: " << filename << " ===" << "\n";

    for (int i = 0; i < 3; ++i)
    {
        cout << "\r[~] Processing " << names[i] << " (wait)..." << flush;

        SortMetrics m1 = measure_sort(shell_sort, sets[i]);
        SortMetrics m2 = measure_sort(timsort, sets[i]);
        SortMetrics m3 = measure_sort(bubble_sort, sets[i]);

        cout << "\r                                              \r";

        cout << "\n--- " << names[i] << " ---\n";

        cout << left 
            << "| " << setw(8) << "Shell:"
            << setw(10) << m1.time_ms << " ms "
            << "| cmp: " << setw(10) << m1.comparisons
            << "| swp: " << m1.swaps << "\n";

        cout << left
            << "| " << setw(8) << "Tim:"
            << setw(10) << m2.time_ms << " ms "
            << "| cmp: " << setw(10) << m2.comparisons
            << "| swp: " << m2.swaps << "\n";

        cout << left
            << "| " << setw(8) << "Bubble:"
            << setw(10) << m3.time_ms << " ms "
            << "| cmp: " << setw(10) << m3.comparisons
            << "| swp: " << m3.swaps << "\n";
    }
    cout << "\nPress enter...\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void main_menu()
{
    cout << "=== M A I N   M E N U ===\n";
    cout << "1. Test N = 100\n";
    cout << "2. Test N = 1 000\n";
    cout << "3. Test N = 10 000\n";
    cout << "4. Test everything (9 arrays)\n";
    cout << "0. Exit\n";
    cout << "=== ================= ===\n";
    cout << "Enter choise: ";

}