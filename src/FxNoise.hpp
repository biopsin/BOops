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

#ifndef FXNOISE_HPP_
#define FXNOISE_HPP_

#include "Fx.hpp"

#ifndef DB2CO
#define DB2CO(x) pow (10, 0.05 * (x))
#endif

#define FX_NOISE_AMP 0
#define FX_NOISE_AMPRAND 1

class FxNoise : public Fx
{
public:
	FxNoise () = delete;

	FxNoise (RingBuffer<Stereo>** buffer, float* params, Pad* pads) :
		Fx (buffer, params, pads),
		amp (0.0f)
	{}

	virtual void init (const double position) override
	{
		Fx::init (position);
		const double r = bidist (rnd);
		const float db = -90.0 + 102.0 * LIMIT (params[SLOTS_OPTPARAMS + FX_NOISE_AMP] + r * params[SLOTS_OPTPARAMS + FX_NOISE_AMPRAND], 0.0, 1.0);
		amp = DB2CO (db);
	}

	virtual Stereo process (const double position, const double size) override
	{
		return Stereo {unidist (rnd) * amp, unidist (rnd) * amp};
	}

protected:
	float amp;

};

#endif /* FXNOISE_HPP_ */
