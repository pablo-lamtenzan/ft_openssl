/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:19:15 by pablo             #+#    #+#             */
/*   Updated: 2020/11/02 01:38:41 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl_md5.h>
#include <algorithms.h>
#include <ft.h>

#include <stdio.h>

/*
    Each message has 512 bytes lenght (32 bytes * 16 words).
    Each message will update the vectors using the following alhgorithm:
        crypt = vectors[B] + ((vectors[A] + vec_fct(vector[B], vector[C], vector[D]) + kernels[i] + chunk[k]) <<< s).
    where i is the iterator, k is the chunk index and s a left retation function.
*/
// this can be in utils with appen pagging once this hash works
static size_t           get_chunks_nb(size_t message_len)
{
    return (((message_len + 1 + 8 + (CHUNK_BYTE_SIZE - 1)) & ~(CHUNK_BYTE_SIZE - 1)) / CHUNK_BYTE_SIZE);
}

static void             ssl_md5_algorithm(t_ssl_md5* md5, unsigned char* padded_msg)
{
    int                 index;
    int                 chunk_index;
    unsigned int        rotation;
    const t_operations  operations[4] = { {.operation=f, .chunk_index=f_op}, {.operation=g, .chunk_index=g_op}, 
        {.operation=h, .chunk_index=h_op}, {.operation=i, .chunk_index=i_op} };

    chunk_index = -1;
    while (++chunk_index < get_chunks_nb(md5->bytes) -1 && (index = -1))
    {
        ft_memcpy(md5->algo_buff, md5->buff, sizeof(md5->algo_buff));
        while (++index < MD5_CYCLE_IT)
        {
            rotation = operations[index / 16].operation(md5->algo_buff[B], \
                md5->algo_buff[C], md5->algo_buff[D]) + md5->algo_buff[A] \
                + g_sines[index] + ((unsigned int*)(padded_msg \
                + chunk_index * CHUNK_BYTE_SIZE))[operations[index / 16].chunk_index(index)];
            md5->algo_buff[A] = md5->algo_buff[D];
            md5->algo_buff[D] = md5->algo_buff[C];
            md5->algo_buff[C] = md5->algo_buff[B];
            md5->algo_buff[B] += vec_rot_left_u32(rotation , g_shift[index]);
        }
        index = -1;
        while (++index < 4)
            md5->buff[index] += md5->algo_buff[index];
    }
}

#include <unistd.h>
const char*             ssl_md5(const char* data)
{
    t_ssl_md5           md5;
	unsigned char*		message;
    const unsigned int  size = ft_strlen(data);
    
	md5 = (t_ssl_md5) {.buff[A]=RVECT_A, .buff[B]=RVECT_B, .buff[C]=RVECT_C, .buff[D]=RVECT_D};

    if (!(md5.bytes = append_padding((unsigned char **)&message, size, get_chunks_nb(size) * CHUNK_BYTE_SIZE, NULL)))
        return (NULL);
    ft_memcpy(message, data, size);
    ssl_md5_algorithm(&md5, message);
	free(message);
	return (int_to_str_u32(md5.buff, 36, 4, swap_u32bits));
}
