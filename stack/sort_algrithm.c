#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void swap(int* a, int* b);
void selection_sort(int arr[],int length);

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int length = sizeof(arr)/sizeof(int);
    selection_sort(arr,length);
    for(int i=0;i<length;i++)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int arr[],int length)
{
    for(int i=0;i<length;i++)
    {
        int min_id = i;
        for(int j=i+1;j<length;j++)
        {
            if(arr[j]<arr[min_id])
            {
                min_id = j;
            }
        }
        swap(&arr[i],&arr[min_id]);
    }
}