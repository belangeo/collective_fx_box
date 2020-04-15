#pragma once

#include <JuceHeader.h>


class CustomLookAndFeel : public LookAndFeel_V4
{
public:
    Colour light = Colour(225, 225, 225);

    // Blue
    Colour darktheme = Colour(20, 20, 20);
    Colour lighttheme = Colour(255, 255, 255);
    Colour red = Colour(255, 255, 0);
    Colour green = Colour(0, 255, 0);
    Colour blue = Colour(0, 0, 255);
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
        setColour(Slider::backgroundColourId, lighttheme.withAlpha(0.1f));
        setColour(Slider::rotarySliderOutlineColourId, lighttheme.withAlpha(0.25f));
        setColour(Slider::rotarySliderFillColourId, lighttheme.withAlpha(0.5f));
        setColour(Slider::trackColourId, lighttheme.withAlpha(0.15f));
        setColour(Slider::thumbColourId, lighttheme);

        // Boutons.
        setColour(TextButton::buttonColourId, darktheme);
        setColour(TextButton::buttonOnColourId, lighttheme.withAlpha(0.25f));
        setColour(TextButton::textColourOnId, light);
        setColour(TextButton::textColourOffId, light);
        setColour(ToggleButton::textColourId, light);
        setColour(ToggleButton::tickColourId, lighttheme);
        setColour(ToggleButton::tickDisabledColourId, lighttheme.withAlpha(0.25f));
    }

