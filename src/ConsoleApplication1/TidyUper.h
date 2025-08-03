#pragma once

class TidyUper {
public:
    virtual void TidyUp(std::string path) = 0;
    virtual ~TidyUper() = default;
};
