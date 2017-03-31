#include <catch.hpp>
#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <string>
#include <list>

#include <url/path.hpp>
using url::path;

TEST_CASE("uploadint file to DISK", "[client][set][overwrite][file]") {

    std::string token = "AQAAAAATPnx3AAQXOJS1w4zmPUdrsJNR1FATxEM";
    path resource{ "/file.dat" };
    ydclient client{ token };
    bool overwrite=true;
    std::list<std::string> fields {};
    auto info = client.patch(to,from,overwrite,fields);
    REQUIRE(client.upload());
    
}
