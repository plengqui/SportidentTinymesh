# How to configure your radio card with TM-CCT
If you have built a new radio card with a TM and a Teensy, you probably want to configure the TM. At least you need to do that with your gateway since all TM's are factory configured as a router.

Radiocrafts has a real useful and easy to use tool that can be used for configuring the TM. It can also be used for sending test strings between TM's and watching the signal levels. The name of the tool is TM-CCT and it can be downloaded from [here](https://radiocrafts.com/products/tinymesh/#software). Pick the file "[RC Tools - TM](https://radiocrafts.com/uploads/rctools-tm_setup_1_06.exe)" and install it.

For TM-CCT to be able to talk to the TM through the Teensy you need a small sketch that copies everything from the USB-serial to the TM-serial and vice versa. Upload the sketch [tm-config.ino](https://github.com/plengqui/SportidentTinymesh/tree/master/RadioUnit/TeensySketches/tm-config) to the Teensy.

When the sketch is running on the Teensy, start the TM-CCT tool and connect it to the Teensy USB-serial port. Use the default 19200 as baud rate.

Now you are in normal mode (not configuration mode) and when you type something and press enter, it is sent to the TM and you should see the LEDs blinking as the TM transmits what you typed.

To enter configuration mode, click the green and red button on the top left. A dialog saying "Waiting for prompt sign, press CONFIG button!" is shown. While this dialog is showing, shortly connect the CONFIG pin on the TM to GND. (Best is probably to install a push button on the PCB in the final design but for now a jumper wire will do just fine.)

If you suceeded to set the TM in configuration mode both the LEDs should be lit with a steady light and the dialog in TM-CCT should have closed. You can now remove the jumper cable again.

Fetch the current configuration of the TM by clicking the green left arrow. The window to the left should fill up with all current configuration.

Change whatever value that you like, e.g. the Device type on address 0x0E. When finished, click the green right arrow to write the new configuration to the TM.

Go back to the normal terminal mode again by clicking the other button saying "abc123" (or type "X" and Enter). This should turn off the LEDs so they start to blink again and the TM is restarted with the the new config.