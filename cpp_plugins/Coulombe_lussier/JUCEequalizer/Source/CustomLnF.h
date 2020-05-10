#pragma once

#include <JuceHeader.h>
#include "Images.h"

/*
Je savais pas comment faire pour utiliser plusieurs
slider different sans faire plusieurs class.
*/

/*******************************************
Red
*******************************************/
class CustomLnFRed : public LookAndFeel_V4
{
public:
	Colour def = Colour(75, 75, 75);
	CustomLnFRed() {
		setColour(Label::backgroundColourId, def.withAlpha(0.0f));
		setColour(Slider::trackColourId, def.withAlpha(0.0f));
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.0f));
		setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
		setColour(Label::outlineWhenEditingColourId, Colours::transparentBlack);
		setColour(Label::backgroundWhenEditingColourId, Colours::transparentBlack);
		setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.5f));
		setColour(Slider::backgroundColourId, Colours::transparentBlack);
		setColour(Label::outlineWhenEditingColourId, def.withAlpha(0.0f));
		setColour(Label::backgroundWhenEditingColourId, def.withAlpha(0.0f));
	}

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)override
	{
		// https://forum.juce.com/t/skinning-the-slider-replacing-knob-and-slider-track-with-pngs/12026/8

		Image strip;
		strip = ImageCache::getFromMemory(Images::knobred_png, Images::knobred_pngSize);
		const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
		const int nFrames = strip.getHeight() / strip.getWidth(); // number of frames for vertical film strip
		const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0)); // current index from 0 --> nFrames-1

		const float radius = jmin(width / 2.0f, height / 2.0f);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius - 3.0f;
		const float ry = centreY - radius /* - 1.0f*/;

		g.drawImage(strip, 
			(int)rx, (int)ry, strip.getWidth(), strip.getWidth(),
			0, frameIdx*strip.getWidth(), strip.getWidth(), strip.getWidth());
		setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
	}

	Label* createSliderTextBox(Slider& slider)
	{
		auto* l = LookAndFeel_V2::createSliderTextBox(slider);
		l->setFont(10.0f);
		if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
			|| slider.getSliderStyle() == Slider::LinearBarVertical))
		{
			l->setColour(Label::textColourId, Colours::black.withAlpha(0.0f));
			l->setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
		}

		return l;
	}
	void drawLabel() {

	}
};

