#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*dest;

	len = ft_strlen(src) + 1;
	dest = (char *)malloc(sizeof(char) * len);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	while ((*s1 || *s2) && n--)
	{
		if (*s1++ != *s2++)
			return ((unsigned char)*--s1 - (unsigned char)*--s2);
	}
	return (0);
}

int	ft_is_redirect(char *s)
{
	if (ft_strncmp(s, ">>", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (1);
	return (0);
}

int	ft_find_count(char *s)
{
	int	i;
	int	flag;
	int	count;

	i = 0;
	flag = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && flag && s[i] == 34)
		{
			i++;
			while (s[i] && s[i] != 34)
				i++;
		}
		if (s[i] && flag && s[i] == 39)
		{
			i++;
			while (s[i] && s[i] != 39)
				i++;
		}
		if (ft_is_redirect(&s[i]))
				return (count);
		if (flag == 0 && s[i] != 34 && s[i] != 39 && s[i] != 32 && s[i])
		{
			flag = 1;
			count++;
		}
		if (s[i] == 32 && flag == 1)
			flag = 0;
		i++;
	}
	return (count);
}

int main()
{
	int	i;
	char	*tmp;

	tmp = ft_strdup("cat -e txt.file > 1 > 2 > 3 > 4 > 5 > 6");
	i = ft_find_count(tmp);
	printf("%d\n", i);
	free(tmp);
	return (0);
}
