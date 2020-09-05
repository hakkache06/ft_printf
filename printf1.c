#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
typedef struct s_print
{
    int prc;
    int prc_nb;
    int wdt;
    char conv;
}   t_print;

int ft_strlen (char *s)
{
    int n = 0;
    while (*s++)
        n++;
    return(n);
}

char	*ft_strchr(char *s, char c)
{
    while (*s)
    {
        if (*s == c)
            return (s);
        s++;
    }
    return (0);
}

char *ft_strjoin(char *s1, char *s2)
{
    int i = 0;
    char *str=malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    while (*s1)
        str[i++] = *s1++;
     while (*s2)
        str[i++] = *s2++;
    str[i] = '\0';
    return (str);
}

char *ft_substr(char *str, int len)
{
    char *ptr = malloc(len + 1);
    int i = 0;
    while (len--)
    {
        ptr[i] = str[i];
        i++;
    }
    ptr[i] = '\0';
    return (ptr);
}

int ft_itoa(int n)
{
    int i =0;
    if (n == 0)
        return (1);
     while (n)
     {
        n = n/10;
        i++;
     }
     return (i);
}

int ft_atoi(const char *str)
{
    long	integer = 0;
	int		i = 0;
	int		sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		integer = integer * 10 + str[i] - '0';
		i++;
	}
	return (integer * sign);
}

char *convert(int num, int base, char v)
{
    long m = num;
    char *rep = malloc(17);
    rep = "0123456789abcdef";
    if (v == 'x' || v == 'X')
    {
        m = (unsigned int)num;
        if (v == 'X')
           rep = "0123456789ABCDEF";
    }
    if (num < 0 && v == 'd')
        m = -m;
    static char buffer[50];
    char *ptr = &buffer[49];
    *ptr = '\0';
    *--ptr = rep[m % base];
    m = m / base;
    while (m)
    {
         *--ptr = rep[m % base];
        m = m / base;
    }
    if (num < 0 && v == 'd')
        *--ptr = '-';
    return (ptr);
}

char *string_create(t_print *st, va_list ap)
{
    char *str;
    if (st->conv == 'd')
        str = convert((int)va_arg(ap, int), 10, st->conv);
    else if (st->conv == 'x' || st->conv == 'X')
        str = convert((int)va_arg(ap, int), 16, st->conv);
    else if (st->conv == 's')
    {
        str = (char *)va_arg(ap, char *);
        if (!str)
            str = "(null)";
    }
    return (str);
}

char *trait(t_print *st, va_list ap)
{
    int len;
    int nzero = 0;
    int sign = 1;
    int nspace;
    char *str = string_create(st, ap);

    if (ft_atoi(str) < 0)
    {
        str = str + 1;
        sign = -1;
        nzero = nzero + 1;
    }
    if (st->conv == 's' && st->prc)
    {
        len = (st->prc_nb < ft_strlen(str)) ? st->prc_nb : ft_strlen(str);
        str = ft_substr(str, len);
    }
    else if (st->prc && !st->prc_nb && !ft_atoi(str))
         str = ft_substr(str, 0);
    else
        nzero = (st->prc_nb < ft_strlen(str)) ? 0 : st->prc_nb - ft_strlen(str);
    while (nzero--)
        str = ft_strjoin("0", str);
    str = (sign == -1) ? ft_strjoin("-", str) : str;
    nspace = (st->wdt && st->wdt > ft_strlen(str)) ? st->wdt - ft_strlen(str) : 0;
     while (nspace--)
        str = ft_strjoin(" ", str);
    return (str);    
}

void  print_str(int *j, t_print *st, va_list ap, const char *fr)
{
    char *str;
    str = trait(st, ap);
    write (1, str, ft_strlen (str));
    *j = *j + ft_strlen (str);
}

t_print ft_check_flag(const char **fr, va_list ap)
{
     t_print st;
     st.conv = '\0';
     st.prc = 0;
     st.prc_nb = 0;
     st.wdt = 0;
     while (**fr)
     {
         if (**fr == '.')
        {
            st.prc = 1;
            (*fr)++;
            st.prc_nb = ft_atoi(*fr);
            (*fr) = (*fr) + ft_itoa(st.prc_nb);
        }
        else if (ft_atoi(*fr))
        {
            st.wdt = ft_atoi(*fr);
            (*fr) = (*fr) + ft_itoa(st.wdt);
        }
        if (ft_strchr("sdxX",**fr))
        {
            st.conv = **fr;
            (*fr)++;
            break ;
        }
     }
     return (st);
}

int reception(const char *fr, va_list ap)
{
    int j;
    t_print st;
    while (*fr)
    {
        if (*fr == '%')
        {
            fr++;
            st = ft_check_flag(&fr, ap);
            print_str(&j, &st, ap, fr);
        }
        else
        {
            write (1, fr, 1);
            j++;
            fr++;
        }
    }
    return (j);
}

int ft_printf(const char *fr, ...)
{
    int res;
    va_list ap;
    va_start(ap, fr);
    res = reception(fr, ap);
    va_end(ap);
    return (res);
}

int main()
{
	ft_printf("souad %s %d %5.2d\n", "souad", 5, -9);
    printf("souad %s %d %5.2d\n", "souad", 5, -9);
}
