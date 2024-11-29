#include <iostream>
#include <curl/curl.h>
#include <string>
#include <regex>

int main(int argc, char *argv[])
{
    // get params
    std::string file_type(argv[1]); // solidity || rust
    std::string link(argv[2]);      // api link

    // only allow one filter per call
    bool rusty = file_type == std::string("rust");
    bool solidity = rusty == true ? false : (file_type == std::string("solidity"));

    std::cout << rusty << std::endl;
    std::cout << solidity << std::endl;

    std::regex rust_pattern("\\.rs$");
    std::regex solidity_pattern("\\.sol$");

    // To use the easy interface, you must first create yourself an easy handle.
    // You need one handle for each easy session you want to perform.
    CURL *handle = curl_easy_init();
}