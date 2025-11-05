#include <stdio.h>

#define MAX_OF_TYPE_UNSIGNED(type) ((type)~(type)0) 
#define MIN_OF_TYPE_UNSIGNED(type) ((type)~((type)~(type)0)) 

#define MAX_OF_TYPE_SIGNED(s_type, u_type) ((s_type)(((u_type)~(u_type)0) >> 1)) 
#define MIN_OF_TYPE_SIGNED(s_type, u_type) ((s_type)(-MAX_OF_TYPE_SIGNED(s_type, u_type) - 1))

#define is_inf_f(x) ((x != 0.0f) && (x * 2.0f == x))
#define is_inf_d(x) ((x != 0.0) && (x * 2.0 == x))
#define is_inf_ld(x) ((x != 0.0L) && (x * 2.0L == x))

float float_max()
{
    float x = 1.0f, previous = x;
    for (;;)
    {
        float next = x * 2.0f;
        if (x == next)
        {
            x = previous; //выход
            break;
        }
        previous = x;
        x = next;
    }
    float dx = x;
    while (dx > 0.0f)
    {
        float next = x + dx;

        if (!is_inf_f(next) && next > x)
        {
            x = next;
        }

        dx *= 0.5f;
    }
    return x;
}

double double_max()
{
    double x = 1.0, previous = x;
    for (;;)
    {
        double next = x * 2.0;
        if (x == next)
        {
            x = previous; //выход
            break;
        }
        previous = x;
        x = next;
    }
    double dx = x;
    while (dx > 0.0)
    {
        double next = x + dx;

        if (!is_inf_d(next) && next > x)
        {
            x = next;
        }

        dx *= 0.5;

    }
    return x;
}

long double long_double_max()
{
    long double x = 1.0L, previous = x;
    for (;;)
    {
        long double next = x * 2.0L;
        if (x == next)
        {
            x = previous; //выход
            break;
        }
        previous = x;
        x = next;
    }
    long double dx = x;
    while (dx > 0.0L)
    {
        long double next = x + dx;

        if (!is_inf_ld(next) && next > x)
        {
            x = next;
        }

        dx *= 0.5;
    }
    return x;
}

int main()
{
    //signed char
    printf("char_max=%d\n", MAX_OF_TYPE_SIGNED(signed char, unsigned char)); // ((signed char))(((unsigned char)~(unsigned char)0) >> 1)) 
    printf("char_min=%d\n", MIN_OF_TYPE_SIGNED(signed char, unsigned char));

    //unsigned char
    printf("uchar_max=%u\n", MAX_OF_TYPE_UNSIGNED(unsigned char));
    printf("uchar_min=%u\n", MIN_OF_TYPE_UNSIGNED(unsigned char));

    //signed short
    printf("short_max=%hd\n", MAX_OF_TYPE_SIGNED(signed short, unsigned short));
    printf("short_min=%hd\n", MIN_OF_TYPE_SIGNED(signed short, unsigned short));

    //unsigned short
    printf("ushort_max=%hu\n", MAX_OF_TYPE_UNSIGNED(unsigned short));
    printf("ushort_min=%hu\n", MIN_OF_TYPE_UNSIGNED(unsigned short));

    //signed int
    printf("int_max=%d\n", MAX_OF_TYPE_SIGNED(signed int, unsigned int));
    printf("int_min=%d\n", MIN_OF_TYPE_SIGNED(signed int, unsigned int));

    //unsigned int
    printf("uint_max=%u\n", MAX_OF_TYPE_UNSIGNED(unsigned int));
    printf("uint_min=%u\n", MIN_OF_TYPE_UNSIGNED(unsigned int));

    //signed long
    printf("long_max=%ld\n", MAX_OF_TYPE_SIGNED(signed long, unsigned long));
    printf("long_min=%ld\n", MIN_OF_TYPE_SIGNED(signed long, unsigned long));

    //unsigned long
    printf("ulong_max=%lu\n", MAX_OF_TYPE_UNSIGNED(unsigned long));
    printf("ulong_min=%lu\n", MIN_OF_TYPE_UNSIGNED(unsigned long));

    //signed long long
    printf("long_long_max=%lld\n", MAX_OF_TYPE_SIGNED(signed long long, unsigned long long));
    printf("long_long_min=%lld\n", MIN_OF_TYPE_SIGNED(signed long long, unsigned long long));

    //unsigned long long
    printf("ulong_long_max=%llu\n", MAX_OF_TYPE_UNSIGNED(unsigned long long));
    printf("ulong_long_min=%llu\n", MIN_OF_TYPE_UNSIGNED(unsigned long long));

    //float
    printf("float_max=%e\n", float_max());
    printf("float_min=%e\n", -float_max());
    
    //double
    printf("double_max=%e\n", double_max());
    printf("double_min=%e\n", -double_max());

    //long double
    printf("long_double_max=%Le\n", long_double_max());
    printf("long_double_min=%Le\n", -long_double_max());

    return 0;
}
// hhu , препроцессор , доп код и как он влияет на дисбаланс signed.