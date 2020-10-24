/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 18:45:38 by pablo             #+#    #+#             */
/*   Updated: 2020/10/23 19:17:56 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_error.h>
#include <stdio.h>

bool        print_error(void* check, char error_code, char* arg)
{
    if (!check)
    {
        if (error_code & ERROR_USAGE)
            printf("%s", MSG_USAGE);
        if (error_code & ERROR_ALGONAME)
            printf(MSG_ALGONAME, arg);

        return (false);
    }
    return (true);
}