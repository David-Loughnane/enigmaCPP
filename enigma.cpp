#include <iostream>
#include <fstream>
#include <iomanip>
#include "errors.h"
#include "components.h"
using namespace std;


int main(int argc, char **argv) {
  /*cout << "There are " << argc << " arguments:" << endl;
  for (int nArg = 0; nArg < argc; nArg++)
  cout << nArg << " " << argv[nArg] << endl;*/

  Plugboard enigmaPlugboard;
  enigmaPlugboard.load_input(argv[1]);

  Reflector enigmaReflector;
  enigmaReflector.load_input(argv[2]);

  typedef Rotor** PtrRotorPtr;
  typedef Rotor* RotorPtr;
  PtrRotorPtr rotors_array;
  int rotors_index = 0;

  //test to see if rotors in command line arguments
  //bool set to true if no rotors are included
  bool no_rotors;
  if (argc > 3) {
    no_rotors = false;
  }
  else {
    no_rotors = true;
  }

  if (!no_rotors) {
    rotors_array = new RotorPtr[argc - 4];
    for (int file_index = 3; file_index < (argc - 1); file_index++) {
      RotorPtr rotor;
      rotor = new Rotor();
      rotors_array[rotors_index] = rotor;
      rotors_index++;
    }
    for (int i = 0; i < rotors_index; i++) {
      rotors_array[i]->load_input(argv[3 + i], argv[argc - 1]);
    }
  }

  char input_char, output_char;
  while (cin >> input_char) {

    int input_int = input_char - 65;

    rotors_array[0]->relative_position++;
    rotors_array[0]->set_relative_mapping();

    for (int i = 0; i < (rotors_index - 1); i++) {
      for (int j = 0; j < rotors_array[i]->notch_count; j++) {
	if (rotors_array[i]->relative_mapping[0] == rotors_array[i]->notches[j]) {
	  rotors_array[i+1]->relative_position++;
	  rotors_array[i+1]->set_relative_mapping();
	}
      }
    }

    enigmaPlugboard.map_input(input_int);

    if (!no_rotors) {
      for (int i = 0; i < rotors_index; i++) {
	rotors_array[i]->map_input(input_int);
      }
    }

    enigmaReflector.map_input(input_int);
  
    if (!no_rotors) {
      for (int i = (rotors_index - 1); i >= 0; i--) {  
	rotors_array[i]->map_input(input_int);
      }
    }
    
    enigmaPlugboard.map_input(input_int);

    output_char = input_int + 65;
    cout << output_char;
  }
  cout << endl;

  //clean up dynamic memory, first each rotor in array, then array
  if (!no_rotors) {
    for(int i = 0; i < rotors_index; i++) {
      delete rotors_array[i];
    }
    delete [] rotors_array;
  }

  return 0;
}


