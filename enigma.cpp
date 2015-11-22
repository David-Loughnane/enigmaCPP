#include <iostream>
#include <fstream>
#include <iomanip>
#include "errors.h"
#include "components.h"
using namespace std;


int main(int argc, char **argv) {
  cout << "There are " << argc << " arguments:" << endl;
  for (int nArg = 0; nArg < argc; nArg++)
  cout << nArg << " " << argv[nArg] << endl;

  Plugboard enigmaPlugboard;
  enigmaPlugboard.load_input(argv[1]);

  Reflector enigmaReflector;
  enigmaReflector.load_input(argv[2]);

  typedef Rotor** PtrRotorPtr;
  typedef Rotor* RotorPtr;
  PtrRotorPtr rotors_array;
  int rotors_index = 0;

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
      //rotor->load_input(argv[file_index], argv[argc -1]);
      rotors_array[rotors_index] = rotor;
      rotors_index++;
    }
    for (int i = 0; i < rotors_index; i++) {
      rotors_array[i]->load_input(argv[rotors_index], argv[argc - 1]);
    }
  }

  cout << setw(6) << "CHAR" << setw(6) << "INT";
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

  cout  << setw(6) << "PLUG" << endl;


  char input_char;
  while (cin >> input_char) {

    cout << setw(6) << input_char;
    int input_int = input_char - 65;
    cout << setw(6) << input_int;

    enigmaPlugboard.map_input(input_int);
    cout << setw(6) << input_int;

  if (!no_rotors) {
    for (int i = 0; i < rotors_index; i++) {   
      rotors_array[i]->map_input(input_int);
      cout << setw(6) << input_int;
    }
  }

    enigmaReflector.map_input(input_int);
    cout << setw(6) << input_int;
  
  if (!no_rotors) {
    for (int i = (rotors_index - 1); i >= 0; i--) {   
      rotors_array[i]->map_input(input_int);
      cout << setw(6) << input_int;
    }
  }
    
    enigmaPlugboard.map_input(input_int);
    cout << setw(6) << input_int;
    
    cout << endl;
  }
  
  if (!no_rotors) {
    for (int i = 0; i < rotors_index; i++) {  
      cout << endl << rotors_array[i]->rotor_id << " "; 
    }
    cout << endl;
  }

  if (!no_rotors) {
    for(int i = 0; i < rotors_index; i++) {
      delete rotors_array[i];
    }
    delete [] rotors_array;
  }

  return 0;
}



