#include <iostream>
#include "test.h"

int main() {
#if defined(TEST_MODE)
    std::cout << "Test-Mode aktiv" << std::endl;
    my_test();
#elif defined(DEBUG_MODE)
    std::cout << "Debug-Mode aktiv" << std::endl;
#elif defined(RELEASE_MODE)
    std::cout << "Release-Mode aktiv" << std::endl;
#else
    std::cout << "Unbekannter Mode (keine Defines gesetzt)" << std::endl;
#endif

#ifdef NDEBUG
    std::cout << "(NDEBUG ist definiert: typische Release-Optimierungen aktiv)\n";
#else
    std::cout << "(NDEBUG ist NICHT definiert: typische Debug-Einstellungen aktiv)\n";
#endif

    // Hier könnten test-/debug-spezifische Codepfade folgen …
    return 0;
}
