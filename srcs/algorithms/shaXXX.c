/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaXXX.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 23:13:15 by pablo             #+#    #+#             */
/*   Updated: 2020/10/20 23:16:26 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sll_sha256.h>

int				append_padding_shaXXX(unsigned int* message,
    unsigned int message_size, unsigned int (*swap_bits)(unsigned int))
{
	unsigned long		size;
	unsigned int		msg_len;
	unsigned long		chunks_nb;
	int					iterator;

	iterator = -1;
	size = msg_len * CHAR_BIT + CHUNK_BYTE_SIZE;
	while (++size & CHUNK_BIT_SIZE)
		;
	msg_len = size;
	chunks_nb = size / CHUNK_BIT_SIZE;
	size % CHUNK_BIT_SIZE ? chunks_nb++ : 0;
	message[message_size] = 1;
	while (++iterator < (chunks_nb * 16) - 1)
		message[iterator] = swap_bits(message[iterator]);
	message[((chunks_nb * CHUNK_BIT_SIZE - CHUNK_BYTE_SIZE) / 32) + 1] = msg_len;
	return (chunks_nb * CHUNK_BYTE_SIZE);
}