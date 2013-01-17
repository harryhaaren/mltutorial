/*
  
  Taken from http://ubuntuforums.org/showthread.php?p=7370184
  
  Adapted fixing crashes & cleanup by Harry van Haaren 2013
  Filtering added by Harry van Haaren, 2013
  
  MLT++ Filter Player Example
  
  g++ filterplayer.cpp -I/usr/include/mlt -I/usr/include/mlt++ -lmlt++ -lmlt -o filterplayer
  
  Usage: filterplayer <file>
*/

// this filterplayer is based on simpleplayer.cpp, if you haven't looked at that
// yet, do so before looking here. These comments only explain the increment
// between the files.

// So we add a greyscale filter, the new video chain now looks like this:
// producer -> filter -> consumer

// the consumer still requests data, but does so from the filter, and the filter
// in turn requests data from the producer.

// See this link for a full list of filter plugins available
// http://www.mltframework.org/bin/view/MLT/PluginsFilters

#include <iostream>
#include <unistd.h>
#include <Mlt.h>

using namespace std;

int main( int argc, char *argv[] )
{
  
  Mlt::Repository *repository;
  
  // initialise the factory
  repository = Mlt::Factory::init();
  
  if ( not repository )
  {
    cout << "Unable to locate factory modules" << endl;
  }
  
  Mlt::Profile *profile;
  Mlt::Consumer *consumer;
  Mlt::Filter   *filter;
  Mlt::Producer *producer;
  
  profile = new Mlt::Profile();
  
  // Create the default consumer
  consumer = new Mlt::Consumer( *profile,"sdl");
  
  // try out some different filters :)
  filter   = new Mlt::Filter  ( *profile, "greyscale");
  //filter   = new Mlt::Filter  ( *profile, "invert");
  //filter   = new Mlt::Filter  ( *profile, "tcolor");
  //filter   = new Mlt::Filter  ( *profile, "threshold");
  
  if ( !filter )
  {
    cout << "Error creating filter! " << endl;
  }
  else
  {
    cout << "Filter created successfully" << endl;
  }
  
  // Create via the default producer
  producer = new Mlt::Producer( *profile,NULL, argv[ 1 ] );
  
  filter->connect( *producer );
  
  // Connect the producer to the consumer
  consumer->connect(*filter);
  
  // Start the consumer
  consumer->start();
  
  // Wait for the consumer to terminate
  while( !consumer->is_stopped() )
      sleep( 1 );
  
  // Close the consumer
  delete(consumer);
  
  // Close the producer
  delete(producer);
  
  // Close the factory
  Mlt::Factory::close();
  
  return 0;
}
