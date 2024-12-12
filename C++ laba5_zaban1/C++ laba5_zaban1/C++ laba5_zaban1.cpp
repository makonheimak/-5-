#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cctype>

// Максимальная вместимость набора
const size_t MAX_CAPACITY = 64;

// Шаблонный класс DataManager<T>
template <typename T>
class DataManager {
private:
    std::vector<T> data;
    void dumpToFile() {
        std::ofstream outFile("dump.dat", std::ios::app);
        for (const auto& elem : data) {
            outFile << elem << " ";
        }
        outFile.close();
        data.clear();
    }

public:
    void push(T elem) {
        if (data.size() >= MAX_CAPACITY) {
            dumpToFile();
        }
        data.insert(data.begin(), elem); // Данные пишутся в начало набора, остальные смещаются вправо
    }

    void push(T elems[], size_t n) {
        for (size_t i = 0; i < n; ++i) {
            push(elems[i]);
        }
    }

    T peek() const {
        if (data.empty()) {
            throw std::underflow_error("Набор пуст.");
        }
        size_t mid = data.size() / 2;
        if (data.size() % 2 == 0) {
            return 0;
        }
        return data[mid];
    }

    T pop() {
        if (data.empty()) {
            // Заполняем массив ранее выгруженными данными, если файл не пуст
            std::ifstream inFile("dump.dat");
            if (inFile.is_open()) {
                T elem;
                while (inFile >> elem) {
                    data.push_back(elem);
                }
                inFile.close();
                std::ofstream clearFile("dump.dat", std::ofstream::out | std::ofstream::trunc); // Очистка
                clearFile.close();
            }
            if (data.empty()) {
                throw std::underflow_error("Набор пуст.");
            }
        }
        size_t mid = data.size() / 2;
        T elem = data[mid];
        data.erase(data.begin() + mid);
        return elem;
    }

    void display() const {
        std::copy(data.begin(), data.end(), std::ostream_iterator<T>(std::cout, " "));
        std::cout << std::endl;
    }
};

// Явная специализация для char
template <>
class DataManager<char> {
private:
    std::vector<char> data;
    void dumpToFile() {
        std::ofstream outFile("dump.dat", std::ios::app);
        for (const auto& elem : data) {
            outFile << elem << " ";
        }
        outFile.close();
        data.clear();
    }

public:
    void push(char elem) {
        if (std::ispunct(static_cast<unsigned char>(elem))) {
            elem = '_'; // Заменяем знаки пунктуации на символ подчеркивания
        }
        if (data.size() >= MAX_CAPACITY) {
            dumpToFile();
        }
        data.insert(data.begin(), elem); // Данные пишутся в начало набора, остальные смещаются вправо
    }

    void push(char elems[], size_t n) {
        for (size_t i = 0; i < n; ++i) {
            push(elems[i]);
        }
    }

    char peek() const {
        if (data.empty()) {
            throw std::underflow_error("Набор пуст.");
        }
        size_t mid = data.size() / 2;
        if (data.size() % 2 == 0) {
            return 0;
        }
        return data[mid];
    }

    char pop() {
        if (data.empty()) {
            std::ifstream inFile("dump.dat");
            if (inFile.is_open()) {
                char elem;
                while (inFile >> elem) {
                    data.push_back(elem);
                }
                inFile.close();
                std::ofstream clearFile("dump.dat", std::ofstream::out | std::ofstream::trunc); // Очистка
                clearFile.close();
            }
            if (data.empty()) {
                throw std::underflow_error("Набор пуст.");
            }
        }
        size_t mid = data.size() / 2;
        char elem = data[mid];
        data.erase(data.begin() + mid);
        return elem;
    }

    char popUpper() {
        char elem = pop();
        return std::toupper(static_cast<unsigned char>(elem));
    }

    char popLower() {
        char elem = pop();
        return std::tolower(static_cast<unsigned char>(elem));
    }

    void display() const {
        std::copy(data.begin(), data.end(), std::ostream_iterator<char>(std::cout, " "));
        std::cout << std::endl;
    }
};

int main() {
    std::setlocale(LC_ALL, "Russian");

    // Пример использования DataManager для int
    DataManager<int> intManager;
    intManager.push(5);
    intManager.push(10);
    intManager.push(15);
    intManager.display();
    std::cout << "Peek: " << intManager.peek() << std::endl;
    std::cout << "Pop: " << intManager.pop() << std::endl;
    intManager.display();

    // Пример использования DataManager для double
    DataManager<double> doubleManager;
    doubleManager.push(5.5);
    doubleManager.push(10.1);
    doubleManager.push(15.2);
    doubleManager.display();
    std::cout << "Peek: " << doubleManager.peek() << std::endl;
    std::cout << "Pop: " << doubleManager.pop() << std::endl;
    doubleManager.display();

    // Пример использования DataManager для char
    DataManager<char> charManager;
    charManager.push('A');
    charManager.push('b');
    charManager.push('!');
    charManager.display();
    std::cout << "Peek: " << charManager.peek() << std::endl;
    std::cout << "Pop: " << charManager.pop() << std::endl;
    charManager.display();
    std::cout << "Pop Upper: " << charManager.popUpper() << std::endl;
    charManager.display();
    std::cout << "Pop Lower: " << charManager.popLower() << std::endl;
    charManager.display();

    return 0;
}
