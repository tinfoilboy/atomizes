#include <atomizes.hpp>
#include "catch.hpp"

TEST_CASE("http message parsing correct", "[http_message_parse]")
{
    atomizes::HTTPMessageParser parser;

    SECTION("parse http request")
    {
        const std::string requestStr = "GET / HTTP/1.1\r\nHost: example.com\r\nUser-Agent: Test Agent\r\nConnection: keep-alive\r\n\r\n";

        atomizes::HTTPMessage request;

        parser.Parse(&request, requestStr);

        REQUIRE(request.HeaderCount() == 3);
        REQUIRE(request.GetHeader("Host") == "example.com");
        REQUIRE(request.GetHeader("User-Agent") == "Test Agent");
        REQUIRE(request.GetHeader("Connection") == "keep-alive");
        REQUIRE(request.GetMethod() == atomizes::MessageMethod::GET);
        REQUIRE(request.GetPath() == "/");
    }

    SECTION("parse http response without body")
    {
        const std::string responseStr = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/plain\r\n\r\n";

        atomizes::HTTPMessage response;

        parser.Parse(&response, responseStr);

        REQUIRE(response.HeaderCount() == 2);
        REQUIRE(response.GetHeader("Connection") == "close");
        REQUIRE(response.GetHeader("Content-Type") == "text/plain");
        REQUIRE(response.GetMessageBody().empty());
    }

    SECTION("parse http response with body")
    {
        const std::string responseStr = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello world!";

        atomizes::HTTPMessage response;

        parser.Parse(&response, responseStr);

        REQUIRE(response.HeaderCount() == 3);
        REQUIRE(response.GetHeader("Connection") == "close");
        REQUIRE(response.GetHeader("Content-Type") == "text/plain");
        REQUIRE(!response.GetMessageBody().empty());

        // convert the body to a string for easy compare
        std::string body(response.GetMessageBody().begin(), response.GetMessageBody().end());

        REQUIRE(body == "Hello world!");
    }
}