#include "instancesMap.h"

namespace test
{
	bool InstancesMap::set(int key, void * instance)
	{
		if (exists(key))
			return false;
		instances.insert(pair<int, void *>(key, instance));
		return true;
	}

	void * InstancesMap::get(int key)
	{
		map<int, void *>::iterator itr = instances.find(key);
		if (itr == instances.end())
			return nullptr;
		return itr->second;
	}

	bool InstancesMap::exists(int key)
	{
		map<int, void *>::iterator itr = instances.find(key);
		return itr != instances.end();
	}

	map<int, void *> InstancesMap::instances;
}
