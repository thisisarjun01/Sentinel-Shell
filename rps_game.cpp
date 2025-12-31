#include<iostream>
#include<ctime>
using namespace std;

void userChoise(char user)
{
    switch (user)
    {
        case 'r': cout<<"your choise: Rock\n";break;
        case 'p': cout<<"your choise: Paper\n";break;
        case 's': cout<<"your choise: Scissor\n";break;
         default:
            cout << "Invalid option — round skipped.\n";
    }
}
int computerChoise()
{
    int num = rand()%3+1;
    switch (num)
    {
        case 1: cout<<"computers choise: Rock\n";break;
        case 2: cout<<"computers choise: Paper\n";break;
        case 3: cout<<"computers choise: Scissor\n";break;
    }
    return num;
}
void result(char user , int computer)
{
    switch (user)
    {
        case 'r':
        switch (computer)
        {
            case 1 : cout<<"Draw !\n";break;
            case 2 : cout<<"You loose !\n";break;
            case 3 : cout<<"You win !\n";break;
        }
        break;
        case 'p':
        switch (computer)
        {
            case 1 : cout<<"You win !\n";break;
            case 2 : cout<<"Draw !\n";break;
            case 3 : cout<<"You loose !\n";break;
        }
         break;
        case 's':
        switch (computer)
        {
            case 1 : cout<<"You loose !\n"; break;
            case 2 : cout<<"You win !\n";break;
            case 3 : cout<<"Draw!\n";break;
        }
         break;
    }

}
int main()
{
    srand (time(NULL));
    char choise;
    do
    {
        cout<<"***********************\n";
        cout<<"rock-paper-scissor game\n";
        cout<<"***********************\n";
        cout<<"Enter your choise:\nrfor rock\np for paper\nsfor scissor\ne to exit game\n";
        cin>>choise;
        if(choise=='e')
        {
            break;
        }
        if (choise != 'r' && choise != 'p' && choise != 's') {
            cout << "Invalid input! Please try again.\n";
            continue;
        }
        userChoise(choise);
        int computer=computerChoise();
        result(choise,computer);

    }
    while(choise != 'e');
    return 0;

}
