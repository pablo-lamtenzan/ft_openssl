/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:13:53 by pablo             #+#    #+#             */
/*   Updated: 2020/10/19 23:22:23 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sll.h>

int         main(int ac, char** av)
{
	t_parse	parse;

	parse = (t_parse){.flags=0, .input_to_print=NULL, .string_input=NULL, .files=NULL};

    if (ac == 1)
        read_from_pipe(&parse);
	else
    	read_standart(&parse, ac, av);
	return (hash_and_print(&parse));
}