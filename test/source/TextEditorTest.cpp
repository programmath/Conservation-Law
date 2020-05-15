#include <TextEditor.h>
#include <doctest/doctest.h>

TEST_CASE("TextEditor::parse") {
  using namespace std;

  vector<char> delimiters{',', ' '};

  vector<string> ret = TextEditor::parse("hello, world this is string.", delimiters);
  CHECK(ret.at(0) == "hello");
  CHECK(ret.at(1) == "");
  CHECK(ret.at(2) == "world");
  CHECK(ret.at(3) == "this");
}
