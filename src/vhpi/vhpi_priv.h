//
//  Copyright (C) 2014  Nick Gasson
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  Additional permission under GNU GPL version 3 section 7
//
//  If you modify this Program, or any covered work, by linking or
//  combining it with the IEEE VHPI reference code (or a modified version
//  of that library), containing parts covered by the terms of the IEEE's
//  license, the licensors of this Program grant you additional permission
//  to convey the resulting work. Corresponding Source for a non-source
//  form of such a combination shall include the source code for the parts
//  of the IEEE VHPI reference code used as well as that of the covered work.
//

#ifndef _VHPI_PRIV_H
#define _VHPI_PRIV_H

#include "config.h"
#include "tree.h"

typedef enum {
   VHPI_START_OF_SIMULATION = 1034,
   VHPI_END_OF_SIMULATION   = 1035,
   VHPI_END_OF_PROCESSES    = 1018,
} vhpi_event_t;

#ifdef ENABLE_VHPI

void vhpi_load_plugins(tree_t top, const char *plugins);
void vhpi_event(vhpi_event_t kind);

#else  // ENABLE_VHPI

#define vhpi_load_plugins(top, plugins)
#define vhpi_event(kind)

#endif  // ENABLE_VHPI

#endif  // _VHPI_PRIV_H