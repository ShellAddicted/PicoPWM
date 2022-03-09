#include <string>

#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

class PicoPwmBaseException : public std::exception {
   protected:
    std::string _msg;

   public:
    PicoPwmBaseException(std::string message = "PWM exception occurred") { _msg = message; };
    virtual const char* what() const throw() { return _msg.c_str(); }
};

class PicoPwmFreqTooLow : public PicoPwmBaseException {
   public:
    PicoPwmFreqTooLow(std::string message = "PWM Frequency too low.") : PicoPwmBaseException(message){};
};

class PicoPwmFreqTooHigh : public PicoPwmBaseException {
   public:
    PicoPwmFreqTooHigh(std::string message = "PWM Frequency too high.") : PicoPwmBaseException(message){};
};

class PicoPwm {
   protected:
    const int TOP_MAX = 65534;
    uint8_t pin = 0;
    uint8_t slice_num = 0;
    uint8_t channel = 0;
    uint32_t duty = 0;
    uint32_t div = 0;
    uint16_t top = 0;

   public:
    PicoPwm(uint8_t pin);
    ~PicoPwm();
    void setFrequency(uint32_t frequency);
    void setDuty(uint32_t duty);
    void setDutyPercentage(uint8_t percentage);
    void setInverted(bool inverted_a, bool inverted_b);

    uint8_t getPin();
    uint8_t getSlice();
    uint8_t getChannel();
    void stop();
};