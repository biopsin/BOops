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

#ifndef FXFILTER_HPP_
#define FXFILTER_HPP_

#include "Fx.hpp"
#include "ButterworthBandPassFilter.hpp"

#define FX_FILTER_LOW 0
#define FX_FILTER_LOWRAND 1
#define FX_FILTER_HIGH 2
#define FX_FILTER_HIGHRAND 3
#define FX_FILTER_ORDER 4

class BOops; // Forward declaration

class FxFilter : public Fx
{
public:
	FxFilter () = delete;

	FxFilter (RingBuffer<Stereo>** buffer, float* params, Pad* pads, double rate) :
		Fx (buffer, params, pads),
		rate (rate), filter (48000, 20, 20000, 8) {}

	virtual void init (const double position) override
	{
		Fx::init (position);
		const double r1 = bidist (rnd);
		double low = 20.0f + 19980.0f * pow (LIMIT (params[SLOTS_OPTPARAMS + FX_FILTER_LOW] + r1 * params[SLOTS_OPTPARAMS + FX_FILTER_LOWRAND], 0.0, 1.0), 4.0);
		const double r2 = bidist (rnd);
		double high = 20.0f + 19980.0f * pow (LIMIT (params[SLOTS_OPTPARAMS + FX_FILTER_HIGH] + r2 * params[SLOTS_OPTPARAMS + FX_FILTER_HIGHRAND], 0.0, 1.0), 4.0);
		int order = 2 * int (LIMIT (1.0 + 8.0 * params[SLOTS_OPTPARAMS + FX_FILTER_ORDER], 1.0, 8.0));
		filter = ButterworthBandPassFilter (rate, low, high, order);
	}

	virtual Stereo process (const double position, const double size) override
	{
		return filter.push ((**buffer).front());
	}

protected:
	double rate;
	ButterworthBandPassFilter filter;
};

#endif /* FXFILTER_HPP_ */
