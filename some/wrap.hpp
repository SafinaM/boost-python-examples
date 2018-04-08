#pragma once

#include <boost/python.hpp>
#include "some.hpp"
#include "single.hpp"
#include <sstream>

using namespace boost::python;

std::string Some_Str(const Some &);
std::string Some_Repr(const Some &);
dict Some_ToDict( Some const& );
void Some_FromDict( Some&, dict const& );

std::string Config_Str( Config const& );
std::string Config_Repr( Config const& );
dict Config_ToDict( Config const& );
void Config_FromDict( Config&, dict const& );

Config* Single_CloneAppConfig();