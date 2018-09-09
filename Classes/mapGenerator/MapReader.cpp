#include "MapReader.h"

void MapReader::readMap()
{
	using json = nlohmann::json;
	json j2 = {
				{ "pi", 3.141 },
				{ "happy", true },
				{ "name", "Niels" },
				{ "nothing", nullptr },
				{ "answer",{
					{ "everything", 42 }
				} },
				{ "list",{ 1, 0, 2 } },
				{ "object",{
					{ "currency", "USD" },
				{ "value", 42.99 }
				} }
			};

	int v_integer = j2.value("pi", 0);
	double v_floating = j2.value("floating", 47.11);

	std::ifstream ifs("map.json");
	if (ifs.fail()) {
		CCLOG("fail to read file!");
	}
	json j = json::parse(ifs);
	string aa = j.value("aa", "bb");

	//CCLOG("map reader ! %s", j);
}
