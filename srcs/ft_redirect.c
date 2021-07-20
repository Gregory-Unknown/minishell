#include "../minishell.h"

void	ft_process_redirect(t_list1 *tmp)
{
	int	i;
	char	**s;

	i = 0;
	while (tmp->redirect_command[i])
	{
		if (ft_strncmp(tmp->redirect_command[i], ">>", 2) == 0)
		{
			s = ft_split(tmp->redirect_command[i], '>');
			ft_double_right(ft_space(s[0]), tmp);
			i++;
			ft_free(s);
		}
		else if (ft_strncmp(tmp->redirect_command[i], ">", 1) == 0)
		{
			s = ft_split(tmp->redirect_command[i], '>');
			ft_single_right(ft_space(s[0]), tmp);
			ft_free(s);
		}
		else if (ft_strncmp(tmp->redirect_command[i], "<<", 2) == 0)
		{
			s = ft_split(tmp->redirect_command[i], '<');
			ft_double_left(ft_space(s[0]), tmp);
			i++;
			ft_free(s);
		}
		else if (ft_strncmp(tmp->redirect_command[i], "<", 1) == 0)
		{
			s = ft_split(tmp->redirect_command[i], '<');
			ft_single_left(ft_space(s[0]), tmp);
			ft_free(s);
		}
		i++;
	}
}
