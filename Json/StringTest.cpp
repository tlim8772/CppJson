#include "JsonObj.hpp"
#include "JsonArray.hpp"
#include "JsonBool.hpp"
#include "JsonNull.hpp"
#include "JsonNum.hpp"
#include "JsonString.hpp"
#include "JsonStruct.hpp"

void test1() {
    cout << JsonBool(1).to_string() << endl;
    cout << JsonNum(123).to_string() << endl;
    cout << JsonString("hello world").to_string() << endl;
    cout << JsonNull().to_string() << endl;
    cout << endl;
}

void test2() {
    unordered_map<string, unique_ptr<JsonObj>> store;
    store["name"] = make_unique<JsonString>("Tom");
    store["age"] = make_unique<JsonNum>(29);
    store["gender"] = make_unique<JsonNull>();
    auto j1 = make_unique<JsonStruct>(std::move(store));
    cout << j1->to_string() << endl;

    auto j2 = unique_ptr<JsonStruct>(j1->clone());
    j2->store["name"] = make_unique<JsonString>("Mary");
    j2->store["child"] = unique_ptr<JsonStruct>(j1->clone());
    cout << j2->to_string() << endl;
    cout << endl;
}

void test3() {
    vector<unique_ptr<JsonObj>> arr;
    for (int i = 0; i < 5; i++) {
        arr.push_back(make_unique<JsonString>("hi " + to_string(i)));
    }
    auto j = JsonArray(std::move(arr));

    unordered_map<string, unique_ptr<JsonObj>> store;
    store["name"] = make_unique<JsonString>("Tom");
    store["age"] = make_unique<JsonNum>(29);
    store["gender"] = make_unique<JsonNull>();
    j.arr.push_back(make_unique<JsonStruct>(std::move(store)));

    unordered_map<string, unique_ptr<JsonObj>> store2;
    store2["name"] = make_unique<JsonString>("Mary");
    store2["age"] = make_unique<JsonNum>(29);
    store2["gender"] = make_unique<JsonNull>();
    j.arr.push_back(make_unique<JsonStruct>(std::move(store2)));

    cout << j.to_string() << endl;
    cout << endl;
}

int main() {
    test1(); 
    test2();
    test3();
}