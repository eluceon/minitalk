#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

# define RED_COLOR		"\033[1;31m"
# define NONE_COLOR 	"\033[0;0m"
# define GREEN_COLOR	"\033[0;32m"

# define SUCCESS	0
# define FAILURE	1

void	ft_putnbr_fd(int n, int fd);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		error_message(char *description);
void	*ft_memset(void *b, int c, size_t len);
char	*str_join_char(char *str, char ch);
size_t	ft_strlen(const char *s);

#endif