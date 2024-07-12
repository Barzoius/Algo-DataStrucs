#include <iostream>
#include <vector>

//DOESNT WORK YET

//Is to note that each operation is standardized 
//in order to ensure a correct final solution
//While this algorithm may not perform the 
//minimum possible number of steps it will still arrive 
//at the reduced echelon form(REF) 

typedef std::vector<std::vector<double>> Matrix;

std::vector<double> GAUSS_JORDAN_METHOD(Matrix A, std::vector<double> a)
{
    int n = a.size();
    Matrix Aa(n, std::vector<double>(n + 1));

    //Creates the AGUMENT MATRIX
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            Aa[i][j] = A[i][j];
        }
        Aa[i][n] = a[i];
    }

    //From here we will perform the 3 possible row operations
    for(int i = 0; i < n; i++)
    {
        //(1) PARTIAL PIVOTING
        //Find the pivot
        int pivot = i;
        for(int j = i + 1; j < n; j++)
        {
            if(abs(Aa[j][i] > abs(Aa[pivot][i])))
            {
                pivot = j;
            }
        }
        //This swaps the pivot row with the current row
        if(pivot != i) { swap(Aa[i], Aa[pivot]); }
        
        //(2)ROW SCALE
        //We want the pivot element to be equal to 1
        //We do this by dividing the pivot with itself
        double Pivot = Aa[i][i];
        for(int j = i; j <= n; j++)
        {
            Aa[i][j] /= Pivot;
        }
        
        //(3)ROW ADDITION
        //This will eliminate the numbers under the pivot
        for(int j = 0; j < n; j++)
        {
            if(j != i)
            {
                double F = Aa[j][i];
                for(int k = i; k <= n; k++)
                {
                    Aa[j][k] -= F * Aa[i][k];
                }
            }

        }
    }
    std::vector<double> x(n);
    for(int i = 0; i < n; i++)
    {
        x[i] = Aa[i][n];
    }
    return x;
}
