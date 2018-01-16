//
// Created by luktor99 on 15.01.18.
//

#ifndef BLINKYTUNE_COLORSPECTRUM_H
#define BLINKYTUNE_COLORSPECTRUM_H

#include <QSlider>

#include "../SoundEffect.h"

/**
 * Implements the ColorSpectrum effect
 */
class ColorSpectrum : public SoundEffect {
public:
    /**
     * The constructor.
     */
    ColorSpectrum();

    void tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *data);

	/**
	* Create a new layout for parameters change in a GUI application
	* @param layout Parent layout of the widget
	* @param parent Parent widget
	*/
    void populateControls(QLayout* layout, QWidget* parent);

	/**
	* Read values of effect parameters from GUI app widgets (defined in populateControls()) 
	*/
    void readControls();

    /**
     * Create a new instance of the effect. This function is used by the EffectsFactory class.
     * @return A pointer to the newly created Effect class object.
     */
    static Effect *create();

    /**
     * The parameters controlling the effect's behaviour.
     */
    struct Params {
        float hue;
    };

private:
    Params p_;
	QSlider* hueSlider;
};


#endif //BLINKYTUNE_COLORSPECTRUM_H
