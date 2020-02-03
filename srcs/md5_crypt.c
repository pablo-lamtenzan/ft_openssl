/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_crypt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 17:40:54 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/02 20:19:49 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.ecured.cu/MD5
//https://github.com/ArtemisKS/ft_ssl_md5/tree/master/src

# include <md5.h>

/*
** for each message (32 bytes * 16 words = 512 bytes) must uptate vectors[] follwing this algo :

    crypt = vectors[B] + ((vectors[A] + vec_fct(vectors[B], vectors[C], vectors[D]) + kernels[k] + chunk[i]) <<< s)
    
    where k follow just math trigo constants values, i is the iteration and s is shift consts rotations val index
    
*/

void        md5_message_crypt(unsigned *vectors, unsigned *chunk)
{
    unsigned    crypt;
    short       i;
    short       k;
    short       s;

    i = -1;
    while (++i < MD5_CYCLE_IT - 1) // - 1 cause is ++i when i = 65 we are on 64h iter
    {
        if (i < 16 && (crypt = vec_f(vectors[B], vectors[C], vectors[D])))
            k = i;
        else if (i < 32 && (crypt = vec_g(vectors[B], vectors[C], vectors[D])))
            k = (i * 5 + 1) % 16;
        else if (i < 48 && (crypt = vec_h(vectors[B], vectors[C], vectors[D])))
            k = (i * 3 + 5) % 16;
        else if ((crypt = vec_i(vectors[B], vectors[C], vectors[D])))
            k = (i * 7) % 16;
        crypt += vectors[A] + g_kernel[k] + chunk[i];
        vectors[A] = vectors[D];
        vectors[D] = vectors[C];
        vectors[C] = vectors[B];
        vectors[B] += vec_rot_left(crypt, g_shitf[i]); // crypt is updated add 
    }
}

void        md5_crypt(t_md5 *data, unsigned char *text) // uchar cause is a str of ascci code
{
    const chunk_nb = data->bits / 64;
    int i;
    int j;

    i = -1;
    j = 0;
    while (++i < chunk_nb)
    {
        ft_mencpy(data->buff_saved, data->buff, sizeof(data->buff_saved));
        md5_message_crypt(data->buff, (unsigned *)(text + j)); // make packets of 4 uchar = 1 uint = 64 bits
        j += 64;
        data->buff_saved[A] += data->buff[A]; // add the messages vectors
        data->buff_saved[B] += data->buff[B];
        data->buff_saved[C] += data->buff[C];
        data->buff_saved[D] += data->buff[D];
    }
}

// TO END :

unsigned    md5_init_crypt(t_md5 *data, char *text)
{
    unsigned char    *ascii_codes;

    ascii_codes = ft_calloc(("total size ?" + 64)) // total size + last 64 bytes for size ?????
    ft_memcpy(ascii_codes, text, "total size ?");
    data->bytes = "fct";
    data->bits = data->bytes * 8;
    md5_message_crypt(data, ascii_codes);
    free(ascii_codes);
    return (data->buff_saved); // no need to digest
}

char        md5(char *text) /*word parsed ? */
{
    t_md5       data;
    unsigned    res;

    data.buff[A] = RVECT_A;
    data.buff[B] = RVECT_B;
    data.buff[C] = RVECT_C;
    data.buff[D] = RVECT_D;
    
    /* error check */
    if (!(res = md5_init(&data)))
        return (0);

    /* print hash */
    return (1);
}

/* have to parse and give the text to md5, it will convert this text into numerical nb the cript it */