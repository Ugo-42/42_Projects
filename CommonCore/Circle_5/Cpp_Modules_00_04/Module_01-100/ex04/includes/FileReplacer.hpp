/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileReplacer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:17:31 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/10/14 13:17:32 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

class FileReplacer
{
	private:
		t_string _filename;
		t_string _s1;
		t_string _s2;
		t_string* _afterLines;
		int _lineCount;

		int countLines() const;

	public:
		FileReplacer(const t_string& filename, const t_string& s1, const t_string& s2);
		~FileReplacer();

		void readAndReplace();
		void printChanges() const;
};
