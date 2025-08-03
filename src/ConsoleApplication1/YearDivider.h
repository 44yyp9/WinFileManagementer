#pragma once
#include "TidyUper.h"
#include <iostream>

class YearDivider : public TidyUper {
public:
    void TidyUp(std::string path) override;

};
