//
// main.cpp
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

#include <cstdlib>
#include <time.h>
#include "babbler.h"
#include "scenario.h"

/*
 * Babbler v1.0-rc1
 *
 * eheh it was fun to create it ;-)
 * Just start with a talk with a friend !
 *
 */

int main(int argc, char** argv) {
  string result;
  long now = 0;
  time(&now);
  srandom(now);

  Scenario* scenario = new Scenario(argc,argv);
  Babbler*  babbler  = scenario->getBabbler();

  bool isLimited  = scenario->isLengthLimited();
  int nbTry       = scenario->getNbTry();
  int limitLength = scenario->getLimitLength();

  for(int indexTry = 0; indexTry < nbTry; indexTry++) {
    for(;;) {
      result = babbler->babble();

      if(isLimited == true) {
      	if( result.length() <= limitLength && result.length() >= 3 ) {
          break;
	}
      }
      else {
        if(result.length() >= 3) {
	        break;
	}
      }

    }
    cout << result << endl;
  }

  delete babbler;
  delete scenario;

  return EXIT_SUCCESS;
}
