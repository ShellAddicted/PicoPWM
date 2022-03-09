// based on https://github.com/micropython/micropython/blob/master/ports/rp2/machine_pwm.c
#include "picopwm.h"

PicoPwm::PicoPwm(uint8_t pin) {
    this->pin = pin;
    this->slice_num = pwm_gpio_to_slice_num(this->pin);
    this->channel = pwm_gpio_to_channel(this->pin);

    gpio_set_function(this->pin, GPIO_FUNC_PWM);
}

PicoPwm::~PicoPwm() { this->stop(); }

void PicoPwm::setFrequency(uint32_t freq) {
    uint32_t source_hz = clock_get_hz(clk_sys);
    uint32_t div16_top = 16 * source_hz / freq;
    uint32_t top = 1;
    while (1) {
        // Try a few small prime factors to get close to the desired frequency.
        if (div16_top >= 16 * 5 && div16_top % 5 == 0 && top * 5 <= TOP_MAX) {
            div16_top /= 5;
            top *= 5;
        } else if (div16_top >= 16 * 3 && div16_top % 3 == 0 && top * 3 <= TOP_MAX) {
            div16_top /= 3;
            top *= 3;
        } else if (div16_top >= 16 * 2 && top * 2 <= TOP_MAX) {
            div16_top /= 2;
            top *= 2;
        } else {
            break;
        }
    }
    if (div16_top < 16) {
        throw PicoPwmFreqTooLow();
    } else if (div16_top >= 256 * 16) {
        throw PicoPwmFreqTooHigh();
    }

    this->div = div16_top;
    this->top = top - 1;

    pwm_set_clkdiv_int_frac(this->slice_num, this->div / 16, this->div & 0xF);
    pwm_set_wrap(this->slice_num, this->top);

    this->setDuty(this->duty);
}

void PicoPwm::setDuty(uint32_t duty) {
    uint32_t cc = duty * (this->top + 1) / 65535;
    pwm_set_chan_level(this->slice_num, this->channel, cc);
    pwm_set_enabled(this->slice_num, true);
    this->duty = duty;
}

void PicoPwm::setDutyPercentage(uint8_t percentage) {
    uint32_t duty = (1 << 16) * (percentage / 100.0);
    this->setDuty(duty);
}

void PicoPwm::setInverted(bool inverted_a, bool inverted_b) { pwm_set_output_polarity(this->slice_num, inverted_a, inverted_b); }

void PicoPwm::stop() { pwm_set_enabled(this->slice_num, false); }

uint8_t PicoPwm::getPin() { return this->pin; }
uint8_t PicoPwm::getSlice() { return this->slice_num; }
uint8_t PicoPwm::getChannel() { return this->channel; }
