# Trivia2020


## Description
A project based around ATMega32 Controller. There are only 2 categories (Pop culture and Sports)  that are implemented due to the lack of storage the microcontroller can hold. Each category holds a series ofrandomized questions. A score out of 10 will be displayed on the LED once 10 randomized questions have been asked. A 70% or higher will produce a pleasing low to high tune, otherwise it will produce a gloomy high to low tune. 

- **Programming Language:** C

- **Category:** Games


## User Stories

The following functionality is complete:

* [x] User can start the game by pressing 0.
* [x] Category will be randomized each time user presses 0.
* [x] Questions are randomized each game.
* [x] Tunes are implemented to inform user of a good/bad score.

Future implementations yet to be completed:

* [ ] User can end game whenever they desire.
* [ ] Implement more categories.
* [ ] Enhance randomization in questions and categories.
* [ ] Create a timed feature in which users answer as many questions as they can within a certain timeframe.

## Video Walkthrough
https://www.youtube.com/watch?v=2u97XLhyB7k

## Notes

A huge thanks and credits to professor Tony Givargis for providing files for lcd and avr. These files contain functions that help display characters on the lcd as well as create a accurate wait function that helps replicate real time. All credits for lcd.c, lcd.h, avr.c, avr.h go to professor Tony Givargis.

## License

    Copyright [2020] [Kevin Tang]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.




