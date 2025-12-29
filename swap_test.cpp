#include<iostream>

void swap(int* num1, int* num2)
{
   *num1=*num1+*num2;
   *num2=*num1-*num2;
   *num1=*num1-*num2;
}
int main()
{
   int x=10, y=20;
   std::cout<<"before swapping x="<<x <<" y="<<y<<'\n';
   swap(x,y);
   std::cout<<"after swapping x="<<num1 <<" y="<<num2<<'\n';
   return 0;
}
