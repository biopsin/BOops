/* B.Oops
 * Glitch effect sequencer LV2 plugin
 *
 * Copyright (C) 2020 by Sven Jähnichen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef PATTERN_HPP_
#define PATTERN_HPP_

#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include "Definitions.hpp"
#include "Ports.hpp"
#include "PadMessage.hpp"
#include "Journal.hpp"


class Pattern
{
public:
        void clear ();
        Pad getPad (const size_t row, const size_t step) const;
        void setPad (const size_t row, const size_t step, const Pad& pad);
        std::vector<PadMessage> undo ();
        std::vector<PadMessage> redo ();
        void store ();
        std::string toString (const std::array<std::string, 2 + sizeof (Pad) / sizeof (float)>& symbols) const;
        void fromString (const std::string& text, const std::array<std::string, 2 + sizeof (Pad) / sizeof (float)>& symbols);
private:
        Journal<std::vector<PadMessage>, MAXUNDO> journal;
        std::array<std::array<Pad, NR_STEPS>, NR_SLOTS> pads;
        struct
        {
                std::vector<PadMessage> oldMessage;
                std::vector<PadMessage> newMessage;
        } changes;
};

#endif /* PATTERN_HPP_ */
