#include<iostream>
#include<iomanip>
using namespace std;
void viewBalance(double balance)
{
    cout<<"Balance: $"<<balance<<'\n';
}
double deposit(double balance)
{
    double deposit;
    cout<<"Enter the amount to be deposited: \n";
    cin>>deposit;
    if(deposit<0)
    {
        cout<<"invalid deposit";
        return 0;
    }
    return deposit;
}
double withdraw(double balance)
{
    double withdraw;
    cout<<"enter amount to be withdrawn\n";
    cin>>withdraw;
    if(withdraw>balance)
    {
        cout<<"insufficient funds!";
        return 0;
    }
    else if(withdraw<=0)
    {
        cout<<"invalid withdraw!\n";
        return 0;
    }
    else
    {
    return withdraw;
    }
}
int main()
{
    double balance=0.00;
    int choise;
    cout << fixed << setprecision(2);
    do
    {
        cout<<"*************************\n";
        cout<<"welcome to banking system\n";
        cout<<"*************************\n";
        cout<<"What would you like to do:\n";
        cout<<"1.Show Balance \n2.Deposit \n3.Withdraw \n4.Exit\n";
        cin>>choise;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        switch(choise)
        {
            case 1:
            viewBalance(balance);
            break;
            case 2:
            balance+=deposit(balance);
            cout<<"Balance: $"<<balance<<'\n';
            break;
            case 3:
            balance-=withdraw(balance);
            cout<<"Balance: $"<<balance<<'\n';
            break;
            case 4:
            cout<<"Thanks for visiting.\n";
            break;
            default :
            cout<<"Please enter a valid input \n";

        }
    } while (choise!=4);
    return 0;  
}
