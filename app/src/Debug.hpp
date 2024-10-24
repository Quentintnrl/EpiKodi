#pragma once

// Declare the debug variable as extern to avoid multiple definitions
extern bool debug;

// Define the macro for setting the debug flag
#define SET_DEBUG(value) (debug = value)

// Optionally, a macro to check the value of debug
#define DEBUG_ENABLED() (debug)