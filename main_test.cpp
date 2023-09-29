#include <iostream>
#include <list>
using namespace std;

class Book{
private:
    string Title;
    string Author;
    int PageCount;
    string ISBN;
    bool Check;
    int CatNum;
public:
    Book(string title, string author, int pagecount, string isbn){
        Title = title;
        Author = author;
        PageCount = pagecount;
        ISBN = isbn;
        Check = false;
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
    void GetInfoShort(){
        cout << "Author: " << Author << endl;
        cout << "Title: " << Title << endl;
        cout << "ISBN: " << ISBN << endl;
    }
    void CheckOut(){
        if (Check == false){
            Check = true;
            cout << "The book has been checked out!" << endl;
        } else {
            cout << "You cannot check out the book that is not in stock!" << endl;
        }
    }
    void Return(){
        Check = false;
    }
};

class User{
private:
    string UserName;
    string Password;
public:
    User(string userName, string password){
        UserName = userName;
        Password = password;
    }
};

class Admin : public User{
public:
    Admin(string userName, string password) : User(userName, password){

    }
};


bool menuOn = true;



bool mainMenu(bool);
bool userLogIn();
void userRegister();
void browseBooks();
bool userLogOut();
void returnBook();
void report();




int main(){
    bool logInOut = false;
    do{
        logInOut = mainMenu(logInOut);
        cout << logInOut << endl;
    } while (menuOn == true);


    cout << endl;
    Book book1("Encykliki Jana Pawla II - dziela zebrane", "Karol Wojtyla", 420, "2137.SS-69");
    book1.GetInfo();
    //system("pause>0");
    system("cls");
    return 0;
}




bool mainMenu(bool logInOut){
    int choice;
    if (logInOut == true){cout << "Logged-in as " << endl;}
    cout << "MAIN MENU\n" << endl;
    if (logInOut == true) {cout << "1. Log out\n" << endl;}
    else {cout << "1. Log in\n" << endl; cout << "2. Register\n" << endl;} 
    cout << "3. Browse the books\n" << endl;
    cout << "4. Return the book\n" << endl;
    cout << "5. Create the report\n" << endl;
    cout << "7. Close\n" << endl << endl;
    cout << "Choose the page: ";
    cin >> choice;
    switch(choice){
    case 1:
        if (logInOut == true) {logInOut = userLogOut(); break;}
        else {logInOut = userLogIn(); break;}       
    case 2:
        if (logInOut == true) {break;}
        else {userRegister(); break;} 
    case 3:
        browseBooks(); break;
    case 4:
        returnBook(); break;
    case 5:
        break;
    case 7:
        menuOn = false;
        break;
    default:
        break;
    }
    return logInOut;
}

void userRegister(){
    string userName;
    string password;
    cout << "REGISTRATION" << endl;
    cout << "Username: "; cin >> userName;
    cout << "Password: "; cin >> password;
    return;
}

bool userLogIn(){
    string userName;
    string password;
    cout << "Username: "; cin >> userName;
    cout << "Password: "; cin >> password;
    return true;
}

bool userLogOut(){
    int yesNo;
    gotoline:
    cout << "Are you sure you want to log-out?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cin >> yesNo;
    if (yesNo == 1){;
        return false;
    }
    if (yesNo == 2){return true;}
    else {
        cout << "You must to choose between 1 or 2!" << endl;
        goto gotoline;
    }
}

void report(){
    return;
}

void browseBooks(){
    cout << "Browsing..." << endl;
    return;
}

void returnBook(){
    int yesNo;
    gotoline:
    cout << "The book you have borrowed: " << endl;
    cout << "Are you sure you want to return the book?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cin >> yesNo;
    if (yesNo == 1){return;}
    if (yesNo == 2){return;}
    else {
        cout << "You must choose between 1 or 2!" << endl;
        goto gotoline;
    }
}
