/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:23:48 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/12/15 13:50:38 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class ScalarConverter
{
	private:
		ScalarConverter() {}

	public:
		static void	convert(const std::string& literal);
};
