# Improved schematic and PCB layout.
Second version of the project, done after the official conclusion of the report.

MAIN CHANGES:
Changed MCU to Arduino Nano, which is smaller;
Added power reverse polarity protection;
Added DAC of 10 bits that will communicate through I2C with the Arduino Nano;
Added copper area to the PCB, something that wasn't done before;
Added bypass capacitors close to the amplifiers and another components that may require stable voltage;
New PCB design with improved location of the components;
Smaller size of the PCB.

![SchematicV2](SchematicV2.png)

![PCBLayoutV2](PCBLayoutV2.png)
