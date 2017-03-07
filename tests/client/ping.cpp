#include <catch.hpp>
#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <string>
#include <list>

#include <url/path.hpp>
using url::path;

TEST_CASE("ping with valid token", "[client][ping]") {
    std::string token = "AQAAAAATPnx3AAQXOJS1w4zmPUdrsJNR1FATxEM";
    ydclient client{ token };
    REQUIRE(client.ping());
}

TEST_CASE("ping with invalid token", "[client][ping]") {
    std::string token = "JS1w4zmPUdrsJNR1FATxEM";
    ydclient client{ token };
    REQUIRE_FALSE(client.ping());
}
