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

#ifndef FXWOWFLUTTER_HPP_
#define FXWOWFLUTTER_HPP_

#include "Fx.hpp"

#define FX_WOWFLUTTER_WOWDEPTH 0
#define FX_WOWFLUTTER_WOWDEPTHRAND 1
#define FX_WOWFLUTTER_WOWRATE 2
#define FX_WOWFLUTTER_WOWRATERAND 3
#define FX_WOWFLUTTER_FLUTTERDEPTH 4
#define FX_WOWFLUTTER_FLUTTERDEPTHRAND 5
#define FX_WOWFLUTTER_FLUTTERRATE 6
#define FX_WOWFLUTTER_FLUTTERRATERAND 7

class FxWowFlutter : public Fx
{
public:
	FxWowFlutter () = delete;

	FxWowFlutter (RingBuffer<Stereo>** buffer, float* params, Pad* pads, double* framesPerStep) :
		Fx (buffer, params, pads),
		framesPerStepPtr (framesPerStep),
		framesPerStep (24000),
		wowDepth (0.0f), wowRate (1.0f), flutterDepth (0.0f), flutterRate (1.0f)
	{
		if (!framesPerStep) throw std::invalid_argument ("Fx initialized with framesPerStep nullptr");
	}

	virtual void init (const double position) override
	{
		Fx::init (position);
		const double r1 = bidist (rnd);
		wowDepth = 0.01 * LIMIT (params[SLOTS_OPTPARAMS + FX_WOWFLUTTER_WOWDEPTH] + r1 * params[SLOTS_OPTPARAMS + FX_WOWFLUTTER_WOWDEPTHRAND], 0.0, 1.0);
		const double r2 = bidist (rnd);
		wowRate = 0.0625 + 0.9375 * LIMIT (params[SLOTS_OPTPARAMS + FX_WOWFLUTTER_WOWRATE] + r2 * params[SLOTS_OPTPARAMS + FX_WOWFLUTTER_WOWRATERAND], 0.0, 1.0);
		const double r3 = bidist (rnd);
		flutterDepth = 0.01 * LIMIT (params[SLOTS_OPTPARAMS + FX_WOWFLUTTER_FLUTTERDEPTH] + r3 * params[SLOTS_OPTPARAMS + FX_WOWFLUTTER_FLUTTERDEPTHRAND], 0.0, 1.0);
		const double r4 = bidist (rnd);
		flutterRate = 1.0 + 15.0 * LIMIT (params[SLOTS_OPTPARAMS + FX_WOWFLUTTER_FLUTTERRATE] + r4 * params[SLOTS_OPTPARAMS + FX_WOWFLUTTER_FLUTTERRATERAND], 0.0, 1.0);
		framesPerStep = *framesPerStepPtr;
	}

	virtual Stereo process (const double position, const double size) override
	{
		const double wow = (0.5 - 0.5 * cos (2 * M_PI * position * wowRate)) * wowDepth;
		const double flutter = (0.5 - 0.5 * cos (2 * M_PI * position * flutterRate)) * flutterDepth;
		const double frame = framesPerStep * (wow + flutter);
		return getSample (frame);
	}

protected:
	double* framesPerStepPtr;
	double framesPerStep;
	float wowDepth;
	float wowRate;
	float flutterDepth;
	float flutterRate;
};

#endif /* FXWOWFLUTTER_HPP_ */
