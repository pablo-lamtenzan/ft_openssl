/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:13:53 by pablo             #+#    #+#             */
/*   Updated: 2020/10/24 04:14:06 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

// stat + change dir before open == bug (raise condition)
// to fix its open, store, fstat + read, close
// TOCTOU

int         main(int ac, char** av)
{
	t_parse	parse;

	parse = (t_parse){.flags=0, .input_to_print=NULL, .pipe_data=NULL, \
			.string_input=NULL, .files=NULL,.algorithm=NULL, .hash_and_print=NULL};

    if (ac == 1) // Usage if stdin is empty
        read_from_pipe(&parse);
	else
    	read_standart(&parse, ac, av);
	return (parse.hash_and_print ? parse.hash_and_print(&parse) : 0);
}