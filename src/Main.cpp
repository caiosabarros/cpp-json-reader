#include <iostream>
#include <curl/curl.h>
#include <string>

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
}