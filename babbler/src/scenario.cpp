//
// scenario.cpp
//

/*
Babbler 0.1
Copyright (C) 2003 Nicolas Dufour

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "config.h"
#include "scenario.h"
#include <iostream>
#include <getopt.h>

const int DEFAULT_LIMIT_LENGTH = 6;
const int DEFAULT_NB_TRY       = 10;
const int DEFAULT_WEIGHT       = 100;

Scenario::Scenario(int argc, char** argv) {
  _isLengthLimited = false;
  _limitLength     = DEFAULT_LIMIT_LENGTH;
  _nbTry           = DEFAULT_NB_TRY;
  char c          = '\0';

  while( (c = getopt(argc,argv,"hn:l:r:v")) != -1) {
    switch(c) {
      case 'h': {
        cout << "Usage: babbler { -r 'filename:weight' } [ -n nbTry ] [ -l limitLength ]" << endl;
	cout << "\t-r : add a new ressource file (1-n themes):" << endl;
	cout << "\t\tfilename : text file (list of terms" << endl;
	cout << "\t\tweight : associated weight to this theme of terms" << endl;
	cout << "\t-n : # of new generated words" << endl;
	cout << "\t-l : limit the length of generated words" << endl;
	cout << "\t-v : display the verson" << endl;
	exit(0);
        break;
      }
      case 'n': {
        _nbTry = atoi(optarg);
        break;
      }
      case 'l': {
        _isLengthLimited = true;
	_limitLength = atoi(optarg);
        break;
      }
      case 'r': {
        string res(optarg);
        string::size_type pos = res.find(":");
	int weight = DEFAULT_WEIGHT;
        if(pos != string::npos) {
	  string name = res.substr(0,pos);
	  string weightString = res.substr(pos+1,res.length()-pos-1);
	  _ressources[name] = atoi(weightString.c_str());
	}
	else {
	}
        break;
      }
      case 'v': {
      	cout << PACKAGE << " " << VERSION << endl;
	exit(0);
      	break;
      }
    }
  } // end while
}


Babbler* Scenario::getBabbler() {
  Babbler* babbler = new Babbler();
  
  for(map<string,int>::iterator iter = _ressources.begin(); iter != _ressources.end(); iter++) {
    int currentProportion = (*iter).second;
    string currentFilename = (*iter).first;
    babbler->addFile(currentProportion, currentFilename);
  }

  return babbler;
}


