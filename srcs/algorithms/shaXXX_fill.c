/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaXXX_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 23:13:15 by pablo             #+#    #+#             */
/*   Updated: 2020/10/21 20:07:58 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sll_sha256.h>
#include <algorithms.h>

int				append_padding_shaXXX(unsigned long* message,
    unsigned int message_size, unsigned int (*swap_bits)(unsigned int))
{
	unsigned long		size;
	unsigned int		msg_len;
	unsigned long		chunks_nb;
	int					iterator;
	unsigned int		*cast;

	cast = (void *)0;
	if (swap_bits == swap_u32bits)
		cast = (unsigned int*)message;

	iterator = -1;
	size = msg_len * CHAR_BIT + CHUNK_BYTE_SIZE;
	while (++size & CHUNK_BIT_SIZE)
		;
	msg_len = size;
	chunks_nb = size / CHUNK_BIT_SIZE;
	size % CHUNK_BIT_SIZE ? chunks_nb++ : 0;
	(cast ? cast : message)[message_size] = 1;
	while (++iterator < (chunks_nb * 16) - 1)
		(cast ? cast : message)[iterator] = swap_bits((cast ? cast : message)[iterator]);
	(cast ? cast : message)[((chunks_nb * CHUNK_BIT_SIZE - CHUNK_BYTE_SIZE) / 32) + 1] = msg_len;
	return (chunks_nb * CHUNK_BYTE_SIZE);
}