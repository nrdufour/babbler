//
// dictreader.h
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

#ifndef __DICTREADER__
#define __DICTREADER__

#include <string>
#include <vector>

using namespace std;

class DictReader {
public:
  DictReader(string filename);
  ~DictReader() { }

  string         getFilename() { return _filename; }
  string         getName()     { return _name;     }
  vector<string> getTerms()    { return _terms;    }

protected:
  vector<string> _terms;
  string         _filename;
  string         _name;
};

#endif
