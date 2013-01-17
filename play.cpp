
// original from
// https://github.com/mltframework/mlt/blob/master/src/examples/play.cpp

// Comments below added by Harry van Haaren, 2013

// this is the most basic "media player" code.
// it allows the automatic selection of types of producer and consumer,
// and the signal path is as direct as possible:
// producer -> consumer

// producer is a "source" or "input" of video material,
// consumer is a "sink"  or "output" of video material.

// Consumer pulls the data from the source, hence the
// consumer.connect( producer );
// The consumer can now ask for more data when it needs it.

// consumer.run(); tells consumer (the output device) to start working.
// then data gets pulled from producer, and displayed.


// compile: g++ play.cpp -I/usr/include/mlt -I/usr/include/mlt++ -lmlt++ -lmlt -o play

#include <Mlt.h>
using namespace Mlt;

int main( int, char **argv )
{
  Factory::init( NULL );
  
  Profile profile;
  
  Producer producer( profile, argv[ 1 ] );
  Consumer consumer( profile );
  
  consumer.set( "rescale", "none" );
  consumer.connect( producer );
  
  consumer.run( );
  
  Factory::close();
  
  return 0;
}
