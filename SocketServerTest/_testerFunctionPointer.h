#ifndef __testerFunctionPointer_h_
#define __testerFunctionPointer_h_

namespace _tester
{
	class _TesterFunctionPointer
	{
		typedef void(*_TestCallback)(int);
		typedef void(_TesterFunctionPointer::*_TestCallback2)(int);

		static void _a(void(*a)(int))
		{
			a(10);
		}

		static void _b(_TestCallback b)
		{
			b(20);
		}

		void _c(void(_TesterFunctionPointer::*c)(int))
		{
			(this->*c)(30);
		}

		void _d(_TesterFunctionPointer::_TestCallback2 d)
		{
			(this->*d)(40);
		}
	};
}

#endif // __testerFunctionPointer_h_
