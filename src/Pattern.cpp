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

#include "Pattern.hpp"

#ifndef LIMIT
#define LIMIT(val, min, max) (val < min ? min : (val < max ? val : max))
#endif /* LIMIT */

#include "BUtilities/to_string.hpp"
#include "BUtilities/stof.hpp"

void Pattern::clear ()
{
	Pad pad0 = Pad ();
        std::array<bool, NR_PIANO_KEYS + 1> k0;
        k0.fill (false);

	changes.oldMessage.clear ();
	changes.newMessage.clear ();
	journal.clear ();

	for (int r = 0; r < NR_SLOTS; ++r)
	{
		for (int s = 0; s < NR_STEPS; ++s) setPad (r, s, pad0);
                setShape (r, Shape<SHAPE_MAXNODES>());
                setKeys (r, k0);
	}

	store ();
}

Pad Pattern::getPad (const size_t row, const size_t step) const
{
	return pads[LIMIT (row, 0, NR_SLOTS)][LIMIT (step, 0, NR_STEPS - 1)];
}
void Pattern::setPad (const size_t row, const size_t step, const Pad& pad)
{
	size_t r = LIMIT (row, 0, NR_SLOTS - 1);
	size_t s = LIMIT (step, 0, NR_STEPS - 1);
	changes.oldMessage.push_back (Action (r, s, BUtilities::makeAny<Pad> (pads[r][s])));
	changes.newMessage.push_back (Action (r, s, BUtilities::makeAny<Pad> (pad)));
	pads[r][s] = pad;
}

Shape<SHAPE_MAXNODES> Pattern::getShape(const size_t row) const
{
        return shapes[LIMIT (row, 0, NR_SLOTS - 1)];
}

void Pattern::setShape (const size_t row, const Shape<SHAPE_MAXNODES>& shape)
{
        size_t r = LIMIT (row, 0, NR_SLOTS - 1);
	changes.oldMessage.push_back (Action (r, 0, BUtilities::makeAny<Shape<SHAPE_MAXNODES>> (shapes[r])));
	changes.newMessage.push_back (Action (r, 0, BUtilities::makeAny<Shape<SHAPE_MAXNODES>> (shape)));
	shapes[r] = shape;
}

std::array<bool, NR_PIANO_KEYS + 1> Pattern::getKeys (const size_t row) const
{
        return keys[LIMIT (row, 0, NR_SLOTS - 1)];
}

bool Pattern::getKey (const size_t row, const size_t note) const
{
        return keys[LIMIT (row, 0, NR_SLOTS - 1)] [LIMIT (note, 0, NR_PIANO_KEYS)];
}

void Pattern::setKeys (const size_t row, const std::array<bool, NR_PIANO_KEYS + 1>& ks)
{
        size_t r = LIMIT (row, 0, NR_SLOTS - 1);
	changes.oldMessage.push_back (Action (r, 0, BUtilities::makeAny<std::array<bool, NR_PIANO_KEYS + 1>> (keys[r])));
	changes.newMessage.push_back (Action (r, 0, BUtilities::makeAny<std::array<bool, NR_PIANO_KEYS + 1>> (ks)));
	keys[r] = ks;
}

void Pattern::setKey (const size_t row, const size_t note, const bool state)
{
        size_t r = LIMIT (row, 0, NR_SLOTS - 1);
        size_t n = LIMIT (note, 0, NR_PIANO_KEYS);
        std::array<bool, NR_PIANO_KEYS + 1> nks = getKeys (row);
        nks[n] = state;
	changes.oldMessage.push_back (Action (r, 0, BUtilities::makeAny<std::array<bool, NR_PIANO_KEYS + 1>> (keys[r])));
	changes.newMessage.push_back (Action (r, 0, BUtilities::makeAny<std::array<bool, NR_PIANO_KEYS + 1>> (nks)));
	keys[r] = nks;
}

std::vector<Action> Pattern::undo ()
{
	store ();

	std::vector<Action> actions = journal.undo ();
	std::reverse (actions.begin (), actions.end ());
	for (Action const& a : actions)
	{
		size_t r = LIMIT (a.row, 0, NR_SLOTS);
		size_t s = LIMIT (a.step, 0, NR_STEPS);
		if (a.content.test<Pad>()) pads[r][s] = a.content.get<Pad>();
                else if (a.content.test<Shape<SHAPE_MAXNODES>>()) shapes[r] = a.content.get<Shape<SHAPE_MAXNODES>>();
                else if (a.content.test<std::array<bool, NR_PIANO_KEYS + 1>>()) keys[r] = a.content.get<std::array<bool, NR_PIANO_KEYS + 1>>();
	}

	return actions;
}

std::vector<Action> Pattern::redo ()
{
	store ();

	std::vector<Action> actions = journal.redo ();
	for (Action const& a : actions)
	{
		size_t r = LIMIT (a.row, 0, NR_SLOTS);
		size_t s = LIMIT (a.step, 0, NR_STEPS);
		if (a.content.test<Pad>()) pads[r][s] = a.content.get<Pad>();
                else if (a.content.test<Shape<SHAPE_MAXNODES>>()) shapes[r] = a.content.get<Shape<SHAPE_MAXNODES>>();
                else if (a.content.test<std::array<bool, NR_PIANO_KEYS + 1>>()) keys[r] = a.content.get<std::array<bool, NR_PIANO_KEYS + 1>>();
	}

	return actions;
}

