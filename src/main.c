/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:06:16 by juhyulee          #+#    #+#             */
/*   Updated: 2023/03/26 20:04:22 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ascii_art(void)
{
	printf("⢸⣿⡇⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⢀⡀⣀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠛⠻⢦⡄⠨⡍⢿⣿⣶⣄⡈⠣⠀⣀⣠⣾\n");
	printf("⢸⣿⡇⠀⠀⢸⣏⠀⠀⠀⢹⡇⠀⠠⠞⠣⠄⢸⡇⣿⠀⠀⠀⢀⣴⣶⣿⣿⣿⣿⣶⣦⡄⢸⣿⣿⣿⣿⣿⣿⣆⠀⠀⢠⣿\n");
	printf("⠘⣿⡇⠀⠀⠤⠤⠬⠿⠥⠤⠤⠄⠉⢹⠫⠭⢼⡇⣿⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⠛⠻⣧⣾⣿⣿⣿⣿⣿⣿⠟⠀⠀⣸⣿\n");
	printf(" ⣿⡇⠀⠀⢀⣶⠏⠉⠙⣶⡀⠀⠀⢐⡒⠒⢒⣒⣶⠀⠀⠀⠀⠙⠻⢿⣿⣿⣿⣦⣠⣽⣿⣿⣿⣿⣿⠿⠋⠀⠀⣠⣿⣿\n");
	printf("⠀⣿⡇⠀⠀⠀⠛⠧⠤⠴⠛⠀⠀⠀⠘⠷⣤⣤⠤⠖⠀⠀⠀⠈⠀⠄⣀⡈⠙⢿⣿⣿⣿⣿⣿⣉⠁⠀⠀⣀⣤⣾⣿⣿⣿\n");
	printf("⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣤⣀⢀⣾⣿⡿⠿⠛⠉⠉⠉⠉⠉⠙⠛⠿⢿⣿⣿⣿⣿⣿\n");
}

void	print_node(t_node *node)
{
	int	i;

	i = 0;
	while (node)
	{
		printf("%d node is %s\n", i, node->str);
		printf("%d type is %d\n", i, node->type);
		node = node->next;
		i++;
	}
}

void	to_do(char *line, t_node *head, t_env *env, int status)
{
	while (1)
	{
		sig_init();
		line = readline("\033[1m\033[9m\033[91mMONGSHELL $ \033[0m");
		if (!line)
			exit(0);
		if (*line != '\0')
			add_history(line);
		if (*line != '\0' && !is_whitespace(line))
		{
			if (error_parsing(line) > 0)
				continue ;
			if (parse(line, &head) == -1)
			{
				free(line);
				continue ;
			}
		}
		free(line);
		check_quote_lst(head);
		check_lst_env(head, env, status);
		merge_cmd(head);
		status = execute(head, env, status);
		free_node(head);
	}
}

int	main(int ac, char **av, char **envp)
{
	char			*line;
	int				status;
	struct termios	term;
	t_node			*head;
	t_env			*env;

	(void)av;
	tcgetattr(0, &term);
	status = 0;
	main_init(ac, envp, &env, &head);
	ascii_art();
	line = 0;
	to_do(line, head, env, status);
	tcsetattr(0, TCSANOW, &term);
}
