21-Sep-2015 ShaneG

Silicon Labs is holding a [low power contest](http://community.silabs.com/t5/Contests/Low-Power-Contest/m-p/153186#U153186)
for devices that make use of their EFM32 product range. As these processors
fit into the category of CPUs I am using in the SensNode project already it
makes sense to add an entry.

There are two related competitions - one for ideas and the other for an actual
design. This page details my entry for the idea competition, the actual implementation
will be entered as part of the design stage.

## Silicon Labs Low Power Contest Idea Entry

My idea is to develop an ambient environment sensor that measures lighting levels,
proximity, temperature and humidity and reports the current status over a NRF24L01
based 2.4GHz wireless network to a base station. The sensors are battery powered
and can be deployed both inside and outside of the house.

The information gathered by the sensors can be used to monitor and adjust for
environmental conditions (by monitoring the light and temperature levels in a
garden for example) and provide triggers to automate other processes (turning
off the lights in a room if it has been unoccupied for a certain amount of
time).

The sensors will be battery powered and my goal is to be able to power a sensor
from a single 2000mAh AA battery for 6 months. This requires the average current
consumption of the sensor to be less than 150uA over it's operating period. To
achieve this goal will require very careful power management.

The design uses a number of Silicon Labs products including:

* EFM32 Cortex-M0+ Microcontroller
* SI7054 Temperature/Humidity sensor
* SI1141 Ambient light and Proximity sensor

All of these products can operate with very low current draws which will aid in
meeting the target. In addition the LESENSE features of the EFM32 will allow
for additional sensor inputs (such as soil moisture) to be added in the future
that can be activated and read while the CPU remains in low power mode.

