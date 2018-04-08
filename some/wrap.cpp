#include <boost/python.hpp>
#include <boost/thread.hpp>
#include "some.hpp"
#include "single.hpp"
#include "wrap.hpp"

using namespace boost::python;


BOOST_PYTHON_MODULE(example)
{
	class_<Some>( "Some" )
		.def(init<int,string>( args( "some_id", "name" ) ) )
		.def("ID", &Some::ID )
		.def("Name", &Some::Name, return_value_policy<copy_const_reference>() )
		.def("ResetID", static_cast< void (Some::*)() >( &Some::ResetID ) )
		.def("ResetID", static_cast< void (Some::*)(int) >(&Some::ResetID ), args("some_id"))
		.def("ChangeName", &Some::ChangeName, args("name"))
		.def("SomeChanges", &Some::SomeChanges, args("some_id", "name"))
		.def("__str__", Some_Str )
		.def("__repr__", Some_Repr )
		.add_static_property( "NOT_AN_IDENTIFIER", make_getter( &Some::NOT_AN_IDENTIFIER ) )
		;

	class_<Config>("Config", init<double, const std::string&, int>(args("coef", "path", "max_size")))
		.add_property( "coef", make_getter( &Config::coef ), make_setter( &Config::coef ) )
		.add_property( "path", make_getter( &Config::path ), make_setter( &Config::path ) )
		.add_property( "max_size", make_getter( &Config::max_size ), make_setter( &Config::max_size ) )
		.def("__str__", Config_Str)
		.def("__repr__", Config_Repr)
		.add_property("as_dict", Config_ToDict, Config_FromDict)
			;

	class_<Single, boost::noncopyable>( "Single", no_init )
		.def("CurrentID", &Single::CurrentID)
		.staticmethod("CurrentID" )
		.def("AppConfig", static_cast<Config& (*)()>( &Single::AppConfig ), return_value_policy<reference_existing_object>() )
		.def("AppConfig", static_cast< void (*)(Config const&)>(&Single::AppConfig) )
		.staticmethod("AppConfig")
		.add_static_property("current_id", &Single::CurrentID )
		.add_static_property("app_config", make_function( static_cast<Config& (*)()>( &Single::AppConfig ),
		return_value_policy<reference_existing_object>()),
			static_cast<void (*)(Config const&)>(&Single::AppConfig))
		.def("CloneAppConfig", Single_CloneAppConfig,
			  return_value_policy<manage_new_object>())
			;
}

std::string Some_Str(const Some& some )
{
	std::stringstream output;
	output << "{ ID: " << some.ID() << ", Name: '" << some.Name() << "' }";
	return output.str();
}

std::string Some_Repr( Some const& some )
{
	return "Some: " + Some_Str(some);
}

std::string Config_Str( Config const& config )
{
	std::stringstream output;
	output << "{ coef: " << config.coef << ", path: '" << config.path << "', max_size: " << config.max_size << " }";
	return output.str();
}

std::string Config_Repr(Config const& config)
{
	return "Config: " + Config_Str( config );
}

dict Config_ToDict( Config const& config )
{
	dict res;
	res["coef"] = config.coef;
	res["path"] = config.path;
	res["max_size"] = config.max_size;
	return res;
}

void Config_FromDict( Config& config, dict const& src )
{
	if (src.has_key("coef")) config.coef = extract<double>(src["coef"]);
	if (src.has_key("path")) config.path = extract<string>(src["path"]);
	if (src.has_key("max_size")) config.max_size = extract<int>(src["max_size"]);
}

Config* Single_CloneAppConfig()
{
	return new Config(Single::AppConfig());
}

