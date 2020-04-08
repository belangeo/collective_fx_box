#pragma once

#include <JuceHeader.h>


class CustomLookAndFeel : public LookAndFeel_V4
{
public:
    Colour light = Colour(212, 211, 224);

    // Blue
    Colour darktheme = Colour(6, 28, 64);
    Colour lighttheme = Colour(113, 137, 209);
    // Steal
    //Colour darktheme = Colour(35, 46, 54);
    //Colour lighttheme = Colour(118, 154, 181);

    // Constructeur.
    CustomLookAndFeel() {

        setColour(ResizableWindow::backgroundColourId, darktheme);
        
        setColour(Label::textColourId, light);
        setColour(Label::textWhenEditingColourId, light);
        setColour(Label::outlineWhenEditingColourId, Colours::transparentBlack);
        setColour(Label::backgroundWhenEditingColourId, Colours::transparentBlack);

        setColour(Slider::textBoxTextColourId, light);
        setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
        setColour(Slider::textBoxHighlightColourId, lighttheme.withAlpha(0.5f));
        setColour(Slider::backgroundColourId, Colours::transparentBlack);
        setColour(Slider::rotarySliderOutlineColourId, lighttheme);
        setColour(Slider::rotarySliderFillColourId, lighttheme.withAlpha(0.25f));
        setColour(Slider::trackColourId, lighttheme.withAlpha(0.25f));
        setColour(Slider::thumbColourId, lighttheme);
    }

    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
    {
        auto bounds = Rectangle<int> ((width - height) / 2.0f, y, height, height).toFloat().reduced (10);

        auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin (1.5f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        Path background;
        background.addEllipse (bounds);
        g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
        g.strokePath (background, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));

        if (slider.isEnabled()) {
            Path value;
            value.addPieSegment (bounds, rotaryStartAngle, toAngle, 0.0f);
            g.setColour (slider.findColour (Slider::rotarySliderFillColourId));
            g.fillPath (value);
        }

        Path thumb;
        Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi),
                                 bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi));

        g.setColour (slider.findColour (Slider::thumbColourId));
        thumb.addLineSegment (Line<float> (bounds.getCentre(), thumbPoint), 1.5f);
        g.strokePath(thumb, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }

};