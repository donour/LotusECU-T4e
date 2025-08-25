# Lotus Elise/Exige/Evora (Toyota Engine) OEM ECU Tuning Guide

## Introduction

This guide should help you to tune your Lotus car using the OEM EFI ECU. This guide applies to cars produced between 2008-2022. There are two ECU versions available from Lotus.

* T4E: used in 4 cylinder (2ZZ-GE) based Elise and Exige platforms
* T6E (B132E0008F): used in 6 cylinder (2GR-FE) based Evora and Exige platforms

### T4E

<TODO>

### T6E

The T6E hardware was designed and assembled by EFi Technology in Italy. The design is based on the MPC5534 microcontroller from NXP, with custom softare for Lotus. Neither the hardware nor software is shared with other platforms or manufacturers. The T6E uses a single-controller design for electronic fuel injection and ignition, as well as a single CAN bus for communicating with safety and driver control systems. Automatic transmission cars (IPS) require a second, dedicate transmission control module (C132F0074F).

## Getting the important information out of the ECU

### The importance of data

If you want to be a better tuner than the average, there is not magic, you will
need to know what is going on in your engine and in your ECU. The more you know
the better you will be at tuning.

So even before thinking about modifying map, spent time about your logging
strategy. You will need data, and a lot of it!

There are a lot of self-called tuner that just add timing and call it a stage 1
tune with a great dyno-plot as a proof. It's not what I'm calling a good tune.

### Polling the standard OBD2 interface

If your Lotus is build after 2008, then you will probably have the OBD interface
over the CAN-Bus interface. So pulling data with it is a great option. 

Before 2008, the OBD interface is on the K-Line interface. And even if this interface
offers all the important data too, the refresh rate is very very slow and it makes
the data analysis much harder.

For cars build before 2008, I would use the RAW RAM access for polling the data.

You can also consider update your 2006-2007 car to the 2008 specifications.

### What data are needed

What is needed really depends on the task being done. But here various item that
are explained and why it's interesting.

#### GPS Position (External)

Not from the ECU itself, but having the GPS position is cheap and interesting.
So if an event appears on the track or on the street, you can localize it.

#### RPM (OBD Mode 0x01 PID 0x0C)

The engine speed is referenced in a lot of maps. Usefuel to determines which
cell needs to be updated.

#### Mass Air Per Stroke (OBD Mode 0x22 PID 0x0226)

The engine load is referenced in a lot of maps. Usefuel to determines which
cell needs to be updated too.

#### TPS (OBD Mode 0x22 PID 0x0245)

The Throttle Position Sensor to know if the engine is running at WOT.

***Tip***: Compare the TPS with PPS. If the TPS is reduced but the PPS has been
keep at the max, it's probably the torque limiter kicking in!

#### PPS (OBD Mode 0x22 PID 0x0246)

The Pedal Position Sensor is used by the ECU for various things including for
the DFSO (Decelerating Fuel Shut Off).

***Tip***: Create a filter in MLVHD to remove all the entries where the DFSO is
active (When PPS < CAL_dfso_enable_pps).

#### Octane Scaler (OBD Mode 0x22 PID 0x0218-0x021A, 0x024D-0x024E)

The octane scalers (one per cylinder) is a critical information. More about it
in the ignition chapter.

***Tip***: If you don't tune yourself the car, ask your tuner if they are award
of the octane scaler. This is an information that you would normally get with the
lotus diagnostic tool. If your tuner don't know what you talking about, avoid it.

### Data Analysis

## Direct Memory Access

## Load calculation

Load is basically the air mass entering the cylinder. It's the key value for
fueling.

Firstly the ECU determines if the MAF can be trusted, for that there is various
condition, but the most important condition is that the TPS has no rapid change
(CAL_load_use_alphaN_dt_tps1_\*_threshold).

In condition where the MAF isn't trustful the ECU fallback using an Alpha-N table.

When conditions are fillfulled and the MAF is trusted, the ECU will derivate the
load from the MAF and at the same it will update the learned Alpha-N table.

There is the base Alpha-N table (CAL_load_alphaN) and the learned Alpha-N table
(LEA_load_alphaN_adj). The learned Alpha-N is simply a the correction factor
applied on the base table by the ECU. The correction is allowed from 50% to 150%
(CAL_alphaN_adj_corr_\*).

The fuel vapour entering the engine via the carchoal canister is also added to
the load calculation. But there is no sensor measuring the quantity of it, so
the ECU makes an estimation of it when purging.

***Tip***: Compare the learned Alpha-N table before and after a modification on
the intake. If the tables has too much changes, it's likely that the air metering
is no more correct.

## Fueling

Monitor the fuel system status (OBD Mode 0x01 PID 0x03), it's usefuel for data
filtering. --> Not TRUE

When ignition retard is applied trough the octane scaler, fuel is also added.

## Ignition

### The 2ZZ case

If you lowering the VVL switch point, be carefuel about the smaller ignition map.

### Octane Scaler

Ths Lotus ECU has a long term, per cylinder, learned, octane estimation value
that it uses to blend the base ignition table with a low timing “safe” table.

### Making a knock noise baseline

## Torque estimation

## Factory Reflash Procedure
## OBD-II Diagnostic Trouble Codes

## Engine Speed Limit (Revlimit)






