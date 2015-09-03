This directory contains the design files for an LPC1114 based SensNode.

CPU:     LPC1114 (ARM Cortex M0)
Flash:   32K
RAM:     4K
Speed:   48MHz
Network: NRF24L01 (via shield)

## Pin Mappings

* D0 - P1.8
* D1 - P1.9
* D2 - P1.0 (NOTE: Not connected on PCB, requires patch wire)
* D3/SCK - P0.7 (NOTE: Not hardware SPI, requires SoftSPI)
* D4/MOSI - P0.2 (NOTE: Not hardware SPI, requires SoftSPI)
* D5/MISO - P0.3 (NOTE: Not hardware SPI, requires SoftSPI)
* D6/SCL - P0.4
* D7/SDA - P0.5

* A0 - P1.3
* A1 - P1.4
* A2 - P1.2
* A3 - P1.1

* VBAT - P0.11
* IND - P0.8
* ACT - P0.9
* ENAB - P0.6
* PSW - P0.10
