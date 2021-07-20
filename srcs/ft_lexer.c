#include "../minishell.h"

int	ft_check_pipe(char * str, char c)
{
	int i;

	i = 0;
	if (str[i] == c)
		return (1);
	while (str[i])
	{
		if (str[i] == c && (!str[i + 1] || str[i + 1] == c))
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_quotes(char *str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (!flag && str[i] == c)
			flag = 1;
		else if (flag && str[i] == c)
			flag = 0;
		i++;
	}
	if (flag)
		return (1);
	return (0);
}

int	ft_check_redirect(char * str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] && flag < 3)
	{
		if (str[i] == c)
			flag++;
		else if (flag && str[i] != '|')
			flag = 0;
		else
			flag = (flag) ? 1 : 0;
		i++;
	}
	if (flag)
		return (1);
	return (0);
}

int	ft_check_symbol(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_lexer(t_struct *env)
{
	char *str;

	str = ft_strdup(env->s_cmd_line);
	if (ft_check_pipe(str, '|'))
	{
		g_status = 258;
		return (1);
	}
	if (ft_check_quotes(str, '\'') || ft_check_quotes(str, '\"'))
	{
		g_status = 127;
		return (1);
	}
	if (ft_check_redirect(str, '>') || ft_check_redirect(str, '<'))
	{
		g_status = 258;
		return (1);
	}
	if (ft_check_symbol(str, '\\') || ft_check_symbol(str, ';'))
	{
		g_status = 258;
		return (1);
	}
	return (0);
}
