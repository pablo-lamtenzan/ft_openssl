/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:44:39 by pablo             #+#    #+#             */
/*   Updated: 2020/10/19 19:48:43 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sll.h>

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
    const char* flags = { "-p", "-q", "-r", "-s" };
	char		last;

    curr_arg = 1;
	last = -1;
	(*parse)->string_input = NULL;
    while (++curr_arg && last != (*parse)->flags)
    {
        index = -1;
		last = (*parse)->flags;
		if ((*parse)->flags & STRING_INPUT && !(*parse)->string_input)
			parse_string_input(*parse, av[curr_arg++]);
        while (++index < 4)
            if (!strncmp(av[curr_arg], flags[index], 2))
                (*parse)->flags |= ft_pow(2, index);
		if ((*parse)->flags & PRINT_INPUT && !(*parse)->input_to_print)
			get_data_from_stdin(&(*parse)->input_to_print);
    }
    return (curr_arg == ac ? false : curr_arg);
}

bool			is_file_and_exist(char* fileame)
{
	// check access of the file
	// check if the file is a file
	// and i think thats all
}

char**			parse_files(int index, int ac, char** av)
{
	const size_t size = ac - index;
	char**		files;
	
	if (!(files = malloc(sizeof(char*) * size)))
		return (NULL);
	while (++index -1 < ac)
	{
		files[size - index - 1] = av[index - 1];
		if (!is_file_and_exist(files[size - index - 1])) // to do
			return (NULL);
	}
	return (files);
}