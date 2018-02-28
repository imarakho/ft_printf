#include "ft_printf.h"

int     main()
{
    setlocale(P_ALL, "");
   printf("%d\n",printf("%-5.3s", "LYDI"));
   printf("%d\n", ft_printf("%-5.3s", "LYDI"));
    return (0);
}
