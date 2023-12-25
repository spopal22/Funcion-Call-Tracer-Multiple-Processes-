#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

void trace_function_call(pid_t process_id, void* this_fn, void* call_site, const char* event) {
    clock_t timestamp = clock(); //Gets the current timestamp so we can trace the clock
    fprintf(stderr, "Monitor: [%s] Process: %d, this_fn: %p, call_site: %p, clock: %ld\n",
            event, process_id, this_fn, call_site, timestamp);
} //Prints out the trace message to stderr in the format that we're looking for with all relevant info
//Function to print a trace message for a function call

void __cyg_profile_func_enter(void* this_fn, void* call_site) {
    trace_function_call(getpid(), this_fn, call_site, "enter");
}//When a function is entered, calls the callback function
//Calls the trace function with "enter" so we get the respective info when it enters/starts

void __cyg_profile_func_exit(void* this_fn, void* call_site) {
    trace_function_call(getpid(), this_fn, call_site, "exit");
}//When a function is exited, calls the callback function
//Calls the trace function with "exit" so we get the respective info when it exits

void monitor_process(int pipe_fd) { //Monitors a process by reading info from a pipe
    pid_t process_id;
    void* this_fn;
    void* call_site; //Variables to store the information thats read from the pipe
    char event[6];  //"enter" or "exit"

    while (read(pipe_fd, &process_id, sizeof(pid_t)) > 0) { //Continues to read from pipe as long as there is data present to ensure everythings read and doesnt stop prematurely
        if (read(pipe_fd, &this_fn, sizeof(void*)) == -1) {
            perror("Could not read this_fn");
            break;
        }
        if (read(pipe_fd, &call_site, sizeof(void*)) == -1) {
            perror("Could not read call_site");
            break;
        }
        if (read(pipe_fd, event, sizeof(event)) == -1) {
            perror("Could not read event");
            break;
        } //Gives errors in case it isnt able to read what we're trying to trace so we know where the error lies

        trace_function_call(process_id, this_fn, call_site, event); //Prints out the trace message based off of the information thats read by the pipe
    }

    if (errno != 0) {
        perror("Could not read from pipe");
    } //Checks for any errors when reading from the pipe
}