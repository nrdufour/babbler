//
// base.h
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


#ifndef __BASE__
#define __BASE__

#include <string>
#include <vector>
#include "dictreader.h"

using namespace std;

class Base {
public:
  Base();
  ~Base() { }

  void addDict(int proportion, DictReader dict);
  vector<string> getRandomTermList();
  int getNbDict() { return _dicts.size(); }

protected:
  void computeRanges();
  
  vector<DictReader> _dicts;
  vector<int>        _ranges;
  vector<int>        _proportions;
  int                _total;
};

#endif
