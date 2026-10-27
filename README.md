# AudioRecordingSensor

A stand-alone audio recorder built around an Arduino. It samples a microphone, writes the samples to an SD card with a real-time-clock timestamp, and uses a MATLAB script to turn the recording into a WAV file. The repo includes a user manual, enclosure CAD parts and photos of the build.

*Early work: electronics coursework.*

## Context

The build photos and the user manual are dated January 2016. The code was uploaded to GitHub in August 2019.

## What it shows

- Arduino firmware that combines an SD card (SPI), a DS1307 real-time clock (I2C), EEPROM for a persistent file counter, and a button on an external interrupt for start/pause.
- A small device state machine (idle, recording, error) shown through status and error LEDs, as described in the manual.
- A MATLAB step that removes the DC offset from the samples and writes a WAV file.
- Full product thinking for a student project: a SolidWorks enclosure (base and side covers), photos of the build, and a written user manual.

## Stack

Arduino (C/C++), SD, Wire and DS1307 libraries, MATLAB, SolidWorks.

## Run it

Flash `Extoc_sticos_Extra.ino` to an Arduino with an SD module, a DS1307 module and an analog microphone on A0. Use `DS1307_programado.ino` once to set the clock. Run `generandowav.m` on the captured samples.

## Looking back (2026)

The samples are written as text lines with a fixed delay. Today I would sample from a timer interrupt, write binary WAV data directly, and document the sample rate.
