#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*dest;

	len = ft_strlen(src) + 1;
	dest = (char *)malloc(sizeof(char) * len);
	if (!dest)
		exit(-1);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
