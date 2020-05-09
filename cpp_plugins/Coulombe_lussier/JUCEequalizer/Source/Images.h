/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Images  : public Component
{
public:
    //==============================================================================
    Images ();
    ~Images() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    bool hitTest (int x, int y) override;

    // Binary resources:
    static const char* bg_png;
    static const int bg_pngSize;
    static const char* blackKnob01_png;
    static const int blackKnob01_pngSize;
    static const char* knobred_png;
    static const int knobred_pngSize;
    static const char* knobgre_png;
    static const int knobgre_pngSize;
    static const char* knobyel_png;
    static const int knobyel_pngSize;
    static const char* knobble_png;
    static const int knobble_pngSize;
    static const char* knobwht_png;
    static const int knobwht_pngSize;
    static const char* knobbla_png;
    static const int knobbla_pngSize;
    static const char* moogKn_png;
    static const int moogKn_pngSize;
    static const char* blackKnob02_png;
    static const int blackKnob02_pngSize;
    static const char* bg2_png;
    static const int bg2_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Images)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

