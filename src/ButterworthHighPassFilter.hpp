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

#ifndef BUTTERWORTHHIGHPASSFILTER_HPP_
#define BUTTERWORTHHIGHPASSFILTER_HPP_

#include "ButterworthFilter.hpp"

class ButterworthHighPassFilter : public ButterworthFilter
{
public:
	ButterworthHighPassFilter (const double rate, const double cutoff, const int order) :
		ButterworthFilter (order)
	
	{
		set (rate, cutoff, order);
	}

	void set (const double rate, const double cutoff, const int order)
	{

		this->order = order;
		o2 = order / 2;
		f1 = -2;
		const double a = tan (M_PI * cutoff / rate);
		const double a2 = a * a;

		for (int i = 0; i < o2; ++i)
		{
			const double r = sin (M_PI * (2.0 * double (i) + 1.0) / (2.0 * double (order)));
			const double s = a2 + 2.0 * a * r + 1.0;
			coeff0[i] = 1.0 / s;
			coeff1[i] = 2.0 * (1.0 - a2) / s;
			coeff2[i] = -(a2 - 2.0 * a * r + 1.0) / s;
		}
	}
};

#endif /* BUTTERWORTHHIGHPASSFILTER_HPP_ */
