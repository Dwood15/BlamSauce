# BlamSauce

Make using Kornman's Yelo library accessible to the mere mortal. 

## WARNING: This project is temporary. 
 - Once I'm done copy and pasting from Open Sauce / BlamLib, this project will be getting ported, piece by piece, into the current, working Tempera repository, after a refactor.
 - This repository will then be frozen / made private, and development for it will cease.

## Attribution

This code is all in part from: 
 - Kornman00 (Sean Cooper)'s BlamLib c++ project, (2015)
 - My Tempera project (2018)
 - (SilentK and Abyll)'s haloforge project (ca ~2008). 

This library is protected under the GPLv3 License, and all usages are expected to abide its terms..

Please make an issue on the github repository (here: https://github.com/Dwood15/BlamSauce) if you have issues or feature requests. It may be mostly a port, but it aims to be a little bit more! 

This Library Expects the Windows 10 sdk, the Visual Studio Build Tools, and a DirectX 9 sdk (June 2010 or June 2007 should both be fine)

I look to do this in a multi-faceted manner:

 1. Scope reduction
    - Xbox support has been removed and is not planned to be added again..
    - Halo Editing Kit support is currently removed. Hoping to add it later, in another project.
 2. Restructure Open Sauce's Yelo SDK to header-only.
 3. Remove Boost
 4. Removing the need to build only with MSVC.
    - Building with MinGW GCC is a long-term goal
    - Visual Studio is a blight upon this planet and its usage should be heavily discouraged
    - No Visual Studio Solution Files required
 5. Remove obfuscating macros, reduce abstractions and indirection as possible.
 6. No dependencies upon Boost.
 7. C++17 Support.
 8. No Boost
 9. CMake 3.9+ Support 
    - Make dependency management easier and more dynamic.
    - Makes adding targets easier 
      - Reduce #ifdef workarounds accommodating different versions.
      - If we're building for pc instead of CE, should be able to specify the path to the PC header of the version we want to target
    - Make building those targets easier and more straightforward
    - Potential for MinGW GCC support. Submit PR?
 10. Style and therefore (hopefully you'll agree) readability improvements.
 
99.9% of the reason for this is to have a second codebase to split Tempera between and reduce the spaghetti.
    
As BlamSauce matures, using it should be a pleasant and enjoyable experience. You, the programmer looking to create a utility or application using this, should be able to pick it up and get programming 
with minimal hassle! You may have to poke at less-documented/researched structures in the game's memory, however, you shouldn't have to fight the library to use it.
    
## Using the Library

   Unfortunately, because Open Sauce and its Yelo sdk is so large and all-encompassing for the Blam! Engine, in my effort to simplify the library, I actually have to remove support for certain platforms.
   
   It's mostly just copy/pasted code from Project Yelo, Tempera, and Haloforge. I have scaffolded a few things out and however it may not build and my 
   changes are certainly untested. This project will remain unversioned _at least_ until another project like Chimera or Tempera is used in it during a major version bump.
      
## Contributing 
   - Contributions are welcome/
   - The following style rules are requested:
       1.  Curly brackets on the same line as the declaring function
       2.  Unix eol format 'LF'
       3.  Tabs for indentations
 
  *
  * Readability improvements and removal of some abusively obfuscating macros.

  Not everything from Open Sauce has been ported. This will take some time to complete, due to the sheer size of BlamLib. The intent, however, is to port BlamLib in whole to this project. 
