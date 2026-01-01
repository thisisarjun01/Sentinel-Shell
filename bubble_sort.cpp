#include<iostream>
using namespace std;
void sort(int array[],int size)
{
   for(int i=0;i<=size-2;i++)
   {
        for(int j=0;j<=size-1-i;j++)
         {   
            if(array[j]>array[j+1])
                {
                    int temp=array[j];
                    array[j]=array[j+1];
                    array[j+1]=temp;
                 }
        }
   }
   for(int i=0;i<=size-1;i++)
    {
        
        cout<<array[i]<<'\t';
       
    }

}
int main()
{
    int array[10];
    int size=sizeof(array)/sizeof(array[0]);
    cout<<"Enter an array of 10 numbers: \n";
    for(int i=0;i<=size-1;i++)
    {
        int temp=0;
        cout<<"Enter the element at index #"<<i<<'\n';
        cin>>temp;
        array[i]=temp;
    }
    sort(array,size);
    return 0;
}
