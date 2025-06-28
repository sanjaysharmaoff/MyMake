#include "utils.h"
#include <filesystem>

namespace fs = std::filesystem;

bool fileExists(const std::string& filename) {
    return fs::exists(filename);
}
