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

#ifndef FXBALANCE_HPP_
#define FXBALANCE_HPP_

#include "Fx.hpp"

#define FX_BALANCE_BALANCE 0
#define FX_BALANCE_BALANCERAND 1



class FxBalance : public Fx
{
public:
	FxBalance () = delete;

	FxBalance (RingBuffer<Stereo>** buffer, float* params, Pad* pads) :
		Fx (buffer, params, pads),
		balance (0.0f)
	{}

	virtual void init (const double position) override
	{
		Fx::init (position);
		const double r = bidist (rnd);
		balance = LIMIT (2.0 * (params[SLOTS_OPTPARAMS + FX_BALANCE_BALANCE] + r * params[SLOTS_OPTPARAMS + FX_BALANCE_BALANCERAND]) - 1.0, -1.0, 1.0);
	}

	virtual Stereo process (const double position, const double size) override
	{
		const Stereo s0 = (**buffer).front();
		return Stereo
		{
			(balance < 0.0f ? s0.left + (0.0f - balance) * s0.right : (1.0f - balance) * s0.left),
			(balance < 0.0f ? (balance + 1.0f) * s0.right : s0.right + balance * s0.left)
		};
	}

protected:
	float balance;

};

#endif /* FXBALANCE_HPP_ */
