#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

class Book {
public:
    std::string title;
    std::string author;
    int year;

    Book(std::string t, std::string a, int y) : title(t), author(a), year(y) {}

    // Вывод информации о книге
    void print() const {
        std::cout << "Название: " << title << ", Автор: " << author << ", Год издания: " << year << std::endl;
    }
};

// Функтор для сортировки по автору (первичный ключ) и названию (вторичный ключ)
struct BookComparator {
    bool operator()(const Book& b1, const Book& b2) const {
        if (b1.author == b2.author) {
            return b1.title < b2.title;
        }
        return b1.author < b2.author;
    }
};

// Функтор для проверки диапазона годов издания
struct YearRange {
    int startYear;
    int endYear;

    YearRange(int start, int end) : startYear(start), endYear(end) {}

    bool operator()(const Book& b) const {
        return b.year >= startYear && b.year <= endYear;
    }
};

int main() {
    std::setlocale(LC_ALL, "Russian");

    // Коллекция книг
    std::vector<Book> books = {
        {"Книга 1", "Автор А", 2010},
        {"Книга 2", "Автор Б", 2008},
        {"Книга 3", "Автор А", 2015},
        {"Книга 4", "Автор В", 2001},
        {"Книга 5", "Автор Б", 2012}
    };

    // Сортировка книг по автору и названию
    std::sort(books.begin(), books.end(), BookComparator());

    std::cout << "Сортировка книг по автору и названию:" << std::endl;
    for (const auto& book : books) {
        book.print();
    }

    // Поиск книг в диапазоне годов издания
    int startYear = 2005;
    int endYear = 2012;
    auto it = std::find_if(books.begin(), books.end(), YearRange(startYear, endYear));

    std::cout << "\nКниги, изданные в диапазоне с " << startYear << " по " << endYear << ":" << std::endl;
    while (it != books.end()) {
        it->print();
        it = std::find_if(std::next(it), books.end(), YearRange(startYear, endYear));
    }

    return 0;
}
