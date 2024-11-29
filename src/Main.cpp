#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <regex>
#include <vector>

std::string data;                  // will be used throughout the program
std::vector<std::string> urls;     // array of urls
std::vector<std::string> filtered; // array of urls
using json = nlohmann::json;

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
    // https://cplusplus.com/reference/string/string/c_str/ since curl_easy_setopt expects `const char*` type
    curl_easy_setopt(handle, CURLOPT_URL, link.c_str());

    // You tell libcurl to pass all data to this function by issuing a function similar to this:
    //  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);

    // You can control what data your callback function gets in the fourth argument by setting another property:
    // curl_easy_setopt(handle, CURLOPT_WRITEDATA, &internal_struct);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &internal_struct);

    // curl_easy_perform connects to the remote site, does the necessary commands and performs the transfer.
    // Whenever it receives data, it calls the callback function we previously set.
    // The function may get one byte at a time, or it may get many kilobytes at once.
    // libcurl delivers as much as possible as often as possible. [that's pretty cool actually :]
    CURLcode ok = curl_easy_perform(handle);

    json outer_json = json::parse(data);

    // ┌──────────────────────────────────────────────────────────────────────────────┐
    // │                              get desired assets                              │
    // └──────────────────────────────────────────────────────────────────────────────┘

    // size is +-361, so it's within the bounds of int32
    int json_length = outer_json.size();
    std::cout << json_length << std::endl;

    int i = 0; // variables need to be initialized
    for (; i < json_length; i++)
    {
        json inner_json = outer_json[i]["assets"];
        int assets_length = inner_json.size();
        int j = 0;
        for (; j < assets_length; j++)
        {
            urls.push_back(inner_json[j]["url"]);
        }
    }

    // ┌──────────────────────────────────────────────────────────────────────────────┐
    // │                                filter assets                                 │
    // └──────────────────────────────────────────────────────────────────────────────┘

    if (rusty)
    {
        int i = 0;
        for (; i < urls.size(); i++)
        {
            if (std::regex_search(urls[i], rust_pattern))
            {
                filtered.push_back(urls[i]);
            }
        }
    }
    else if (solidity)
    {
    }

    int j = 0;
    for (; j < filtered.size(); j++)
    {
        std::cout << filtered[j] << std::endl;
    }

    // Remember that easy handles should be curl_easy_cleanuped.
    curl_easy_cleanup(handle);
}