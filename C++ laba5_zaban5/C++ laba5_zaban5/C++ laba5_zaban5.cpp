#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <locale>

// Шаблонный класс Cache<T>
template <typename T>
class Cache {
private:
    std::vector<T> elements; // Вектор для хранения элементов кэша
public:
    // Метод для добавления элемента в конец кэша
    void put(T elem) {
        elements.push_back(elem);
    }

    // Перегрузка оператора += для добавления элемента
    Cache& operator+=(T elem) {
        put(elem);
        return *this;
    }

    // Метод для проверки наличия элемента в кэше
    bool contains(T elem) {
        for (const auto& element : elements) {
            if (element == elem) {
                return true;
            }
        }
        return false;
    }

    // Метод push: данные пишутся в начало набора остальные смещаются вправо
    void push(T elem) {
        elements.insert(elements.begin(), elem);
    }

    // Метод peek: возвращает центральный элемент в наборе или 0 если число элементов четное
    T peek() {
        if (elements.empty()) {
            throw std::underflow_error("Кэш пуст.");
        }
        size_t mid = elements.size() / 2;
        if (elements.size() % 2 == 0) {
            return 0; // Возвращает 0 если количество элементов четное
        }
        return elements[mid];
    }

    // Метод pop: извлекает средний элемент из набора
    T pop() {
        if (elements.empty()) {
            throw std::underflow_error("Кэш пуст.");
        }
        size_t mid = elements.size() / 2;
        T elem = elements[mid];
        elements.erase(elements.begin() + mid);
        return elem;
    }
};

// Специализация для std::string
template <>
class Cache<std::string> {
private:
    std::vector<std::string> elements; // Вектор для хранения строк
    static const size_t MAX_SIZE = 100; // Максимальное количество строк в кэше
public:
    void put(std::string elem) {
        if (elements.size() >= MAX_SIZE) {
            throw std::overflow_error("Кэш достиг своего максимального размера в 100 элементов.");
        }
        elements.push_back(elem);
    }

    Cache& operator+=(std::string elem) {
        put(elem);
        return *this;
    }

    bool contains(std::string elem) {
        for (const auto& element : elements) {
            if (!element.empty() && element[0] == elem[0]) {
                return true;
            }
        }
        return false;
    }

    void push(std::string elem) {
        if (elements.size() >= MAX_SIZE) {
            throw std::overflow_error("Кэш достиг своего максимального размера в 100 элементов.");
        }
        elements.insert(elements.begin(), elem);
    }

    std::string peek() {
        if (elements.empty()) {
            throw std::underflow_error("Кэш пуст.");
        }
        size_t mid = elements.size() / 2;
        if (elements.size() % 2 == 0) {
            return ""; // Возвращает пустую строку если количество элементов четное
        }
        return elements[mid];
    }

    std::string pop() {
        if (elements.empty()) {
            throw std::underflow_error("Кэш пуст.");
        }
        size_t mid = elements.size() / 2;
        std::string elem = elements[mid];
        elements.erase(elements.begin() + mid);
        return elem;
    }
};

int main() {
    std::setlocale(LC_ALL, "Russian");

    // Пример использования Cache<int>
    Cache<int> intCache;
    intCache.put(1);
    intCache += 2;
    std::cout << "Содержит 1: " << intCache.contains(1) << std::endl;
    std::cout << "Содержит 3: " << intCache.contains(3) << std::endl;
    intCache.push(3);
    std::cout << "После push 3, содержит 3: " << intCache.contains(3) << std::endl;
    std::cout << "Центральный элемент: " << intCache.peek() << std::endl;
    std::cout << "Извлекаем центральный элемент: " << intCache.pop() << std::endl;

    // Пример использования Cache<std::string>
    Cache<std::string> stringCache;
    try {
        for (int i = 0; i < 1; ++i) {
            stringCache.put("string" + std::to_string(i));
        }
    }
    catch (const std::overflow_error& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }

    std::cout << "Содержит 'apple': " << stringCache.contains("apple") << std::endl;
    std::cout << "Содержит 'avocado': " << stringCache.contains("avocado") << std::endl;
    stringCache.push("cherry");
    std::cout << "После push 'cherry', содержит 'cherry': " << stringCache.contains("cherry") << std::endl;
    std::cout << "Центральный элемент: " << stringCache.peek() << std::endl;
    std::cout << "Извлекаем центральный элемент: " << stringCache.pop() << std::endl;

    return 0;
}