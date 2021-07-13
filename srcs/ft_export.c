#include "../minishell.h"

void	ft_swap_list(char **s1, char **s2)
{
	char	*tmp;

	tmp = ft_strdup(*s1);
	free(*s1);
	*s1 = ft_strdup(*s2);
	free(*s2);
	*s2 = ft_strdup(tmp);
	free(tmp);
}

void	ft_copy_env(t_struct *env)
{
	t_list	*tmp;

	tmp = env->s_env;
	while (tmp)
	{
		ft_lstadd_back(&env->s_exp, ft_lstnew(ft_strdup(tmp->content), tmp->flag));
		tmp = tmp->next;
	}
}

void	ft_sort_exp(t_struct *env)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = 0;
	tmp = env->s_exp;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		while (tmp2->next)
		{
			if (ft_strcmp(tmp->content, tmp2->content) > 0)
				ft_swap_list(&tmp->content, &tmp2->content);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	ft_print_exp(t_struct *env, int (*fd))
{
	t_list	*tmp;

	ft_copy_env(env);
	ft_sort_exp(env);
	tmp = env->s_exp;
	while (tmp)
	{
		write(fd[1], "declare -x ", 11);
		write(fd[1], tmp->content, ft_strlen(tmp->content));
		write(fd[1], "\n", 1);
		tmp = tmp->next;
	}
	ft_lstclear(&(env->s_exp), free);
}

int	ft_check_first_letter(char c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123) || c == 95)
		return (1);
	return (0);
}

int	ft_check_sym(char c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123)
		|| c == 95 || (c > 48 && c < 58))
		return (1);
	return (0);
}

int	ft_check_name(char *str)
{
	int	i;

	if (ft_check_first_letter(str[0]))
	{
		i = 1;
		while (str[i])
		{
			if (!ft_check_sym(str[i]))
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	ft_add_elem(t_struct *env, int len, char *str)
{
	if (len > 1)
		len = 1;
	else
		len = 0;
	ft_lstadd_back(&(env)->s_env, ft_lstnew(ft_strdup(str), len));
	ft_lstclear(&(env->s_exp), free);
}

void	ft_add_env(t_struct *env)
{
	char	**tmp;
	int	len;
	int	i;

	i = 1;
	while (env->temporary[i])
	{
		tmp = ft_split(env->temporary[i], '=');
		len = ft_arraylen(tmp);
		if (!ft_check_name(tmp[0]) && len < 3)
			ft_add_elem(env, len, env->temporary[i]);
		i++;
	}
}

void	ft_export(t_struct *env, int (*fd))
{
	int		len;

	len = ft_arraylen(env->temporary);
	if (len > 1)
		ft_add_env(env);
	else if (len == 1)
		ft_print_exp(env, fd);
}