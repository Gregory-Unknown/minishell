#include "../minishell.h"

char	**ft_make_array(t_struct *env)
{
	char	**array;
	t_list	*tmp;
	int	i;

	tmp = env->s_env;
	i = ft_lstsize(tmp) + 1;
	array = (char **)malloc(sizeof(char *) * i);
	if (!array)
		return (NULL);
	i = 0;
	while (tmp)
	{
		array[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
