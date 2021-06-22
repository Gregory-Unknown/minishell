#include "../minishell.h"

t_list	*ft_init_env(char **envv)
{
	t_list	*head;
	int		i;

	i = 0;
	head = 0;
	while (envv[i])
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(envv[i]), 1));
		i++;
	}
	return (head);
}

void	ft_print_env(t_struct *env)
{
	t_list	*tmp;

	tmp = env->s_env;
	while (tmp)
	{
		if (tmp->flag)
			printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}
