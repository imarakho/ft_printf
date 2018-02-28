#include "ft_printf.h"

int     main()
{
    setlocale(P_ALL, "");
   printf("%llx, %llx\n", 0, ULLONG_MAX);
   ft_printf("%llx, %llx\n", 0, ULLONG_MAX);
    return (0);
}
