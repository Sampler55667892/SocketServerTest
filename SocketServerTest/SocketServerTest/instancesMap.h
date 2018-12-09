#ifndef _instancesMap_h_
#define _instancesMap_h_

#include <map>

namespace test
{
	using namespace std;

	class InstancesMap
	{
		public:
			static bool set(int key, void * instance);
			static void * get(int key);
		private:
			static bool exists(int key);
			static map<int, void *> instances;
	};
}

#endif // _instancesMap_h_
