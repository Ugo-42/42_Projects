#┌─────────────────────────────────────────────────────────────────────────────┐#
#│                                                                             │#
#│   config.mk                                              ▒▒▒▒    ▒▒▒▒       │#
#│                                                          ▒▒▒▒    ▒▒▒▒       │#
#│   By: ugwentzi <ugwentzi@student.42.fr>                      ▒▒▒▒           │#
#│                                                            ▒▒▒▒▒▒▒▒         │#
#│   Created: 2026/02/17 11:21:37 by ugwentzi                 ▒▒▒▒▒▒▒▒         │#
#│   Updated: 2026/02/17 11:21:37 by ugwentzi                 ▒▒    ▒▒         │#
#│                                                                             │#
#└─────────────────────────────────────────────────────────────────────────────┘#

# Set the rule all by default (for `make` without args)
.DEFAULT_GOAL := all

# Silence the `Entering/Leaving directory` message
MAKEFLAGS += --no-print-directory
