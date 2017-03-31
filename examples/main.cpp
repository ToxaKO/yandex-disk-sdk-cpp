#include <yadisk/client.hpp>

int main()
{
  yadisk::Client client{"token"};
  client.upload("file.dat","http://hostname/path/to/file.dat",true);
}