void Pattern::store ()
{
	if (changes.newMessage.empty ()) return;

	journal.push (changes.oldMessage, changes.newMessage);
	changes.oldMessage.clear ();
	changes.newMessage.clear ();
}

std::string Pattern::toString (const std::array<std::string, 2 + sizeof (Pad) / sizeof (float)>& symbols) const
{
        std::string text = "";

        for (size_t r = 0; r < pads.size(); ++r)
        {
                for (size_t s = 0; s < pads[r].size(); ++s)
                {
                        const Pad& p = pads[r][s];
                        if (p != Pad())
                        {
                                if (text != "") text += ";\n";
                                text += symbols[0] + ":" + std::to_string (r) + "; " + symbols[1] + ":" + std::to_string (s) + ";";
                                const float* values = (const float*)&p;
                                for (size_t i = 2; i < symbols.size(); ++i)
                                {
                                        text += " " + symbols[i] + ":" + BUtilities::to_string (values[i - 2], "%1.3f");
                                        if (i != symbols.size() - 1) text += ";";
                                }
                        }
                }
        }

        text += "\n";

        return text;
}

void Pattern::fromString (const std::string& text, const std::array<std::string, 2 + sizeof (Pad) / sizeof (float)>& symbols)
{
        // Clear old data
        for (int r = 0; r < NR_SLOTS; ++r)
	{
		for (int s = 0; s < NR_STEPS; ++s)
		{
			setPad (r, s, Pad());
		}
	}

        // Parse from string
        size_t pos = 0;
        while (pos < text.size())
        {
                // Look for mandatory row
                size_t r = -1;
                size_t strPos = text.find (symbols[0] + ":", pos);
                size_t nextPos = 0;
                if (strPos == std::string::npos) break;	// No row found => end
                if (strPos + symbols[0].size() + 1 > text.size()) break;	// Nothing more after row => end
                pos = strPos + symbols[0].size() + 1;
                try {r = BUtilities::stof (text.substr (pos, 63), &nextPos);}
                catch  (const std::exception& e)
                {
                        fprintf (stderr, "BOops.lv2#GUI: Import pattern incomplete. Can't parse row nr from \"%s...\"\n", text.substr (pos, 63).c_str());
                        break;
                }

                pos += nextPos;

                if (r >= pads.size())
                {
                        fprintf (stderr, "BOops.lv2#GUI: Import pattern incomplete. Invalid row nr %li.\n", r);
                        break;
                }

                // Look for mandatory step
                size_t s = -1;
                strPos = text.find (symbols[1] + ":", pos);
                nextPos = 0;
                if (strPos == std::string::npos) break;	// No step found => end
                if (strPos + symbols[1].size() + 1 > text.size()) break;	// Nothing more after step => end
                pos = strPos + symbols[1].size() + 1;
                try {s = BUtilities::stof (text.substr (pos, 63), &nextPos);}
                catch  (const std::exception& e)
                {
                        fprintf (stderr, "BOops.lv2#GUI: Import pattern incomplete. Can't parse step nr from \"%s...\"\n", text.substr (pos, 63).c_str());
                        break;
                }

                pos += nextPos;
                if (s >= pads[r].size())
                {
                        fprintf (stderr, "BOops.lv2#GUI: Import pattern incomplete. Invalid step nr %li.\n", s);
                        break;
                }

                // Look for pad data
                Pad p = Pad();
                float* padValues = (float*)&p;
                for (size_t i = 2; i < symbols.size(); ++i)
                {
                        nextPos = 0;
                        strPos = text.find (symbols[i] + ":", pos);
                        if (strPos == std::string::npos) continue;	// Keyword not found => next keyword
                        if (strPos + symbols[i].size() + 1 > text.size())	// Nothing more after keyword => end
                        {
                                pos = std::string::npos;
                                break;
                        }
                        pos = strPos + symbols[0].size() + 1;
                        float val = 0;
                        try {val = BUtilities::stof (text.substr (pos, 63), &nextPos);}
                        catch  (const std::exception& e)
                        {
                                fprintf (stderr, "BOops.lv2#GUI: Import pattern incomplete. Can't parse %s from \"%s...\"\n",
                                                 symbols[i].c_str(), text.substr (pos, 63).c_str());
                                break;
                        }

                        switch (i)
                        {
                                case 2:	val = LIMIT (val, 0, 1);
                                        break;

                                case 3:	val = LIMIT (val, 1, NR_STEPS - s);
                                        break;

                                case 4:	val = LIMIT (val, 0, 1);
                                        break;

                                default:break;
                        }

                        pos += nextPos;

                        padValues[i - 2] = val;
                }

                setPad (r, s, p);
        }

        store ();
}
