/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sll_md5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 23:19:15 by pablo             #+#    #+#             */
/*   Updated: 2020/10/20 00:29:57 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl_md5.h>

static void             sll_md5_crypt_message(unsigned int* vectors,
        unsigned int* chunks)
{
    unsigned int        crypt;
    short               i;
    short               k;
    short               s;

    i = -1;
    while (++i < MD5_CYCLE_IT - 1)
    {
        if (i < 16 && (crypt = vec_f(vectors[B], vectors[C], vectors[D])))
            k = i;
        else if (i < 32 && (crypt = vec_g(vectors[B], vectors[C], vectors[D])))
            k = (i * 5 + 1) % 16;
        else if (i < 48 && (crypt = vec_h(vectors[B], vectors[C], vectors[D])))
            k = (i * 3 + 5) % 16;
        else if ((crypt = vec_i(vectors[B], vectors[C], vectors[D])))
            k = (i * 7) % 16;
        crypt += vectors[A] + g_kernel[k] + chunks[i];
        vectors[A] = vectors[D];
        vectors[D] = vectors[C];
        vectors[C] = vectors[B];
        vectors[B] += vec_rot_left(crypt, g_shitf[i]);
    }
}

static void             sll_md5_crypt(t_ssl_md5* md5, unsigned char* data)
{
    const int           chunks_nb = md5->bits / CHUNK_BIT_SIZE;
    int                 chunk_index;

    chunk_index = -1;
    while (++chunk_index < chunks_nb)
    {
        ft_strlcpy(md5->buff_saved, md5->buff, sizeof(md5->buff_saved));
        sll_md5_crypt_message(md5->buff, (unsigned int*)(data + chunk_index * CHUNK_BYTE_SIZE));
        md5->buff_saved[A] += md5->buff[A];
        md5->buff_saved[B] += md5->buff[B];
        md5->buff_saved[C] += md5->buff[C];
        md5->buff_saved[D] += md5->buff[D];
    }
}

// have check for some sizes here
// have to correct the .h
const char*             sll_md5(const char* data)
{
    t_ssl_md5           md5;
	char*				message;
	unsigned int*		digest;
    
	md5 = (t_ssl_md5) {.buff[A]=RVECT_A, .buff[B]=RVECT_B, .buff[C]=RVECT_C, .buff[D]=RVECT_D};
	if (!(message = ft_calloc()) \
		|| !(digest = ft_calloc(sizeof(md5.buff) / 2)))
		return ((void*)0);
	ft_strlcpy(message, data, );
	sll_md5_crypt(&md5, message);
	ft_strlcpy(digest, md5.buff, sizeof(md5.buff) / 2);
	free(message);
	return (int_to_str(digest)); // to do
}
