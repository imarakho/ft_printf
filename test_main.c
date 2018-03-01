#include "ft_printf.h"

int     main()
{
    setlocale(P_ALL, "");
    printf("%d\n",printf("{%-13p}", &strlen));
   printf("%d\n", ft_printf("{%-13p}", &strlen));
    return (0);
}
