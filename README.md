

#  :cyclone: TurbTroll :japanese_goblin:

TurbTroll is event-driven wind turbine control software targeted at ATMega (Arduino-based) hardware platforms. 

# For developers

TurbTroll has been built with the [PlatformIO](https://platformio.org/) framework, at current, things are setup to work on an Arduino Uno host. Although this can easily be modified for other target platforms by changing [platformio.ini](https://github.com/rossGardiner/TurbTroll/blob/master/platformio.ini). The [platformio.ini](https://github.com/rossGardiner/TurbTroll/blob/master/platformio.ini) file also includes references to libraries used and serial config. 

To get setup with development, I'd reccomend using the PlatformIO plugin for VSCode. Check it out [here.](https://platformio.org/install/ide?install=vscode) 

# How does it work?

## Software 

TurbTroll uses an event-driven observer design pattern to drive a chain of callbacks which update a PWM duty cycle for a given input frequency at the ADC. 

The [Eventually Library by Jonathan Bartlett](https://www.arduino.cc/reference/en/libraries/eventually/) is used to trigger the pipeline and can be scaled to add more/alternative triggers in the future.  

To store ADC samples, a ring buffer is created (thanks to [rlogiacco/CircularBuffer](https://github.com/rlogiacco/CircularBuffer)) and a simple time-domain (per sample) frequency detection scheme is proposed in [DspEngine.cpp](https://github.com/rossGardiner/TurbTroll/blob/master/src/DspEngine.cpp). 

The [DecisionMaker](https://github.com/rossGardiner/TurbTroll/blob/master/src/DecisionMaker.cpp) object handles the logic for converting a measured speed into action on the PWM duty cycle. This is achieved with a basic state-machine. 

## Control 

Speed is adjusted using a very basic proportional control system which currently does not do any proper MPPT. 

## Hardware

Add a circuit diagram (TODO)
