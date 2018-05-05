//
// Created by boczolaf on 09.03.18.
//

int **Array2D(int n_rows, int n_columns)
{
    int *tab = new int[n_rows];
    for(int i=0;i<n_rows;i++)
    {
        tab[i]= new int[n_columns];
    }
    for(int j=1;j<=n_rows*n_columns)
    {
        (tab+j)=j;
    }
}


void DeleteArray2D(int **array, int n_rows, int n_columns);
{

}