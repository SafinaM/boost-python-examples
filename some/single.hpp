#include <string>
#pragma once

struct Config
{
	double coef;
	std::string path;
	int max_size;
	Config(double def_coef = 0.0, const std::string& def_path = "", int def_max_size = 0);
	~Config();
};

class Single
{

public:
	static int CurrentID();
	static Config &AppConfig();
	static void AppConfig(Config const&);

private:
	int mCurrentID = 0;
	Config mAppConfig;

	Single();
	Single(const Single&);

	static Single& Instance();

	int ThisCurrentID();
	Config& ThisAppConfig();
	void ThisAppConfig(Config const&);
};

