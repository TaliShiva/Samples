#include <stdio.h>

void Demo(int (*_printf) (const char *,...))
{
    _printf("Hello, OSIX!n");
    return;
}

int main(int argc, char* argv[])
{
    char buff[1000];
    int (*_printf) (const char *,...);
    int (*_main) (int, char **);
    void (*_Demo) (int (*) (const char *,...));

    _printf=printf;
    int func_len = (unsigned int) _main (unsigned int) _Demo;

    for (int a=0; a<func_len; a++)
        buff[a] = ((char *) _Demo)[a];
    _Demo = (void (*) (int (*) (const char *,...))) &buff[0];
    _Demo(_printf);
    return 0;
}
