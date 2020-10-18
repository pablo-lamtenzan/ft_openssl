/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:13:53 by pablo             #+#    #+#             */
/*   Updated: 2020/10/18 23:35:57 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sll.h>

static bool			get_data_from_stdin(char **data)
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

static bool			read_from_pipe()
{
    char*           name;
    char*			data;
    size_t          index;
    t_algorithms    algorithm;

    index = 0;
    //printf("%s", PROMT);
    while (get_next_line(STDIN_FILENO, &name)) // only read could be enought... ?
    {
        while (index < TOTAL_ALGORITHMS)
        {
            if (ft_strncmp((algorithm = get_algorithm(index++)).name, name, ft_strlen(name)) \
                    && get_data_from_stdin(&data))
			{
				algorithm.algorithm(data);
				free(name);
				free(data);
				return (0);
			}
			free(name);
        }
		print_error(name);
		return (1);
    }
    
}

int         main(int ac, char** av)
{
    /* Read from stdin ( echo "something" | ./ft_sll md5 ) */
    if (ac == 1)
        return (read_from_pipe());
    return (read_from_arguments());
}