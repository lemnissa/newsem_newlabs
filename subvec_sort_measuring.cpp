#include <iostream>
#include "subvec_sort.cpp"
#include <chrono>
#include <fstream>
#include <random>
#include <iomanip>

double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

void clear_file(const char *file_name){
  std::ofstream fout;
  fout.open(file_name, std::ios::out);
  fout.close();
}

int rand_uns(int min, int max)

{

unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();

static std::default_random_engine e(seed);

std::uniform_int_distribution<int> d(min, max);

return d(e);

}

void fullfull_vector(subvector* sv, int* seq, unsigned long long int n){

    //destructor(sv);

    for (int i = 0; i < n; i++)
    {

        push_back(sv, seq[i]);
    }
}

void apply(void (* sort_func)(subvector* ), const char *file_name){

int start_n = 1;
long long int n = 101;
int delta_n = 10;

int cell_num = n/delta_n;

int epochs = 1;
int repetitions = 200000;

int* random_sequence = new int[n];

for(int i = 0; i < n; i++){
    *(random_sequence + i) = rand_uns(-1000, 1000);
}

cout << "random ready" << endl;
float *sort_mas = new float[cell_num];


subvector* subvectors = new subvector[repetitions*cell_num];

std::ofstream fout;
///* _sort------------------------------------------
clear_file(file_name);


for (int i = 0; i < cell_num; i++){
    sort_mas[i] = 0;
}

subvector sv;
init(&sv);
resize(&sv, 10);
fullfull_vector(&sv, random_sequence, 10);
for(int i = 0; i < 10; i++){
    cout << *(sv.mas + i) << " ";
}
sort_func(&sv);
cout << endl;
for(int i = 0; i < 10; i++){
    cout << *(sv.mas + i) << " ";
}

for (int i = 0; i<(n-start_n)/delta_n; i++){
    for (int j = 0; j < repetitions; j++){
        init(&(*(subvectors + i*repetitions + j)));
        //resize(&(*(subvectors + i*repetitions + j)), start_n+i*delta_n);

        int *new_mas = new int[start_n+i*delta_n];

        (subvectors + i*repetitions + j)->mas = new int[start_n+i*delta_n];
        (subvectors + i*repetitions + j)->capacity = start_n+i*delta_n;
        (subvectors + i*repetitions + j)->top = 0;

        for (int k = 0; k < start_n+i*delta_n; k++)
        {

            //push_back(&(*(subvectors + i*repetitions + j)), *(random_sequence + k));
            *((subvectors + i*repetitions + j)->mas + k) = *(random_sequence + k);
            ((subvectors + i*repetitions + j)->top)++;
        }
        //cout << (subvectors + i*repetitions + j)->capacity << " " << (subvectors + i*repetitions + j)->top << endl;
    }
}
cout << endl << "prepared" << endl;
fout.open(file_name, std::ios_base::app);
int start_ind = 0;
int ind_for_sort_mas = 0;
///*
for (long long int num_els = start_n; num_els < n; num_els+=delta_n)
{
    ind_for_sort_mas += 1;
    for (int epoch = 0; epoch < epochs; epoch++){

        auto start = get_time();
        for(int i = 0; i<repetitions; i++){
            sort_func(subvectors + start_ind + i);
        }
        auto finish = get_time();
        sort_mas[ind_for_sort_mas] += (finish - start);
        start_ind += repetitions;
        //for(int i = 0; i<repetitions-1; i++){
        //    cout << (subvectors[start_ind + i].mas)[0];
        //}
        cout << endl;

    }

    fout << std::fixed << std::setprecision(40) << num_els << "," << 1.0f* sort_mas[ind_for_sort_mas]/epochs / repetitions << endl;
}
fout.close();

//------------------------------------------*/
}

