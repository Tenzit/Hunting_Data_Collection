# Hunting_Data_Collection

This is an SA2B mod which records data about hunting levels.

## Features

- Record exact pieces collected
- Record time pieces were collected in IL, IGT, V1, and V2.5 $^{1}$
- Identify if a stage was played story-style or not (PH, DC, EQ, MS)
- Count number of deaths/restarts taken in the stage

$^{1}$ Timing not guaranteed to be the exact same as LiveSplit, but it's typically within 5 frames

## Usage

Download the latest release from the [releases](https://github.com/Tenzit/Hunting_Data_Collection/releases) page.
Extract the .7z into your SA2 mods directory and enable in the modloader

Output is placed in `hunting_data.csv` in the mod directory

## Bugs

- Probably doesn't work in a hero/dark run, only tested w/stage select
- Sora's Debug Mode savestates or free movement cause the mod to output wrong data
