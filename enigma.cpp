#include <iostream>
#include <fstream>
#include <iomanip>
#include "errors.h"
#include "components.h"
using namespace std;


int main(int argc, char **argv) {

  //error if less than 3 command line arguments provided
  if (argc < 3) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  int load_failure = 0;

  //load Plugboard from 2nd cmd line arg
  Plugboard enigmaPlugboard;
  load_failure = enigmaPlugboard.load_input(argv[1]);
  if (load_failure) {
    return load_failure;
  }

  //load Reflector from 3rd cmd line arg
  Reflector enigmaReflector;
  enigmaReflector.load_input(argv[2]);
  if (load_failure) {
    return load_failure;
  }

  //define array of pointers to Rotors
  typedef Rotor** PtrRotorPtr;
  typedef Rotor* RotorPtr;
  PtrRotorPtr rotors_array;
  int rotors_index = 0;

  //if cmd line args < 3 then there are no Rotors
  bool no_rotors;
  if (argc > 3) {
    no_rotors = false;
  }
  else {
    no_rotors = true;
  }

  //call Rotor constructor for each Rotor cmd line arg
  if (!no_rotors) {
    rotors_array = new RotorPtr[argc - 4];
    for (int file_index = 3; file_index < (argc - 1); file_index++) {
      RotorPtr rotor;
      rotor = new Rotor();
      rotors_array[rotors_index] = rotor;
      rotors_index++;
    }
    //laod Rotor configurations
    for (int i = 0; i < rotors_index; i++) {
      load_failure = rotors_array[i]->load_input(argv[3 + i], argv[argc - 1]);
      if (load_failure) {
	return load_failure;
      }
      rotors_array[i]->set_relative_mapping();
    }
  }

  char input_char, output_char;
  //input character, skip whitespace
  while (cin >> input_char) {
    if (input_char < 'A' || input_char > 'Z') {
      cerr << input_char << " is not a valid input character"
      << " (input characters must be upper case letters A-Z)!";
      return INVALID_INPUT_CHARACTER;
    }
    int input_int = input_char - 65;

    //every time key is pressed, right hand rotor rotates, relative mapping updated
    if (!no_rotors) {
      rotors_array[rotors_index - 1]->relative_position++;
      rotors_array[rotors_index - 1]->set_relative_mapping();
    }

  
  for (int i = (rotors_index - 1); i >= 0; i--) {
    for (int j = 0; j < rotors_array[i]->notch_count; j++) {
      if ((rotors_array[i]->relative_position % 26) == rotors_array[i]->notches[j]) {
	rotors_array[i-1]->relative_position++;
	rotors_array[i-1]->set_relative_mapping();
      }
    }
  }

  enigmaPlugboard.map_input(input_int);

  if (!no_rotors) {
    for (int i = (rotors_index - 1); i >= 0; i--) {
      rotors_array[i]->map_input(input_int);
    }
  }

  enigmaReflector.map_input(input_int);
  
  if (!no_rotors) {
    for (int i = 0; i < rotors_index; i++) {
      rotors_array[i]->reverse_map_input(input_int);
    }
  }
    
  enigmaPlugboard.map_input(input_int);
  
  //final int value mapped to uppercase char
  output_char = input_int + 65;
  cout << output_char;
  }

  //clean up dynamic memory, first each rotor in array, then array
  if (!no_rotors) {
    for(int i = 0; i < rotors_index; i++) {
      delete rotors_array[i];
    }
    delete [] rotors_array;
  }

  return 0;
}


