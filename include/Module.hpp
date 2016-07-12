#pragma once

#include <Configuration.hpp>
#include <Core/MW/CoreModule.hpp>


class Module:
	public Core::MW::CoreModule
{
public:
	static bool
	initialize();

	Module();
	virtual ~Module() {}
};

