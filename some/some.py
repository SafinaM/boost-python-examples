from example import *

# a = Some()
a = Config(1.0, ".", 1)
c = a
# c = Single.AppConfig(a)
# c = Single.CloneAppConfig()
c.coef = 11.11; c.path = 'cloned'; c.max_size = 111111
print( "c.coef = 12.34; c.path = 'cloned'; c.max_size = 100500" )
print( "c:", c ); print( "Single.AppConfig():", Single.AppConfig() )
print( "c = Single.CloneAppConfig()" ); c = Single.CloneAppConfig()
c.coef = 22.22; c.path = 'another'; c.max_size = 222222
print( "c.coef = 22.22; c.path = 'another'; c.max_size = 222222" )
print( "c:", c ); print( "Single.app_config:", Single.app_config )
print( "c = None" ); c = None
print( "Single.app_config:", Single.app_config )