#pragma once
#include "JsonObj.hpp"

struct JsonNull: JsonObj {
    string to_string() {
        return "null";
    }

    JsonObj* clone() const {
        return new JsonNull();
    }
};