/*
  ALUNO: MARCOS MARTINS
  DISCILINA: PPA
  schedule = static com chunk 10
*/

#include <complex>
#include <iostream>
#include <omp.h>

using namespace std;

int
main()

{

  int max_row, max_column, max_n;
  cin >> max_row;
  cin >> max_column;
  cin >> max_n;

  int r;
  int c;
  int i;
  double start;
  double end;
  int chunk = 10;


  char** mat = (char**)malloc(sizeof(char*) * max_row);

    for (int i = 0; i < max_row; i++)
      mat[i] = (char*)malloc(sizeof(char) * max_column);

  // Pega o tempo inicial antes de abrir o bloco
  start = omp_get_wtime();

#pragma omp parallel private(r, c, i) shared(max_row, max_column, max_n, mat)
  {
    
    #pragma omp for schedule(static, chunk)
    for (int r = 0; r < max_row; ++r) {

      for (int c = 0; c < max_column; ++c) {
        complex<float> z;
        int n = 0;
        while (abs(z) < 2 && ++n < max_n)
          z = pow(z, 2) + decltype(z)((float)c * 2 / max_column - 1.5,
                                      (float)r * 2 / max_row - 1);
        mat[r][c] = (n == max_n ? '#' : '.');
      }
    }

  }

  // Pega o tempo final depois de paralelizar o bloco
  end = omp_get_wtime();

  printf("%f\n", end - start);
}
