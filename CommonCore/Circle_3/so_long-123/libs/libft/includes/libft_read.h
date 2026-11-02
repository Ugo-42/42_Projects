/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_read.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:09:23 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/05 14:25:43 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_READ_H
# define LIBFT_READ_H

/*┌───────┐
  │ read/ │
  └───────┘*/

void		gnl_reset_fd(int fd);
char		*get_next_line(int fd);

#endif
