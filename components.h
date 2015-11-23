#ifndef COMPONENTS_H
#define COMPONENTS_H

const int MAX_ELEMENTS = 26;

class Plugboard {
public:
  //constructor - sets all values to zero
  Plugboard();
  //loads data from file, and check for errors
  int load_input(const char *mapping_file);
  //maps the input value to corresponding pair in mapping array
  void map_input(int &input_value);
private:
  //number of mappings in the mapping array
  int mapping_count;
  //contains the mappings of inputs to outputs
  int mapping[MAX_ELEMENTS];
};

class Reflector {
public:
  //constructor - sets all values to zero
  Reflector();
  //loads data from file, and check for errors
  int load_input(const char *mapping_file);
  //maps the input value to corresponding pair in mapping array
  void map_input(int &input_value);
private:
  //number of mappings in the mapping array
  int mapping_count;
  //contains the mappings of inputs to outputs
  int mapping[MAX_ELEMENTS];
};

class Rotor {
public:
  //constructor - sets all values to zero
  Rotor();
  //loads rotor mapping from 1st argument, inital position of rotors in 2nd argument
  int load_input(const char *mapping_file, const char *init_pos_file);
  //maps the input value to value in the mapping array at that index position
  void map_input(int &input_value);
  //reverses the map_input process - maps from array value to corresponding index
  void reverse_map_input(int &input_value);
  //class variable
  static int rotor_count;
  //assigns a unique id to each rotor
  const int rotor_id;
  //intial mapping array adjusted for staring position and rotations
  void set_relative_mapping();
  //count of elements in mapping array - expected 26
  int mapping_count;
  //absolute mapping internal to rotor
  int mapping[MAX_ELEMENTS];
  //count of notches external to rotor
  int notch_count;
  //array that holds notches
  int notches[MAX_ELEMENTS];
  //relative intial position of rotor read from config file
  int start_position;
  //start position + number of rotations so far
  int relative_position;
  //absolute mapping adjusted for the relative position
  int relative_mapping[MAX_ELEMENTS];
};


#endif
