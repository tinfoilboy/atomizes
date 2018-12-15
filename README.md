# atomizes

[![Build Status](https://travis-ci.com/tinfoilboy/atomizes.svg?branch=master)](https://travis-ci.com/tinfoilboy/atomizes)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Github Releases](https://img.shields.io/github/release/tinfoilboy/atomizes.svg)](https://github.com/tinfoilboy/atomizes/releases)

A header-only HTTP/1.1 request/response builder/parser.
Depends only on the C++11 standard library.
Uses the [Catch2](https://github.com/catchorg/Catch2) header-only library for tests.

## Usage

Copy the `atomizes.hpp` file to your project source.
Or, if you're using CMake, you can add this project as a dependency, using the `INTERFACE` flag, like below (this assumes that you have cloned/submoduled atomizes next to your project files).

    add_subdirectory(atomizes INTERFACE)

### Including

Every class and enum for atomizes is located in `atomizes.hpp` and thus, begin the file you'd like to use atomizes in with `#include <atomizes.hpp>`.

### Namespacing

Every portion of atomizes is stored under the `atomizes` namespace, so if you want to define say, an atomizes HTTP message, you would use `atomizes::HTTPMessage`.

### Messages

To represent both requests and responses, atomizes defines a `HTTPMessage` class.
This class has support for headers, status codes (with generated status messages), message bodies, and a method to convert the message to a `std::string`.

#### Responses

To define a basic response message with atomizes and print it to standard out, you would write the following:

```cpp
#include <iostream>
#include <string>
#include <atomizes.hpp>

int main()
{
    atomizes::HTTPMessage response;

    response.SetStatusCode(200)
            .SetHeader("Content-Type", "text/plain")
            .SetHeader("Connection", "close")
            .SetMessageBody("Hello world!");

    std::cout << response.ToString() << std::endl;

    return 0;
}
```

This simple message would result in the following output:

```
HTTP/1.1 200 OK
Connection: close
Content-Type: text/plain
Content-Length: 12

Hello world!
```

Notice how the `Content-Length` header is automatically appended due to the message body being set.

#### Requests

To define a simple request with an `HTTPMessage` and print it to standard out, you could write the following:

```cpp
#include <iostream>
#include <string>
#include <atomizes.hpp>

int main()
{
    atomizes::HTTPMessage response;

    response.SetMethod(atomizes::MessageMethod::GET)
            .SetPath("/")
            .SetHeader("User-Agent", "Test Agent")
            .SetHeader("Connection", "keep-alive")
            .SetHeader("Host", "example.com");

    std::cout << response.ToString() << std::endl;

    return 0;
}
```

This gives the following output in standard out:

```
GET / HTTP/1.1
Host: example.com
User-Agent: Test Agent
Connection: keep-alive

```

Whether a message is a request or a response depends on the method set for the message, either `MessageMethod::NONE` for a response or any other value for a request.

### Parser

atomizes also allows for the parsing of either an `std::string` or a `std::vector<uint8_t>` to get a `HTTPMessage` object using the `HTTPMessageParser` class.
This works for both requests and responses.

For example, this is a program that defines a string for a request and parses it into a message, then outputting to standard out.

```cpp
#include <iostream>
#include <string>
#include <atomizes.hpp>

std::string requestString = "GET / HTTP/1.1\r\nHost: example.com\r\nUser-Agent: Test Agent\r\nConnection: keep-alive\r\n\r\n";

int main()
{
    atomizes::HTTPMessageParser parser;
    atomizes::HTTPMessage       request;

    parser.Parse(&request, requestString);

    std::cout << request.ToString() << std::endl;

    return 0;
}
```

This returns the following output:

```
GET / HTTP/1.1
Host: example.com
User-Agent: Test Agent
Connection: keep-alive

```

Notice how the request string uses `\r\n` for new lines, this is because the HTTP specification says that lines must be seperated with a carriage return. Thus, the parser only supports this type of line ending.

### Tests

Tests can be built by enabling the `ATOMIZES_ENABLE_TESTS` flag in the CMake project.

## License

This project (atomizes) is licensed under the MIT License.
You may read the terms of the license [here](https://github.com/tinfoilboy/atomizes/blob/master/LICENSE).