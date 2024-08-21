#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <Windows.h>


int find_min_index(const std::vector<int>& arr, int start, int end) {
    int min_index = start;
    for (int i = start + 1; i <= end; ++i) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

void selection_sort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        
        std::promise<int> prom;
        std::future<int> fut = prom.get_future();

        std::thread([&arr, &prom, i, n] {
            int min_index = find_min_index(arr, i, n - 1);
            prom.set_value(min_index);
            }).detach();

        int min_index = fut.get();

        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }
    }
}

void print_array(const std::vector<int>& arr) {
    for (const auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    std::vector<int> arr = { 64, 25, 12, 22, 11 };

    std::cout << "Исходный массив: ";
    print_array(arr);

    selection_sort(arr);

    std::cout << "Отсортированный массив: ";
    print_array(arr);

    return 0;
}
