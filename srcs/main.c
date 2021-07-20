#include "../minishell.h"

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			printf("  \n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			printf("\n");
	}
}

void	ft_signal_quit_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		if (waitpid(-1, NULL, WNOHANG) == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			printf("  \b\b");
		}
		else
			printf("Quit: 3\n");
	}
}


// int	ft_check_double_quotes(char *str, int i)
// {
// 	if (str[i] == '"' && str[i + 1] == '"')
// 		return (1);
// 	if (str[i] == '\'' && str[i + 1] == '\'')
// 		return (1);
// 	return (0);
// }

// void	ft_quotes(t_struct *env)
// {
// 	int i;
// 	int j;
// 	char *str;

// 	i = 0;
// 	j = 0;
// 	str = ft_strdup(env->s_cmd_line);
// 	ft_bzero(env->s_cmd_line, ft_strlen(env->s_cmd_line));
// 	while (i < ft_strlen(str))
// 	{
// 		if (ft_check_double_quotes(str, i))
// 			i += 2;
// 		else
// 		{
// 			env->s_cmd_line[j] = str[i];
// 			j++;
// 			i++;
// 		}
// 	}
// 	env->s_cmd_line[j] = '\0';
// 	free(str);
// }

int	main(int argc, char **argv, char **envv)
{
	t_struct	*env;

	(void)argc;
	(void)argv;
	env = (t_struct *)malloc(sizeof(t_struct));
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_quit_handler);
	env->s_env = ft_init_env(envv);
	env->s_exp = 0;
	while (1)
	{
		g_status = 0;
		env->count_pipe = 0;
		env->s_cmd_line = readline("minishell $>> ");
		env->s_cmd_line = ft_space(env->s_cmd_line);
		add_history(env->s_cmd_line);
		if (env->s_cmd_line == NULL)
		{
			printf("\033[Aminishell >> $ exit\n");
			exit(0);
		}
		if (ft_strlen(env->s_cmd_line) > 0)
		{
			ft_lexer(env);
			//ft_quotes(env);
			if (!g_status)
				ft_parser(env);
			else
				printf("FUCK ERROR !\n");
		}
	}
	return (0);
}
