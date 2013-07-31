#pragma once
#include <iostream>
#include <string>
#include <sstream>

#define DEBUG_ENABLED true

class Debug {
public:
    static bool enabled(void);
	static void msg(std::ostringstream& msg, bool p_stderr = false,  bool p_killproc = false);

};