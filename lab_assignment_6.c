#include <stdio.h>
#include <stdlib.h> 
#define _CRT_SECURE_NO_WARNINGS 

int search(int numbers[], int low, int high, int value) {
    if (low > high) {
        return -1; // value not found
    }

    int mid = (low + high) / 2;
    
    if (numbers[mid] == value) {
        return mid; // Found the value at middle index
    } else if (numbers[mid] > value) {
        return search(numbers, low, mid - 1, value); // Search left half
    } else {
        return search(numbers, mid + 1, high, value); // Search right half
    }
}

void printArray(int numbers[], int sz) {
    printf("Number array : ");
    for (int i = 0; i < sz; ++i) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

int main(void) {
    int numInputs;
    FILE* inFile;
    errno_t err = fopen_s(&inFile, "input.txt", "r");
    if (err != 0 || inFile == NULL) {
        printf("Failed to open file.\n");
        return 1; // return an error code
    }

    err = fscanf_s(inFile, "%d", &numInputs);
    if (err == EOF) {
        printf("Failed to read from file.\n");
        fclose(inFile);
        return 1; // return an error code
    }
    
    while (numInputs-- > 0) {
        int countOfNums;
        err = fscanf_s(inFile, "%d", &countOfNums);
        if (err == EOF) {
            printf("Failed to read from file.\n");
            fclose(inFile);
            return 1; // return an error code
        }
        
        int* numArray = (int*)malloc(countOfNums * sizeof(int));
        if (numArray == NULL) {
            printf("Memory allocation failed.\n");
            fclose(inFile);
            return 1; // return an error code
        }
        
        float average = 0;
        
        for (int i = 0; i < countOfNums; i++) {
            err = fscanf_s(inFile, "%d", &numArray[i]);
            if (err == EOF) {
                printf("Failed to read from file.\n");
                fclose(inFile);
                free(numArray);
                return 1; // return an error code
            }
            average += numArray[i];
        }

        printArray(numArray, countOfNums);
        int value = average / countOfNums;
        int index = search(numArray, 0, countOfNums - 1, value);
        
        if (index >= 0) {
            printf("Item %d exists in the number array at index %d!\n", value, index);
        } else {
            printf("Item %d does not exist in the number array!\n", value);
        }

        free(numArray);
    }

    fclose(inFile);
    return 0;
}
