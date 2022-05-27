#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
using namespace std;

//Declarations
string sinput(string arg);
string rounded(double myValue);
void showPreviousTransactions();
void showInventory();
void showMenu();
void setPrices();
void setList();
void game();

//Classes

class Inventory{
    public:
    int cows=0;
    int chickens=0;
    int pigs=0;
    int lottery=0;

};

class Transaction{
    private:
    double amount;
    string txtype;
  
    public:
    Transaction(string ttype,double price)
    {
        amount = price;
        txtype=ttype;
    }
    double getAmount(){
        return amount;
    }
    string getTxtype(){
        return txtype;
    }
};

//Global


vector<Transaction> myTXList(50,Transaction("",0));
vector<double> myPrices(5);
Inventory myInventory;
int placer = 0;
double startBalance = 1000;

int main(){
    int choice = 0;
    double price;
    setPrices();
    while (choice!=8){
        showMenu();
        cin>>choice;
        price = myPrices[choice-1];
        if (!(startBalance>=price)){cout<<"[x] Insufficient balance!";sleep(2);continue;}
        switch(choice){
            case 1:
                {Transaction trans("Chicken",price);
                myTXList[placer]=trans;
                myInventory.chickens+=1;
                cout<<"1x Chicken has successfully been purchased!\n";
                startBalance-=price;
                if (placer<50){placer++;}
                sleep(2);
                break;}
            case 2:
                {Transaction trans("Cow",price);
                myTXList[placer]=trans;
                myInventory.chickens+=1;
                startBalance-=price;
                cout<<"1x Cow has successfully been purchased!\n";
                if (placer<50){placer++;}
                sleep(2);
                break;}
            case 3:
                {Transaction trans("Pig",price);
                myTXList[placer]=trans;
                myInventory.pigs+=1;
                startBalance-=price;
                cout<<"1x Pig has successfully been purchased!\n";
                if (placer<50){placer++;}
                sleep(2);
                break;}
            case 4:
                {Transaction trans("Lottery Ticket",price);
                myTXList[placer]=trans;
                myInventory.lottery+=1;
                startBalance-=price;
                cout<<"1x Lottery Ticket has successfully been purchased!\n";
                if (placer<50){placer++;}
                sleep(2);
                break;}
            case 5:
                if (myInventory.lottery==0){cout<<"[x] You have no lottery tickets available!\n";sleep(2);break;}
                game();
                myInventory.lottery-=1;

            case 6:
                showPreviousTransactions();
                break;
            case 7:
                showInventory();
                break;
            default:
                break;    

        }
    }


    return 0;
}

void game(){
    system("CLS");
    int myNumber;
    int computerNumber = rand() % 5 + 1;
    int prize = rand() % 1000 + 5;
    string message = "I am thinking of a number 1 through 5...";
    cout<<message;
    cout<<"\n\n[+] Enter your guess:  ";
    cin>>myNumber;
    if (myNumber==computerNumber){
        startBalance+=prize;
        cout<<"\n Congrats! You won: $"+to_string(prize);
    }
    else{
        cout<<"\n Wrong number! Correct Answer: "+to_string(computerNumber);
    }
    sinput("\nPress any key then ENTER key to continue... ");
}

void showInventory(){
    cout<<"Your Farm Inventory\n+++++++++++++++++++++\n";
    cout<<"Chickens: \t" + to_string(myInventory.chickens)<<endl;
    cout<<"Cows: \t" + to_string(myInventory.cows)<<endl;
    cout<<"Pigs: \t" + to_string(myInventory.pigs)<<endl;
    cout<<"Lottery Tickets: \t" + to_string(myInventory.lottery)<<endl;
    sinput("Press any key then ENTER key to continue... ");
}

void showPreviousTransactions(){
    system("CLS");
    cout<<"Previous Farm and Fleet Purchases\n+++++++++++++++++++++\n";
    for(int i =0; i<myTXList.size();i++){
        Transaction trans = myTXList[i];
        if (trans.getAmount()!=0){
        cout<<trans.getTxtype() + "\t" + rounded(trans.getAmount())<<endl;}
    }
    sinput("\nPress ENTER key to continue...");
}

void setPrices(){
    myPrices[0]=10.99;
    myPrices[1]=30.99;
    myPrices[2]=29.99;
    myPrices[3]=1.99;
}

void showMenu(){ //yea
    system("CLS");
    cout<<"Farm and Fleet\n+++++++++++\n\n[-] Current Balance: " + rounded(startBalance)+ "\n[1] Buy Chicken ~ $10.99\n[2] Buy Cow ~ $30.99\n[3] Buy Pig ~ $29.99\n[4] Buy Lottery Ticket ~ $1.99\n[5] Play The Lottery\n[6] Previous Transactions\n[7] Show Inventory\n[8] Exit\n\n[+] Enter Your Choice: ";
}

string sinput(string arg){
    string input;
    cout<<arg;
    cin>>input;
    return input;
}

string rounded(double myValue) //lmfao
{
    string result;
    string base= "";
    string decimals=".";
    double bal = myValue;
    int balx = (int)(bal *100); 
    result = to_string(balx);
    char decimal1 = result[result.length()-2];
    decimals+=decimal1;
    char decimal2 = result[result.length()-1];
    decimals+=decimal2;
    for (int i = 0; i<result.length()-2;i++){
        base+=result[i];}
    result="$"+base+decimals;
    return result;
}


