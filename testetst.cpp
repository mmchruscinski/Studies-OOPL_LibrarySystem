#include <iostream>
#include <list>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;

fstream cat, catb1, catb2, users, us2;

//****************************************************************
//classes
//****************************************************************

class Book{
private:
    bool Check;
protected:
    string Title;
    string Author;
    int PageCount;
    string ISBN;
    int CatNum;
public:
    Book(string title, string author, int pagecount, string isbn){
        Title = title;
        Author = author;
        PageCount = pagecount;
        ISBN = isbn;
        Check = false;
    }
    void Create(){
        cat.open("BookCathalog.csv", ios::app);
        if(cat.is_open()){
            cat << Author << ',' 
                << Title << ',' 
                << PageCount << ','
                << ISBN << ','
                << Check << ','
                << endl;
            cat.close();
        }
    }
    void GetInfoShort() {
        cout << Author << " - " << Title;
    }
    void GetInfoCat() {
        cout << Author << " - " << Title << ", Status: ";
        if (Check == false) cout << "Available" << endl;
        else cout << "Borrowed" << endl;
    }
    void GetInfo(){
        cout << "Author: " << Author << endl;
        cout << "Title: " << Title << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Page count: " << PageCount << endl;
        cout << "Check-out state: "; 
        if (Check == true){ cout << "Checked out";} 
        else {cout << "In stock";} cout << endl;
    }
    void CheckOut(){
        if (Check == false){
            Check = true;
            cout << "The book has been checked out!" << endl;
        } else {
            cout << "You cannot check out the book that is not in stock!" << endl;
        }
    }
    void Return() {Check = false;}
    void setStatus(bool stat) {Check = stat;}
};

class BookBorrowed:public Book{
public:
    BookBorrowed(string title, string author, int pagecount, string isbn):Book(title, author, pagecount, isbn){
        catb1.open("BorrowedBooks.csv", ios::app);
        if(catb1.is_open()){
            catb1 << Author << ',' 
            << Title << ',' 
            << PageCount << ','
            << ISBN << ','
            << endl;
        }
        cout << "The book has been borrowed" << endl;
    }
    void bookReturn(){

    }
};

int main(){
    char choice;
    do {
        catb1.open("BookCathalog.csv", ios::in);
        //catb2.open("BookCathalog_n.csv", ios::out);
        vector<Book> bookinfo;
        vector<string> row;
        string line, word;
        int tempint;
        bool tempbool; 

        do {
            while (getline(catb1, line)) {
                row.clear();
                stringstream s(line);
                while (getline(s, word,',')) {
                    row.push_back(word);
                }
                tempint = stoi(row[2]);
                Book tempBook(row[0], row[1], tempint, row[3]);

                if (row[4] == "0") tempbool = false;
                else tempbool = true;

                tempBook.setStatus(tempbool);
                bookinfo.push_back(tempBook);
            }
        } while (!catb1.eof());

        catb1.close();

        for (int i=0; i<bookinfo.size(); i++) {
	        cout << i+1 << ". ";
	        bookinfo[i].GetInfoCat();
        }

        char bookNum;
        cout << "Choose the book or type 'r' to return: ";
        cin >> bookNum; //dać wyjątki na numer i na znak
        if (bookNum == 'r') break; 

        int bookNumint = static_cast<int>(bookNum) - 49;

        cout << "Are you sure you want to borrow: "; 
        bookinfo[bookNumint].GetInfoShort(); 
        cout << "?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cin >> choice;

        if (choice == '1') {
 
            remove("BookCathalog.csv");

            bookinfo[bookNumint].CheckOut();  
            for (int i = 0; i<bookinfo.size(); i++) {
                bookinfo[i].Create();
            }
            us2.close();

        }

    } while (choice != 'r');
    return 0;
}