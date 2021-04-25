#include <iostream>
using std::cout;
using std::endl;

struct subvector {
int *mas;
unsigned int top;
unsigned int capacity;
};

bool resize(subvector *qv, unsigned int new_capacity);

bool init(subvector *qv){
    qv->capacity = 0;
    qv->top = 0;
    qv->mas = NULL;
    return true;
}


bool push_back(subvector *qv, int d){
    if ( (qv->capacity - qv->top) >= 1 ){

        *(qv->mas + qv->top) = d;
        qv->top++;
    }else{
        cout << endl << "needed resize" << qv->top << qv->capacity << endl;
        resize(qv, qv->capacity + 1);
        *(qv->mas + qv->top) = d;
        qv->top++;
    }
    return true;
}


int pop_back(subvector *qv){
    if(qv->top >= 1){
        qv->top--;
        return *(qv->mas + qv->top);
    }
    return 0;
}


bool resize(subvector *qv, unsigned int new_capacity){
    if(qv->capacity >= new_capacity){
        return false;
    }
    int *new_mas = new int[new_capacity];

    for (int i = 0; i < qv->top; i++){
        *(new_mas + i) = *(qv->mas + i);
    }

    if (qv->mas){delete[] qv->mas;}
    qv->mas = new_mas;
    qv->capacity = new_capacity;
    return true;
}


void shrink_to_fit(subvector *qv){
    int* new_mas = new int[qv->top];
    for (int i = 0; i < qv->top; i++){
        *(new_mas + i) = *(qv->mas + i);
    }
    qv->capacity = qv->top;
    delete[] qv->mas;
    qv->mas = new_mas;
}


void clear(subvector *qv){
    qv->top = 0;
}

void destructor(subvector *qv){
    if (qv->top > 0) delete[] qv->mas;
    qv->capacity = 0;
    qv->top = 0;
    qv->mas = NULL;
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(subvector *qv){
    for(int i = 0; i < qv->top; i++){
        for(int j = i+1; j < qv->top; j++){
            if(*(qv->mas + j) < *(qv->mas + i)){
                swap(qv->mas + j, qv->mas + i);
            }
        }
    }
}

void insert_sort(subvector* qv){
    if (qv->top >= 2){

    for(int i = 1; i < qv->top; i++){
        int temp = *(qv->mas + i);
        int j = i - 1;
        while (j >= -1){
            if (j >= 0){
                if(*(qv->mas + j) > temp){
                    *(qv->mas + j + 1) = *(qv->mas + j);
                }else{
                    *(qv->mas + j + 1) = temp;
                    j = -2;
                }
            }else{
                *(qv->mas + j + 1) = temp;
            }
            j--;
        }
    }
    }
}


void shaker_sort(subvector *qv)
{

  int count = qv->top;
  int *mass = qv->mas;
  int left = 0, right = count - 1; 
  while ((left < right) && flag > 0)
  {
    flag = 0;
    for (int i = left; i<right; i++)  
    {
      if (mass[i]>mass[i + 1])
      {            
        swap(mass+i, mass+i+1);
        flag = 1;      
      }
    }
    right--; 
    for (int i = right; i>left; i--) 
    {
      if (mass[i - 1]>mass[i]) 
      {            
        swap(mass + i-1, mass+i);
        flag = 1;    
      }
    }
    left++; 
  }
}

void qsortRecursive(int *mas, int size) {

   
    int i = 0;
    int j = size - 1;

   
    int mid = mas[size / 2];

  
    do {
       
        while(mas[i] < mid) {
            i++;
        }
      
        while(mas[j] > mid) {
            j--;
        }

        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    if(j > 0) {
        qsortRecursive(mas, j + 1);
    }
    if (i < size) {
        qsortRecursive(&mas[i], size - i);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1; 
    int r = 2*i + 2; 


    if (l < n && arr[l] > arr[largest])
        largest = l;

 
    if (r < n && arr[r] > arr[largest])
        largest = r;

   
    if (largest != i)
    {
        swap(arr+i, arr+ largest);


        heapify(arr, n, largest);
    }
}


void heapSort(int arr[], int n)
{
  
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

  
    for (int i=n-1; i>=0; i--)
    {
      
        swap(arr+0, arr+i);

       
        heapify(arr, i, 0);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

 
    int L[n1], R[n2];

   
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

  
    int i = 0;

    int j = 0;

    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}


/*
int main(){
    subvector sv;
    push_back()
    return 0;
}//*/
