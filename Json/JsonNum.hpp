#pragma once
#include "JsonObj.hpp"

struct JsonNum: JsonObj {
    int n;

    JsonNum(int n): n(n) {}

    string to_string() {
        return std::to_string(n);
    }

    JsonNum* clone() const {
        return new JsonNum(n);
    }
};