/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:09:54 by pablo             #+#    #+#             */
/*   Updated: 2020/10/25 03:11:08 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <stdlib.h>

void            clear_all(t_parse* parse)
{
    size_t      index;

	index = 0;
    free(parse->pipe_data);
    //while (parse->filenames && parse->filenames[index])
	//	free(parse->filenames[index++]);
	free(parse->files_fds);
    free(parse->filenames);
}