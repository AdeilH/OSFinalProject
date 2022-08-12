#include <string> 
#include <cstdlib>
#include <ctime>

namespace Fuzz{
    namespace RandomGenerators{
        const int generate_int(const int range);
        const double generate_double(const double range);
        const std::string generate_string(const int len);
    }
}