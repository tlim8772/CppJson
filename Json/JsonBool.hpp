#pragma once
#include "JsonObj.hpp"

struct JsonBool: JsonObj {
    bool b;

    JsonBool(bool b): b(b) {}

    string to_string() {
        return (b) ? "true" : "false";
    }

    JsonBool* clone() const {
        return new JsonBool(b);
    }
};