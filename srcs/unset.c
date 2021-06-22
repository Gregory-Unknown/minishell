#include "../minishell.h"

int	ft_content_name_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

void	ft_del_elem(t_struct *env, int len, char *str)
{
	t_list	*curr;
	t_list	*prev;

	curr = env->s_env;
	prev = 0;
	while (curr)
	{
		if (ft_strlen(str) > ft_content_name_len(curr->content))
			len = ft_strlen(str);
		else
			len = ft_content_name_len(curr->content);
		if (ft_strncmp(str, curr->content, len) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				env->s_env = env->s_env->next;
			ft_lstdelone(curr, free);
			ft_lstclear(&env->s_exp, free);
			env->s_exp = 0;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_unset(t_struct *env)
{
	char	**tmp;
	int		len;

	len = 0;
	tmp = ft_split(env->s_cmd_line, ' ');
	if (tmp[1])
	{
		ft_del_elem(env, len, tmp[1]);
	}
}
