/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:18:33 by pablo             #+#    #+#             */
/*   Updated: 2020/10/22 18:39:32 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

const char*         	long_to_str(unsigned long* digest, unsigned long (*litle_endian)(unsigned long));
unsigned long           swap_u32bits(unsigned long aux);
unsigned long           swap_u64bits(unsigned long target);
unsigned int            vec_rot_left_u32(unsigned int vec, unsigned int rot);
unsigned int            vec_rot_right_u32(unsigned int vec, unsigned int rot);
unsigned long           vec_rot_left_u64(unsigned long vec, unsigned long rot);
unsigned long           vec_rot_right_u64(unsigned long vec, unsigned long rot);

#endif