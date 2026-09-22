#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Book
{
private:
    string title;
    string author;
    bool available;

public:

    Book(string t, string a)
    {
        title = t;
        author = a;
        available = true;
    }

    string getTitle()
    {
        return title;
    }

    string getAuthor()
    {
        return author;
    }

    bool isAvailable()
    {
        return available;
    }

    void borrowBook()
    {
        available = false;
    }

    void returnBook()
    {
        available = true;
    }
};


class Member
{
private:
    string name;
    vector<string> borrowedBooks;

public:

    Member(string n)
    {
        name = n;
    }

    void borrowBook(string title)
    {
        borrowedBooks.push_back(title);
    }

    void returnBook(string title)
    {
        for (int i = 0; i < borrowedBooks.size(); i++)
        {
            if (borrowedBooks[i] == title)
            {
                borrowedBooks.erase(borrowedBooks.begin() + i);
                break;
            }
        }
    }
};



class Library
{
private:
    vector<Book> books;

public:

    
    void addBook()
    {
        string title, author;

        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, title);

        cout << "Enter author: ";
        getline(cin, author);

        books.push_back(Book(title, author));

        cout << "Book \"" << title << "\" added.\n";
    }


    
    void removeBook()
    {
        string title;

        cout << "Enter book title to remove: ";
        cin.ignore();
        getline(cin, title);

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getTitle() == title)
            {
                if (!books[i].isAvailable())
                {
                    cout << "Book is borrowed and cannot be removed.\n";
                    return;
                }

                books.erase(books.begin() + i);

                cout << "Book \"" << title << "\" removed.\n";
                return;
            }
        }

        cout << "Book not found.\n";
    }


    
    void borrowBook(Member& member)
    {
        string title;

        cout << "Enter book title to borrow: ";
        cin.ignore();
        getline(cin, title);

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getTitle() == title)
            {
                if (!books[i].isAvailable())
                {
                    cout << "Book is already borrowed.\n";
                    return;
                }

                books[i].borrowBook();
                member.borrowBook(title);

                cout << "\"" << title << "\" borrowed successfully.\n";
                return;
            }
        }

        cout << "Book not found.\n";
    }


    void returnBook(Member& member)
    {
        string title;

        cout << "Enter book title to return: ";
        cin.ignore();
        getline(cin, title);

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getTitle() == title)
            {
                if (books[i].isAvailable())
                {
                    cout << "Book is not borrowed.\n";
                    return;
                }

                books[i].returnBook();
                member.returnBook(title);

                cout << "\"" << title << "\" returned successfully.\n";
                return;
            }
        }

        cout << "Book not found.\n";
    }


    
    void searchBook()
    {
        string search;

        cout << "Enter title or author to search: ";
        cin.ignore();
        getline(cin, search);

        bool found = false;

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getTitle() == search ||
                books[i].getAuthor() == search)
            {
                cout << "Title: " << books[i].getTitle()
                    << " | Author: " << books[i].getAuthor()
                    << " | Status: "
                    << (books[i].isAvailable() ? "Available" : "Borrowed")
                    << endl;

                found = true;
            }
        }

        if (!found)
        {
            cout << "Book not found.\n";
        }
    }


    
    void displayBooks()
    {
        if (books.empty())
        {
            cout << "No books in the library.\n";
            return;
        }

        for (int i = 0; i < books.size(); i++)
        {
            cout << "Title: " << books[i].getTitle()
                << " | Author: " << books[i].getAuthor()
                << " | Status: "
                << (books[i].isAvailable() ? "Available" : "Borrowed")
                << endl;
        }
    }
};



int main()
{
    Library library;

    Member member("Student");

    int choice;

    do
    {
        cout << "\n----- Library Management System -----\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Book\n";
        cout << "6. Display All Books\n";
        cout << "7. Exit\n";

        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            library.addBook();
            break;

        case 2:
            library.removeBook();
            break;

        case 3:
            library.borrowBook(member);
            break;

        case 4:
            library.returnBook(member);
            break;

        case 5:
            library.searchBook();
            break;

        case 6:
            library.displayBooks();
            break;

        case 7:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid option.\n";
        }

    } while (choice != 7);

    return 0;
}
