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

#ifndef FXTAPESPEED_HPP_
#define FXTAPESPEED_HPP_

#include "Fx.hpp"

#define FX_TAPESPEED_SPEED 0
#define FX_TAPESPEED_SPEEDRAND 1

class FxTapeSpeed : public Fx
{
public:
	FxTapeSpeed () = delete;

	FxTapeSpeed (RingBuffer<Stereo>** buffer, float* params, Pad* pads, double* framesPerStep) :
		Fx (buffer, params, pads),
		framesPerStepPtr (framesPerStep),
		framesPerStep (24000),
		speed (1.0)
	{
		if (!framesPerStep) throw std::invalid_argument ("Fx initialized with framesPerStep nullptr");
	}

	virtual void init (const double position) override
	{
		Fx::init (position);
		const double r = bidist (rnd);
		speed = LIMIT (params[SLOTS_OPTPARAMS + FX_TAPESPEED_SPEED] + r * params[SLOTS_OPTPARAMS + FX_TAPESPEED_SPEEDRAND], 0.0, 1.0);
		framesPerStep = *framesPerStepPtr;
	}

	virtual Stereo process (const double position, const double size) override
	{
		return getSample ((1.0 - speed) * framesPerStep * std::min (position, double (NR_STEPS)));
	}

protected:
	double* framesPerStepPtr;
	double framesPerStep;
	double speed;
};

#endif /* FXTAPESPEED_HPP_ */
