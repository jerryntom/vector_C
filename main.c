#include <stdio.h>
#include "vector.h"

int main(void) {
    int vector_size, res, choice, num, character;
    struct vector_t *vector;
    printf("Please input vector size:");

    if(scanf("%d", &vector_size) != 1) {
        printf("Incorrect input");
        return 1;
    }
    else if(vector_size <= 0) {
        printf("Incorrect input data");
        return 2;
    }

    res = vector_create_struct(&vector, vector_size);
    if(res == 2) {
        printf("Failed to allocate memory");
        return 8;
    }

    while(1) {
        printf("Please input choice:");
        while((character = getchar()) && character != '\n' && character != EOF);
        if(scanf("%d", &choice) != 1) {
            vector_destroy_struct(&vector);
            printf("Incorrect input");
            return 1;
        }

        if(choice == 0) {
            vector_destroy_struct(&vector);
            return 0;
        }
        else if(choice == 1) {
            printf("Please input numbers to add:");
            while(1) {
                if(scanf("%d", &num) != 1) {
                    vector_destroy_struct(&vector);
                    printf("Incorrect input");
                    return 1;
                }
                if(num == 0) break;
                else {
                    res = vector_push_back(vector, num);
                    if(res == 2) {
                        printf("Failed to allocate memory\n");
                        break;
                    }
                }
            }
            if(vector->size == 0) printf("Buffer is empty\n");
            else {
                vector_display(vector);
                printf("\n");
            }
        }
        else if(choice == 2) {
            printf("Please input numbers to remove:");
            while(1) {
                if(scanf("%d", &num) != 1) {
                    vector_destroy_struct(&vector);
                    printf("Incorrect input");
                    return 1;
                }
                if(num == 0) break;
                else vector_erase(vector, num);
            }
            if(vector->size == 0) printf("Buffer is empty\n");
            else {
                vector_display(vector);
                printf("\n");
            }
        }
        else printf("Incorrect input data\n");
    }
}
