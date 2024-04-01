#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cmp(const void * a, const void * b) {
    const char ** arg1 = (const char **)a;
    const char ** arg2 = (const char **)b;

    return strcmp(*arg1, *arg2);
}

void clearArr(char *** arr, int * n) {
    for (int i = 0; i < *n; i++) {
        (*arr)[i] = NULL;
    }
    *n = 0;
}

int cmprfx(char ** arg1, char ** arg2) {
    int i = 0;
    for (; i < (int)strlen(*arg1); i++) {
        if (*(*arg1 + i) != *(*arg2 + i)) {
            break;
        }
    }
    return i;
}

void rStr(char * src, char * dst, int n) {
    n--;

    for (int i = 0; i <= n; i++) {
        dst[n-i] = src[i];
    }
    dst[n + 1] = 0;
}

void stripN(char * line) {
    int n = strlen(line);
    line[n - 1] = 0;
}

void dealloc2d(char *** puzzle, long long int n) {
    for (int i = 0; i < n; i++) {
        free((*puzzle)[i]);
    }
    free(*puzzle);
}

void readInput(char *** puzzle, long int * width) {
    char * line = NULL;
    long int counter = 0, rows = 0;
    long unsigned int len = 0;

    rows = getline(&line, &len, stdin) - 1;
    if (rows <= 0) {
        printf("Invalid input.\n");
        free(line);
        exit(0);
    }
    stripN(line);

    *puzzle = (char **)malloc(sizeof(char **) * (rows));
    (*puzzle)[counter] = line;
    counter++;

    line = NULL;
    len = 0;

    while (getline(&line, &len, stdin) - 1 == rows && counter < rows) {
        stripN(line);
        (*puzzle)[counter] = line;
        counter++;

        line = NULL;
        len = 0;
    }

    if(!feof(stdin)) {
        printf("Invalid input.\n");
        dealloc2d(puzzle, counter);
        free(line);
        exit(0);
    }
    else if(counter != rows) {
        printf("Invalid input.\n");
        dealloc2d(puzzle, counter);
        free(line);
        exit(0);
    }
    *width = rows;
    free(line);
}

void memcheck(char *** arr, int * currSize, int * totSize) {
    if (*currSize >= *totSize) {
        *totSize *= 2;
        *arr = (char **)realloc(*arr, sizeof(char **) * *totSize);
    }
}

void arrcpy(char ** arr, char *** totarr, int n, int * counter, int * size) {
    for (int i = 0; i < n; i++) {
        if (strlen((*arr) + i) > 0) {
            memcheck(totarr, counter, size);
            (*totarr)[*counter] = (*arr) + i;
            (*counter)++;
        }
    }
}

int charcmp(const void * a, const void * b) {
    const char * arg1 = (const char *)a;
    const char * arg2 = (const char *)b;

    return strncmp(arg1, arg2, 1);
}

void checkletters(char *** puzzle, int width) {
    int i = 0, total = 0, size = width * width;
    char * all = (char *)malloc(sizeof(char) * size);
    char * result = (char *)malloc(sizeof(char) * size);
	
    for (; i < width; i++) {
        for (int j = 0; j < width; j++) {
            all[(i * width)+j] = (*puzzle)[j][i];
        }
    }

    qsort(all, size, sizeof(all[0]), charcmp);

    for (i = 0; i < size; i++) {
        if (i + 1 < size && (all[i] == all[i+1])) {
            result[total] = all[i];
            while (i + 1 < size && (all[i] == all[i+1])) {
                i++;
            }
            total++;
        }
    }

    if (total == 0) {
        printf("All words are unique.\n");
    }
    else {
        printf("Longest repeating words:\n");
        for (i = 0; i < total; i++) {
            printf("%c\n", result[i]);
        }
    }
    free(all);
    free(result);
}

int fdup(char *** arr, int n, char *** result, int * resultSize, int * max) {
    int counter = 0, i = 0, length = 0;
    for (; i < n; i++) {
        memcheck(result, &counter, resultSize);
        if (i + 1 < n) {
            length = cmprfx(&(*arr)[i], &(*arr)[i + 1]);
            if (length == *max) {
                if (counter - 1 < 0) {
                    (*result)[counter] = (*arr)[i];
                    counter++;
                }
                else if (strncmp((*arr)[i], (*result)[counter - 1], *max) != 0) {
                    (*result)[counter] = (*arr)[i];
                    counter++;
                }
            }
            else if (length > *max) {
                clearArr(result, &counter);
                counter = 0;
                *max = length;
                if (counter - 1 < 0) {
                    (*result)[counter] = (*arr)[i];
                    counter++;
                }
                else if (strncmp((*arr)[i], (*result)[counter - 1], n) != 0) {
                    (*result)[counter] = (*arr)[i];
                    counter++;
                }
            }
        }
    }

    return counter;
}

