/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychirouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:49:32 by ychirouz          #+#    #+#             */
/*   Updated: 2024/02/14 16:08:31 by ychirouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"

# define READ_END 0
# define WRITE_END 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_prompt
{
	pid_t	pid;
	t_list	*cmds;
	char	**envv;
}			t_prompt;

typedef struct s_ms
{
	int		rd_file;
	int		wr_file;
	char	**full_cmd;
	char	*full_path;
}			t_ms;

enum	e_error_ms
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	UNUSED = 4,
	CMDERR = 5,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

//Corrections : Utiles :
//
void		show_matrix(char **str);
//
//pgm1 -i arg <myfile |pgm2
//echo "bjr eval42"       'toi      ' $USER  pourquoi!|       echo off >file
//
//starting
/*---------------------------Initialize prompt-------------------------------*/

t_prompt	init_prompt(char **argv, char **envv);

/*----------------------------Display Prompt---------------------------------*/

char		*ms_dsplprompt(t_prompt prompt);

/*-------------------------Parsing Fuctions----------------------------------*/

void		*check_args(char *out, t_prompt *p);

char		**ft_cmdtrim(char const *s, char *set);

char		**ft_cmdsubsplit(char const *s, char *set);

char		*ft_strtrim_all(char const *s1, int squote, int dquote);

t_list		*fill_nodes(char **args, int i);

/*------------------------Handling Fuctions---------------------------------*/

void		ms_sig_hdl(int sig);

int			all_builtins(t_prompt *prompt, t_list *cmd, int *is_exit, int n);

int			check_builtin(t_ms *n);

void		*checking_fork(t_prompt *prompt, t_list *cmd, int fd[2]);

void		check_cmd(t_prompt *prompt, t_list *start,
				char **split_path, char *path);

void		cd_error(char **str[2]);

int			open_fd(int oldfd, char *path, int flags[2]);

t_ms		*open_file_in_1(t_ms *node, char **args, int *i);

t_ms		*open_file_in_2(t_ms *node, char **args, int *i);

t_ms		*open_file_out_1(t_ms *node, char **args, int *i);

t_ms		*open_file_out_2(t_ms *node, char **args, int *i);

char		*expand_env(char *str, int i, int quotes[2], t_prompt *prompt);

char		*expand_path(char *str, int i, int quotes[2], char *var);

int			here_doc_mk(char *str[2], char *aux[2]);

void		*ms_perror(int err_type, char *param, int err);

char		*ms_env_value(char	*var, char **envv, int n);

char		**ms_set_newenv(char *var, char *value, char **envv, int n);

/*-------------------------Exec Fuctions-----------------------------------*/

void		*exec_cmd(t_prompt *prompt, t_list *cmd);

void		exec_child_cmd(t_prompt *prompt, t_ms *n, int l, t_list *cmd);

void		exec_custom(char ***out, char *full, char *args, char **envv);

/*--------------------------Builtins Functions-----------------------------*/

int			ms_cd(t_prompt *prompt);

int			ms_pwd(void);

int			ms_echo(t_list *cmd);

int			ms_export(t_prompt *prompt);

int			ms_unset(t_prompt *prompt);

int			ms_exit(t_list *cmd, int *is_exit);

/*-----------------------------Utils Functions--------------------------------*/

void		free_content(void *content);

char		**ft_dup_matrix(char **m);

char		*ft_itoa(int n);

char		*ft_strdup(const char *str);

void		ft_free_matrix(char ***m);

int			ft_atoi(const char *nptr);

int			ft_putchar_fd(char c, int fd);

int			ft_putstr_fd(char *s, int fd);

int			ft_putendl_fd(char *s, int fd);

size_t		ft_strlen(const char *s);

int			ft_countchar(char *s, char c);

char		**ft_extend_matrix(char **in, char *newstr);

char		*ft_strchr(const char *s, int c);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_putmatrix_fd(char **m, int nl, int fd);

void		ft_lstclear(t_list **lst, void (*del)(void*));

void		ft_lstadd_back(t_list **lst, t_list *newnode);

t_list		*ft_lstnew(void *content);

t_list		*ft_lstlast(t_list *lst);

char		*ft_substr(char const *s, unsigned int start, size_t len);

int			ft_strchars_i(const char *s, char *set);

char		*ft_strjoin(char const *s1, char const *s2);

int			ft_isspace(char c);

int			ft_isdigit(int c);

int			ft_strchr_i(const char *s, int c);

int			ft_matrixlen(char **m);

char		**ft_matrix_replace_in(char ***big, char **small, int n);

char		**ft_split(char const *s, char c);

char		*ft_strtrim(char const *s1, char const *set);

char		*ft_strnstr(const char *big, const char *little, size_t len);

int			ft_lstsize(t_list *lst);

size_t		ft_strlcpy(char *dst, const char *src, size_t size);

int			ft_nbrlen(long n, int base);

void		*ft_calloc(size_t nmemb, size_t size);

void		*ft_memset(void *s, int c, size_t n);

/*----------------------------------------------------------------------------*/
#endif
