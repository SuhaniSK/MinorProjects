#include<iostream>
using namespace std;
void customswap(int *a ,int *b){
    int t= *a;
    *a=*b;
    *b=t;
}
int quicksort(int a[],int low,int high){
 int i,j,key;
 i=low;j=high;
key=a[low];
while(i<j){
    while(i <= high&&a[i]<=key){
        i++;
    }
    while(a[j]>key){
        j--;
    }
    if(i<j){
      customswap(&a[i],&a[j]);  
    }
}
customswap(&a[low],&a[j]);
return j;
    }
void quick(int a[],int low,int high){
    if(low<=high){
    int pi=quicksort(a,low,high);
     quick(a,low,pi-1);
     quick(a,pi+1,high);
    }
}
int main(){
    int a[]={1,5,2,4,3,9,6,7,8};
    quick(a,0,8);
    cout<<"the sorted array is:\n";
    for(int i=0;i<9;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}