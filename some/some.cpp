#include "some.hpp"

const int Some::NOT_AN_IDENTIFIER = -1;

Some::Some()
		: mID(NOT_AN_IDENTIFIER)
{
}

Some::Some( int some_id, string const& name )
		: mID(some_id), mName(name)
{
}

int Some::ID() const
{
	return mID;
}

string const& Some::Name() const
{
	return mName;
}

void Some::ResetID()
{
	mID = NOT_AN_IDENTIFIER;
}

void Some::ResetID( int some_id )
{
	mID = some_id;
}

void Some::ChangeName( string const& name )
{
	mName = name;
}

void Some::SomeChanges( int some_id, string const& name )
{
	mID = some_id;
	mName = name;
}