/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:17:22 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/17 10:22:03 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.hpp"

class Harl
{
	private:
		void debug(void);
		void info(void);
		void warning(void);
		void error(void);

	public:
		void complain(t_string level);
};
