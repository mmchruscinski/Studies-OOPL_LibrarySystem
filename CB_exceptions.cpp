#include<iostream>
#include<string>
using namespace std;

class Printer{
    string _name;
    int _availablePaper;
public:
    Printer(string name, int availablePaper){
        _name = name;
        _availablePaper = availablePaper;
    }
    void Print(string txtDoc){
        int requiredPaper = txtDoc.length() / 10;

        if(requiredPaper > _availablePaper)
            throw 101;

        cout << "Printing..." << txtDoc << endl;
        _availablePaper -= requiredPaper;
    }
};

int main(){

    Printer myPrinter("HP DeskJet 1234", 10);
    try {
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
        myPrinter.Print("Hello xdddd");
    }
    catch(const char* txtException) {
        cout << "Exception: " << txtException << endl;
    }
    catch(int exCode)  {
        cout << "Exception: " << exCode << endl;
    }
    catch(...) {
        cout << "Exception happened!" << endl;
    }

    system("pause>nul");
    return 0;
}