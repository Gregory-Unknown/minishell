#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>

int	g_status;

typedef struct s_struct
{
	t_list	*s_env;
	t_list	*s_exp;
	t_list1	*s_com;
	char	**env_array;
	char	*s_cmd_line;
	int	count_pipe;
}t_struct;

t_list	*ft_init_env(char **envv);
void	ft_print_env(t_struct *env, t_list1 *fd);
void	ft_export(t_struct *env, t_list1 *fd);
void	ft_unset(t_struct *env, t_list1 *fd);
void	ft_parser(t_struct *env);
void	ft_name_quotes(t_list1 *tmp);
int		ft_check_buildins(char *str);
void	ft_buildins_one(t_struct *env, t_list1 *fd);
void	ft_buildins(t_struct *env, t_list1 *fd);
int		ft_echo(t_list1 *fd);
void	ft_pwd();
int		ft_cd(t_struct *env, t_list1 *fd);
void	ft_pipe(t_struct *env, t_list1 *tmp);
void	ft_exec(t_struct *env, t_list1 *tmp);
void	ft_process_redirect(t_list1 *tmp);
void	ft_double_right(char *str, t_list1 *tmp);
void	ft_single_right(char *str, t_list1 *tmp);
void	ft_double_left(char *str, t_list1 *tmp);
void	ft_single_left(char *str, t_list1 *tmp);
char	**ft_make_array(t_struct *env);
char	*ft_space(char *str);
void	ft_pipe_start(t_struct *env);
char	**ft_make_array(t_struct *env);
int		ft_lexer(t_struct *env);
void	ft_clean(t_struct *env);
void	ft_shell_lvl(t_struct *env);

#endif
