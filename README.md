Step.rc editor (change.dll) version 1.00
This file was created on 2000-00-18 by Asperon
**************************************************************
1. Introduction

   This modules' purpose is to write changes directly to the 
   step.rc. It writes the change to the step and saves it 
   "behind the scenes". The changes are put into effect when 
   the user recycles litestep.

**************************************************************
2. Installation

   Unzip the change.dll into your litestep dir. Add the line:

   loadmodule c:\litestep\change.dll   

   to your step.rc (change c:\litestep to point at your 
   litestep dir)
 

**************************************************************
3. Usage
	
   The syntax for this module is very simple. Each change you 
   wish to make becomes a bang command. The bang command that 
   you create can be activated by any of the common ways. 
   Ie: shortcut, popup, wharf, hotkey, or command line 
   (lsxcommand).
   The bang command looks like this:
   !changeline [original line][new line][mode]
   an example of this might be: 
   !changeline [SystrayHidden][;SystrayHidden][normal]
   This would disable the systray always on top command. So 
   obviously, whatever function you wish to change has to be 
   alreay present (abled or disabled) in your step.rc. 
   The mode setting determines how the changes are made.
   currently there are 3 modes:
   [normal]    - find the line in param1, replace with param2
   [substring] - is param1 a substring of the current line,
                 if so, replace
   [force]     - just like normal mode, but if the line isn't
                 found then append param2 to the end of 
           	    step.rc

**************************************************************
4. Updates
	
   1.00 first release

**************************************************************
5. Thnx to

   Phar0e - Documentation and beta testing by.
   Slimer - helping out with some code.

**************************************************************