// Redéfinition de la méthode pour dessiner un potentiomètre linéaire (traditionnel vertical ou horizontal et
// rectangulaire plein avec la valeur écrite dans le potentiomètre, vertical ou horizontal).
void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                       float minSliderPos, float maxSliderPos, const Slider::SliderStyle style,
                       Slider& slider) {
    if (slider.isBar()) {
        g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
        g.drawRect(Rectangle<float>(0.f, 0.f, width, height));
        if (slider.isHorizontal()) {
            float linePos = sliderPos < 0.0f ? 0.0f : sliderPos > width ? width : sliderPos;
            g.drawLine(Line<float>(linePos, y + 1.0f, linePos, height - 2.0f));
            g.setColour (slider.findColour (Slider::trackColourId));
            g.fillRect(Rectangle<float> (static_cast<float> (x), y + 1.0f, sliderPos - x - 1.0f, height - 2.0f));
        } else {
            float linePos = sliderPos < 0.0f ? 0.0f : sliderPos > height ? height : sliderPos;
            g.drawLine(Line<float>(x = 1.0f, linePos, width - 2.0f, linePos));
            g.setColour (slider.findColour (Slider::trackColourId));
            g.fillRect(Rectangle<float>(x + 1.0f, sliderPos, width - 2.0f, y + (height - sliderPos - 2.0f)));
        }
    }
    else {
        auto isTwoVal   = (style == Slider::SliderStyle::TwoValueVertical   || style == Slider::SliderStyle::TwoValueHorizontal);
        auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

        auto trackWidth = jmin (6.0f, slider.isHorizontal() ? height * 0.25f : width * 0.25f);

        Point<float> startPoint (slider.isHorizontal() ? x : x + width * 0.5f,
                                 slider.isHorizontal() ? y + height * 0.5f : height + y);

        Point<float> endPoint (slider.isHorizontal() ? width + x : startPoint.x,
                               slider.isHorizontal() ? startPoint.y : y);

        Rectangle<float> track = slider.isHorizontal() ? Rectangle<float>(x, y, width, height).withSizeKeepingCentre(width, height * 0.25f) :
                                                         Rectangle<float>(x, y, width, height).withSizeKeepingCentre(jmin(6.0f, width * 0.1f), height);
        g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));
        g.drawRect(track);

        Point<float> minPoint, maxPoint, thumbPoint;

        if (isTwoVal || isThreeVal)
        {
            minPoint = { slider.isHorizontal() ? minSliderPos : width * 0.5f,
                         slider.isHorizontal() ? height * 0.5f : minSliderPos };

            if (isThreeVal)
                thumbPoint = { slider.isHorizontal() ? sliderPos : width * 0.5f,
                               slider.isHorizontal() ? height * 0.5f : sliderPos };

            maxPoint = { slider.isHorizontal() ? maxSliderPos : width * 0.5f,
                         slider.isHorizontal() ? height * 0.5f : maxSliderPos };
        }
        else
        {
            auto kx = slider.isHorizontal() ? sliderPos : (x + width * 0.5f);
            auto ky = slider.isHorizontal() ? (y + height * 0.5f) : sliderPos;

            minPoint = startPoint;
            maxPoint = { kx, ky };
        }

        auto thumbWidth = slider.isHorizontal() ? 6.0f : width * 0.33f;
        auto thumbHeight = slider.isHorizontal() ? height * 0.8f : 6.0f;

        if (! isTwoVal)
        {
            g.setColour (slider.findColour (Slider::thumbColourId));
            g.fillRect (Rectangle<float> (thumbWidth, thumbHeight).withCentre (isThreeVal ? thumbPoint : maxPoint));
        }

        if (isTwoVal || isThreeVal)
        {
            auto sr = jmin (trackWidth, (slider.isHorizontal() ? height : width) * 0.4f);
            auto pointerColour = slider.findColour (Slider::thumbColourId);

            if (slider.isHorizontal())
            {
                drawPointer (g, minSliderPos - sr,
                             jmax (0.0f, y + height * 0.5f - trackWidth * 2.0f),
                             trackWidth * 2.0f, pointerColour, 2);

                drawPointer (g, maxSliderPos - trackWidth,
                             jmin (y + height - trackWidth * 2.0f, y + height * 0.5f),
                             trackWidth * 2.0f, pointerColour, 4);
            }
            else
            {
                drawPointer (g, jmax (0.0f, x + width * 0.5f - trackWidth * 2.0f),
                             minSliderPos - trackWidth,
                             trackWidth * 2.0f, pointerColour, 1);

                drawPointer (g, jmin (x + width - trackWidth * 2.0f, x + width * 0.5f), maxSliderPos - sr,
                             trackWidth * 2.0f, pointerColour, 3);
            }
        }
    }
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
    // Redéfinition de la méthode pour dessiner le bouton à deux états.
    void drawToggleButton (Graphics& g, ToggleButton& button,
                           bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
        auto fontSize = jmin (50.0f, button.getHeight() * 0.75f);
        auto tickWidth = fontSize * 1.1f;

        drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                     tickWidth, tickWidth,
                     button.getToggleState(),
                     button.isEnabled(),
                     shouldDrawButtonAsHighlighted,
                     shouldDrawButtonAsDown);

        g.setColour (button.findColour (ToggleButton::textColourId));
        g.setFont (fontSize);

        if (! button.isEnabled())
            g.setOpacity (0.5f);

        g.drawFittedText (button.getButtonText(),
                          button.getLocalBounds().withTrimmedLeft (roundToInt (tickWidth) + 10)
                                                 .withTrimmedRight (2),
                          Justification::centredLeft, 10);
    }
    // Redéfinition de la méthode pour dessiner la case à cocher du bouton à deux états.
    void drawTickBox (Graphics& g, Component& component, float x, float y, float w, float h,
                                      const bool ticked, const bool isEnabled,
                                      const bool shouldDrawButtonAsHighlighted,
                                      const bool shouldDrawButtonAsDown) {
        ignoreUnused (shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

        Rectangle<float> tickBounds (x, y, w, h);

        g.setColour (component.findColour (isEnabled ? ToggleButton::tickColourId : ToggleButton::tickDisabledColourId));
        g.drawRect (tickBounds, 1.0f);

        if (ticked) {
            g.setColour (component.findColour (ToggleButton::tickColourId));
            g.fillRect(tickBounds.reduced(4.0f, 4.0f));
        }
    }

};