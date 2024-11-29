#include <iostream>
#include <curl/curl.h>
#include <string>
#include <regex>

std::string data; // will be used throughout the program

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    // totalSize is the number of chunks coming up times the size of each chunck
    const size_t totalSize = size * nmemb;
    // Extends the string by appending additional characters at the end of its current value: https://cplusplus.com/reference/string/string/append/
    // we say the buffer is a pointer to a char or a sequence of chars
    data.append((char *)buffer, totalSize); // append from the initial ptr up to ptr+totalSize

    return totalSize;
}

int main(int argc, char *argv[])
{
    // get params
    std::string file_type(argv[1]); // solidity || rust
    std::string link(argv[2]);      // api link

    // only allow one filter per call
    bool rusty = file_type == std::string("rust");
    bool solidity = rusty == true ? false : (file_type == std::string("solidity"));

    // debug
    std::cout << rusty << std::endl;
    std::cout << solidity << std::endl;
    std::cout << link << std::endl;

    // variables
    std::regex rust_pattern("\\.rs$");
    std::regex solidity_pattern("\\.sol$");
    std::string internal_struct; // from libcurl docs

    // To use the easy interface, you must first create yourself an easy handle.
    // You need one handle for each easy session you want to perform.
    CURL *handle = curl_easy_init();

    // You set properties and options for this handle using curl_easy_setopt.

    // One of the most basic properties to set in the handle is the URL.
    //  curl_easy_setopt(handle, CURLOPT_URL, "http://domain.com/");
    curl_easy_setopt(handle, CURLOPT_URL, link);

    // You tell libcurl to pass all data to this function by issuing a function similar to this:
    //  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);

    // You can control what data your callback function gets in the fourth argument by setting another property:
    // curl_easy_setopt(handle, CURLOPT_WRITEDATA, &internal_struct);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &internal_struct);
}