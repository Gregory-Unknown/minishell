#include "../minishell.h"

void	ft_builtins(t_struct *env)
{
	if (ft_strcmp(env->s_cmd_line, "env") == 0)
		ft_print_env(env);
	if (ft_strncmp(env->s_cmd_line, "export", 6) == 0)
		ft_export(env);
	if (ft_strncmp(env->s_cmd_line, "unset", 5) == 0)
		ft_unset(env);
}

int	ft_check_double_quotes(char *str, int i)
{
	if (str[i] == '"' && str[i + 1] == '"')
		return (1);
	if (str[i] == '\'' && str[i + 1] == '\'')
		return (1);
	return (0);
}

void	ft_quotes(t_struct *env)
{
	int i;
	int j;
	char *str;

	i = 0;
	j = 0;
	str = ft_strdup(env->s_cmd_line);
	ft_bzero(env->s_cmd_line, ft_strlen(env->s_cmd_line));
	while (i < ft_strlen(str))
	{
		if (ft_check_double_quotes(str, i))
			i += 2;
		else
		{
			env->s_cmd_line[j] = str[i];
			j++;
			i++;
		}
	}
	env->s_cmd_line[j] = '\0';
	free(str);
}

int	main(int argc, char **argv, char **envv)
{
	t_struct	*env;

	(void)argc;
	(void)argv;
	env = (t_struct *)malloc(sizeof(t_struct));
	// env->s_env = (t_list *)malloc(sizeof(t_list));
	// env->s_exp = (t_list *)malloc(sizeof(t_list));
	// env->s_env = 0;
	// env->s_exp = 0;
	// env->s_pid = 0;
	env->s_env = ft_init_env(envv);
	while (1)
	{
		env->s_cmd_line = readline("minishell $>> ");
		if (ft_strlen(env->s_cmd_line) != 0)
			add_history(env->s_cmd_line);
		ft_quotes(env);
		ft_parser(env);
			//ft_builtins(env);
	}
	return (0);
}
