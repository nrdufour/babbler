//
// scenario.h
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

#ifndef _SCENARIO_H_
#define _SCENARIO_H_

#include <string>
#include <map>
#include "babbler.h"

using namespace std;

class Scenario {
public:
  Scenario(int argc, char** argv);
  ~Scenario() { }

  Babbler* getBabbler();

  bool isLengthLimited() { return _isLengthLimited; }
  int  getLimitLength()  { return _limitLength;     }
  int  getNbTry()        { return _nbTry;           }

protected:
  bool            _isLengthLimited;
  int             _limitLength;
  int             _nbTry;
  map<string,int> _ressources;
};

#endif
