/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:13:53 by pablo             #+#    #+#             */
/*   Updated: 2020/10/26 02:29:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft_error.h>

#include <algorithms.h>

// -r segfault
// check that in shell "echo "test" | openssl"

int         main(int ac, char** av)
{
	t_parse	parse;

	parse = (t_parse){.flags=0, .pipe_data=NULL, \
			.string_input=NULL, .files_fds=NULL, .filenames=NULL, .algorithm=NULL, .hash_and_print=NULL};

    if (ac == 1)
		return (print_error(NULL, ERROR_USAGE, NULL));
	else
    	read_standart(&parse, ac, av);
	return (parse.hash_and_print ? parse.hash_and_print(&parse) : 0);
}