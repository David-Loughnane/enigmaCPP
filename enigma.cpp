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

  if (argc < 3) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  int load_failure = 0;

  Plugboard enigmaPlugboard;
  load_failure = enigmaPlugboard.load_input(argv[1]);
  if (load_failure) {
    return load_failure;
  }

  Reflector enigmaReflector;
  enigmaReflector.load_input(argv[2]);
  if (load_failure) {
    return load_failure;
  }

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
      //ut << "Rotors index " << rotors_index << endl;
      rotors_index++;
    }
    for (int i = 0; i < rotors_index; i++) {
      load_failure = rotors_array[i]->load_input(argv[3 + i], argv[argc - 1]);
      if (load_failure) {
	return load_failure;
      }
    }
  }

  /*TEST HEADER*/
  /*cout << setw(6) << "CHAR" << setw(6) << "INT";
  cout << setw(6) << "PLUG";

  if (!no_rotors) {
    for (int i = 0; i < rotors_index; i++) {
      cout << setw(6) << "ROTR";
    }
  }

  cout <<setw(6) << "RFLCT";

  if (!no_rotors) {
    for (int i = 0; i < rotors_index; i++) {
      cout << setw(6) << "ROTR";
    }
  }  

  cout << setw(6) << "PLUG";
  cout << setw(6) << "CHAR" << endl;*/


  char input_char, output_char;
  while (cin >> input_char) {
    if (input_char < 'A' || input_char > 'Z') {
      cerr << input_char << " is not a valid input character"
      << " (input characters must be upper case letters A-Z)!";
      return INVALID_INPUT_CHARACTER;
    }
    //cout << setw(6) << input_char;
    int input_int = input_char - 65;
    //cout << setw(6) << input_int;

    /*    for (int i = 0; i < rotors_array[0]->mapping_count; i++) {
      cout << setw(3) << rotors_array[0]->relative_mapping[i] << " ";
    }
    cout << endl;*/

  if (!no_rotors) {    
    //cout << rotors_array[0]->relative_position << " ";
    rotors_array[rotors_index - 1]->relative_position++;
    //cout << rotors_array[0]->relative_position << endl;
    rotors_array[rotors_index - 1]->set_relative_mapping();
  }

  /*for (int i = 0; i < rotors_array[0]->mapping_count; i++ ){
    cout << setw(3) << rotors_array[0]->relative_mapping[i] << " ";
  }
  cout << endl << endl;*/

  for (int i = (rotors_index - 1); i >= 0; i--) {
    for (int j = 0; j < rotors_array[i]->notch_count; j++) {
      if (rotors_array[i]->relative_mapping[0] == rotors_array[i]->notches[j]) {
	rotors_array[i-1]->relative_position++;
	rotors_array[i-1]->set_relative_mapping();
      }
    }
  }

  enigmaPlugboard.map_input(input_int);
  //cout << setw(6) << input_int;

  if (!no_rotors) {
    for (int i = (rotors_index - 1); i >= 0; i--) {
      rotors_array[i]->map_input(input_int);
      //cout << setw(6) << input_int;
    }
  }

  enigmaReflector.map_input(input_int);
  //cout << setw(6) << input_int;
  
  if (!no_rotors) {
    for (int i = 0; i < rotors_index; i++) {
      rotors_array[i]->reverse_map_input(input_int);
      //cout << setw(6) << input_int;
    }
  }
    
  enigmaPlugboard.map_input(input_int);
  //cout << setw(6) << input_int;


  output_char = input_int + 65;
  //cout << setw(6) << output_char << endl;
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


