/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:13:53 by pablo             #+#    #+#             */
/*   Updated: 2020/10/19 19:45:04 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sll.h>

bool				get_data_from_stdin(char **data)
{
	int				fd;
	size_t			size;
	ssize_t			bytes_read;
	char*			buffer;
	char*			aux;

	if ((fd = open(STDIN_FILENO, O_RDONLY)) < 0 \
			|| !(buffer = malloc(sizeof(char) * BUFFER_SIZE))
			|| !(*data = ft_calloc(1, 1)))
		return (false);
	**data = 0;
	size = 0;
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) < 0)
	{
		if (!(aux = malloc(sizeof(char) * (size + bytes_read + 1))))
			return (false);
		ft_strncpy(aux, *data, size);
		ft_strncpy(aux + size, buffer, bytes_read);
		size += bytes_read;
		aux[size] = 0;
		free(*data);
		*data = aux;
	}
	free(buffer);
	return (true);
}

static bool			read_from_pipe(t_parse* parse)
{
    char*           name;
    size_t          index;
    t_algorithms    algorithm;

    index = 0;
    //printf("%s", PROMT);
    while (get_next_line(STDIN_FILENO, &name) > 0) // only read could be enought... ?
    {
        while (index < TOTAL_ALGORITHMS)
        {
            if (!ft_strncmp((algorithm = get_algorithm(index++)).name, name, ft_strlen(name)) \
                    && get_data_from_stdin(&parse->pipe_data))
			{
				parse->algorithm = algorithm.algorithm;
				free(name);
				return (0);
			}
			free(name);
        }
		print_error(name);
		return (1);
    }
    return (1);
}

/* Have to probally here to read from pipes too, but i'm not sure at all */
static bool			read_standart(t_parse* parse, int ac, char** av)
{
	size_t			index;
	int				files_pos;
	t_algorithms	algorithm;

	index = 0;
	while (index < TOTAL_ALGORITHMS)
	{
		if (!ft_strncmp((algorithm = get_algorithm(index)).name, av[1], ft_strlen(av[1])) \
				&& (files_pos = parse_flags(&parse, ac, av))
				&& get_data_from_stdin(&parse->pipe_data))
		{
			parse->files = parse_files(files_pos, ac, av);
			parse->algorithm = algorithm.algorithm;
			return (0);
		}
	}
	print_error(av[1]);
}

int         main(int ac, char** av)
{
	t_parse	parse;

	parse = (t_parse){.flags=0, .input_to_print=NULL, .string_input=NULL, .files=NULL};

    if (ac == 1)
        read_from_pipe(&parse);
	else
    	read_standart(&parse, ac, av);
	return (hash_and_print(parse));
}