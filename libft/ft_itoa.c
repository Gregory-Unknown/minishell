#include "libft.h"

static size_t	ft_count(int n)
{
	size_t count;

	if (n == 0)
		return (1);
	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	num;
	size_t	count;

	num = n;
	num = ((n < 0) ? (-num) : (num));
	count = ((n < 0) ? (ft_count(n) + 1) : (ft_count(n)));
	if (!(str = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	str[count] = '\0';
	while (count--)
	{
		str[count] = num % 10 + 48;
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
