#include "Debug.h"

bool Debug::enabled(void)
{
    return (DEBUG_ENABLED == true);
}

void Debug::msg(std::ostringstream& p_msg, bool p_stderr, bool p_killproc) {
    
	std::ostringstream& message = p_msg;
    if(Debug::enabled())
    {
        // Affiche le message sur le flux stderr ou stdout
        if(p_stderr == true)
        {
			std::cerr << message.str() << std::endl;
        }
        else
        {
            std::cout << message.str() << std::endl;
        }

    }

    // Kill l'appli si demandé
    if(p_killproc == true) { exit(EXIT_FAILURE); }
}