#include <locale.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>

#define MAXW 310000
#define MAXN 124

void struper(wchar_t *str)
{
    for (wchar_t *p = str; *p; ++p)
        *p = towupper(*p);
}

int compare(const void* a, const void* b)
{
    return wcscmp((const wchar_t *) a, (const wchar_t *) b);
}

wchar_t words[MAXW][MAXN];

int main(int argc, char *argv[]) {

  setlocale(LC_ALL, "pt_BR.utf8"); 

  char filename[4096];

  if (argc < 2) 
  {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    return -1;
  }

  strcpy(filename, argv[1]);

  FILE *fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
    return -1;
  }
    int k = 0;

    while (fscanf(fp, "%ls", words[k]) > 0)
    {
        wchar_t *p = wcschr(words[k], '/');
        
        if (p != NULL)
            *p = 0;

        struper(words[k]);
        ++k;
    }
    
  printf("k = %d\n", k);
  fclose(fp);
 
  int total = 0 , i;

    for (i = 0; i < MAXW; ++i)
    {
        int N = wcslen(words[i]);
        if (N < 4)
            continue;

        for (int j = 2; j <= N - 2; ++j)
        {
            wchar_t prefix[MAXN];
            memset(prefix, 0, sizeof(prefix));

            wcsncpy(prefix, words[i], j);

            int count = 0;
            wchar_t *p = bsearch(prefix, words, k, sizeof(wchar_t)*MAXN, compare);

            if (p){
              
                ++count;
            }

            p = bsearch(words[i] + j, words, k, sizeof(wchar_t)*MAXN, compare);
            if (p)
            {
                ++count;
            }
      
            if (count == 2)
            {
                printf("%ls: ", words[i]);
                printf("%ls + ", prefix);
                printf("%ls\n", words[i] + j);
                total++;
            }
        }
    }

  printf("Count: %d\n", total);
  
  return 0; 
}