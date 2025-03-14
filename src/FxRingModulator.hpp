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

#ifndef FXRINGMOD_HPP_
#define FXRINGMOD_HPP_

#include "Fx.hpp"

#define FX_RINGMOD_RATIO 0
#define FX_RINGMOD_RATIORAND 1
#define FX_RINGMOD_FREQ 2
#define FX_RINGMOD_FREQRAND 3
#define FX_RINGMOD_ENV 4

class FxRingModulator : public Fx
{
public:
	FxRingModulator () = delete;

	FxRingModulator (RingBuffer<Stereo>** buffer, float* params, Pad* pads, double* framesPerStep, double rate) :
		Fx (buffer, params, pads),
		rate (rate),
		framesPerStepPtr (framesPerStep),
		framesPerStep (24000),
		ratio (0.5f), freq (100.0), env (SINE_WAVE)
	{
		if (!framesPerStep) throw std::invalid_argument ("Fx initialized with framesPerStep nullptr");
	}

	virtual void init (const double position) override
	{
		Fx::init (position);
		const double r1 = bidist (rnd);
		ratio = LIMIT (params[SLOTS_OPTPARAMS + FX_RINGMOD_RATIO] + r1 * params[SLOTS_OPTPARAMS + FX_RINGMOD_RATIORAND], 0.0, 1.0);
		const double r2 = bidist (rnd);
		freq = 20000.0f * pow (LIMIT (params[SLOTS_OPTPARAMS + FX_RINGMOD_FREQ] + r2 * params[SLOTS_OPTPARAMS + FX_RINGMOD_FREQRAND], 0.0, 1.0), 4.0);
		env = BOopsWaveformIndex (LIMIT (int (round (params[SLOTS_OPTPARAMS + FX_RINGMOD_ENV] * 8)), 0, 4));
		framesPerStep = *framesPerStepPtr;
	}

	virtual Stereo process (const double position, const double size) override
	{
		const Stereo s0 = (**buffer).front();
		float f = 0.0f;
		double t = position * framesPerStep / rate;
		switch (env)
		{
			case SINE_WAVE:			f = sin (2.0 * M_PI * t * freq);
									break;

			case TRIANGLE_WAVE:		f = (fmod (t * freq, 1.0) < 0.5 ? 4.0 * fmod (t * freq, 1.0) - 1.0 : 3.0 - 4.0 * fmod (t * freq, 1.0));
									break;

			case SQUARE_WAVE:		f = (fmod (t * freq, 1.0) < 0.5 ? 1.0 : -1.0);
									break;

			case SAW_WAVE:			f = 2.0 * fmod (t * freq, 1.0) - 1.0;
									break;

			case REVERSE_SAW_WAVE:	f = 1.0 - 2.0 * fmod (t * freq, 1.0);
									break;
		};

		return BUtilities::mix<Stereo> (s0, s0 * f, ratio);
	}

protected:
	double rate;
	double* framesPerStepPtr;
	double framesPerStep;
	float ratio;
	float freq;
	BOopsWaveformIndex env;

};

#endif /* FXRINGMOD_HPP_ */