int main (void) {
    char ** puzzle;
    long int width = 0;

    printf("Puzzle:\n");
    readInput(&puzzle, &width);

    int hvconst = (width * width) + width;
    int dconst = ((width * width) + (2 * width - 1));

    char * harr1 = (char *)malloc(sizeof(char *) * hvconst);
    char * harr2 = (char *)malloc(sizeof(char *) * hvconst);
    char * varr1 = (char *)malloc(sizeof(char *) * hvconst);
    char * varr2 = (char *)malloc(sizeof(char *) * hvconst);
    char * ldarr1 = (char *)malloc(sizeof(char *) * dconst);
    char * ldarr2 = (char *)malloc(sizeof(char *) * dconst);
    char * rdarr1 = (char *)malloc(sizeof(char *) * dconst);
    char * rdarr2 = (char *)malloc(sizeof(char *) * dconst);
    
    int i = 0, j = 0, k = 0, counter = 0;
    for (i = 0; i < width; i++) {
        for (j = 0; j <= width; j++) {
            harr1[i*(width+1) + j] = puzzle[i][j];
        }
    }
    for (i = 0; i < width; i++) {
        for (j = 0; j <= width; j++) {
            if (j == width) {
                varr1[i*(width + 1) + j] = 0;
            }
            else {
                varr1[i*(width + 1) + j] = puzzle[j][i];
            }
        }
    }

    for (i = 0; i <= 2*(width - 1); i++) {
        for (j = width - 1; j >= 0; j--) {
            for (k = width - 1; k >= 0; k--) {
                if (j + k == i) {
                    ldarr1[counter] = puzzle[j][k];
                    counter++;
                }
            }
        }
        ldarr1[counter] = 0;
        counter++;
    }
/*---------This block of code does the other diagonal---------*/
    counter = 0;
    for(k = 0; k < width; k++) {
        j = k;
        i = 0;
        while ( j < width) {
            rdarr1[counter] = puzzle[i][j];
            j++;
            i++;
            counter++;
        }
        rdarr1[counter] = 0;
        counter++;
    }
    for(k = 1; k < width; k++) {
        i = k;
        j = 0;
        while ( i < width) {
            rdarr1[counter] = puzzle[i][j];
            j++;
            i++;
            counter++;
        }
        rdarr1[counter] = 0;
        counter++;
    }
/*---------ENDBLOCK---------*/
    counter = 0;
    rStr(harr1, harr2, hvconst - 1);
    rStr(varr1, varr2, hvconst - 1);
    rStr(rdarr1, rdarr2, dconst - 1);
    rStr(ldarr1, ldarr2, dconst - 1);
    int totSize = 1, resultSize = 1;
    char ** totarr = (char **)malloc(sizeof(char **) * totSize);
    char ** result = (char **)malloc(sizeof(char **) * resultSize);

    arrcpy(&rdarr1, &totarr, dconst, &counter, &totSize);
    arrcpy(&rdarr2, &totarr, dconst, &counter, &totSize);
    arrcpy(&ldarr1, &totarr, dconst, &counter, &totSize);
    arrcpy(&ldarr2, &totarr, dconst, &counter, &totSize);
    arrcpy(&harr1, &totarr, hvconst, &counter, &totSize);
    arrcpy(&harr2, &totarr, hvconst, &counter, &totSize);
    arrcpy(&varr1, &totarr, hvconst, &counter, &totSize);
    arrcpy(&varr2, &totarr, hvconst, &counter, &totSize);

    qsort(totarr, counter, sizeof(totarr[0]), cmp);
    int max = 2;
    
    int total = fdup(&totarr, counter, &result, &resultSize, &max);

    if (total != 0) {
        printf("Longest repeating words:\n");
        for (i = 0; i < total; i++) {
            printf("%.*s\n", max, result[i]);
        }
    }
    else {
        checkletters(&puzzle, width);
    }

    dealloc2d(&puzzle, width);
    free(result);
    free(harr1);
    free(varr1);
    free(rdarr1);
    free(ldarr1);
    free(harr2);
    free(varr2);
    free(rdarr2);
    free(ldarr2);
    free(totarr);
    return 0;
}