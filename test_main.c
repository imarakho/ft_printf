#include "ft_printf.h"

int     main()
{
    setlocale(P_ALL, "");
   printf("%d\n",printf("% 4.5i\n", 42));
   printf("%d\n", ft_printf("% 4.5i\n", 42));
    return (0);
}
