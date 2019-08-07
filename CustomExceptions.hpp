#pragma once
#include <exception>

namespace CourseWork_WinApi
{
	namespace cex
	{
		class InvalidOperationException
			:public std::exception
		{
		public:
			InvalidOperationException()
				:exception("invalid operation")
			{
			}

			explicit InvalidOperationException(char const* const _Message) throw()
				:exception(_Message)
			{
			}
		};

		class NoCurrentUserException
			:public InvalidOperationException
		{
		public:
			NoCurrentUserException()
				:InvalidOperationException("no current user")
			{
			}
		};

	}

}