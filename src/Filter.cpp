//
// Created by luktor99 on 31.12.17.
//

#include "Filter.h"

Filter::Filter(float alpha_inc, float alpha_dec) : alpha_inc_(alpha_inc), alpha_dec_(alpha_dec) {

}

float &Filter::update(const float &value) {
    if (value > value_) // Increase - use alpha_inc
        value_ = alpha_inc_ * value + (1.0f - alpha_inc_) * value_;
    else if (value < value_) // Decrease - use alpha_dec
        value_ = alpha_dec_ * value + (1.0f - alpha_dec_) * value_;

    return value_;
}

float Filter::get() const {
    return value_;
}

Filter &Filter::operator=(const float &value) {
    update(value);
    return *this;
}