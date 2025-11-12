#pragma once
#include "JsonObj.hpp"

struct JsonString: JsonObj {
    string s;

    JsonString(string s): s(s) {}

    string to_string() {
        return "\"" + s + "\"";
    }

    JsonString* clone() const {
        return new JsonString(s);
    }
};