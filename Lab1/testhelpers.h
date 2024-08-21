#pragma once
#include <fstream>


static std::stringstream fake_cout;
static std::stringstream fake_cin;

#define WHERE (__FILE__ + std::string(":") + std::string(std::to_string(__LINE__)) + std::string(": "))

static std::string strip_white(const std::string& in) {
  std::string result;
  for(const char& c:in) {
    if (not std::isspace(c)) result += c;
  }
  return result;
}

template<typename T>
static void fake_execute(T m,
			 const std::string input,
			 const std::string expected,
			 const std::string alternate=""
			 ) {
  {
    std::ofstream in("input");
    std::ofstream a("expected");
    std::ofstream b("actual");
  }

  fake_cin.clear();
  fake_cin.str(input);
  fake_cout.clear();
  fake_cout.str("");
  m();

  if (fake_cout.str() == expected) {
    std::cout << "Matched expected output" << std::endl;
    return;
  }
    
  if (alternate.size() > 0 and fake_cout.str() == alternate) {
    std::cout << "Matched alternate output" << std::endl;
    return;
  }

  // Dump input
  std::ofstream in("input");
  in << input;
  in.close();

  // Dump expected
  std::ofstream a("expected");
  a << expected;
  a.close();

  // Dump actual
  std::ofstream b("actual");
  b << fake_cout.str();
  b.close();

  throw std::runtime_error(
			   WHERE+"expected:\n"+expected+
			   "\ngot:\n"+fake_cout.str());
}



