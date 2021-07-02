#include "libft.h"

t_list1	*ft_new_list(char *command, int pipe)
{
	t_list1	*list;

	list = (t_list1 *)malloc(sizeof(t_list1));
	list->command = command;
	list->pipe = pipe;
	list->pid = 0;
	list->next = 0;
	list->prev = 0;
	return (list);
}
