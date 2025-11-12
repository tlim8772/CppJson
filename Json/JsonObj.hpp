#pragma once
#include <bits/stdc++.h>
using namespace std;

struct JsonObj {
    virtual ~JsonObj() {}

    virtual string to_string() = 0;

    virtual JsonObj* clone() const = 0;
};
