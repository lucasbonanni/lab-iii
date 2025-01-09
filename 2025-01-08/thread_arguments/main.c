/*
I want to write a example program of how to create threads in C and how to pass arguments to them. 
I will create a thread that will print the arguments passed to it and also the thread id.
*/

#include <stdio.h>
#include <pthread.h>

void *print_thread(void *arg) {
    int *thread_id = (int *)arg;
    printf("Thread id: %d\n", *thread_id);
    return NULL;
}

/*Another function that will be a new thread and receive an struct as argument */
struct thread_args {
    int thread_id;
    char thread_name[50];
};

void *print_struct(void *arg) {
    struct thread_args *args = (struct thread_args *)arg;
    printf("Thread id: %d\n", args->thread_id);
    printf("Thread name: %s\n", args->thread_name);
    return NULL;
}

/* A third function that prints a custom  struct called person with name, age and list of childs */
struct person {
    char name[50];
    int age;
    char childs[10][50];
};
void *print_person(void *arg) {
    struct person *p = (struct person *)arg;
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Childs: ");
    for (int i = 0; i < 10; i++) {
        if (p->childs[i][0] == '\0') {
            break;
        }
        printf("%s, ", p->childs[i]);
    }
    printf("\n");
    return NULL;
}

int main() {
    pthread_t thread;
    int thread_id = 1;
    struct thread_args args = {2, "Thread 2"};
    struct person p = {"John", 30, {"Alice", "Bob", "Charlie"}};
    pthread_create(&thread, NULL, print_thread, &thread_id);
    pthread_create(&thread, NULL, print_struct, &args);
    pthread_create(&thread, NULL, print_person, &p);
    pthread_join(thread, NULL);
    return 0;
}