/*******************************************
 Yellow
*******************************************/
class CustomLnFBlue : public LookAndFeel_V4
{
public:
	Colour def = Colour(75, 75, 75);
	CustomLnFBlue() {
		setColour(Label::backgroundColourId, def.withAlpha(0.0f));
		setColour(Slider::trackColourId, def.withAlpha(0.0f));
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.0f));
		setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
		setColour(Label::outlineWhenEditingColourId, Colours::transparentBlack);
		setColour(Label::backgroundWhenEditingColourId, Colours::transparentBlack);
		setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.5f));
		setColour(Slider::backgroundColourId, Colours::transparentBlack);
		setColour(Label::outlineWhenEditingColourId, def.withAlpha(0.0f));
		setColour(Label::backgroundWhenEditingColourId, def.withAlpha(0.0f));
	}
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)override
	{
		Image strip;
		strip = ImageCache::getFromMemory(Images::knobble_png, Images::knobble_pngSize);
		const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
		const int nFrames = strip.getHeight() / strip.getWidth();
		const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0));
		const float radius = jmin(width / 2.0f, height / 2.0f);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius - 3.0f;
		const float ry = centreY - radius /* - 1.0f*/;
		g.drawImage(strip,
			(int)rx, (int)ry, strip.getWidth(), strip.getWidth(),
			0, frameIdx*strip.getWidth(), strip.getWidth(), strip.getWidth());
	}
	Label* createSliderTextBox(Slider& slider){
		auto* l = LookAndFeel_V2::createSliderTextBox(slider);
		l->setFont(10.0f);
		if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
			|| slider.getSliderStyle() == Slider::LinearBarVertical))
		{
			l->setColour(Label::textColourId, Colours::black.withAlpha(0.7f));
		}
		return l;
	}
};
/*******************************************
 Green
*******************************************/
class CustomLnFGreen : public LookAndFeel_V4
{
public:
	Colour def = Colour(75, 75, 75);
	CustomLnFGreen() {
		setColour(Label::backgroundColourId, def.withAlpha(0.0f));
		setColour(Slider::trackColourId, def.withAlpha(0.0f));
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.0f));
		setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
		setColour(Label::outlineWhenEditingColourId, Colours::transparentBlack);
		setColour(Label::backgroundWhenEditingColourId, Colours::transparentBlack);
		setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.5f));
		setColour(Slider::backgroundColourId, Colours::transparentBlack);
		setColour(Label::outlineWhenEditingColourId, def.withAlpha(0.0f));
		setColour(Label::backgroundWhenEditingColourId, def.withAlpha(0.0f));
	}
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)override
	{
		Image strip;
		strip = ImageCache::getFromMemory(Images::knobgre_png, Images::knobgre_pngSize);
		const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
		const int nFrames = strip.getHeight() / strip.getWidth();
		const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0));
		const float radius = jmin(width / 2.0f, height / 2.0f);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius - 3.0f;
		const float ry = centreY - radius /* - 1.0f*/;
		g.drawImage(strip,
			(int)rx, (int)ry, strip.getWidth(), strip.getWidth(),
			0, frameIdx*strip.getWidth(), strip.getWidth(), strip.getWidth());
	}
	Label* createSliderTextBox(Slider& slider) {
		auto* l = LookAndFeel_V2::createSliderTextBox(slider);
		l->setFont(10.0f);
		if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
			|| slider.getSliderStyle() == Slider::LinearBarVertical))
		{
			l->setColour(Label::textColourId, Colours::black.withAlpha(0.7f));
		}
		return l;
	}
};
/*******************************************
 white
*******************************************/
class CustomLnFWhite : public LookAndFeel_V4
{
public:
	Colour def = Colour(75, 75, 75);
	CustomLnFWhite() {
		setColour(Label::backgroundColourId, def.withAlpha(0.0f));
		setColour(Slider::trackColourId, def.withAlpha(0.0f));
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.0f));
		setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
		setColour(Label::outlineWhenEditingColourId, Colours::transparentBlack);
		setColour(Label::backgroundWhenEditingColourId, Colours::transparentBlack);
		setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.5f));
		setColour(Slider::backgroundColourId, Colours::transparentBlack);
		setColour(Label::outlineWhenEditingColourId, def.withAlpha(0.0f));
		setColour(Label::backgroundWhenEditingColourId, def.withAlpha(0.0f));
	}
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)override
	{
		Image strip;
		strip = ImageCache::getFromMemory(Images::knobwht_png, Images::knobwht_pngSize);
		const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
		const int nFrames = strip.getHeight() / strip.getWidth();
		const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0));
		const float radius = jmin(width / 2.0f, height / 2.0f);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius - 3.0f;
		const float ry = centreY - radius /* - 1.0f*/;
		g.drawImage(strip,
			(int)rx, (int)ry, strip.getWidth(), strip.getWidth(),
			0, frameIdx*strip.getWidth(), strip.getWidth(), strip.getWidth());
	}
	Label* createSliderTextBox(Slider& slider) {
		auto* l = LookAndFeel_V2::createSliderTextBox(slider);
		l->setFont(10.0f);
		if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
			|| slider.getSliderStyle() == Slider::LinearBarVertical))
		{
			l->setColour(Label::textColourId, Colours::black.withAlpha(0.7f));
		}
		return l;
	}
};
/*******************************************
 black
*******************************************/
class CustomLnFBlack : public LookAndFeel_V4
{
public:
	Colour def = Colour(75, 75, 75);
	CustomLnFBlack() {
		setColour(Label::backgroundColourId, def.withAlpha(0.0f));
		setColour(Slider::trackColourId, def.withAlpha(0.0f));
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.0f));
		setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
		setColour(Label::outlineWhenEditingColourId, Colours::transparentBlack);
		setColour(Label::backgroundWhenEditingColourId, Colours::transparentBlack);
		setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.5f));
		setColour(Slider::backgroundColourId, Colours::transparentBlack);
		setColour(Label::outlineWhenEditingColourId, def.withAlpha(0.0f));
		setColour(Label::backgroundWhenEditingColourId, def.withAlpha(0.0f));
	}
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)override
	{
		Image strip;
		strip = ImageCache::getFromMemory(Images::knobbla_png, Images::knobbla_pngSize);
		const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
		const int nFrames = strip.getHeight() / strip.getWidth();
		const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0));
		const float radius = jmin(width / 2.0f, height / 2.0f);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius - 3.0f;
		const float ry = centreY - radius /* - 1.0f*/;
		g.drawImage(strip,
			(int)rx, (int)ry, strip.getWidth(), strip.getWidth(),
			0, frameIdx*strip.getWidth(), strip.getWidth(), strip.getWidth());
	}
	Label* createSliderTextBox(Slider& slider) {
		auto* l = LookAndFeel_V2::createSliderTextBox(slider);
		l->setFont(10.0f);
		if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
			|| slider.getSliderStyle() == Slider::LinearBarVertical))
		{
			l->setColour(Label::textColourId, Colours::black.withAlpha(0.7f));
		}
		return l;
	}
};
/*******************************************
 Moog
*******************************************/
class CustomLnFMoog : public LookAndFeel_V4
{
public:
	Colour def = Colour(75, 75, 75);
	Colour purp = Colour(64,20,255);
	CustomLnFMoog() {
		setColour(Label::backgroundColourId, def.withAlpha(0.0f));
		setColour(Slider::trackColourId, def.withAlpha(0.0f));
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.0f));
		setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
		setColour(Label::outlineWhenEditingColourId, Colours::transparentBlack);
		setColour(Label::backgroundWhenEditingColourId, Colours::transparentBlack);
		//setColour(Slider::textBoxTextColourId, purp);
		

		setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.5f));
		setColour(Slider::backgroundColourId, Colours::transparentBlack);
		setColour(Label::outlineWhenEditingColourId, def.withAlpha(0.0f));
		setColour(Label::backgroundWhenEditingColourId, def.withAlpha(0.0f));
	}
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)override
	{
		Image strip;
		strip = ImageCache::getFromMemory(Images::moogKn_png, Images::moogKn_pngSize);
		const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
		const int nFrames = strip.getHeight() / strip.getWidth();
		const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0));
		const float radius = jmin(width / 2.0f, height / 2.0f);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius - 1.0f;
		const float ry = centreY - radius /* - 1.0f*/;
		g.drawImage(strip,
			(int)rx, (int)ry, strip.getWidth(), strip.getWidth(),
			0, frameIdx*strip.getWidth(), strip.getWidth(), strip.getWidth());
	}
	Label* createSliderTextBox(Slider& slider) {
		auto* l = LookAndFeel_V2::createSliderTextBox(slider);
		l->setFont(10.0f);
		if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
			|| slider.getSliderStyle() == Slider::LinearBarVertical))
		{
			l->setColour(Label::textColourId, Colours::black.withAlpha(0.7f));
		}
		return l;
	}
};
/*******************************************
 Comp
*******************************************/
class CustomLnFComp : public LookAndFeel_V4
{
public:
	Colour def = Colour(75, 75, 75);
	CustomLnFComp() {
		setColour(Label::backgroundColourId, def.withAlpha(0.0f));
		setColour(Slider::trackColourId, def.withAlpha(0.0f));
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.0f));
		setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
		setColour(Label::outlineWhenEditingColourId, Colours::transparentBlack);
		setColour(Label::backgroundWhenEditingColourId, Colours::transparentBlack);
		setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.5f));
		setColour(Slider::backgroundColourId, Colours::transparentBlack);
		setColour(Label::outlineWhenEditingColourId, def.withAlpha(0.0f));
		setColour(Label::backgroundWhenEditingColourId, def.withAlpha(0.0f));
	}
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)override
	{
		Image strip;
		strip = ImageCache::getFromMemory(Images::blackKnob01_png, Images::blackKnob01_pngSize);
		const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
		const int nFrames = strip.getHeight() / strip.getWidth();
		const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0));
		const float radius = jmin(width / 2.0f, height / 2.0f);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius - 1.0f;
		const float ry = centreY - radius;
		g.drawImage(strip,
			(int)rx, (int)ry, strip.getWidth(), strip.getWidth(),
			0, frameIdx*strip.getWidth(), strip.getWidth(), strip.getWidth());
	}
	Label* createSliderTextBox(Slider& slider) {
		auto* l = LookAndFeel_V2::createSliderTextBox(slider);
		l->setFont(10.0f);
		if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
			|| slider.getSliderStyle() == Slider::LinearBarVertical))
		{
			l->setColour(Label::textColourId, Colours::black.withAlpha(0.7f));
		}
		return l;
	}
};
/*******************************************
 Deesser
*******************************************/
class CustomLnFDees : public LookAndFeel_V4
{
public:
	Colour def = Colour(75, 75, 75);
	CustomLnFDees() {
		setColour(Label::backgroundColourId, def.withAlpha(0.0f));
		setColour(Slider::trackColourId, def.withAlpha(0.0f));
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.0f));
		setColour(Label::outlineColourId, Colours::black.withAlpha(0.0f));
		setColour(Label::outlineWhenEditingColourId, Colours::transparentBlack);
		setColour(Label::backgroundWhenEditingColourId, Colours::transparentBlack);
		setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
		setColour(Slider::textBoxHighlightColourId, def.withAlpha(0.5f));
		setColour(Slider::backgroundColourId, Colours::transparentBlack);
		setColour(Label::outlineWhenEditingColourId, def.withAlpha(0.0f));
		setColour(Label::backgroundWhenEditingColourId, def.withAlpha(0.0f));
	}
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)override
	{
		Image strip;
		strip = ImageCache::getFromMemory(Images::blackKnob02_png, Images::blackKnob02_pngSize);
		const double fractRotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
		const int nFrames = strip.getHeight() / strip.getWidth();
		const int frameIdx = (int)ceil(fractRotation * ((double)nFrames - 1.0));
		const float radius = jmin(width / 2.0f, height / 2.0f);
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius - 6.0f;
		const float ry = centreY - radius;
		g.drawImage(strip,
			(int)rx, (int)ry, strip.getWidth(), strip.getWidth(),
			0, frameIdx*strip.getWidth(), strip.getWidth(), strip.getWidth());
	}
	Label* createSliderTextBox(Slider& slider) {
		auto* l = LookAndFeel_V2::createSliderTextBox(slider);
		l->setFont(10.0f);
		if (getCurrentColourScheme() == LookAndFeel_V4::getGreyColourScheme() && (slider.getSliderStyle() == Slider::LinearBar
			|| slider.getSliderStyle() == Slider::LinearBarVertical))
		{
			l->setColour(Label::textColourId, Colours::black.withAlpha(0.7f));
		}
		return l;
	}
};