//
// dictreader.cpp
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

#include "dictreader.h"
#include <fstream>
#include <iostream>

const long BUFFER_LENGTH = 1024;

DictReader::DictReader(string filename) {
  _filename = filename;
  if(filename.length() == 0) {
    _name = "";
    return;
  }

  ifstream stream;
  char buffer[BUFFER_LENGTH] = "";
  long counter = 0;
  string currentLine = "";

  stream.open(filename.c_str());

  while(stream) {
    stream.getline(buffer,BUFFER_LENGTH);
    currentLine = buffer;

    if(stream.eof()) break;
    if(counter == 0 && currentLine[0] == '%') {
      _name = currentLine.substr(1);
      continue;
    }
    
    _terms.push_back(string(buffer));
    counter++;
  }
  stream.close();

  //_terms.sort();
}

