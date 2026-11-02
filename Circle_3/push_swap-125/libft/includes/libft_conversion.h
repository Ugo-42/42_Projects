/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_conversion.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:58:18 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/01/21 13:39:04 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_CONVERSION_H
# define LIBFT_CONVERSION_H

# include <stdbool.h>
# include <stdint.h>

/*┌─────────────┐
  │ conversion/ │
  └─────────────┘*/

int		ft_atoi(const char *str);
int		ft_tolower(int c);
int		ft_toupper(int c);

char	*ft_addrtoa(uintptr_t addr, bool uppercase);
char	*ft_ctoa(char c);
char	*ft_itoa(int n);
char	*ft_utoa(unsigned int n);
char	*ft_xtoa(unsigned long n, bool uppercase);

#endif
