/*This program shows an idea how "container_of" works*/
#include <stdio.h>
#include <stddef.h>

struct some_data{
    int a;
    char b;
    int c;
    char d;
};

struct some_data data;

#define container_of(ptr, type, member)    ( (type*)( (long)ptr - offsetof(type,member) ) )

void get_container(char *ptr){
  #if 0  //use ptr to get container adress
    long offset;

    offset = (int) ( &((struct some_data*)0)->b );
    struct some_data *data1 = (struct some_data*)(ptr - offset);
    #endif
}

int main()
{
    data.a = 10;
    data.b = 3;
    data.c = 'a';
    data.d = 100;
    /*instead of "a" we can write b,c or d*/
    struct some_data *data1 = container_of(&data.a, struct some_data, a);
    
    printf("a = %d\n", data.a);
    printf("b = %d\n", data.b);
    printf("c = %c\n", data.c);
    printf("d = %d\n", data.d);

    return 0;
}
