/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:45:52 by pablo             #+#    #+#             */
/*   Updated: 2020/10/23 19:17:27 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

#include <stdbool.h>
#include <stdlib.h>

#define ERROR_USAGE         1
#define ERROR_ALGONAME      2

#define MSG_USAGE           "usage: ft_ssl command [command opts] [command args]\n"
#define MSG_ALGONAME        "ft_ssl: Error: %s is an invalid command.\n\nStandard commands:\n\nMessage Digest commands:\nmd5\nsha256\nsha512\nwirthlpool\n\nCipher commands:\n"

bool        print_error(void* check, char error_code, char* arg);

#endif