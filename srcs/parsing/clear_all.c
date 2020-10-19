/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:09:54 by pablo             #+#    #+#             */
/*   Updated: 2020/10/19 23:14:23 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sll.h>

void            clear_all(t_parse* parse)
{
    size_t      index;

	index = 0;
    free(parse->input_to_print);
    free(parse->pipe_data);
    free(parse->string_input);
    while (parse->files && parse->files[index])
		free(parse->files[index++]);
	free(parse->files);
}