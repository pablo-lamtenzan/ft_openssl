/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:19:15 by pablo             #+#    #+#             */
/*   Updated: 2020/10/23 20:46:07 by pablo            ###   ########.fr       */
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

static void             ssl_md5_crypt_message(unsigned int* vectors,
        unsigned int* chunks)
{
    unsigned int        crypt;
    short               iterator;
    short               k;

    iterator = 0;
    while (++iterator < MD5_CYCLE_IT)
    {
        if (iterator < 16 && (crypt = vec_f(vectors[B], vectors[C], vectors[D])))
            k = iterator;
        else if (iterator < 32 && (crypt = vec_g(vectors[B], vectors[C], vectors[D])))
            k = (iterator * 5 + 1) % 16;
        else if (iterator < 48 && (crypt = vec_h(vectors[B], vectors[C], vectors[D])))
            k = (iterator * 3 + 5) % 16;
        else if (crypt = vec_i(vectors[B], vectors[C], vectors[D]))
            k = (iterator * 7) % 16;
        crypt += vectors[A] + g_kernel[iterator] + chunks[k];
        vectors[A] = vectors[D];
        vectors[D] = vectors[C];
        vectors[C] = vectors[B];
        vectors[B] += vec_rot_left_u32(crypt, g_shift[iterator]);
    }
}

static void             ssl_md5_crypt(t_ssl_md5* md5, unsigned char* data)
{
    const unsigned int  chunks_nb = md5->bits / CHUNK_BIT_SIZE;
    int                 chunk_index;

    chunk_index = -1;
    while (++chunk_index < chunks_nb)
    {
        ft_memcpy(md5->algo_buff, md5->buff, sizeof(md5->algo_buff));
        ssl_md5_crypt_message(md5->algo_buff, (unsigned int*)(data + chunk_index * CHUNK_BYTE_SIZE));
        md5->buff[A] += md5->algo_buff[A];
        md5->buff[B] += md5->algo_buff[B];
        md5->buff[C] += md5->algo_buff[C];
        md5->buff[D] += md5->algo_buff[D];
    }
}

/* mesage lenght must be "n" bits where n = (512 * z) + 448 and z is any number */
/* format of the msg : [message][1][pagging of 0s][msg_len] */
static unsigned int     append_padding(char** message, unsigned int message_size)
{
    unsigned long       size;
    unsigned int        msg_len;

    size = message_size * CHAR_BIT;
    while (++size % CHUNK_BIT_SIZE != 448)
        ;
    msg_len = size;
    size /= CHAR_BIT;
    (*message)[size] = 1;
    ft_memcpy((*message) + size, &msg_len, 4);
    return (size + 8);
}

const char*             ssl_md5(const char* data)
{
    t_ssl_md5           md5;
	char*				message;
    const unsigned int  size = ft_strlen(data);
    
	md5 = (t_ssl_md5) {.buff[A]=RVECT_A, .buff[B]=RVECT_B, .buff[C]=RVECT_C, .buff[D]=RVECT_D};
	if (!(message = ft_calloc(size + CHUNK_BYTE_SIZE, sizeof(char))))
		return ((void*)0);
	ft_memcpy(message, data, size);
    md5.bytes = append_padding(&message, size);
    md5.bits = md5.bytes * CHAR_BIT;
	ssl_md5_crypt(&md5, message);
    /*for (int i = 0 ; i < 4; i++)
        printf("%u\n", digest[i]); */
	free(message);
	return (int_to_str_u32(md5.buff, swap_u32bits));
}
