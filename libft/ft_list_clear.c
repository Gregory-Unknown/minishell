#include "libft.h"

void	ft_list_clear(t_list1 *list, void (*del)(void *))
{
	if (list)
	{
		del(list->command);
		del(list->redcom);
		if (list->redirect_command)
			ft_free(list->redirect_command);
		list->pipe = 0;
		list->pid = 0;
		list->next = 0;
		list->prev = 0;
		free(list);
	}
}
