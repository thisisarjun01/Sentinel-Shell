#include<iostream>
using namespace std;
int odd(string card, int length)
{
    int sum=0;
    for(int i=length-2;i>=0;i-=2)
    {
        int num=card[i]-'0';
        int doubled = num * 2;
        if (doubled > 9)
        {
             doubled -= 9;
        }
        sum += doubled;

    }
    return sum;
}
int even(string card, int length)
{
    int sum=0;
    for(int i=length-1;i>=0;i-=2)
    {
        int num=card[i]-'0';
        sum+=num;
    }
    return sum;
}
bool divisibility(int sumodd, int sumeven)
{
    int temp=sumodd+sumeven;
    return temp % 10 == 0;

}
int main()
{
    string card;
    cout<<"*********************\n";
    cout<<"Credit Card Validator\n";
    cout<<"*********************\n";
    cout<<"Enter Your Card Number : #";
    cin>>card;
    int length=card.size();
    int sumodd=odd(card,length);
    int sumeven=even(card,length);
    divisibility(sumodd,sumeven) ? cout<<"This is a Valid card\n" : cout<<"this is an Invalid card\n";
    cout<<"*******************\n";
    cout<<"Thanks for visiting\n";
    cout<<"*******************\n";
    return 0;
}
