#include "Debug.h"
#include <time.h>

bool Debug::enabled(void)
{
    return (DEBUG_ENABLED == true);
}

void Debug::msg(std::ostringstream& p_msg, bool p_stderr, bool p_killproc) {
    
	std::ostringstream& message = p_msg;
	time_t now = time(NULL);
    if(Debug::enabled())
    {
        // Affiche le message sur le flux stderr ou stdout
        if(p_stderr == true)
        {
			std::cerr << now << "\t" << message.str() << std::endl;
        }
        else
        {
            std::cout << now << "\t" << message.str() << std::endl;
        }

    }

    // Kill l'appli si demandé
    if(p_killproc == true) { exit(EXIT_FAILURE); }
}