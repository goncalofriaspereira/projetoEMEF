# Improved schematic and PCB layout
Second version of the project, done after the official conclusion of the report.

MAIN CHANGES:
Changed MCU to Arduino Nano, which is smaller; added power reverse polarity protection; added DAC of 10 bits that will communicate through I2C with the Arduino Nano; added copper area to the PCB, something that was not done on the previous iteration of the project; added bypass capacitors close to the amplifiers and another components that may require stable voltage; new PCB design with improved location of the components; smaller size of the PCB; added LED signals to verify digital pins states; removed MAX485 module and built my own in-board; removed Zener diodes in the voltage divider since it was messing with the measurement (probably due to leakage current).

NOTE: Arduino Nano code will be updated as soon as the DAC code is sucessfully tried and tested with the arrival of the PCB and respective montage, since there was no μMAX to DIP adapter to test the DAC before implementation.

![SchematicV2](SchematicV2.png)

![PCBLayoutV2](PCBLayoutV2.png)
