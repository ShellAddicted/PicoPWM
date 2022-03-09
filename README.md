# PicoPWM

A C++ way to control PWM for Raspberry Pico C/C++ SDK.

## Getting started

Download this library
```bash
mkdir lib/
cd lib/
git clone https://github.com/ShellAddicted/PicoPWM
```

adjust your `CMakeLists.txt` accordingly:
```
# Add this line before target_link_libraries()
pico_add_subdirectory(lib/PicoPWM) 

# Add PicoPWM to your target_link_libraries()
# Example: target_link_libraries(PicoTest pico_stdlib PicoPWM)
```

Example:
```
#include <iostream>
#include "picopwm.h"

int main() {
    PicoPwm pwm0 = PicoPwm(0);

    try {
        pwm0.setFrequency(25e3);  // set 25khz frequency
    } catch (const PicoPwmBaseException& e) {
        std::cout << e.what() << std::endl;
    }

    pwm0.setDutyPercentage(30);  // 30% (0%-100%)
    // pwm0.setDuty(256);  // alternative (0-65536)

    return 0;
}
```
## License
This library is [MIT](https://github.com/ShellAddicted/PicoPWM/blob/master/LICENSE) licensed, and is based on [Micropython](https://github.com/micropython/micropython/blob/master/LICENSE)'s PWM implementation