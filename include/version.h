/**
 *  This file is part of Sweep.
 *
 *  Sweep is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Sweep is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with Sweep.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SWEEP_VERSION_H
#define SWEEP_VERSION_H

# define SWEEP_TITLE "Sweep"
# define SWEEP_AUTHOR "Zohar \"dotfloat\" Malamant"
# define SWEEP_DESC "A Minesweeper Clone"

# define SWEEP_VERMAJOR 0
# define SWEEP_VERMINOR 0
# define SWEEP_VERFULL "0.0"

# define SWEEP_FULLTITLE SWEEP_TITLE " - " SWEEP_DESC

# define SWEEP_WTEXT(x) L##x
# define SWEEP_WTITLE SWEEP_WTEXT(SWEEP_TITLE)
# define SWEEP_WAUTHOR SWEEP_WTEXT(SWEEP_AUTHOR)
# define SWEEP_WDESC SWEEP_WTEXT(SWEEP_DESC)
# define SWEEP_WVERFULL SWEEP_WTEXT(SWEEP_VERFULL)
# define SWEEP_WFULLTITLE SWEEP_WTEXT(SWEEP_WFULLTITLE)

#endif // SWEEP_VERSION_H
