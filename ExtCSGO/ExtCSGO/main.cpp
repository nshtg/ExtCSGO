#include <Update.h>

int main(int argc, char* argv[])
{
	if (argc < 5)
		return 0;
	return ExtCSGO::Update(argv).Run();
}