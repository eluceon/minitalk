#include "client.h"

int	is_signal_received(int is_signal)
{
	static int	status = FALSE;

	if (is_signal)
		status = TRUE;
	else if (status)
	{
		status = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

void	send_message(pid_t server_pid, char *msg)
{
	int		i;
	int		ret;
	int		mask;

	i = 0;
	while (1)
	{	
		mask = 0b10000000;
		while (mask)
		{
			if (mask & msg[i])
				ret = kill(server_pid, SIGUSR1);
			else
				ret = kill(server_pid, SIGUSR2);
			if (ret)
				exit(error_message("Couldn't send signal"));
			mask >>= 1;
			usleep(500);
			while (!is_signal_received(FALSE))
				continue ;
		}
		if (!msg[i++])
			break ;
	}
}

void	handle_server_signal(int signum, siginfo_t *siginfo, void *context)
{
	(void)context;
	(void)siginfo;
	if (signum == SIGUSR1)
		is_signal_received(TRUE);
	else if (signum == SIGUSR2)
	{
		ft_putstr_fd(GREEN_COLOR, STDERR_FILENO);
		ft_putstr_fd("[v] minitalk: ", STDERR_FILENO);
		ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
		ft_putendl_fd("All data has been received.", STDOUT_FILENO);
		exit (SUCCESS);
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

int	main(int argc, char *argv[])
{
	if (is_wrong_arg(argc, argv))
		return (1);
	if (catch_signal(SIGUSR1, handle_server_signal) == -1
		|| catch_signal(SIGUSR2, handle_server_signal) == -1)
		return (error_message("Can't handle signal"));
	send_message(ft_atoi(argv[1]), argv[2]);
	while (1)
		continue ;
	return (SUCCESS);
}
