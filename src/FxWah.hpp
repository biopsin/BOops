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

#ifndef FXWAH_HPP_
#define FXWAH_HPP_

#include "Fx.hpp"
#include "ButterworthBandPassFilter.hpp"
#include "Shape.hpp"

#define FX_WAH_CFREQ 0
#define FX_WAH_CFREQRAND 1
#define FX_WAH_DEPTH 2
#define FX_WAH_DEPTHRAND 3
#define FX_WAH_WIDTH 4
#define FX_WAH_WIDTHRAND 5
#define FX_WAH_ORDER 6
#define FX_WAH_REACH 7

class FxWah : public Fx
{
public:
	FxWah () = delete;

	FxWah (RingBuffer<Stereo>** buffer, float* params, Pad* pads, double rate, Shape<SHAPE_MAXNODES>* shape) :
		Fx (buffer, params, pads),
		rate (rate),
		shape (shape),
		cFreq (500.0f),
		depth (0.5f),
		width (0.1f),
		order (2),
		reach (1.0),
		filter (48000, 20, 20000, 8)
	{
		if (!shape) throw std::invalid_argument ("Fx initialized with shape nullptr");
	}

	virtual void init (const double position) override
	{
		Fx::init (position);
		const double r3 = bidist (rnd);
		cFreq = 20.0 + 19980.0 * pow (LIMIT (params[SLOTS_OPTPARAMS + FX_WAH_CFREQ] + r3 * params[SLOTS_OPTPARAMS + FX_WAH_CFREQRAND], 0.0, 1.0), 3.0);
		const double r4 = bidist (rnd);
		depth = (params ? LIMIT (params[SLOTS_OPTPARAMS + FX_WAH_DEPTH] + r4 * params[SLOTS_OPTPARAMS + FX_WAH_DEPTHRAND], 0.0, 1.0) : 0.5);
		const double r5 = bidist (rnd);
		width = (params ? LIMIT (params[SLOTS_OPTPARAMS + FX_WAH_WIDTH] + r5 * params[SLOTS_OPTPARAMS + FX_WAH_WIDTHRAND], 0.0, 1.0) : 0.1);
		order = 2 * int (LIMIT (1.0 + 8.0 * params[SLOTS_OPTPARAMS + FX_WAH_ORDER], 0, 8));
		reach = 1.0 + LIMIT (32.0 * params [SLOTS_OPTPARAMS + FX_WAH_REACH], 0, 31);

		const float m = (shape ? shape->getMapValue (0): 0.0);
		const float f = cFreq * (1 + depth * m);
		filter = ButterworthBandPassFilter (rate, f * (1.0 - 0.5 * width), f * (1.0 + 0.5 * width), order);
	}

	virtual Stereo process (const double position, const double size) override
	{
		const Stereo s0 = (**buffer).front();
		const float m = shape->getMapValue (fmod (position / reach, 1.0));
		const float f = cFreq * (1.0f + depth * m);
		const float fmin = LIMIT (f * (1.0f - width), 0.0f, 20000.0f);
		const float fmax = LIMIT (f * (1.0f + width), 0.0f, 20000.0f);
		filter.set (rate, fmin, fmax, order);
		return filter.push (s0);
	}

protected:
	double rate;
	Shape<SHAPE_MAXNODES>* shape;
	float cFreq;
	float depth;
	float width;
	int order;
	double reach;
	ButterworthBandPassFilter filter;
};

#endif /* FXWAH_HPP_ */
