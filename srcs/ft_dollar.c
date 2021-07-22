#include "../minishell.h"

char	*ft_check_env_param(char *str, t_struct *env)
{
	t_list	*tmp;
	char	**s;

	tmp = env->s_env;
	while (tmp)
	{
		s = ft_split(tmp->content, '=');
		if (s[1] && !ft_strncmp(str, s[0], ft_strlen(s[0])) && (ft_isspace(str[ft_strlen(s[0]) + 1]) || (ft_strlen(str) == ft_strlen(s[0]))))
			return(ft_strdup(s[1]));
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_dollar_change(char *str, int start, int finish, t_struct *env)
{
	char	*tmp;
	char	*s;

	tmp = ft_check_env_param(ft_substr(&str[1], start, finish), env);
	s = ft_substr(str, 0, start);
	s = ft_strjoin1(s, tmp);
	s = ft_strjoin1(s, ft_substr(str, finish, ft_strlen(str)));
	free(tmp);
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (s);
}

int	ft_check_finish(char *str, int start)
{
	char	c;
	int	i;

	c = str[start];
	i = start;
	while (str[i] && i < ft_strlen(str))
	{
		if (c == '$')
		{
			start++;
			while (str[start] && ft_isspace(str[start]) == 0 && str[start] != '$')
				start++;
			return (start);
		}
		i++;
	}
	return (0);
}

char	*ft_status_dollar(char *str, int i, t_struct *env)
{
	char	*s;

	s = ft_substr(str, 0, i);
	s = ft_strjoin1(s, ft_itoa(env->status));
	if (str[i + 2])
		s = ft_strjoin1(s, ft_substr(str, i + 2, ft_strlen(str)));
	free(str);
	return (s);
}

char	*ft_check_dollar2(char *s, t_struct *env)
{
	int	i;
	int	flag;
	int	start;
	int	finish;
	char	*str;

	i = 0;
	flag = 0;
	finish = 0;
	str = ft_strdup(s);
	free(s);
	while (str[i])
	{
		if (!flag && str[i] == '\'')
			flag = 1;
		else if (flag && str[i] == '\'')
			flag = 0;
		else if (!flag && str[i] == '$' && !ft_isspace(str[i + 1]))
		{
			if (str[i + 1] == '?')
				str = ft_status_dollar(str, i, env);
			else
			{
				start = i;
				finish = ft_check_finish(str, start);
				str = ft_dollar_change(str, start, finish, env);
			}
			flag = 0;
			i = -1;
		}
		i++;
	}
	return (str);
}

void	ft_check_dollar(t_list1 *tmp, t_struct *env)
{
	int	i;

	i = 0;
	while (tmp->temporary[i])
	{
		tmp->temporary[i] = ft_check_dollar2(tmp->temporary[i], env);
		i++;
	}
}

