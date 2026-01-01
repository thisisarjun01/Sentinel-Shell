#include<iostream>
using namespace std;
int find(int array[],int num, int size)
{
    for (int i=0;i<=size-1;i++)
    {
        if(array[i]==num)
        {
            return i;
        }
    }
    return -1;

}
int main()
{
    int array[]={2,4,7,9,0,1,6,3,5,8};
    int num;
    int size=sizeof(array)/sizeof(array[0]);
    cout<<"Enter the number whose position you would like to know: ";
    cin>>num;
    int index =find(array,num,size);
    if (index != -1)
    {
        cout << "Your number is at index #" << index << endl;
    }
     else
    {
        cout << "Sorry, that number is not in the list." << endl;
    }
    return 0;
}


