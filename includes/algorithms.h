/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:18:33 by pablo             #+#    #+#             */
/*   Updated: 2020/10/23 20:28:06 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

const char*         	long_to_str_u64(unsigned long* digest, unsigned long (*litle_endian)(unsigned long));
const char*             int_to_str_u32(unsigned int* digest, unsigned int (*litle_endian)(unsigned int));
unsigned int            swap_u32bits(unsigned int aux);
unsigned long           swap_u64bits(unsigned long target);
unsigned int            vec_rot_left_u32(unsigned int vec, unsigned int rot);
unsigned int            vec_rot_right_u32(unsigned int vec, unsigned int rot);
unsigned long           vec_rot_left_u64(unsigned long vec, unsigned long rot);
unsigned long           vec_rot_right_u64(unsigned long vec, unsigned long rot);

#endif