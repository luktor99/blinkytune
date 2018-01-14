//
// Created by luktor99 on 31.12.17.
//

#ifndef BLINKYTUNE_FILTER_H
#define BLINKYTUNE_FILTER_H

class Filter {
public:
    Filter(float alpha_inc = 0.8f, float alpha_dec = 0.8f);

    float &update(const float &);

    Filter &operator=(const float &value);

    float get() const;

private:
    float alpha_inc_, alpha_dec_;
    float value_;
};


#endif //BLINKYTUNE_FILTER_H
