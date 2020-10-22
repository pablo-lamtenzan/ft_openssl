/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:22:28 by pablo             #+#    #+#             */
/*   Updated: 2020/10/22 19:45:43 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft.h>

const char*			get_data_from_file(const char* filename)
{
	char*			data;
	int				fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (NULL);
	if (get_data_from_fd(fd, &data));
		return (data);
	return (NULL);
}

bool				get_data_from_fd(int fd, char **data)
{
	size_t			size;
	ssize_t			bytes_read;
	char*			buffer;
	char*			aux;

	if (!(buffer = malloc(sizeof(char) * BUFFER_SIZE))
			|| !(*data = ft_calloc(1, 1)))
		return (false);
	**data = 0;
	size = 0;
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) < 0)
	{
		if (!(aux = malloc(sizeof(char) * (size + bytes_read + 1))))
			return (false);
		ft_strlcpy(aux, *data, size);
		ft_strlcpy(aux + size, buffer, bytes_read);
		size += bytes_read;
		aux[size] = 0;
		free(*data);
		*data = aux;
	}
	free(buffer);
	return (true);
}

bool			    read_from_pipe(t_parse* parse)
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
                    && get_data_from_fd(STDIN_FILENO, &parse->pipe_data))
			{
				parse->algorithm = algorithm.algorithm;
				parse->hash_and_print = algorithm.hash_and_print;
				free(name);
				return (0);
			}
			free(name);
        }
		//print_error(name);
		return (1);
    }
    return (1);
}

bool			    read_standart(t_parse* parse, int ac, char** av)
{
	size_t			index;
	t_algorithms	algorithm;
	char			error;

	index = 0;
	error = 0;
	while (index < TOTAL_ALGORITHMS)
		if (!ft_strncmp((algorithm = get_algorithm(index)).name, av[1], ft_strlen(av[1])))
			error = algorithm.parse(parse, ac, av, &algorithm);
	//if (error) // use the error for bitwise if is necesarry
	//	print_error(av[1]);
	parse->hash_and_print = algorithm.hash_and_print;
	return (true);
}