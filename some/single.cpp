#include "single.hpp"
#include <boost/thread.hpp>

using boost::mutex;
using boost::unique_lock;

const double CONFIG_DEFAULT_COEFF = 2.5;
const int CONFIG_DEFAULT_MAX_SIZE = 0x1000;
const std::string CONFIG_DEFAULT_PATH = ".";

struct Config;

int Single::CurrentID()
{
	return Instance().ThisCurrentID();
}

Config& Single::AppConfig()
{
	return Instance().ThisAppConfig();
}

void Single::AppConfig(const Config& config)
{
	Instance().ThisAppConfig(config);
}

Single::Single() : mCurrentID( 0 )
{
	mAppConfig.coef = CONFIG_DEFAULT_COEFF;
	mAppConfig.max_size = CONFIG_DEFAULT_MAX_SIZE;
	mAppConfig.path = CONFIG_DEFAULT_PATH;
}

Single& Single::Instance()
{
	static mutex single_mutex;
	unique_lock<mutex> single_lock(single_mutex);
	static Single instance;

	return instance;
}

int Single::ThisCurrentID()
{
	static mutex id_mutex;
	unique_lock<mutex> id_lock(id_mutex);
	return ++mCurrentID;
}

Config& Single::ThisAppConfig()
{
	return mAppConfig;
}

void Single::ThisAppConfig(const Config& config)
{
	mAppConfig = config;
}

Config::~Config()
{
	std::cout << "Config destructor of Config: { coef: " << coef
		 << ", path: '" << path
		 << "', max_size: " << max_size << " }" << std::endl;
}

Config::Config(double def_coef, const std::string &def_path, int def_max_size) :
		coef(def_coef), path(def_path), max_size(def_max_size) {}

