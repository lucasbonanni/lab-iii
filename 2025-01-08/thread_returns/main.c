/*
In this file we will see how to return a value from a thread.
One example is to return the sum of the elements of an array.
Second example is to return an structure of a person.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

typedef struct {
    char name[20];
    int age;
} Person;

int sum = 0;
Person person;

void *sum_array(void *arg) {
    int *array = (int *)arg;
    int i;
    for (i = 0; i < SIZE; i++) {
        sum += array[i];
    }
    pthread_exit(&sum);
}

void *get_person(void *arg) {
    person.age = 25;
    sprintf(person.name, "John Doe");
    pthread_exit(&person);
}

int main() {
    int array[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    pthread_t thread1, thread2;
    int *result;
    Person *p;

    pthread_create(&thread1, NULL, sum_array, (void *)array);
    pthread_create(&thread2, NULL, get_person, NULL);

    pthread_join(thread1, (void **)&result);
    pthread_join(thread2, (void **)&p);

    printf("Sum of the array: %d\n", *result);
    printf("Person: %s, %d\n", p->name, p->age);

    return 0;
}
