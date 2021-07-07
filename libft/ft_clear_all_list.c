#include "libft.h"

void	ft_clear_all_list(t_list1 **list, void (*del)(void *))
{
	t_list1	*tmp;

	tmp = *list;
	if (list && *list)
	{
		while (tmp)
		{
			ft_list_clear(*list, del);
			*list = NULL;
			tmp = tmp->next;
		}
	}
}