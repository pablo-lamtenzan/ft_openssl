/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:44:39 by pablo             #+#    #+#             */
/*   Updated: 2020/10/24 04:36:35 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft.h>

static bool		parse_string_input(t_parse* parse, char* string_input)
{
	const size_t size = ft_strlen(string_input);

	if (parse->string_input || !(parse->string_input = malloc(sizeof(char) * size)))
		return (false);
	return (ft_strlcpy(parse->string_input, string_input, size));
}

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
			parse_string_input(*parse, av[curr_arg++]);
		if (!av[curr_arg])
			break ;
        while (++index < 4)
            if (!ft_strncmp(av[curr_arg], flags[index], 2) && (find = true))
                (*parse)->flags |= (1 << index);
		if ((*parse)->flags & PRINT_INPUT && !(*parse)->input_to_print)
			get_data_from_fd(STDIN_FILENO, &(*parse)->input_to_print);
    }
    return (curr_arg);
}

char**			parse_files(int index, int ac, char** av)
{
	const size_t size = ac - index;
	char**		files;
	struct stat	stat_path;

	if (!(files = malloc(sizeof(char*) * size)))
		return (NULL);
	ft_bzero(&stat_path, sizeof(stat_path));
	while (++index -1 <= ac)
	{
		if (stat(av[index - 1], &stat_path) || !S_ISREG(stat_path.st_mode)) // problem here returns null last iteration
			return (NULL);
		files[size - index - 1] = ft_strdup(av[index - 1]);
		printf("%s\n", files[size - index - 1]);
	}
	files[size - index - 1] = 0;
	return (files);
}

bool			parse_message_digest(t_parse** parse, int ac, char** av, t_algorithms* algorithm)
{
	int			files_pos;

	if (!(files_pos = parse_flags(parse, ac, av)) \
			|| !get_data_from_fd(STDIN_FILENO, &(*parse)->pipe_data))
		return (false);
	if (files_pos < ac)
	(*parse)->files = parse_files(files_pos, ac, av);
	(*parse)->algorithm = algorithm->algorithm;
	return (true);
}