#include <stdlib.h>
#include<unistd.h>
#include <stdio.h>
#include <fcntl.h>
int ft_strlen(char *s)
{
	int n = 0;
	while(*s++)
		n++;
	return (n);
}

char *ft_strchr(char *s, char c)
{
	while(*s)
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
	char *ptr;
	ptr = malloc(ft_strlen(s1)+ft_strlen(s2)+1);
	while(*s1)
		ptr[i++] = *s1++;
	while(*s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
		
}

char *ft_strcpy(char *s, char *str)
{
	int i = 0;
	while(*str)
	{
		s[i] = *str++;
		i++;
	}
	s[i] = '\0';
	return (s);
}

char *ft_calloc(int len)
{
	char *ptr=malloc(len);
	int i = 0;
	while(len--)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char *resize(char *line)
{
	char *buf;
	int i = 0;

	while(line[i] != '\n' && line[i])
		i++;
	line[i] = '\0';
	buf = ft_calloc(i+1);
	buf = ft_strcpy(buf, line);
	free(line);
	return (buf);
}
int get_next_line(char **line)
{
	static char *stock = NULL;
	int n;
	char *buf;
  	 char 	*tmp;
	
   *line = ft_calloc(1);
   if (stock)
   {
	   tmp =  *line;
	   *line = ft_strjoin(stock, *line);
	   free(tmp);
   }
   while(!(tmp = ft_strchr(*line, '\n')))
 	{
		buf = ft_calloc(1024 + 1);
		if (!(n = read(0, buf, 1024)))
		{
			free(buf);
			return (0);
		}
		if (n == -1)
		{
			free(buf);
			free(*line);
			return(-1);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
   stock = ft_calloc(ft_strlen(tmp + 1) + 1);
   stock = ft_strcpy(stock, tmp + 1);
   *line = resize(*line);
   return (1);


}

