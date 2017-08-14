# DualEncoders
Use dual concentric encoders with 2 steps per detent like those sold by Propwash

This is Version 1.1

Backward compatible with version 1.0
  
Added a .begin() method to initialise the pins in the setup() section. Version 1.0 initialised the pins in the instanciation phase of the object. Just add the .begin() method in the setup() section of any sketch that was using version 1.0.
  
Added an ultrafast Debouncer and EMF filter
