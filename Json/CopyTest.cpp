#include "JsonObj.hpp"
#include "JsonArray.hpp"
#include "JsonBool.hpp"
#include "JsonNull.hpp"
#include "JsonNum.hpp"
#include "JsonString.hpp"
#include "JsonStruct.hpp"

#include "testUtils.hpp"

void test1() {
    unordered_map<string, unique_ptr<JsonObj>> store;
    store["name"] = make_unique<JsonString>("Tom");
    store["age"] = make_unique<JsonNum>(29);
    store["gender"] = make_unique<JsonNull>();
    auto j1 = make_unique<JsonStruct>(std::move(store));
    
    auto j2 = unique_ptr<JsonStruct>(j1->clone());
    j2->store["name"] = make_unique<JsonString>("Mary");
    j2->store["age"] = make_unique<JsonNum>(31);
    cout << j2->to_string() << endl;
    
    cout << j1->to_string() << endl;

    cout << endl;
}

void test2() {
    vector<unique_ptr<JsonObj>> arr;
    arr.push_back(gen("Tom", 29));
    arr.push_back(gen("Mary", 31));
    auto j1 = JsonArray(std::move(arr));
    auto j2 = j1;

    j1.arr.push_back(gen("John", 18));
    cout << j1.to_string() << endl;
    cout << j2.to_string() << endl;
    cout << endl;
}

void test3() {
    auto p1 = gen("Tom", 29);
    auto j2 = *p1;
    p1->store["name"] = make_unique<JsonString>("John");
    cout << p1->to_string() << endl;
    cout << j2.to_string() << endl;
    cout << endl;
}


int main() {
    test2();
    test3();
}
