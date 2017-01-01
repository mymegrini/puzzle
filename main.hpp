#ifndef MAIN_HPP
#define MAIN_HPP

#include <getopt.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

static void usage(ostream& out) {
  out << "Usage: puzzle [-ahts] GAMENAME\n\
Example : puzzle -a taquin -s 9x16" << endl;
}

void parse_argv(int argc, char* argv[], int& n, int& m, bool& text,
				bool& human, string& game)
{  
  int32_t opt;
  int32_t index = 0;
    
  static struct option long_options[] = {
    {"auto", no_argument, NULL, 'a'},
    {"help", no_argument, NULL, 'h'},
    {"size", required_argument, NULL, 's'},
    {"text", no_argument, NULL, 't'},
    {0, 0, 0, 0}
  };
  
  while((opt = getopt_long_only(argc,argv,
				"ag:hs:t",long_options,&index)) !=-1){

    switch(opt){
    case 'h':
      usage(cout);
      cout << "\n\
2D Box Puzzle games.\n\
Available options:\n\
 -a, --auto\n\
\tuse automatic player\n\
 -s, --size\tHxW\n\
\tcustom grid size '\n\
 -t, --text\n\
\trun in text mode\n\
 -h, --help\n\
\tshow this help and exit." << endl;
      exit(0);
    case 'a':
      human = false;
      break;
    case 't':
      text = true;
      break;
    case 's': {
	  string size = string(optarg);
	  uint x = size.find('x');
	  if (x != string::npos){
		n = stoi(size.substr(0, x));
		m = stoi(size.substr(x+1));
	  } else {
		usage(cerr);
		exit(1);
	  }
      break;
	}
    default : /* '?' ':' */
      usage(cerr);
      exit(1);
    }
  }
  
  if (optind >= argc){
    cerr << "No game specified." << endl << "Available games: "
		 << "taquin, 2048, 2048D, 2035, sokoban" << endl;
	usage(cerr);
	exit(1);
  } else
	game = argv[optind++];
}

#endif
