#include "libft.h"

static int	ft_word_count(char *s, char c)
{
	int count;
	int flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		if (flag == 0 && *s != 34 && *s != 39 && *s != c && *s)
		{
			flag = 1;
			count++;
		}
		if (*s && flag && *s == 34)
		{
			s++;
			count++;
			while (*s && *s != 34)
			{
				count++;
				s++;
			}
		}
		if (*s && flag && *s == 39)
		{
			s++;
			count++;
			while (*s && *s != 39)
			{
				count++;
				s++;
			}
		}
		if (*s == c && flag == 1)
			flag = 0;
		s++;
	}
	return (count);
}

static int	ft_len(char *s, char c)
{
	int len;

	len = 0;
	while (*s && *s != c)
	{
		if (*s && *s == 34)
		{
			s++;
			len++;
			while (*s && *s != 34)
			{
				len++;
				s++;
			}
		}
		else if (*s && *s == 39)
		{
			s++;
			len++;
			while (*s && *s != 39)
			{
				len++;
				s++;
			}
		}
		else
			len++;
		s++;
	}
	return (len);
}

static void		*ft_free_split(char **str, int i)
{
	while (i--)
		free(str[i]);
	free(str);
	return (NULL);
}

char			**ft_split_pipe(char *s, char c)
{
	char	**str;
	int	i;
	int	j;

	if (!s)
		return (NULL);
	i = 0;
	if (!(str = (char **)malloc(sizeof(char*) * (ft_word_count(s, c) + 1))))
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			if (!(str[i] = (char *)malloc(sizeof(char) * (ft_len(s, c) + 1))))
				return (ft_free_split(str, i));
			j = 0;
			while (*s && *s != c)
			{
				if (*s == '\"')
				{
					str[i][j++] = *s++;
					while (*s != '\"' && *s)
						str[i][j++] = *s++;
					if (*s == '\"')
						str[i][j++] = *s++;
				}
				else if (*s == '\'')
				{
					str[i][j++] = *s++;
					while (*s != '\'' && *s)
						str[i][j++] = *s++;
					if (*s == '\'')
						str[i][j++] = *s++;
				}
				else
					str[i][j++] = *s++;
			}
			str[i++][j] = '\0';
		}
	}
	str[i] = NULL;
	return (str);
}
