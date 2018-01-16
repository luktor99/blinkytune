//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_COLORBEAT_H
#define BLINKYTUNE_COLORBEAT_H

#include <QCheckBox>
#include <QComboBox>
#include "../StereoAnalysisBuffer.h"
#include "../SoundEffect.h"

/**
 * Implements the Color Beat effect
 */
class ColorBeat : public SoundEffect {
public:
    /**
     * The constructor.
     */
    ColorBeat();

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

    enum Modes {
        M_BASS_MID_TREB = 0,
        M_BASS_TREB_MID,
        M_TREB_BASS_MID,
        M_TREB_MID_BASS,
        M_MID_BASS_TREB,
        M_MID_TREB_BASS
    };

    /**
     * The parameters controlling the effect's behaviour.
     */
    struct Params {
        Modes mode;
        bool mixChannels;
    };

private:
	QCheckBox* mixChannelsCheckBox;
	QComboBox* colorMappingComboBox;
    Params p_;
};

#endif //BLINKYTUNE_COLORBEAT_H