void apply_2(void (* sort_func)(int*, int ), const char *file_name){

int start_n = 2;
long long int n = 102;
int delta_n = 10;
int cell_num = n/delta_n;

int epochs = 1;
int repetitions = 2000000;

int* random_sequence = new int[n];

for(int i = 0; i < n; i++){
    *(random_sequence + i) = rand_uns(-1000, 1000);
}

cout << "random ready" << endl;
float *sort_mas = new float[cell_num];


subvector* subvectors = new subvector[repetitions*cell_num];

std::ofstream fout;
///* _sort------------------------------------------
clear_file(file_name);


for (int i = 0; i < cell_num; i++){
    sort_mas[i] = 0;
}

subvector sv;
init(&sv);
resize(&sv, 10);
fullfull_vector(&sv, random_sequence, 10);
for(int i = 0; i < 10; i++){
    cout << *(sv.mas + i) << " ";
}
sort_func(sv.mas, sv.top);
cout << endl;
for(int i = 0; i < 10; i++){
    cout << *(sv.mas + i) << " ";
}

for (int i = 0; i<(n-start_n)/delta_n; i++){
    for (int j = 0; j < repetitions; j++){
        init(&(*(subvectors + i*repetitions + j)));
        //resize(&(*(subvectors + i*repetitions + j)), start_n+i*delta_n);

        int *new_mas = new int[start_n+i*delta_n];

        (subvectors + i*repetitions + j)->mas = new int[start_n+i*delta_n];
        (subvectors + i*repetitions + j)->capacity = start_n+i*delta_n;
        (subvectors + i*repetitions + j)->top = 0;

        for (int k = 0; k < start_n+i*delta_n; k++)
        {

            //push_back(&(*(subvectors + i*repetitions + j)), *(random_sequence + k));
            *((subvectors + i*repetitions + j)->mas + k) = *(random_sequence + k);
            ((subvectors + i*repetitions + j)->top)++;
        }
        //cout << (subvectors + i*repetitions + j)->capacity << " " << (subvectors + i*repetitions + j)->top << endl;
    }
}
cout << endl << "prepared" << endl;
fout.open(file_name, std::ios_base::app);
int start_ind = 0;
int ind_for_sort_mas = 0;
///*
for (long long int num_els = start_n; num_els < n; num_els+=delta_n)
{
    ind_for_sort_mas += 1;
    for (int epoch = 0; epoch < epochs; epoch++){

        auto start = get_time();
        for(int i = 0; i<repetitions; i++){
            sort_func(subvectors[start_ind + i].mas, subvectors[start_ind + i].top);
        }
        auto finish = get_time();
        sort_mas[ind_for_sort_mas] += (finish - start);
        start_ind += repetitions;
        //for(int i = 0; i<repetitions; i++){
        //    cout << (subvectors[start_ind + i].mas)[0];
        //}
        cout << endl;


    }

    fout << std::fixed << std::setprecision(40) << num_els << "," << 1.0f* sort_mas[ind_for_sort_mas]/epochs / repetitions << endl;
}
fout.close();

//------------------------------------------*/
}

void apply_3(void (* sort_func)(int*, int, int ), const char *file_name){
int start_n = 2;
long long int n = 102;
int delta_n = 10;
int cell_num = n/delta_n;

int epochs = 1;
int repetitions = 1000000;

int* random_sequence = new int[n];

for(int i = 0; i < n; i++){
    *(random_sequence + i) = rand_uns(-1000, 1000);
}

cout << "random ready" << endl;
float *sort_mas = new float[cell_num];


subvector* subvectors = new subvector[repetitions*cell_num];

std::ofstream fout;
///* _sort------------------------------------------
clear_file(file_name);


for (int i = 0; i < cell_num; i++){
    sort_mas[i] = 0;
}

subvector sv;
init(&sv);
resize(&sv, 10);
fullfull_vector(&sv, random_sequence, 10);
for(int i = 0; i < 10; i++){
    cout << *(sv.mas + i) << " ";
}
sort_func(sv.mas, 0, sv.top-1);
cout << endl;
for(int i = 0; i < 10; i++){
    cout << *(sv.mas + i) << " ";
}

for (int i = 0; i<(n-start_n)/delta_n; i++){
    for (int j = 0; j < repetitions; j++){
        init(&(*(subvectors + i*repetitions + j)));
        //resize(&(*(subvectors + i*repetitions + j)), start_n+i*delta_n);


        (subvectors + i*repetitions + j)->mas = new int[start_n+i*delta_n];
        (subvectors + i*repetitions + j)->capacity = start_n+i*delta_n;
        (subvectors + i*repetitions + j)->top = 0;

        for (int k = 0; k < start_n+i*delta_n; k++)
        {

            //push_back(&(*(subvectors + i*repetitions + j)), *(random_sequence + k));
            *((subvectors + i*repetitions + j)->mas + k) = *(random_sequence + k);
            ((subvectors + i*repetitions + j)->top)++;
        }
        //cout << (subvectors + i*repetitions + j)->capacity << " " << (subvectors + i*repetitions + j)->top << endl;
    }
}
cout << endl << "prepared" << endl;

fout.open(file_name, std::ios_base::app);
int start_ind = 0;
int ind_for_sort_mas = 0;
///*
for (long long int num_els = start_n; num_els < n; num_els+=delta_n)
{

    ind_for_sort_mas += 1;
    for (int epoch = 0; epoch < epochs; epoch++){

        auto start = get_time();
        for(int i = 0; i<repetitions; i++){
            sort_func(subvectors[start_ind + i].mas, 0, subvectors[start_ind + i].top - 1);
        }
        auto finish = get_time();
        sort_mas[ind_for_sort_mas] += (finish - start);
        start_ind += repetitions;
        cout << "sorted x 50" << endl;

    }

    fout << std::fixed << std::setprecision(40) << num_els << "," << 1.0f* sort_mas[ind_for_sort_mas]/epochs / repetitions << endl;
}
fout.close();

//------------------------------------------*/
}

int main()

{
//apply(&bubble_sort, "bubble_sort_small.txt");
apply(&bubble_sort, "bubble_sort_whorst.txt");
apply(&insert_sort, "insert_sort_small.txt");
apply(&shaker_sort, "shaker_sort_small.txt");


apply_2(&qsortRecursive, "qsortRecursive_small.txt");
apply_2(&heapSort, "heapSort_small.txt");
apply_3(&mergeSort, "mergeSort_small.txt");


return 0;

}



//Функция для рандома (из профайлеров)


