#include "JsonObj.hpp"
#include "JsonArray.hpp"
#include "JsonBool.hpp"
#include "JsonNull.hpp"
#include "JsonNum.hpp"
#include "JsonString.hpp"
#include "JsonStruct.hpp"

unique_ptr<JsonStruct> gen(string name, int age) {
    unordered_map<string, unique_ptr<JsonObj>> store;
    store["name"] = make_unique<JsonString>(name);
    store["age"] = make_unique<JsonNum>(age);
    return make_unique<JsonStruct>(std::move(store));
}