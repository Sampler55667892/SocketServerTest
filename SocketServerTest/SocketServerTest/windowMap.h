#ifndef _windowMap_h_
#define _windowMap_h_

#include <map>
#include "windowBase.h"

using namespace std;

namespace frame
{
	// {Singleton}
	class WindowMap
	{
		public:
			static WindowMap * instance()
			{
				if (ob == nullptr)
					ob = new WindowMap();
				return ob;
			}

			bool add(int key, WindowBase * window)
			{
				WindowBase * found = get(key);
				if (found == nullptr)
					return false;
				mapWindow.insert(pair<int, WindowBase *>(key, window));
				return true;
			}

			WindowBase * get(int key)
			{
				map<int, WindowBase *>::iterator itr = mapWindow.find(key);
				return itr != mapWindow.end() ? itr->second : nullptr;
			}

		private:
			WindowMap();
			map<int, WindowBase *> mapWindow;
			static WindowMap * ob;
	};
}

#endif // _windowMap_h_