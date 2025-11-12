copy-test: CopyTest.cpp
	clang++ -fsanitize=address -g -std=c++20 $^ -o $@

string-test: StringTest.cpp
	clang++ -fsanitize=address -g -std=c++20 $^ -o $@

clean:
	rm string-test copy-test