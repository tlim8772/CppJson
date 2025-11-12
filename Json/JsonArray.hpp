#pragma once
#include "JsonObj.hpp"

struct JsonArray: JsonObj {
    vector<unique_ptr<JsonObj>> arr;

    JsonArray(vector<unique_ptr<JsonObj>>&& arr): arr(std::move(arr)) {}

    JsonArray(const JsonArray& other) {
        auto j = unique_ptr<JsonArray>(other.clone());
        arr = std::move(j->arr);
    }

    string to_string() {
        string out = "[";
        for (auto& obj : arr) {
            out += obj->to_string();
            out += ", ";
        }
        out.erase(out.end() - 2, out.end());
        out += "]";
        return out;
    }

    JsonArray* clone() const {
        vector<unique_ptr<JsonObj>> res;
        for (auto& p : arr) {
            res.push_back(unique_ptr<JsonObj>(p->clone()));
        }
        return new JsonArray(std::move(res));
    }
};