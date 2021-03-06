/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:44:39 by pablo             #+#    #+#             */
/*   Updated: 2020/10/26 04:40:26 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft.h>
#include <ft_error.h>

#include <string.h>

int				parse_flags(t_parse** parse, int ac, char** av)
{
    int         curr_arg;
    int         index;
    const char 	flags[4][2] = { "-p", "-q", "-r", "-s" };
	bool		find;
	bool		once;

    curr_arg = 2;
	once = true;
    while (once || (find && av[curr_arg + 1] && ++curr_arg))
    {
		once = false;
		find = false;
        index = -1;
		if ((*parse)->flags & STRING_INPUT && !(*parse)->string_input)
			(*parse)->string_input = av[curr_arg++];
		index = -1;
		if (!av[curr_arg])
			break ;
        while (++index < 4)
            if (!ft_strncmp(av[curr_arg], flags[index], 2) && (find = true))
                (*parse)->flags |= (1 << index);
    }
    return (curr_arg);
}

void			parse_files(t_parse* parse, int index, int ac, char** av)
{
	const size_t size = ac - index;
	int			i;
	
	i = 0;
	if (!(parse->files_fds = malloc(sizeof(int) * size))
			|| !(parse->filenames = malloc(sizeof(char*) * size)))
		return ;
	while (++index - 1 <= ac - 1)
	{
		parse->filenames[i] = av[index - 1];
		parse->files_fds[i++] = open(av[index - 1], O_RDONLY);
	}
	parse->files_fds[i] = 0;
	parse->filenames[i] = 0;
}

bool			parse_message_digest(t_parse** parse, int ac, char** av, t_algorithms* algorithm)
{
	int			files_pos;

	files_pos = parse_flags(parse, ac, av);
	if (av[files_pos] && (files_pos < ac - 1 || ((!(*parse)->flags || (*parse)->flags & REV_OUTPUT || (*parse)->flags & PRINT_INPUT) && files_pos < ac)))
		parse_files(*parse, files_pos, ac, av);
	if (((!(*parse)->files_fds && !((*parse)->flags & STRING_INPUT)) || (((*parse)->files_fds || (*parse)->flags & STRING_INPUT) && (*parse)->flags & PRINT_INPUT)) && !get_data_from_fd(STDIN_FILENO, &(*parse)->pipe_data))
		return (false);
	(*parse)->algorithm = algorithm->algorithm;
	return (true);
}