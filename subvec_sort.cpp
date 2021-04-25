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
//добавление элемента в конец недовектора
//с выделением дополнительной памяти при необходимости


int pop_back(subvector *qv){
    if(qv->top >= 1){
        qv->top--;
        return *(qv->mas + qv->top);
    }
    return 0;
}
//удаление элемента с конца недовектора


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
//очистить неиспользуемую память


void clear(subvector *qv){
    qv->top = 0;
}
//очистить содержимое недовектора, занимаемое место
//при этом не меняется

void destructor(subvector *qv){
    if (qv->top > 0) delete[] qv->mas;
    qv->capacity = 0;
    qv->top = 0;
    qv->mas = NULL;
}
//очистить всю используемую память, инициализировать
//недовектор как пустой

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
  int left = 0, right = count - 1; // левая и правая границы сортируемой области массива
  int flag = 1;  // флаг наличия перемещений
  // Выполнение цикла пока левая граница не сомкнётся с правой
  // и пока в массиве имеются перемещения
  while ((left < right) && flag > 0)
  {
    flag = 0;
    for (int i = left; i<right; i++)  //двигаемся слева направо
    {
      if (mass[i]>mass[i + 1]) // если следующий элемент меньше текущего,
      {             // меняем их местами
        swap(mass+i, mass+i+1);
        flag = 1;      // перемещения в этом цикле были
      }
    }
    right--; // сдвигаем правую границу на предыдущий элемент
    for (int i = right; i>left; i--)  //двигаемся справа налево
    {
      if (mass[i - 1]>mass[i]) // если предыдущий элемент больше текущего,
      {            // меняем их местами
        swap(mass + i-1, mass+i);
        flag = 1;    // перемещения в этом цикле были
      }
    }
    left++; // сдвигаем левую границу на следующий элемент
  }
}

void qsortRecursive(int *mas, int size) {

    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(mas[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while(mas[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0) {
        //"Левый кусок"
        qsortRecursive(mas, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsortRecursive(&mas[i], size - i);
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
// Инициализируем наибольший элемент как корень
    int l = 2*i + 1; // левый = 2*i + 1
    int r = 2*i + 2; // правый = 2*i + 2

 // Если левый дочерний элемент больше корня
    if (l < n && arr[l] > arr[largest])
        largest = l;

   // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Если самый большой элемент не корень
    if (largest != i)
    {
        swap(arr+i, arr+ largest);

// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, n, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(int arr[], int n)
{
  // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

   // Один за другим извлекаем элементы из кучи
    for (int i=n-1; i>=0; i--)
    {
        // Перемещаем текущий корень в конец
        swap(arr+0, arr+i);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
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

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
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
