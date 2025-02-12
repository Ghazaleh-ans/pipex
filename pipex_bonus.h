#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "./Libft/libft.h"

/* Mandatory part functions */
int		pipex(int argc, char **argv, char **envp);
void	first_cmd_exec(int *fd, char **argv, char **envp);
void	second_cmd_exec(int *fd, char **argv, char **envp);

/* Bonus part main functions */
int		pipex_bonus(int argc, char **argv, char **envp);
void	exec_cmd(char *cmd, char **envp, int *last_status);
void	ft_exec(char *cmd, char **envp);
void execute_final_command(char **argv, char **envp, int argc, int *last_status);
void	process_commands(char **argv, char **envp, int num, int argc, int *last_status);

/* Heredoc functions */
void	setup_here_doc(int argc, char **argv, int *num, int *fd_out);
int		here_doc(int argc, char **argv);
void	write_to_limiter(int *fd, char *limiter);
void	clean_line(char *line);
int		write_line_to_fd(int fd, char *line);
void	handle_heredoc_line(int fd, char *line, char *limiter, int *status);

/* File and path handling utils */
int		file_opener(char *path, char flag);
char	**parse_path(char **envp);
char	*ft_makepath(char const *path, char const *cmd);
void	free_array(char **arr_to_free);

/* Static function declarations for internal use */
void	child_process(int *fd, char *cmd, char **envp);
void	parent_process(int *fd, int pid, int *last_status);
char	*find_executable(char **paths, char *cmd);


#endif
