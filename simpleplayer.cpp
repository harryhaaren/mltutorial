/*
  
  Taken from http://ubuntuforums.org/showthread.php?p=7370184
  
  Adapted fixing crashes & cleanup by Harry van Haaren 2013
  
  
  MLT++ Player Example
  
  g++ simpleplayer.cpp -I/usr/include/mlt -I/usr/include/mlt++ -lmlt++ -lmlt -o simpleplayer
  
  Usage: simpleplayer <file>
  
  http://www.mltframework.org/twiki/bin/view/MLT/Framework
*/

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
  Mlt::Producer *producer;
  
  profile = new Mlt::Profile();
  
  // Create the default consumer
  consumer = new Mlt::Consumer( *profile,"sdl");
  
  // Create via the default producer
  producer = new Mlt::Producer( *profile,NULL, argv[ 1 ] );
  
  // Connect the producer to the consumer
  consumer->connect(*producer);
  
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
