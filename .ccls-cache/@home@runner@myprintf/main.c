#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

char *int_to_str(unsigned int num, int base) 
{
    char diff_dec[] = "0123456789ABCDEF";
    char buff[50];
    char* point;
    point = &buff[49];
    *point = '\0';

    do
    {
        *--point = diff_dec[num%base];
        num /= base;
    } while (num != 0);

    return(point);
}

int my_printf(char* input, ...) 
{
    va_list arg;
    va_start (arg, input);

    char* value;
    signed int i;
    char* s;
    long ptr;
    char c[0];

    for(value = input; *value; value++)
    {
        if(*value != '\0') 
        {
            if(*value != '%') 
            {
                write(1, value, 1);
                continue;
                //break;
            }
            switch(*++value)
            {
                case 'c': 
                    i = va_arg(arg, int); //Handle Character
                    c[0]= i;
                    write(1, c, 1);
                    break;
                case 'd': 
                    i = va_arg(arg,int); //handle decimal
                    if(i < 0) 
                    {
                        i = -i;
                        write(1, "-", 1);
                    }    
                    char* d_l = int_to_str(i,10); //base 10 here
                    write(1, d_l, (strlen(d_l) +1));
                    break;
                case 'o':
                    i = va_arg(arg,unsigned int);
                    char* o_l = int_to_str(i,8); //base 8 here
                    write(1, o_l, (strlen(o_l)+1));
                    break;
                case 's':
                    s = va_arg(arg,char *); //handle string
                    if(s == NULL)
                    {
                        char* null = "(null)";
                        write(1, null, (strlen(null)));
                    }
                    else
                    {
                    write(1, s, (strlen(s)));
                    }
                    write(1, " ", 1);
                    break;
                case 'x':
                    i = va_arg(arg,unsigned int);
                    char* x_l = int_to_str(i,16); //base 16 here
                    write(1, x_l, (strlen(x_l)+1));
                    break;
                case 'p':
                    ptr = va_arg(arg, long);
                    intptr_t num = (intptr_t)ptr;
                    char buff[18];
                    int buffer_to_fill = sizeof(buff) - 2; // Size_buffer_to_fill: 16
                    buff[0] = '0';
                    buff[1] = 'x';
                    for (int index = 0; index < buffer_to_fill; index++)
                        buff[index + 2] = "0123456789abcdef"[(num >> ((buffer_to_fill - 5 - index) * 4)) & 0xf]; // Shift 5 digits to offset for leading zeros in original address
                    write(1, buff, sizeof(buff) - 4);
                    break;
            }
        }
    }
    va_end(arg);
    return 0;
}

int main()
{
    // my_printf("Hello world!\n");
    // my_printf("%c!\n", 'H');
    // my_printf("%c-%c-%c-%c-%c!\n", 'H', 'e', 'l', 'l', 'o');
    // my_printf("Testing %s!\n", "Single_string");
    // my_printf("Testo el %s %s!\n", "Double", "String");
    // my_printf("Should print NULL -  %s!\n", (char *)NULL); 
    // my_printf("testing d - %d!\n", 1337);
    // my_printf("testing multiple ds - %d - %d-%d!\n", 2048, 0, -1337);
    // my_printf("testing o -%o!\n", 100);
    // my_printf("testing x - %x!\n", 10);
  int var;  
  int any_variable = 1;
    my_printf("%p\n", &var); 
    my_printf("Hello world!\n");
    my_printf("%c!\n", 'H');
    my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o');
    my_printf("Hello %s!\n", "QWASAR.IO");
    my_printf("Hello %s %s!\n", "Mr", "Gaetan");
    my_printf("NULL STRING %s!\n", (char*)NULL);
    my_printf("%d!\n", 1337);
    my_printf("%d - %d - %d!\n", 2048, 0, -1337);
    my_printf("%o!\n", 100);
    my_printf("%u!\n", 1337);
    my_printf("%x!\n", 14);
    my_printf("%p!\n", any_variable);


    return 0;
}