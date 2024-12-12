#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

struct Book {
    std::string title;
    int year;
};

int main() {
    std::setlocale(LC_ALL, "Russian");

    std::vector<Book> books = {
        {"Книга 1", 2010},
        {"Книга 2", 2008},
        {"Книга 3", 2015},
        {"Книга 4", 2001},
        {"Книга 5", 2012}
    };

    // std::count_if для подсчета книг новее 2009 года
    int count = std::count_if(books.begin(), books.end(), [](const Book& book) {
        return book.year > 2009;
        });

    std::cout << "Количество книг новее 2009 года: " << count << std::endl;

    return 0;
}
