
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<string> commands;

	commands.push_back("pushd C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\Common7\\Tools");
	commands.push_back("VsDevCmd.bat");
	commands.push_back("popd");
	commands.push_back("msbuild build.vcxproj /p:configuration=debug");

	string command = "";
	for (string c : commands)
	{
		if (command != "")
			command += " && ";

		command += c;
	}

	if (system(NULL))
		system(command.c_str());

	if (system(NULL))
		system("start ./Build/app.exe");

	return 0;
}