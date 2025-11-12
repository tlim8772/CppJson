#include "Parser.hpp"

void test1() {
    string json = "{\"age\":19, \"name\":\"Tom\", \"is old\": true}";
    vector<string> tokens = tokenise(json);
    for (string& s : tokens) cout << s << endl;
    cout << endl;
}

void test2() {
    string json = "[\"Tom\", \"Mary\", 10, 20, true, null]";
    vector<string> tokens = tokenise(json);
    for (string& s : tokens) cout << s << endl;
    cout << endl;
}

void test3() {
    string json = "true";
    auto p = parse(json);
    cout << p->to_string() << endl;

    json = "[null, 10, [null]]";
    p = parse(json);
    cout << p->to_string() << endl;

    cout << endl;
}

void test4() {
    string json = "{\"name\": \"Tom\", \"age\": 20, \"child\": null}";
    auto p = parse(json);
    cout << p->to_string() << endl;

    json = "{\"name\": \"Tom\", \"child\": {\"name\": \"Ben\"}, \"parents\": [{\"name\": \"Mary\", \"age\":  20}, {\"name\": \"Tim\"}]}";
    p = parse(json);
    cout << p->to_string() << endl;

    cout << endl;
}

int main() {
    //test1();
    //test2();
    test3();
    test4();
}