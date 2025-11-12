#pragma once
#include "JsonObj.hpp"

struct JsonStruct: JsonObj {
    unordered_map<string, unique_ptr<JsonObj>> store;

    JsonStruct(unordered_map<string, unique_ptr<JsonObj>>&& store): store(std::move(store)) {}

    JsonStruct(const JsonStruct& other) {
        auto j = unique_ptr<JsonStruct>(other.clone());
        store = std::move(j->store);
    }

    string to_string() {
        string out = "{";
        for (auto& [k, v] : store) {
            out += "\"" + k + "\"";
            out += ":";
            out += v->to_string();
            out += ", ";
        }
        if (store.size() > 0) out.erase(out.end() - 2, out.end());
        out += "}";
        return out;
    }

    JsonStruct* clone() const {
        unordered_map<string, unique_ptr<JsonObj>> res;
        for (auto& [k, v] : store) {
            res[k] = unique_ptr<JsonObj>(v->clone());
        }
        return new JsonStruct(std::move(res));
    }
};