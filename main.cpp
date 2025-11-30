// ICT0008 - Assessment 2 - Library application
#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    string dateAdd;   // date the library bought the book
    bool available;

public:
    Book()
        : title(""), author(""), isbn(""),
          dateAdd(""), available(true) {}

    void setBookDetails(const string& t,
                        const string& a,
                        const string& i,
                        const string& date,
                        bool isAvailable = true) {
        title     = t;
        author    = a;
        isbn      = i;
        dateAdd   = date;
        available = isAvailable;
    }

    void displayBookDetails() const {
        cout << "Title: "        << title   << '\n'
             << "Author: "       << author  << '\n'
             << "ISBN: "         << isbn    << '\n'
             << "Date added: "   << dateAdd << '\n'
             << "Availability: " << (available ? "Available" : "Borrowed")
             << "\n\n";
    }

    bool borrowBook() {
        if (available) {
            available = false;
            return true;
        } else {
            return false;
        }
    }

    void returnBook() {
        available = true;
    }

    string getIsbn() const {
        return isbn;
    }

    bool isAvailable() const {
        return available;
    }

    // Static method to sort an array of Book objects by ISBN (ascending)
    static void sortBookData(Book books[], int size) {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - 1 - i; ++j) {
                if (books[j].isbn > books[j + 1].isbn) {
                    Book temp    = books[j];
                    books[j]     = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }
    }
};

int main() {
    const int NUM_BOOKS = 5;
    Book library[NUM_BOOKS];

    // Initialise the 5 books in the library
    library[0].setBookDetails(
        "Clean Code", "Robert C. Martin",
        "9780132350884", "2023-01-15");
    library[1].setBookDetails(
        "The Pragmatic Programmer", "Andrew Hunt",
        "9780201616224", "2022-11-10");
    library[2].setBookDetails(
        "Design Patterns", "Erich Gamma",
        "9780201633610", "2021-08-01");
    library[3].setBookDetails(
        "Effective Modern C++", "Scott Meyers",
        "9781491903995", "2023-05-27");
    library[4].setBookDetails(
        "C++ Primer", "Stanley Lippman",
        "9780321714114", "2020-09-09");

    // Sort the array by ISBN before user interaction
    Book::sortBookData(library, NUM_BOOKS);

    cout << "Welcome to the Community Library\n";
    cout << "Enter ISBN to borrow a book (or 0 to exit)\n\n";

    string requestedIsbn;

    while (true) {
        cout << "ISBN: ";
        getline(cin, requestedIsbn);

        if (requestedIsbn == "0") {
            break;
        }

        bool found = false;

        for (int i = 0; i < NUM_BOOKS; ++i) {
            if (library[i].getIsbn() == requestedIsbn) {
                found = true;

                if (library[i].borrowBook()) {
                    cout << "Book successfully borrowed:\n";
                    library[i].displayBookDetails();
                } else {
                    cout << "Sorry, that book is currently not available.\n\n";
                }
                break;
            }
        }

        if (!found) {
            cout << "No book with ISBN " << requestedIsbn
                 << " found in the library.\n\n";
        }
    }

    cout << "Thank you for using the library system.\n";
    return 0;
}
