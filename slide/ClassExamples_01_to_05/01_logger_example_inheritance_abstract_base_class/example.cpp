//README: This example is just a very simple illustration of the concept of
//        abstract base classes. It defines a base-class Logger, which is then
//        inherited by either a ConsoleLogger or a FileLogger. The main function
//        uses (after initialization) only the abstract interface, which demonstrates
//        the flexibility in writing our code.
//        Note: The example uses simple C-style I/O.
//        Note: The example just has everything in one file, ideally we would
//              like to have different files for all class definitions/implementations.

#include <stdio.h>

class Logger {
public:
  Logger();
  virtual ~Logger();

  virtual void write( int number );
};

Logger::Logger() {
}

Logger::~Logger() {
}

void
Logger::write( int number ){
}

class ConsoleLogger : public Logger {
public:
  ConsoleLogger();
  virtual ~ConsoleLogger();

  virtual void write( int number );
};

ConsoleLogger::ConsoleLogger() {
}

ConsoleLogger::~ConsoleLogger() {
}

void
ConsoleLogger::write( int number ) {
  printf( "%d\n", number );
}

class FileLogger : public Logger {
public:
  FileLogger( char * path );
  virtual ~FileLogger();

  virtual void write( int number );

private:
  FILE * m_fp;
};

FileLogger::FileLogger( char * path ) {
  m_fp = fopen(path,"w");
}

FileLogger::~FileLogger() {
  fclose( m_fp );
}

void
FileLogger::write( int number ) {
  fprintf( m_fp, "%d\n", number );
}

int main()
{
  //The pointer we are going to use in an abstract way (could be a global variable accessed from anywhere)
  Logger * log;

  //Initialization (the only part which is child-class specific)
  if(true) {
    log = new ConsoleLogger();
  } else {
    log = new FileLogger( "/Users/laurent/Documents/CS_100/log.txt" );
  }

  //Using and deleting the logger in an abstract way
  log->write(10);
  delete log;

  return 0;
}