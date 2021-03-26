#include <iostream>
#include<time.h>
#include <ctime>

using namespace std;
void insertion_sort(int A[],int low,int high);
void merge_sort(int A[],int low,int high);
void merge(int A[],int  low,int mid,int high);
void quick_sort_1(int A[],int low,int high);
void quick_sort_2(int A[],int low,int high);
void quick_sort_3(int A[],int low,int high);
void partition(int A[],int low,int high,int& pivot);
void print(int A[], int low,int high);
void swap(int A[],int i,int j);
void copy(int source[],int dest[],int start,int end,int dest_index);
void fill_rand(int A[],int n);
int main()
{
    srand(time(NULL));
    clock_t start;
    double duration;
    int N = 2048;
    int A[N];
    int temp[N];
    float avg = 0;

    for(int i = 0 ;i < N;i++)
        A[i] = i;
    copy(A,temp,0,N,0);

    for(int i = 0; i < 20;i++){//repeats process 20 times to find avg time taken
        copy(temp,A,0,N,0);//resets data to be sorted
        start = std::clock();//reset time at each loop
        quick_sort_1(A,0,N);
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        avg += duration;
    }
       cout<<"avg time taken for "<<N<<" items:"<<avg/20.0<<endl;
    print(A,0,N);
    return 0;
}
void insertion_sort(int A[],int low,int high){
    for(int i = low; i < high;i++)
        for(int j = i ;j > 0 && A[j-1] > A[j];j--)
            swap(A,j,j-1);
}
void merge_sort(int A[], int low, int high)
{
    int mid;
    if(low < high){
        mid = (low + high)/2;
        merge_sort(A,low,mid);
        merge_sort(A,mid + 1,high);
        merge(A,low,mid,high);
    }
}
void merge(int A[],int  low,int mid,int high)
{
    int i = 0;
    int j = 0;
    int k = low;
    int ln = mid - low + 1;
    int rn = high - mid;
    int left[ln];
    int right[rn];

    for(int l = 0 ; l < ln;l++)
        left[l] = A[low + l];
    for(int l = 0 ; l < rn;l++)
        right[l] = A[mid + l + 1];

    while( i < ln && j < rn)
        if(left[i] <= right[j])
            A[k++] = left[i++];
        else
            A[k++] = right[j++];
    copy(left,A,i,ln,k);
    copy(right,A,j,rn,k);
}
void quick_sort_1(int A[],int low,int high){
    int pivot_point;
    if( high > low){
        partition(A,low,high,pivot_point);
        quick_sort_1(A,low,pivot_point - 1);
        quick_sort_1(A,pivot_point + 1,high);
    }
}
void quick_sort_2(int A[],int low,int high){
    int pivot_point;
    if(high > low)
        if(high - low < 16)
            insertion_sort(A,low,high);
        else
        {
            partition(A,low,high,pivot_point);
            quick_sort_2(A,low,pivot_point);
            quick_sort_2(A,pivot_point + 1,high);
        }
    else return;
}
void quick_sort_3(int A[],int low,int high){
    int pivot_point;
    if(high > low){
        if(high - low < 16)
            insertion_sort(A,low,high);
        else
            if(high - low > 16)
                swap(A,low,rand()% (high - low) + 1);
        partition(A,low,high,pivot_point);
        quick_sort_3(A,low,pivot_point);
        quick_sort_3(A,pivot_point + 1,high);
    }
}
void partition(int A[],int low,int high,int& pivot)
{
    int j = low;
    int pivot_item = A[low];
    for(int i = low + 1;i < high;i++)
        if(A[i]< pivot_item){
            j++;
            swap(A,i,j);
        }
    pivot = j;
    swap(A,low,pivot);
}
void print(int A[], int low, int high)
{
    for(;low < high;low++){
        if(!(low % 15))
            cout<<endl<<A[low]<<",";
        else
            cout<<A[low]<<",";
    }
    cout<<endl;
}
void swap(int A[],int i,int j)
{
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}
void copy(int source[],int dest[],int start,int end,int dest_index)
{
    while(start < end)
        dest[dest_index++] = source[start++];
}
void fill_rand(int A[],int n){
    for(int i = 0; i < n;i++)
        A[i] = rand() % n + 1;
}
