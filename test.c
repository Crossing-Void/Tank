#include <stdio.h>

int main(void) {
  FILE* pFile;
  char name[20];
  double x, y, z, a, b, c, d;
   pFile = fopen("profile.dat", "r");
fscanf(pFile, "%s", name);
fscanf(pFile, "%f", &x);
// fscanf(pFile, "%f", y);
// fscanf(pFile, "%f",
//     z);
// fscanf(pFile, "%f", a);
// fscanf(pFile, "%f",
//     b);
// fscanf(pFile, "%f",
//     c);
// fscanf(pFile, "%f",
//     d);
fclose(pFile);
    printf("%s\n", name);
    printf("%f", x);
}
