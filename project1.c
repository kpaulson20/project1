#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int A[], int n);
void countSort(int A[], int n);
void printArray(int A[], int n);
void generateInFile(int n);

int main()
{
    int *A1, *A2;
    int n;
    double time_spent1, time_spent2;
    clock_t start1, end1, start2, end2;
    //1. Call generateInFile function to generate integer random numbers and store them in a text file
    generateInFile(10000000);
    FILE* in;
    in = fopen("A1.txt", "r");
    fscanf(in, "%d", &n);
    printf("%d\n", n);
    
    //2. Copy the numbers from the file to an array A1 and another array A2 (A1=A2). Use dynamic allocation to declare A1 and A2
    A1 = (int*)malloc(n * sizeof(int));
    A2 = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) 
    {
        fscanf(in, "%d", &A1[i]);
        A2[i] = A1[i];
    }

    //3. Define two variables start1 and end1 of type clock_t.

    
    //4. Keep the following code to measure the running time of the selection sort algorithm.
    start1 = clock();
    selectionSort(A1, n);
    end1 = clock();
    time_spent1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("Time taken by selectionSort algorithm is %f sec.\n", time_spent1);

    //5. repeat steps 3. and 4. to measure the running time of the counting sort algorithm
    start2 = clock();
    countSort(A2, n);
    end2 = clock();
    time_spent2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("Time taken by countSort algorithm is %f sec. \n", time_spent2);
    return 0;
}
//selection sort function
void selectionSort(int A[], int n) // n is the size of A
{
    //Implement selection sort algorithm here
    int i, j, low, temp;
    for (i = 0; i < n-2; i++)
    {
        low = i;
        for (j = i +1; j < n-1; j++)
        {
            if (A[j] < A[low])
                low = j;
            if (low != i) {
                temp = A[i];
                A[i] = A[low];
                A[low] = temp;
            }
        }
    }
}

//counting sort function
void countSort(int A[], int n) // n is the size of A
{
    int i, j, temp, min, * B, * C, k = A[0];
    B = (int*)malloc(n * sizeof(int));

    for (i = 1; i < n; i++)
        if (A[i] > k)
            k = A[i];
    C = (int*)malloc((k + 1) * sizeof(int));

    for (i = 0; i <= k; i++)
        C[i] = 0;
    for (i = 0; i < n; i++)
        C[A[i]] = C[A[i]] + 1;
    for (i = 1; i <= k; i++)
        C[i] = C[i] + C[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        B[C[A[i]] - 1] = A[i];
        C[A[i]] = C[A[i]] - 1;
    }
    for (i = 0; i < n; i++)
        A[i] = B[i];
}

//Function to print the content of an array
void printArray(int A[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

 //Function to generate n random integer numbers in the range 0 to RAND_MAX = 32767
 void generateInFile(int n)
 {
    int x;
    FILE *out;
    out = fopen("A1.txt", "r+");
    fprintf(out, "%d\n", n);
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        x = rand();
        fprintf(out, "%d ", x);
    }
    fclose(out);
 }
