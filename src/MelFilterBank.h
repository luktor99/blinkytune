//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MELFILTERBANK_H
#define BLINKYTUNE_MELFILTERBANK_H

#undef min
#undef max
#include <kfr/base/univector.hpp>


#include <memory>
#include "Settings.h"

/**
* This class is used for calculation of Mel filter banks used in sound processing.
* User can transform his probes in hertz to Mel scale.
*/

class MelFilterBank {

public:

	/**
	* Constructor
	* @param nOut Number of output values from filter.
	*/
    explicit MelFilterBank(const unsigned int &nOut);

	/**
	* Static function transforming frequency values in Mel scale to hertz.
	* @param freqInMel Given reference to frequency in Mel scale.
	*/
    static float melToHertz(const float &freqInMel);

	/**
	* Static function transforming frequency values in hertz to Mel scale.
	* @param freqInHertz Given reference to frequency in hertz.
	*/
    static float hertzToMel(const float &freqInHertz);

	/**
	* Static function transforming frequency values in hertz to Mel scale.
	* @param freqValues A univector (from kfr library) representing input sound samples.
	* @param sampleRate Sample rate of input sound frequencies.
	* @param lowerFreq A lower value of output frequencies to clamp to.
	* @param upperFreq An upper value of output frequencies to clamp to.
	* @return A vector of float frequency values.
	*/
    std::vector<float>
    compute(kfr::univector<float, SPECTRUM_LENGTH> &freqValues, const unsigned int &sampleRate, float lowerFreq = 0, float upperFreq = SAMPLE_RATE/2) const;

private:

    unsigned int nOutputValues; /*!< Number of output samples value */

	/**
	* Function calculates lower index of given frequency when transforming to Mel scale.
	* @param lowerBandFrequency A reference to wanted frequency value index.
	* @param sampleRate Sample rate of input sound frequencies.
	* @return Value indicating index of given value in vector.
	*/
    std::size_t getLowerIndex(const float &lowerBandFrequency, const unsigned int &sampleRate) const;

	/**
	* Function calculates upper index of given frequency when transforming to Mel scale.
	* @param lowerBandFrequency A reference to wanted frequency value index.
	* @param sampleRate Sample rate of input sound frequencies.
	* @return Value indicating index of given value in vector.
	*/
    std::size_t getUpperIndex(const float &upperBandFrequency, const unsigned int &sampleRate) const;

};


#endif //BLINKYTUNE_MELFILTERBANK_H
