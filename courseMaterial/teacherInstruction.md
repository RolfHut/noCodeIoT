for teachers

Overview / intention
"no code Internet of Things" is a 5 day workshop in which students build their own sensor and publish their measurements online. All of this, without the need to write any line of software code. The setup of the workshop is very flexible and can be adjusted to different levels of students and different durations.

required skill / knowledge
A basic understanding of Ohms law is preferable, but not needed.

materials
Every student (or group of students) gets the following
- a Spark Photon (www.spark.io). The teacher needs to upload new firmware to these devices. See teacher preperations below.
- an electrical components starter set. Make sure that at least:
	x a 10k potentiometer
	x a temperature sensor like the TMP36
	x a tilt sensor
	x a few LDRs
	x a Hall sensor (suited for 5V or 3.3V) and a small permanent magnet
	x a pushbutton
	x some LEDs
	x some 220 Ohm and some 10kOhm resistors
	x a small breadboard and connector wires
are incluided. I personally like this set, and order them without the arduino: http://floris.cc/shop/en/starter-kits/216-arduino-kit-tu-delft.html. 

It helps if the teacher has a collection of other sensors that the students can use, such as gas sensors, UV sensors, accelerometers, etc. 

teacher preperation
The teacher needs to prepare the Spark Photons to make sure that the students can hit the ground running. This means that the following need to be achieved:
- tell the Spark Photon the wifi credentials.
- upload firmware to the Photon.
There are multiple ways to go about this. I will explain two: using the app and the web-interface, which is easy, but a lot of work if done for a lot of Photons. Or using the Command Line Interface, which requires a bit more tech savvy, but is quicker.

App and web interface.
Follow the steps on http://docs.spark.io/start/ to connect a photon for the first time. Make sure that you are in the same WiFi that the students are going to use. During this process you are asked to give the Photon a unique name. Use something easy, like your name followed by a number Write the name/number on the box that the Photon came in using a sharpie. 

As soon as a Photon is connected, use a computer to log into spark.io/build. Copy the code from https://github.com/RolfHut/noCodeIoT/blob/master/firmware/publishAnalogRead.ino or https://github.com/RolfHut/noCodeIoT/blob/master/firmware/publishTimeInterval.ino into the web-editor. Half of the Photons should be loaded with AnalogRead and the other half with TimeInverval. Press the "flash" icon (lightning icon) in the upper left corner. The lights on the Photon should start blinking magnenta. After the lights have gone back to breathing cyan, the firmware has been succesfully uploaded. Go to the cores icon (target-icon, lower left corner). Select the core that you have just flashed by clicking on the > next to its name. Copy paste the unique ID to an excel file. Write the name of the Photon (that you wrote on the box with a sharpie) in the column next to the just copied ID.  Click on "remove core". This final steps removes the core from your account, ready to be claimed by one of your students. 

Command Line Interface
Install the CLI as described here: http://docs.spark.io/cli/ including the advanced install options, since we will be using dfu-util.
Download https://github.com/RolfHut/noCodeIoT/blob/master/firmware/publishAnalogRead.bin and https://github.com/RolfHut/noCodeIoT/blob/master/firmware/publishTimeInterval.bin to your computer. 
spark compile app.ino --saveTo firmware.bin



Connect a Photon and put it in DFU mode by holding the mode button continously while pressing the reset button. Let go of the mode button as soon as the Photon starts flashing yellow.
Flash one of the two .ino files by running, from the directory where you saved the files: 
spark flash --usb publishAnalogRead.bin
or
spark flash --usb publishTimeInterval.bin

After flashing, the Photon should be breathing cyan, or blinking green. press and hold the mode button untill it blinks blue. This means it is in "listening mode". now run
spark identify
Copy paste the unique ID to an excel file. run
spark setup wifi
and follow the instructions. Make sure you profide it with the WiFi credentials of the network that the students will be using. You are asked to 
where NAME is a name that you make up. Copy the name of the Photon in the column next to the just copied ID in your excel file, and write it on the box of the Photon with a sharpie.


