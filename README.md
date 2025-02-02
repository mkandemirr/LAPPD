# LAPPD Geant4 Simulation

The **Large Area Picosecond Photodetector (LAPPD)** is an advanced photodetector designed for fast timing and high spatial resolution applications. This package provides a Geant4 implementation of the LAPPD geometry based on Incom’s product sheet ([LAPPD Product Sheet](https://incomusa.com/wp-content/uploads/LAPPD-Product-Sheet-08-19.pdf)), enabling the simulation of photon propagation up to detection at the photocathode. All materials, optical surfaces, and the geometric volumes that make up the LAPPD, including the LAPPD housing, photocathode window, and the gaps between volumes, have been properly defined. Their properties can be configured using Geant4's user interface commands. Additionally, the package includes an example Geant4 application demonstrating the use of LAPPDs. With a single line of code, an LAPPD can be instantiated as a G4LogicalVolume object, making it easy to integrate into simulations.

The figure below shows the geometry details of the LAPPD.

![githubPic](https://github.com/mkandemirr/lappd/assets/114905224/7b5fac8c-dd54-485f-8d32-925b3bdc55da)

## Dependency

This tool relies on [OPSim](https://github.com/mkandemirr/OpSim.git) for efficient optical photon simulation and [G4DCP](https://github.com/mkandemirr/G4DCP.git) for detector geometry construction.


## How to use lappd in a Geant4 optical application?

The tool can be easily integrated into a typical Geant4 application/project as a library by copying the entire directory (directory name is lappd) into the project source directory where your CMakeList.txt file is located, and adding the following lines of code to the CMakeList.txt file (for help, you can examine the CMakeList.txt files in the provided example application):

before the executable target is created:

```cmake	
   add_subdirectory(lappd)
   add_subdirectory(OPSim)
   add_subdirectory(g4dcp)
  ```  
after the executable target is created:

```cmake	
   target_link_libraries(yourExecutableTarget OPSim g4dcp lappd)
  ```  

You can now get the lappd as either G4LogicalVolume or G4VPhysicalVolume object with just two lines of code! Add the following code to the Construct() method of your detector construction class to visualise the geometry:


```c++	
   #include "LAPPDPVBuilder.hh"
   
   G4String lappdModel = "lappd"; 
   LAPPDPVBuilder builder(lappdModel);
   G4VPhysicalVolume* lappdEnvelopePV = builder.GetProduct();
   return lappdEnvelopePV;
  ```  

or to obtain an LAPPD as a G4LogicalVolume object:

```c++	
   #include "LAPPDLVFactory.hh"
   G4LogicalVolume* pmtLv = LAPPDLVFactory::GetInstance()->Get(lappdModel)
  ```
              
## The package structure:   

_lappd/include_: This directory contains all LAPPD header files (.h).

_lappd/src_: This directory contains all LAPPD source files (.cc).

_lappd/data_: This directory contains data on the optical properties of the materials and surfaces defined to construct the LAPPD. The data is categorized based on the material optical properties and surface optical properties.  

_lappd/data/material_mpt_: This directory contains data files for the optical properties of materials defined to construct the LAPPD. 

_lappd/data/surface_mpt_: This directory contains data files for the optical properties of surfaces defined to construct the LAPPD. 

_lappd/macros_: This directory contains macro files (.mac) that control the parameters used in LAPPD construction.

_lappd/macros/mpt_: This directory contains macro files to control material optical properties such as refractive index, absorption length, etc..

_lappd/macros/os_: This directory contains macro files to control surface optical properties such as reflector reflectivity and PMT photocathode quantum efficiency. 
 
_lappd/macros/lappds_: This directory contains macro files to control the geometry construction parameters of LAPPDs.

_lappd/macros/vis_: This directory contains macro files to control visual parameters such as visibility and colors.

_lappd-g4-app_: This directory contains a sample Geant4 application using LAPPDs in the detector geometry. To test the LAPPDs, a toy Cherenkov detector surrounded by LAPPDs was constructed, and a sensitive detector was defined to count the photons detected. The program prints out the photon detection time and the number of photons detected by each LAPPD. Other classes needed to complete the application (except the UserDetectorConstruction class) have been kept in their simplest form.

## Tested on 

* Os: Linux (Ubuntu 24.04.2 LTS)
* Architecture: x86_64
* Compiler: GCC 13.3.0
* Geant4.11.2.2

## How to run the provided example applications?   
  
1. Go to the directory where you installed the lappd-g4-app directory in your system.
  ```bash	
   cd path/To/lappd-g4-app
  ```
  
2. Create a directory named lappd-g4-app-build in the same directory as lappd-g4-app. 
  ```bash
   mkdir lappd-g4-app-build
   ```

3. Now go inside this build directory and run CMake to generate the Makefiles needed to build the application. Two arguments are 
passed to CMake. The first argument to CMake is the path to the source directory that includes the CMakeList.txt file. The second argument is the path to the build directory where the generated make files will be located. CMake will now run to configure the build and generate Makefiles.
```bash
  cd lappd-g4-app-build
  cmake -S ../lappd-g4-app -B .
 ```
5. With the Makefile available, you can now build by simply running make: 
  ```bash
   make  
  ```
5. The application is now ready to run. If you now list the contents of your build directory, you will notice that the executable main has been created. The program can be executed in two modes: interactive and batch. To run in an interactive mode:
  ```bash
   ./main
```

The figure below shows an example event output from the program.

![ToyCherenkovDet](https://github.com/mkandemirr/lappd/assets/114905224/f4206c1a-7585-41df-8e95-643f41f26d54)

## Contacts 

If you have any questions or wish to notify of updates and/or modifications please contact: \
Mustafa Kandemir (mustafa.kandemir@erdogan.edu.tr)

