#include "JsonObj.hpp"
#include "JsonArray.hpp"
#include "JsonBool.hpp"
#include "JsonNull.hpp"
#include "JsonNum.hpp"
#include "JsonString.hpp"
#include "JsonStruct.hpp"

using namespace std;

string single = "{}[]:,";

bool is_letter(char c) {
    int p1 = c - 'a', p2 = c - 'A';
    return (p1 >= 0 && p1 < 26) || (p2 >= 0 && p2 < 26);
}

bool is_digit(char c) {
    int p1 = c - '0';
    return (p1 >= 0 && p1 < 10);
}

vector<string> tokenise(string json) {
    vector<string> tokens;
    for (int i = 0; i < json.size();) {
        if (json[i] == ' ') {
            i++;
            continue;
        } 
        
        if (i == json.find_first_of(single, i)) {
            tokens.emplace_back(1, json[i]);
            i++;
        } else if (json[i] == '"') {
            int end = json.find('"', i + 1) + 1;
            tokens.push_back(json.substr(i, end - i));
            i = end;
        } else if (is_letter(json[i])) {
            int end;
            for (end = i; end < json.size() && is_letter(json[end]); end++);
            tokens.push_back(json.substr(i, end - i));
            i = end;
        } else if (is_digit(json[i])) {
            int end;
            for (end = i; end < json.size() && is_digit(json[end]); end++);
            tokens.push_back(json.substr(i, end - i));
            i = end;
        }
    }
    return tokens;
}

unique_ptr<JsonObj> parse_special(string s) {
    if (s == "true") {
        return make_unique<JsonBool>(true);
    } else if (s == "false") {
        return make_unique<JsonBool>(false);
    } else if (s == "null") {
        return make_unique<JsonNull>();
    } else if (is_digit(s[0])) {
        return make_unique<JsonNum>(stoi(s));
    } else if (s[0] == '"') {
        return make_unique<JsonString>(string{s.begin() + 1, s.end() - 1});
    }
    throw invalid_argument(s);
}

unique_ptr<JsonObj> parse_helper(vector<string>& tokens, int& i) {
    if (tokens[i] == "{") {
        i++;
        unordered_map<string, unique_ptr<JsonObj>> store;
        
        while (tokens[i] != "}") {
            string key = tokens[i]; key = string(key.begin() + 1, key.end() - 1);
            i += 2;
            
            unique_ptr<JsonObj> ptr;
            if (tokens[i] == "{" || tokens[i] == "[") {
                ptr = parse_helper(tokens, i);
            } else {
                ptr = parse_special(tokens[i]);
                i++;
            }
            store[key] = std::move(ptr);

            if (tokens[i] == "}") break;
            else if (tokens[i] == ",") i++;
        }
        
        i++;
        return make_unique<JsonStruct>(std::move(store));
    } 
    
    if (tokens[i] == "[") {
        i++;
        vector<unique_ptr<JsonObj>> arr;

        while (tokens[i] != "]") {
            unique_ptr<JsonObj> ptr;
            if (tokens[i] == "{" || tokens[i] == "[") {
                ptr = parse_helper(tokens, i);
            } else {
                ptr = parse_special(tokens[i]);
                i++;
            }
            arr.push_back(std::move(ptr));

            if (tokens[i] == "]") break;
            else if (tokens[i] == ",") i++;
        }

        i++;
        return make_unique<JsonArray>(std::move(arr));
    }

    return parse_special(tokens[i]);
}

unique_ptr<JsonObj> parse(string json) {
    auto tokens = tokenise(json);
    int i = 0;
    return parse_helper(tokens, i);
}


