#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

// Функция подсчета частоты слов
void countWords(const std::string& filename, std::map<std::string, int>& wordCount) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        // Удаляем знаки препинания в начале и конце слова
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return std::ispunct(static_cast<unsigned char>(c));
            }), word.end());

        // Приводим слово к нижнему регистру
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (word.length() > 3) {
            wordCount[word]++;
        }
    }

    file.close();
}

// Функция для сортировки слов по частоте встречаемости
std::vector<std::pair<std::string, int>> sortWordsByFrequency(const std::map<std::string, int>& wordCount) {
    std::vector<std::pair<std::string, int>> sortedWords(wordCount.begin(), wordCount.end());
    std::sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });
    return sortedWords;
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    std::string filename = "C:\\Users\\Максим\\Desktop\\text.txt.txt";
    std::map<std::string, int> wordCount;

    // Считаем слова из файла
    countWords(filename, wordCount);

    // Сортируем слова по частоте встречаемости
    std::vector<std::pair<std::string, int>> sortedWords = sortWordsByFrequency(wordCount);

    std::cout << "Слова, встречающиеся не менее 7 раз:" << std::endl;
    for (const auto& pair : sortedWords) {
        if (pair.second >= 7) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    return 0;
}