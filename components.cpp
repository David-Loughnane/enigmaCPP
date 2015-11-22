#include <iostream>
#include <fstream>
#include "components.h"
#include "errors.h"
using namespace std;


//PLUGBOARD DEFINITIONS
Plugboard::Plugboard() : mapping_count(0) {
  //body intentionally blank
}

int Plugboard::load_input(const char *mapping_file) {
  ifstream spec_input;

  spec_input.open(mapping_file);
  if (spec_input.is_open()) {
    while (spec_input >> mapping[mapping_count]) {
      if (mapping[mapping_count] < 0 || mapping[mapping_count] > 25) {
	cerr << "INVALID_INDEX" << endl;
	return INVALID_INDEX;
      }
      mapping_count++;
    }
    spec_input.close();
  }
  else if (spec_input.fail()) {
    cerr << "ERROR_OPENING_CONFIGURATION_FILE" << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  for (int i = 0; i < mapping_count; i++) {
    for (int j = 0; j < mapping_count; j++) {
      if ((mapping[i] == mapping[j]) && (i != j)) {
	cerr << "IMPOSSIBLE_PLUGBOARD_CONFIGURATION" << endl;
	return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
  }
  if (mapping_count % 2 == 1) {
    cerr << "INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS" << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  return NO_ERROR;
}


void Plugboard::map_input(int &input_value) {
  for (int i = 0; i < mapping_count; i++) {
    if (input_value == mapping[i]) {
      if ((i % 2) == 0) {
	input_value = mapping[i+1];
      }
      else {
	input_value = mapping[i-1];
      }
      break;
    }
  }
}
// PLUGBOARD DEFINITIONS END


// REFLECTOR DEFINITIONS
Reflector::Reflector() : mapping_count(0) {
  //body intentionally blank
}

int Reflector::load_input(const char *mapping_file) {
  ifstream spec_input;

  spec_input.open(mapping_file);
  if (spec_input.is_open()) {
    while(spec_input >> mapping[mapping_count]) {
      if (mapping[mapping_count] < 0 || mapping[mapping_count] > 25) {
	cerr << "INVALID_INDEX" << endl;
	return INVALID_INDEX;
      }
      mapping_count++;
    }
    spec_input.close();
  }
  else if (spec_input.fail()) {
    cerr << "ERROR_OPENING_CONFIGURATION_FILE" << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  for (int i = 0; i < mapping_count; i++) {
    for (int j = 0; j < mapping_count; j++) {
      if ((mapping[i] == mapping[j]) && (i != j)) {
	cerr << "INVALID_REFLECTOR_MAPPING" << endl;
	return INVALID_REFLECTOR_MAPPING;
      }
    }
  }
  if (mapping_count != 26) {
    cerr << "INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS" << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  return NO_ERROR;
}


void Reflector::map_input(int &input_value) {
  for (int i = 0; i < mapping_count; i++) {
    if (input_value == mapping[i]) {
      if ((i % 2) == 0) {
	input_value = mapping[i+1];
      }
      else {
	input_value = mapping[i-1];
      }
      break;
    }
  }
}
// REFLECTOR DEFINITIONS END


// ROTOR DEFINITIONS
int Rotor::rotor_count = 0;

Rotor::Rotor() : rotor_id(rotor_count++), mapping_count(0), 
		 notch_count(0),start_position(0),
		 relative_position(0) {
  //body intentionally blank
}

int Rotor::load_input(const char *mapping_file, const char* init_pos_file) {
  ifstream spec_input, start_input;

  spec_input.open(mapping_file);
  if (spec_input.is_open()) {
    //read the first 26 integers into the mapping array
    while((mapping_count < 26) && (spec_input >> mapping[mapping_count])) {
      if (mapping[mapping_count] < 0 || mapping[mapping_count] > 25) {
	cerr << "INVALID_INDEX" << endl;
	return INVALID_INDEX;
      }
      mapping_count++;
    }
    //read remaining integers into notch array
    while(spec_input >> notches[notch_count]) {
      if (notches[notch_count] < 0 || notches[notch_count] > 25) {
	cerr << "INVALID_INDEX" << endl;
	return INVALID_INDEX;
      }
      notch_count++;
    }
    spec_input.close();
  }
  else if (spec_input.fail()) {
    cerr << "ERROR_OPENING_CONFIGURATION_FILE" << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  if (mapping_count != 26) {
    cerr << "INVALID_ROTOR_MAPPING" <<endl;
    return INVALID_ROTOR_MAPPING;
  }
  for (int i = 0; i < mapping_count; i++) {
    for (int j = 0; j < mapping_count; j++) {
      if ((mapping[i] == mapping[j]) && (i != j)) {
	cerr << "Not all inputs mapped in rotor file: " << mapping_file  << endl;
	return INVALID_ROTOR_MAPPING;
      }
    }
  }

  if (notch_count < 1 || notch_count > 26) {
    cerr << "INVALID_ROTOR_MAPPING" << endl;
    return INVALID_ROTOR_MAPPING;
  }
  for (int i = 0; i < notch_count; i++) {
    for (int j = 0; j < notch_count; j++) {
      if ((notches[i] == notches[j]) && (i != j)) {
	cerr << "INVALID_ROTOR_MAPPING" << endl;
	  return INVALID_ROTOR_MAPPING;
      }
    }
  }

 start_input.open(init_pos_file);
  if (start_input.is_open()) {
    int temp = -99, input_counter = 0;
    while(start_input >> temp) { //which one
      if (input_counter == rotor_id) {
	start_position = temp;
	relative_position = start_position;
	if (start_position < 0 || start_position > 25) {
	  cerr << "INVALID_INDEX" << endl;
	  return INVALID_INDEX;
	}
      }
      input_counter++;
    }
    spec_input.close();
  }
  else if (start_input.fail()) {
    cerr << "ERROR_OPENING_CONFIGURATION_FILE" << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  return NO_ERROR;
}


void Rotor::map_input(int &input_value) {
  //set_relative_mapping();
  for (int i = 0; i < MAX_ELEMENTS; i++) {
    if (input_value == relative_mapping[i]) {
      if ((i % 2) == 0) {
	input_value = relative_mapping[i+1];
      }
      else {
	input_value = relative_mapping[i-1];
      }
      break;
    }
  }
}

void Rotor::set_relative_mapping(){
  int relative_index = 0;
  for (int i = 0; i < MAX_ELEMENTS; i++) {
    relative_index = ((i - relative_position) % MAX_ELEMENTS);
    if ((i - relative_position) < 0) {
      relative_index += MAX_ELEMENTS;
    }
    relative_mapping[relative_index] = mapping[i];
  }
}

// ROTOR DEFINITIONS END

