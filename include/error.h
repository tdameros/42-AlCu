/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 01:19:09 by tdameros          #+#    #+#             */
/*   Updated: 2024/03/30 01:19:10 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define GENERIC_ERROR "ERROR\n"
# define INVALID_MOVE_ERROR "The move must be between 1 and 3.\n"
# define MOVE_TOO_HIGH "Move too high.\n"

void	print_error(char *error);

#endif
