/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:22:28 by pablo             #+#    #+#             */
/*   Updated: 2020/10/26 03:18:09 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft.h>
#include <ft_error.h>

char*				get_data_from_file(int fd, char* filename, char flags)
{
	char*			data;

	if (fd < 0)
	{
		if (!(flags & QUIET_MODE))
			return ((void *)print_error(NULL, ERROR_FILENF, filename));
		else
			return (NULL);
	}
	if (get_data_from_fd(fd, &data) && !(close(fd)));
		return (data);
	return (NULL);
}

bool				get_data_from_fd(int fd, char** data)
{
	size_t			size;
	ssize_t			bytes_read;
	char			buffer[BUFFER_SIZE];
	char*			aux;

	if (!(*data = ft_calloc(sizeof(char), 1)))
		return (false);
	size = 0;
	while ((bytes_read = read(fd, &buffer, BUFFER_SIZE)) > 0)
	{
		if (!(aux = ft_calloc(sizeof(char), (size + bytes_read + 1))))
			return (false);
		ft_memcpy(aux, *data, size);
		ft_memcpy(aux + size, buffer, bytes_read);
		size += bytes_read;
		aux[size] = 0;
		free(*data);
		*data = aux;
		ft_bzero(&buffer, BUFFER_SIZE);
	}
	return (true);
}

// do at the and
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
            if (!ft_strncmp((algorithm = get_algorithm(index)).name, name, ft_strlen(name)) \
                    && get_data_from_fd(STDIN_FILENO, &parse->pipe_data))
			{
				parse->algorithm = algorithm.algorithm;
				parse->hash_and_print = algorithm.hash_and_print;
				free(name);
				name = NULL;
				return (0);
			}
			print_error((void*)name, ERROR_ALGONAME, name);
			index++;
        }
		free(name);
    }
    return (print_error((void* )parse->hash_and_print, ERROR_USAGE, NULL));
}

bool			    read_standart(t_parse* parse, int ac, char** av)
{
	size_t			index;
	t_algorithms	algorithm;

	index = 0;
	while (index < TOTAL_ALGORITHMS)
		if (!ft_strncmp((algorithm = get_algorithm(index++)).name, av[1], ft_strlen(av[1])))
			algorithm.parse(&parse, ac, av, &algorithm);
	parse->hash_and_print = parse->algorithm ? algorithm.hash_and_print : NULL;
	return (!parse->algorithm && print_error(NULL, ERROR_ALGONAME, av[1]));
}