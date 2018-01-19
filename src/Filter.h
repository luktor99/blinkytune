//
// Created by luktor99 on 31.12.17.
//

#ifndef BLINKYTUNE_FILTER_H
#define BLINKYTUNE_FILTER_H

/**
 * Represents an exponential filter.
 */
class Filter {
public:
    /**
     * The constructor.
     * @param alpha_inc The increasing alpha coefficient.
     * @param alpha_dec The decreasing alpha coefficient.
     */
    Filter(float alpha_inc = 0.8f, float alpha_dec = 0.8f);

    /**
     * Update the filter's value.
     * @param value The new value.
     * @return The updated value of the filter.
     */
    float &update(const float &value);

    /**
     * Assignment operator. Updates the filter's value.
     * @param value The new value.
     * @return The updated filter's instance.
     */
    Filter &operator=(const float &value);

    /**
     * Retrieve the current value of the filter.
     * @return The current value of the filter.
     */
    float get() const;

private:
    float alpha_inc_, alpha_dec_; /*!< The values of alpha coefficients for increasing and decreasing. */
	float value_; /*!< The current value of the filtered value */
};


#endif //BLINKYTUNE_FILTER_H
