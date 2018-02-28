#include "ft_printf.h"

int     main()
{
    setlocale(P_ALL, "");
   printf("%d\n",printf("%lx, %lx", 0, ULONG_MAX));
   printf("%d\n", ft_printf("%lx, %lx", 0, ULONG_MAX));
    return (0);
}
