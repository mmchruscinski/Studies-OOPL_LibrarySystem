#include <iostream>
#include <list>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;

//****************************************************************
//global settings
//****************************************************************

fstream cat, catb, users, us2, catb1, catb2;

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
    string getIdentifier() {return ISBN;}
};

class User{
private:
    string UserName;
    string Password;
    string hasBook;
    string Status;
public:
    User(string userName, string password){
        UserName = userName;
        Password = password;
        Status = "normal";
        hasBook = "none";
    }

    string getBook(){return hasBook;}
    string getName(){return UserName;}

    void setBook(string book){
        if (hasBook != "none") {
            cout << "You already have a book on your account!" << endl;
            return;
        }
        else hasBook = book;
    }   
    void writeRegistered(){
        users.open("Users.csv", ios::app);
        if (users.is_open()) {
            users << UserName << ','
                  << Password << ','
                  << Status << ','
                  << hasBook << ','
                  << endl;
            users.close();
        }
    }
    void updateData(){
        users.open("Users.csv", ios::in);
        us2.open("Users_n.csv", ios::out);
        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        do {
            while (getline(users, line)){
                row.clear();
                stringstream s(line);
                while(getline(s,word,',')) {
                    row.push_back(word);

                }
                if (row[0] == UserName) continue;
                content.push_back(row);
            }
        } while (!users.eof());
        users.close();

        row[0] = UserName;
        row[1] = Password;
        row[2] = Status;
        row[3] = hasBook;
        content.push_back(row);

        for (int i = 0; i<content.size(); i++) {
            us2 << content[i][0] << ',' 
                << content[i][1] << ',' 
                << content[i][2] << ',' 
                << content[i][3] << ',' 
                << endl;
        }
        us2.close();
        remove("Users.csv");
        rename("Users_n.csv", "Users.csv");
    }
    bool login(){
         users.open("Users.csv", ios::in);
        if (users.is_open()) {
            vector<string> row;
            string line, word;

            while(getline(users, line)) {
                row.clear();
                stringstream s(line);
                while(getline(s, word, ',')) {
                    row.push_back(word);
                }
                if (row[0] == UserName) { 
                    if (row[1] == Password) {
                        Status = row[2];
                        hasBook = row[3];
                        cout << "You are succesfully logged in!" << endl;
                        users.close();
                        return true;
                    }
                    else {
                        cout << "The username or password is incorrect!" << endl;
                        users.close();
                        return false;
                    }
                }
            }
            if (users.eof()) {
                cout << "There is no such username in the database!" << endl;
                users.close();
                return false;                 
            }
        }     
    return false;
    }
};



//****************************************************************
//functions declarations
//****************************************************************

void mainMenu();
bool userLogIn();
void userRegister();
string windowBrowse();
bool userLogOut();
bool windowReturn();
void windowReport();
void windowAdmin();
void bookCreate();

//****************************************************************
//main function
//****************************************************************

int main(){
    bool menuOn = true;
    mainMenu();

    cout << endl;
    return 0;
}

//****************************************************************
//minor functions
//****************************************************************

void mainMenu(){
    //system("cls");
    string tempbook;
    bool ifReturn;
    string isbn;
    char choice;
    bool logInOut = false;
    User* currentUser = new User("default", "default");
    do{
        if (logInOut == true){cout << "Logged-in as " << currentUser->getName() << endl;}
        cout << "MAIN MENU\n" << endl;
        if (logInOut == true) {cout << "1. Log out\n" << endl;}
        else {cout << "1. Log in\n" << endl; cout << "2. Register\n" << endl;} 
        cout << "3. Browse the books\n" << endl;
        cout << "4. Return the book\n" << endl;
        //cout << "5. Create the report\n" << endl;
        cout << "6. Manage the list\n" << endl;
        cout << "7. Close\n" << endl << endl;
        cout << "Choose the page: ";
        cin >> choice;

        switch(choice){
//*********************************************************************
        case '1':
            if (logInOut == false) {
                string userName;
                string password;
                cout << "Username: "; cin >> userName;
                cout << "Password: "; cin >> password;
                *currentUser = User(userName, password);
                logInOut = currentUser->login();
                break;
            } 
            else {
                logInOut = userLogOut(); 
                delete currentUser;
                cout << "You are succesfully logged out." << endl;
                break;
            } 

//*********************************************************************
        case '2':
            if (logInOut == true) {break;}
            else {userRegister(); break;} 

//*********************************************************************       
        case '3':

            if (logInOut == false) {cout << "You must be logged-in to browse the books!" << endl; break;}
            else{
                tempbook = currentUser->getBook(); 
                if (tempbook == "none"){
                    isbn = windowBrowse(); 
                    currentUser->setBook(isbn);
                    currentUser->updateData();
                    break;
                }
                else {
                    cout << "First return the current book!" << endl; 
                    break;
                }
            }

//*********************************************************************       
        case '4':
            ifReturn = windowReturn(); 
            if (ifReturn == true) {
                currentUser->setBook("none");
                currentUser->updateData();
            }
            break;

//*********************************************************************      
        /* case '5':
            break; */

//*********************************************************************       
        case '6':
            windowAdmin(); break;

//*********************************************************************      
        case 'r':
            break;

//*********************************************************************       
        default:
            cout << "You must choose the number" << endl;
            //_sleep(2000);
        }
    } while (choice!= '7');
}

void userRegister(){
    string userName;
    string password;
    cout << "REGISTRATION" << endl;
    cout << "Username: "; cin >> userName;
    cout << "Password: "; cin >> password;
    User newUser(userName, password);
    newUser.writeRegistered();
    return;
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

void windowReport(){
    return;
}

string windowBrowse(){
    string borrowedName = "none";
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
            borrowedName = bookinfo[bookNumint].getIdentifier();
            bookinfo[bookNumint].CheckOut();  
            for (int i = 0; i<bookinfo.size(); i++) {
                bookinfo[i].Create();
            }
            us2.close();

        }

    } while (choice != 'r');
    return borrowedName;
}

bool windowReturn(){
    char yesNo;
    gotoline:
    cout << "The book you have borrowed: " << endl;
    cout << "Are you sure you want to return the book?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cin >> yesNo;
    if (yesNo == '1'){return true;}
    if (yesNo == '2'){return false;}
    else {
        cout << "You must choose between 1 or 2!" << endl;
        goto gotoline;
    }
}

void windowAdmin(){
    char ch;
    do{
    cout << "1. Add the record\n" << endl;
    cout << "2. Delete the record\n" << endl;
    cout << "3. Edit the record\n" << endl;
    cout << "7. Return\n" << endl;
    try {cin >> ch;}
    catch (const char* numException) {
        cout << "Error: " << numException << endl;
    }
    switch(ch){
    case '1':
        bookCreate();
    case '2':
        break;
    case '3':
        break;
    case '7':
        break;
    default:
        if (!(cin >> ch)){
            throw "The entry must be a number!";
        }
        //_sleep(2000);
    }
    } while(ch != '7');

}

void bookCreate(){
    string title, author, isbn; 
    int pagecount;
    cout << "Author: ";             cin.sync();     getline(cin, author);
    cout << "Title: ";              cin.sync();     getline(cin, title); cin.clear();
    cout << "Number of pages: ";    cin.sync();     try {cin >> pagecount;} catch (const char* exc) {cout << "Error: " << exc << endl;}                                                                                   
    cout << "ISBN number: ";        cin.sync();     getline(cin, isbn);
 
    Book newbook(title, author, pagecount, isbn);
    newbook.Create();
    cout << "The book record has been added to the cathalog" << endl;
}
