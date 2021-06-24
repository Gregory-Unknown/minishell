#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
#include <sys/wait.h>

//char        **g_env;

// typedef struct      s_list
// {
//     char            *content;
//     int             flag;
//     struct s_list   *next;
// }                   t_list;


typedef struct s_struct
{
	t_list	*s_env;
	t_list	*s_exp;
	char	**env_array;
	char	*s_cmd_line;
	char	**dir;
	char	**temporary;
	int	i;
	int	j;
	int	count;
}t_struct;

t_list	*ft_init_env(char **envv);
void	ft_print_env(t_struct *env);
void	ft_export(t_struct *env);
void	ft_unset(t_struct *env);
void	ft_parser(t_struct *env);

#endif
