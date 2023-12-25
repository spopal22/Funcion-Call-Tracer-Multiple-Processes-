# Funcion Call Tracer(Multiple Processes)

*  Program traces function calls for programs that can create multiple processes
*  Uses gcc's code instrumentation
*  Built off the previous project that recorded call information at the enter/exit instrumentation points of the functions in a call trace file
*  A dedicated monitor process is created to record the information
*  The monitoring process uses the standard error device to report the information
*  Main program creates and ends the monitor process
*  The process ID and the call event in addition to the function call information is passed to the monitor process
*  When the call information is received from the process, the monitor retrieves the clock and prints the call information. Also reports the process id
