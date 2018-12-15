#include "catch.hpp"
#include <atomizes.hpp>
#include <string>

TEST_CASE("http messages constructed correctly", "[http_message_construct]")
{
    SECTION("basic http response construction")
    {
        const std::string expected = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello world!";

        atomizes::HTTPMessage response;

        response.SetStatusCode(200)
                .SetHeader("Content-Type", "text/plain")
                .SetHeader("Connection", "close")
                .SetMessageBody("Hello world!");

        REQUIRE(response.ToString() == expected);
    }

    SECTION("http response with custom status")
    {
        const std::string expected = "HTTP/1.1 200 All Good\r\nConnection: close\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello world!";

        atomizes::HTTPMessage response;

        response.SetStatusCode(200)
                .SetStatusMessage("All Good")
                .SetHeader("Content-Type", "text/plain")
                .SetHeader("Connection", "close")
                .SetMessageBody("Hello world!");

        REQUIRE(response.ToString() == expected);
    }

    SECTION("basic http request construction")
    {
        const std::string expected = "GET / HTTP/1.1\r\nHost: example.com\r\nUser-Agent: Test Agent\r\nConnection: keep-alive\r\n\r\n";

        atomizes::HTTPMessage response;

        response.SetMethod(atomizes::MessageMethod::GET)
                .SetPath("/")
                .SetHeader("User-Agent", "Test Agent")
                .SetHeader("Connection", "keep-alive")
                .SetHeader("Host", "example.com");

        REQUIRE(response.ToString() == expected);
    }
}