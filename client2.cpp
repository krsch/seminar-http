#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <map>

using nlohmann::json;

struct page {
  int id;
  std::string touched;
};

void from_json(json const& j, page& p) {
  j.at("pageid").get_to(p.id);
  j.at("touched").get_to(p.touched);
}

int main(int argc, char** argv) {
  auto title = argc < 2 ? "Main Page" : argv[1];
  // auto str = "str1\n\"(str2)\"";
  auto str = R"mytext(str1
"(str2)")mytext";
  auto r = cpr::Get(cpr::Url{"https://en.wikipedia.org/w/api.php"},
                    cpr::Parameters{{"action", "query"},
                                    {"format", "json"},
                                    {"prop", "info"},
                                    {"titles", title}});
  json j = json::parse(r.text);
  auto const& pages = j["query"]["pages"].get<std::map<std::string, page>>();
  for (auto const& [id, p] : pages) {
    // std::map<std::string, std::string> m(value);
    // page p = value.get<page>();
    std::cout << p.id << ": " << p.touched << "\n";
  }
}
