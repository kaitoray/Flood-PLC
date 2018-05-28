# Flood PLC
SCADA train system penetration tests

Before debugging the program in visual studio
1. Add source files and header files
2. Click on the project name and select the properties--Linker--General, change the Enable Incremental Linking to "NO"
3. Click on the project name and select the properties--Linker--Input, add the "ws2_32.lib" to Additional Dependencies and select the OK button

Attack Steps
1. Keep sending emergency stop message within a small intervals.--------------------Press S or s
2. Keep sending session handle requests and connection ID requests.-----------------Press R or r
3. Keep creating socket to connect and closing.-------------------------------------Press C or c
4. Keep sending the exceed value of speed within a small intervals.-----------------Press O or o
5. Keep sending the track switch commands within a small intervals.-----------------Press X or x
6. Keep sending false direction commands within a small intervals.------------------Press F or f