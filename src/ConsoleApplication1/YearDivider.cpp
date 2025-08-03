#include "YearDivider.h"
#include <iostream>
#include <filesystem>
using namespace std;

void YearDivider::TidyUp(std::string path) {
    int count = 0;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (std::filesystem::is_regular_file(entry.status())) {
                ++count;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "ƒGƒ‰[: " << e.what() << std::endl;
    }
    cout << count << endl;
}