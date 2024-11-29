# cpp-json-reader

## Overview

This is a C++ program to fetch urls in a specific JSON returned by an API endpoint. The program handles both the call to the endpoint using the globally famous [libcurl](https://curl.se/libcurl/) package and it does log the urls found. An argument might be passed to filter the `rust` or `solidity` files.

## Motivation
The purpose of this program is to assist me on my efforts as a security researcher. This will enable me have quicker results for the target assets I will be exploring.

## Development Environment

The tools that enabled this software to exist are:
- C++
- [libcurl](https://curl.se/libcurl/) 
- [nlohmann/json](https://github.com/nlohmann/json)

Each of them being:
- `C++`
- `libcurl` is probably the most portable, most powerful and most often used network transfer library on this planet.
- `nlohmann/json` is a JSON handler within C++.

## Useful Websites

- [libcurl Official Tutorial](https://curl.se/libcurl/c/libcurl-tutorial.html)
- [json.hpp File](https://github.com/nlohmann/json/blob/develop/include/nlohmann/json.hpp)

## Future Work

There are a lot to improve on this project and contributions are welcome. Main tasks yet to be done or nice to have are

- Error handling 
- Go, Haskell and other filters
- Call to GitHub urls to retrieve desired files

