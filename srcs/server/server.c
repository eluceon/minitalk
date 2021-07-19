#include "server.h"

void	print_str(char **str, pid_t pid)
{
	ft_putendl_fd(*str, STDOUT_FILENO);
	free(*str);
	*str = NULL;
	if (kill(pid, SIGUSR2) == -1)
		error_message("Error signal\n");
}

void	decode_signal(int signum, siginfo_t *siginfo, void *context)
{
	static char	symbol;
	static char	*str = NULL;		
	static int	mask = 0b10000000;

	(void)context;
	if (signum == SIGUSR1)
		symbol |= mask;
	mask >>= 1;
	if (mask && kill(siginfo->si_pid, SIGUSR1) == -1)
		error_message("Error signal\n");
	if (mask == 0)
	{
		str = str_join_char(str, symbol);
		if (!str)
			exit(12);
		if (kill(siginfo->si_pid, SIGUSR1) == -1)
			error_message("Error signal\n");
		if (symbol == '\0')
			print_str(&str, siginfo->si_pid);
		symbol = 0;
		mask = 0b10000000;
	}
}

int	catch_signal(int signum, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	s_action;

	ft_memset(&s_action, 0, sizeof(s_action));
	s_action.sa_sigaction = handler;
	s_action.sa_flags = SA_SIGINFO;
	sigemptyset(&s_action.sa_mask);
	return (sigaction(signum, &s_action, NULL));
}

int	main(void)
{
	ft_putstr_fd("pid: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	if (catch_signal(SIGUSR1, decode_signal) == -1
		|| catch_signal(SIGUSR2, decode_signal) == -1)
		return (error_message("Can't handle signal"));
	while (1)
		continue ;
	return (SUCCESS);
}
