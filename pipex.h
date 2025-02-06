#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "./Libft/libft.h"

//main functions
void	pipex(int argc, char **argv, char **envp);
void	first_cmd_exec(int *fd, char **argv, char **envp);
void	second_cmd_exec(int *fd, char **argv, char **envp);
void	ft_exec(char *cmd, char **envp);

//utils
char	**parse_path(char *envp[]);
char	*ft_makepath(char const *path, char const *cmd);
void	free_array(char **arr_to_free);


#endif
