if (pr->space < ft_strlen(pr->s))
	{
		pr->wdth = 0;
		pr->res += ft_strlen(pr->s);
	}
	if(pr->md_sp &&
	 pr->val >= 0 && !pr->plus)
	{
		if(pr->pres)
		pr->res++;
		pr->space--;
		ft_putchar(' ');
	}
	if (pr->space < pr->pres)
		pr->wdth = 0;
	if (pr->pres == 0 && pr->val == 0)
	{
		if(!pr->space && !pr->alter)
			pr->res--;
	   pr->res += pr->space;
		free(pr->s);
		pr->s = "";
	}
	if (pr->pres > 1 && pr->pres > pr->space)
	{
		if(pr->pres > ft_strlen(pr->s))
			if(pr->space)
				pr->res -= pr->space;
		if(pr->space)
		{
			pr->res +=  pr->pres;
		}
	}
	if (!pr->minus)
	{
		if(pr->space > pr->pres && pr->pres > 1 && (pr->pres > ft_strlen(pr->s) || pr->val < 0)) 
		{
			pr->space -= pr->pres;
			pr->space += ft_strlen(pr->s);
			pr->res -= pr->pres;
			pr->res += ft_strlen(pr->s);
		}
		if (pr->plus && pr->val >= 0 && (pr->nll || 
		(pr->pres > ft_strlen(pr->s) && pr->pres > pr->space)))
		{
				pr->space--;
				ft_putchar('+');
		}
		if (pr->val < 0 && (pr->nll || pr->pres > 1))
		{
			pr->val *= -1;
			pr->s = ft_itoa_base(pr->val, 10);
			if(ft_strlen(pr->s) >= pr->space || ft_strlen(pr->s) >= pr->pres)
				pr->space--;
			else
			{
				pr->res++;
				pr->pres--;
			}
			ft_putchar('-');
		}
		if (pr->plus && pr->val >= 0 && !pr->nll)
			{
				if(pr->space < ft_strlen(pr->s))
				pr->res++;
				pr->space--;
			}
		make_width(pr , 'd');
		if (pr->plus && pr->val >= 0 && !pr->nll)
			ft_putchar('+');
			make_pres(pr, 'd');
			ft_putstr(pr->s);
			return ;
	}
	else
	{
		if(pr->space > pr->pres && pr->pres > 1)
			pr->space--;
		if(pr->plus && pr->val >= 0)
		{
			if(ft_strlen(pr->s) > pr->space || ft_strlen(pr->s) > pr->pres)
				pr->res++;
			else
				pr->space--;
			ft_putchar('+');
		}
			make_pres(pr, 'd');
			ft_putstr(pr->s);
		make_width(pr , 'd');
	}