#ifndef COMPONENTS_H
#define COMPONENTS_H

const int MAX_ELEMENTS = 26;

class Plugboard {
public:
  Plugboard();
  int load_input(const char *mapping_file);
  void map_input(int &input_value);
private:
  int mapping_count;
  int mapping[MAX_ELEMENTS];
};

class Reflector {
public:
  Reflector();
  int load_input(const char *mapping_file);
  void map_input(int &input_value);
private:
  int mapping_count;
  int mapping[MAX_ELEMENTS];
};

class Rotor {
public:
  Rotor();
  int load_input(const char *mapping_file, const char *init_pso_file);
  void map_input(int &input_value);
  static int rotor_count;
  const int rotor_id;
private:
  int mapping_count;
  int mapping[MAX_ELEMENTS];
  int notch_count;
  int notches[MAX_ELEMENTS];
  int start_position;
};


#endif
