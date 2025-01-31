/* B.Oops
 * Glitch effect sequencer LV2 plugin
 *
 * Copyright (C) 2020 by Sven Jähnichen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef OPTIONCHOPPER_HPP_
#define OPTIONCHOPPER_HPP_

#include <new>
#include "OptionWidget.hpp"
#include "BWidgets/Label.hpp"
#include "Dial.hpp"
#include "VSlider.hpp"

class OptionChopper : public OptionWidget
{
public:
	OptionChopper () : OptionChopper (0.0, 0.0, 0.0, 0.0, "widget") {}
	OptionChopper (const double x, const double y, const double width, const double height, const std::string& name) :
		OptionWidget (x, y, width, height, name),
		stepsLabel (0, 90, 80, 20, "ctlabel", BOOPS_LABEL_NR_CHOPS),
		smoothLabel (90, 90, 60, 20, "ctlabel", BOOPS_LABEL_SMOOTH),
		chopLabel (170, 90, 220, 20, "ctlabel", BOOPS_LABEL_CHOPS),
		randLabel (410, 90, 60, 20, "ctlabel", BOOPS_LABEL_RANDOM),
		reachLabel (490, 90, 60, 20, "ctlabel", BOOPS_LABEL_REACH)

	{
		try
		{
			options[0] = new Dial (10, 20, 60, 60, "pad0", 1.0, 0.0, 1.0, 0.0, "%1.0f", "", [] (double x) {return LIMIT (int (1.0 + 8.0 * x), 1, 8);}, [] (double x) {return (LIMIT (x, 1, 8) - 1.0) / 8.0;});
			options[1] = new Dial (90, 20, 60, 60, "pad0", 0.5, 0.0, 1.0, 0.0, "%1.2f", "", [] (double x) {return x;});
			for (int i = 0; i < 8; ++i) options [i + 2] = new VSlider (170 + i * 30, 20, 20, 60, "pad0", 0.5, 0, 1, 0);
			options[10] = new Dial (410, 20, 60, 60, "pad0", 0.5, 0.0, 1.0, 0.0, "%1.2f", "", [] (double x) {return x;});
			options[11] = new Dial (490, 20, 60, 60, "pad0", 0.5, 0.0, 1.0, 0.0, "%1.0f", BOOPS_LABEL_STEPS, [] (double x) {return floor (1 + LIMIT (32.0 * x, 0.0, 31.0));}, [] (double x) {return (LIMIT (x, 1, 32) - 1.0) / 32.0;});
		}
		catch (std::bad_alloc& ba) {throw ba;}

		for (int i = 0; i < 12; ++i) options[i]->setCallbackFunction (BEvents::VALUE_CHANGED_EVENT, valueChangedCallback);

		for (int i = 0; i < 12; ++i) add (*options[i]);
		add (stepsLabel);
		add (smoothLabel);
		add (chopLabel);
		add (randLabel);
		add (reachLabel);
	}

	OptionChopper (const OptionChopper& that) :
		OptionWidget (that), stepsLabel (that.stepsLabel), smoothLabel (that.smoothLabel), chopLabel (that.chopLabel),
		randLabel (that.randLabel), reachLabel (that.reachLabel)
	{
		add (stepsLabel);
		add (smoothLabel);
		add (chopLabel);
		add (randLabel);
		add (reachLabel);
	}

	OptionChopper& operator= (const OptionChopper& that)
	{
		release (&stepsLabel);
		release (&smoothLabel);
		release (&chopLabel);
		release (&randLabel);
		release (&reachLabel);
		OptionWidget::operator= (that);
		stepsLabel = that.stepsLabel;
		smoothLabel = that.smoothLabel;
		chopLabel = that.chopLabel;
		randLabel = that.randLabel;
		reachLabel = that.reachLabel;
		add (stepsLabel);
		add (smoothLabel);
		add (chopLabel);
		add (randLabel);
		add (reachLabel);

		return *this;
	}

	virtual Widget* clone () const override {return new OptionChopper (*this);}

	virtual void applyTheme (BStyles::Theme& theme) override {applyTheme (theme, name_);}

	virtual void applyTheme (BStyles::Theme& theme, const std::string& name) override
	{
		OptionWidget::applyTheme (theme, name);
		stepsLabel.applyTheme (theme);
		smoothLabel.applyTheme (theme);
		chopLabel.applyTheme (theme);
		randLabel.applyTheme (theme);
		reachLabel.applyTheme (theme);
	}

	static void valueChangedCallback(BEvents::Event* event)
	{
		if (!event) return;
		BWidgets::Widget* widget = event->getWidget ();
		if (!widget) return;
		OptionChopper* p = (OptionChopper*) widget->getParent();
		if (!p) return;
		BOopsGUI* ui = (BOopsGUI*) widget->getMainWindow();
		if (!ui) return;

		// Steps changed ? Re-arrange sliders
		if (widget == p->getWidget(0))
		{
			const double value = ((BWidgets::ValueWidget*)widget)->getValue();
			const int steps = LIMIT (int (1.0 + 8.0 * value), 1, 8);
			for (int i = 0; i < 8; ++i)
			{
				if (i < steps)
				{
					p->getWidget (i + 2)->moveTo (170 + i * 240 / steps, 20);
					p->getWidget (i + 2)->setWidth (240 / steps - 10);
					p->getWidget (i + 2)->show();
				}
				else p->getWidget (i + 2)->hide();
			}
		}

		// Forward all changed options to ui
		ui->optionChangedCallback (event);
	}

protected:
	BWidgets::Label stepsLabel;
	BWidgets::Label smoothLabel;
	BWidgets::Label chopLabel;
	BWidgets::Label randLabel;
	BWidgets::Label reachLabel;
};

#endif /* OPTIONCHOPPER_HPP_ */
