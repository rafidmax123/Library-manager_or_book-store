#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    friend class Library;
    string bookname;
    string authorname;
    int bookid,publishedyear,price,quantity;
    vector<Book> books;
public:
    Book() : bookid(0), publishedyear(0), price(0), quantity(0) {}
    void addbooks(){
        cout << "Enter book name: ";
        cin >> bookname;
        cout << "Enter author name: ";
        cin >> authorname;
        cout << "Enter book ID: ";
        cin >> bookid;
        cout << "Enter published year: ";
        cin >> publishedyear;
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter quantity: ";
        cin >> quantity;
    };
    void displaybooks() const {
        cout << "Book Name: " << bookname << endl;
        cout << "Author Name: " << authorname << endl;
        cout << "Book ID: " << bookid << endl;
        cout << "Published Year: " << publishedyear << endl;
        cout << "Price: " << price << endl;
        cout << "Quantity: " << quantity << endl;
    };
    void searchbooks(vector<Book> &books, int id){
        for(int i=0; i<books.size(); i++){
            if(books[i].bookid == id){
                books[i].displaybooks();
                return;
            }
        }
        cout << "Book not found!" << endl;
    };
    void updatebooks(vector<Book> &books, int id){
        for(int i=0; i<books.size(); i++){
            if(books[i].bookid == id){
                cout << "Enter new book name: ";
                cin >> books[i].bookname;
                cout << "Enter new author name: ";
                cin >> books[i].authorname;
                cout << "Enter new published year: ";
                cin >> books[i].publishedyear;
                cout << "Enter new price: ";
                cin >> books[i].price;
                cout << "Enter new quantity: ";
                cin >> books[i].quantity;
                return;
            }
        }
        cout << "Book not found!" << endl;
    };
    void deletebooks(vector<Book> &books, int id){
        for(int i=0; i<books.size(); i++){
            if(books[i].bookid == id){
                books.erase(books.begin() + i);
                cout << "Book deleted!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    };

};
class Library {
private:
    vector<Book> books;
public:
    void addBook() {
        Book book;
        book.addbooks();
        books.push_back(book);
    };
    void bookLen() {
        int id;
        cout << "Enter book ID to lend: ";
        cin >> id;
        for(int i=0; i<books.size(); i++){
            if(books[i].bookid == id){
                if(books[i].quantity > 0){
                    books[i].quantity--;
                    cout << "Book lent!" << endl;
                } else {
                    cout << "Book not available!" << endl;
                }
                return;
            }
        }
        cout << "Book not found!" << endl;
    };
    void returnBook() {
        int id;
        cout << "Enter book ID to return: ";
        cin >> id;
        for(int i=0; i<books.size(); i++){
            if(books[i].bookid == id){
                books[i].quantity++;
                cout << "Book returned!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    };

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books found!" << endl;
            return;
        }
        for (const Book &book : books) {
            book.displaybooks();
            cout << endl;
        }
    };

    void bookStatus() const {
        if (books.empty()) {
            cout << "No books found!" << endl;
            return;
        }

        cout << "\n===== Book Availability =====\n";
        for (const Book &book : books) {
            cout << "Book Name: " << book.bookname << endl;
            cout << "Book ID: " << book.bookid << endl;
            cout << "Available Quantity: " << book.quantity << endl;
            cout << endl;
        }
    };

    void searchBook() {
        int id;
        cout << "Enter book ID to search: ";
        cin >> id;
        Book book;
        book.searchbooks(books, id);
    };

    void updateBook() {
        int id;
        cout << "Enter book ID to update: ";
        cin >> id;
        Book book;
        book.updatebooks(books, id);
    };

    void deleteBook() {
        int id;
        cout << "Enter book ID to delete: ";
        cin >> id;
        Book book;
        book.deletebooks(books, id);
    };

    
};    
class member{
    private:
        string membername;
        int memberid,memberage;
        struct LoanRecord {
            string bookname;
            int bookid;
            string lentdate;
            string returndate;
            bool returned;
        };
        vector<LoanRecord> loanhistory;
    public:
        member() : memberid(0), memberage(0) {}
        void addmember(){
            cout << "Enter member name: ";
            cin >> membername;
            cout << "Enter member ID: ";
            cin >> memberid;
            cout << "Enter member age: ";
            cin >> memberage;
        };
        void displaymember() const {
            cout << "Member Name: " << membername << endl;
            cout << "Member ID: " << memberid << endl;
            cout << "Member Age: " << memberage << endl;
        };
        int getMemberId() const {
            return memberid;
        };
        void member_tracking(){
            int choice;
            do {
                cout << "\n1. Lend a book\n";
                cout << "2. Return a book\n";
                cout << "3. Show lending history\n";
                cout << "4. Exit\n";
                cout << "Enter choice: ";
                cin >> choice;

                if (choice == 1) {
                    LoanRecord record;
                    record.returned = false;
                    cout << "Enter book name: ";
                    cin >> record.bookname;
                    cout << "Enter book ID: ";
                    cin >> record.bookid;
                    cout << "Enter lending date: ";
                    cin >> record.lentdate;
                    cout << "Enter return due date: ";
                    cin >> record.returndate;
                    loanhistory.push_back(record);
                    cout << "Book lending recorded!" << endl;
                } else if (choice == 2) {
                    int bookid;
                    cout << "Enter book ID to return: ";
                    cin >> bookid;
                    bool found = false;
                    for (LoanRecord &record : loanhistory) {
                        if (record.bookid == bookid && !record.returned) {
                            cout << "Enter actual return date: ";
                            cin >> record.returndate;
                            record.returned = true;
                            found = true;
                            cout << "Book return recorded!" << endl;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Active lending record not found!" << endl;
                    }
                } else if (choice == 3) {
                    if (loanhistory.empty()) {
                        cout << "No lending history found." << endl;
                    } else {
                        for (const LoanRecord &record : loanhistory) {
                            cout << "Book Name: " << record.bookname << endl;
                            cout << "Book ID: " << record.bookid << endl;
                            cout << "Lent Date: " << record.lentdate << endl;
                            cout << (record.returned ? "Returned Date: " : "Due Date: ")
                                 << record.returndate << endl;
                            cout << "Status: " << (record.returned ? "Returned" : "On loan") << endl;
                            cout << endl;
                        }
                    }
                } else if (choice != 4) {
                    cout << "Invalid choice!" << endl;
                }
            } while (choice != 4);
        };
};

int main() {
    Library library;
    vector<member> members;
    int choice;

    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add book\n";
        cout << "2. Display all books\n";
        cout << "3. Show book status\n";
        cout << "4. Search book\n";
        cout << "5. Update book\n";
        cout << "6. Delete book\n";
        cout << "7. Lend book\n";
        cout << "8. Return book\n";
        cout << "9. Add member\n";
        cout << "10. Display members\n";
        cout << "11. Track member lending\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            library.addBook();
        } else if (choice == 2) {
            library.displayBooks();
        } else if (choice == 3) {
            library.bookStatus();
        } else if (choice == 4) {
            library.searchBook();
        } else if (choice == 5) {
            library.updateBook();
        } else if (choice == 6) {
            library.deleteBook();
        } else if (choice == 7) {
            library.bookLen();
        } else if (choice == 8) {
            library.returnBook();
        } else if (choice == 9) {
            member newmember;
            newmember.addmember();
            members.push_back(newmember);
            cout << "Member added!" << endl;
        } else if (choice == 10) {
            if (members.empty()) {
                cout << "No members found!" << endl;
            } else {
                for (const member &currentmember : members) {
                    currentmember.displaymember();
                    cout << endl;
                }
            }
        } else if (choice == 11) {
            int id;
            cout << "Enter member ID: ";
            cin >> id;
            bool found = false;
            for (member &currentmember : members) {
                if (currentmember.getMemberId() == id) {
                    currentmember.member_tracking();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Member not found!" << endl;
            }
        } else if (choice != 0) {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    cout << "Goodbye!" << endl;
    return 0;
}