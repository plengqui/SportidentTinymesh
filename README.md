# Sportident online control using Tinymesh 169Mhz radio
A forest-optimized, reliable mesh radio for Sportident with up to 1,5km per hop.
This document introduces the project idea and product vision on a high level.
# Project context and background
In orienteering and other outdoor sports, the Sportident system is often used to electronically register when a participant passes a checkpoint. One drawback of Sportident is that the checkpoint pass time registrations cannot be read out until the participant has finished the course. In order to make sports using the Sportident system more exciting for the audience, there is a need for real-time communication from the checkpoints to the competition administration at the arena. A number of solutions already exist for this, such as the Radio Online Control, current loop signaling over military telephone wire, etc. While they each have their advantages, most solutions are a bit bulky which makes it burdensome to deploy more than a couple of online checkpoints in each race.
# Product vision
This project aims to produce a neat lightweight radio solution that is easy to deploy in forest conditions, while being very reliable in terms of delivering 100% of punches to the arena in all possible weather conditions. The finished product is a flexible 130 cm roll-up antenna, which is directly attached to a radio unit - a small box about the size of a fist. The antenna + radio unit can hang from a tree anywhere within 8m from the Sportident units at the control. No cabling is needed on the ground. No calibration of directional antennas is needed.
About 10 radio units including antennas can be carried in a backpack and easily deployed by one person with very limited technical knowledge. 
# Technologies used
## Tinymesh
The radio units communicate using a tried and tested mesh radio protocol from Radiocrafts called Tinymesh. They use the 169 MHz band, which implies wavelengths of almost 2 meters. Thus they have very good propagation even through dense and wet forest. Distances of over 1 km per hop have been tested with continuous operation. Tinymesh is a self-configuring, self-healing, monitorable mesh technology, implemented in a small surface-mounted component containing both transceiver and protocol logic. 
## Sportident Short Range Radio (SRR)
The Sportident units at the control are SRR stations, which communicate with the radio unit via a proprietary Sportident radio protocol on the 2,4 GHz band. 
# Project progress and status

This has been completed so far:
1.	Selected and tested antenna solution. 1,5km hop reached with rollup slim-jim antenna. 
2.	Verified Tinymesh mesh radio network in real Orienteering competition using Tinymesh developer kits in July 2016. 
3.	Written pc application in python to receive and parse Tinymesh and Sportident packets. Monitoring of the mesh network. Checks that all units are online, even if no control punches are made.
4.	Designed and built a neat field-deployable radio unit with custom-printed circuitboard, surface-mounted Tinymesh chip, battery, and a Teensy (a cheap small Arduino style microcontroller).
5.	Written and tested Teensy code to simulate Sportident punches with. Tested connectivity over Tinymesh from Teensy to the python application running on the PC.

Remains to do:
-	Connect SRR-OEM chip to the Teensy and test serial communication with Teensy.
-	Test end-to-end from punch in Sportident station to the python application on the PC.
-	Build more units and test a full mesh network. 

