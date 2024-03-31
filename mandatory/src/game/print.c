/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:23:19 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/31 19:28:05 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

#include "parsing/get_next_line.h"

int	ft_putstr(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

int	ft_putu16(uint16_t n)
{
	char	c;

	if (n > 9 && ft_putu16(n / 10) == -1)
		return (-1);
	c = n % 10 + '0';
	return (write(1, &c, 1));
}
