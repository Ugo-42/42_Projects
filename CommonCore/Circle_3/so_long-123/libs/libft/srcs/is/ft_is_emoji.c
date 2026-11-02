/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_emoji.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <ugwentzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:23:45 by ugwentzi          #+#    #+#             */
/*   Updated: 2025/02/11 09:26:57 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 }  Emoji Codepoint Ranges:
 } 0x1F600 to 0x1F64F => Emoticons
 } 0x1F300 to 0x1F5FF => Miscellaneous Symbols and Pictographs
 } 0x1F680 to 0x1F6FF => Transport and Map Symbols
 } 0x2600  to 0x26FF  => Miscellaneous Symbols
 } 0x2700  to 0x27BF  => Dingbats
 } 0x1F900 to 0x1F9FF => Supplemental Symbols and Pictographs
 } 0x1FA70 to 0x1FAFF => Extended Supplemental Symbols and Pictographs
 } 0x1FB00 to 0x1FBFF => Symbols and Pictographs Extended-A (Unicode 15.0+)
 } 0x1F1E6 to 0x1F1FF => Flags (Regional Indicator Symbols)
 } 0x2300  to 0x23FF  => Miscellaneous Technical
 } 0x1F170 to 0x1F251 => Enclosed Alphanumeric Symbols
 } 0x20E3, 0xFE0F    => Keycap Variants & Emoji Modifiers
 } 0xE0020 to 0xE007F => Tags (used for flags & modifiers)
*/

// Convert UTF-8 bytes to a Unicode codepoint
static unsigned int	ft_utf8_to_codepoint(const char *wide_c)
{
	unsigned char	*bytes;

	bytes = (unsigned char *)wide_c;
	if ((*bytes & 0x80) == 0)
		return (*bytes);
	else if ((*bytes & 0xE0) == 0xC0)
		return (((bytes[0] & 0x1F) << 6) | (bytes[1] & 0x3F));
	else if ((*bytes & 0xF0) == 0xE0)
		return (((bytes[0] & 0x0F) << 12) | ((bytes[1] & 0x3F) << 6)
			| (bytes[2] & 0x3F));
	else if ((*bytes & 0xF8) == 0xF0)
		return (((bytes[0] & 0x07) << 18) | ((bytes[1] & 0x3F) << 12)
			| ((bytes[2] & 0x3F) << 6) | (bytes[3] & 0x3F));
	return (0);
}

bool	ft_is_emoji(const char *wide_c)
{
	unsigned int	codepoint;

	codepoint = ft_utf8_to_codepoint(wide_c);
	if ((codepoint >= 0x1F600 && codepoint <= 0x1F64F)
		|| (codepoint >= 0x1F300 && codepoint <= 0x1F5FF)
		|| (codepoint >= 0x1F680 && codepoint <= 0x1F6FF)
		|| (codepoint >= 0x2600 && codepoint <= 0x26FF)
		|| (codepoint >= 0x2700 && codepoint <= 0x27BF)
		|| (codepoint >= 0x1F900 && codepoint <= 0x1F9FF)
		|| (codepoint >= 0x1FA70 && codepoint <= 0x1FAFF)
		|| (codepoint >= 0x1FB00 && codepoint <= 0x1FBFF)
		|| (codepoint >= 0x1F1E6 && codepoint <= 0x1F1FF)
		|| (codepoint >= 0x2300 && codepoint <= 0x23FF)
		|| (codepoint >= 0x1F170 && codepoint <= 0x1F251)
		|| (codepoint == 0x20E3 || codepoint == 0xFE0F)
		|| (codepoint >= 0xE0020 && codepoint <= 0xE007F))
		return (true);
	return (false);
}
