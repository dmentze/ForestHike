

# Problem Statement

Write a C++ program that simulates a team hiking through a forest at night.  The team encounters a series of narrow bridges along the way.
At each bridge they may meet additional hikers who need their help to cross the bridge.  The narrow bridge can only hold two people at a time. They have one torch and because it's night, the torch has to be used when crossing the bridge.  Each hiker can cross the bridge at different speeds. When two hikers cross the bridge together, they must move at the slower person's pace.

Determine the fastest time that the hikers can cross the each bridge and the total time for all crossings.  The input to the program will be a yaml file that describes the speeds of each person, the bridges encountered, their length, and the additional hikers encountered along the way.

Your solution should assume any number of people and bridges can be provided as inputs.

Demonstrate the operation of your program using the following inputs: the hikers cross 3 bridges, at the first bridge (100 ft long) 4 hikers cross (hiker A can cross at 100 ft/minute, B at 50 ft/minute, C at 20 ft/minute, and D at 10 ft/minute), at the second bridge (250 ft long) an additional hiker crosses with the team (E at 2.5 ft/minute), and finally at the last bridge (150 ft long) two hikers are encountered (F at 25 ft/minute and G at 15 ft/minute).


## Design Options

The goal is to create a software program to simulate a night hike for hikers crossing bridges.

Simulations are an approximation of a real world event.

The goal of the simulation is generally to explore correctness or approaches for problem solving.

The granularity and complexity of the simulation can be modified depending on many reasons such as the accuracy needed or the purpose of the simulation.

Currently the following aspects of the simulation are not included:
   - factors relating to human capabilities and environment, such as
     - endurance of an individual
     - distance between bridges
     - lifetime of torch
     - duration of night (in daylight torch is not needed)
     - environment (temperature, weather) impacts- e.g. speeds/endurance impact

The specific problem to be solved is:
    ***Determine the fastest time that the hikers can cross the each bridge and the total time for all crossings.***


## Algorithm

The nature of the problem clearly leads to an approach of using the fastest hiker to ferry individuals across the bridge.  Since each bridge can have more hikers, then a new fastest hiker could emerge.  Given the endurance/environment factors are not being included, then the time to cross each bridge can be calculated as follows:

   Given:
    bridgeLength
    hikerSet, size N, each nth hiker has n.hikerSpeed
    fastestHiker

   Distance = Speed * Time

   So Time = Distance / Speed

   Each hiker in the hiker set is guided across the bridge by the fastest hiker, and takes time:  bridgeLength / n.hikerSpeed

  CrossTime = (time to guide each hiker) + (time for fastest hiker to return)
  
  The number of times the fastest hiker must return is N - 2.

### Example

  For example, with 4 hikers, the guide must return 2 times. Assuming the hikers A,B,C,D where D is fastest:
      1. Guide A:  time1 = bridgeLength / A.hikerSpeed
      2. Return    time2 = bridgeLength / D.hikerSpeed
      3. Guide B:  time3 = bridgeLength / B.hikerSpeed
      4. Return    time4 = bridgeLength / D.hikerSpeed
      5. Guide C:  time5 = bridgeLength / C.hikerSpeed

  Total time = sum of times 1 - 5 = bridgeLength * ( 1/A.hikerSpeed + 1/B.hikerSpeed + 1/C.hikerSpeed + 2/D.hikerSpeed )

### Formula

   This leads to the following formula:

   ***CrossTime = bridgeLength * ( sumAll(1/nonGuide.hikerSpeed) + (N-2)/fastestHiker.hikerSpeed )***

## Design

The application is written in c++ to be cross platform and high performance.

The input file is in yaml format, and parsed using an available parser libary: https://github.com/jbeder/yaml-cpp

The overall application includes the following classes:

    - class:  ForestHike
      -Responsibility: This top level class orchestrates the simulation.
      -Collaborators:  This class uses ForestHikeYaml, Bridge to run th simulation.  It also uses user input to selection the simulation parameters.
    - class:  ForestHikeYaml
      -Responsibility: This class reads a yaml file and populates a list of Bridges
      -Collaborators:  YAML library (to parse YAML) and Bridge/Hiker to hold simulation inputs
    - class:  Bridge
      -Responsibility: Contain simulation data regarding a particular bridge read from yaml:  lenth, hiker(name,speed)
    - class:  Hike
      -Responsbility:  Contain Hiker simulation data read from yaml

Note that while Hiker is used when parsing yamls, the Bridge only stores a sum of hiker inverse speeds.  So per hiker data is transient.

Also note that by keeping a sum of inverse speeds for each bridge, the CrossTime algorihm can be modified as follows:

   ***ImprovedCrossTime = bridgeLength * ( sumAll(1/all.hikerSpeed) + (N-3)/fastestHiker.hikerSpeed )***

   That calc works for N>1;

   For N=1 the cross time is simple the time for the single hiker to traverse the bridge.


## Instructions to run

Prerequisites are to have standard c++ tools suite installed along with cmake.

Download application from here:  xxx

Change directories into the topmost directory, and create a build directory:  e.g. mkdir build

Now change directories into the build dir:  cd build

Now run cmake:  cmake ..

Now run make:  make

Now the application can be invoked:  ./foresthike

This runs the application with an exmaple input yaml file.

To see options type:  ./foresthike --help

The unitests also can be invoked:  ./foresthiker-ut






