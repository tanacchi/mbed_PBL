enum struct Mode {
  INIT,
  MODE_SELECT,
  THERMOMETER,
  COUNTER
};

void init_hardware() {
  // init pins
  // ex) degits_init();
}

Mode taskInit() {
  // init variables
  // ex) mbedLED_init();
  //     wait_switch_left();
  return Mode::SELECT;
}

Mode taskSelect() {
  return starter_switch();
}

Mode taskThermo() {
  // ex) Thermometer();
  return Mode::INIT;
}

Mode taskCounter() {
  // ex) Counter();
  return Mode::INIT;
}

void task(Mode mode) {
  switch (mode) {
  case Mode::INIT: return taskInit();
  case Mode::SELECT: return taskSelect();
  case Mode::THERMOMETER: return taskThermo();
  case Mode::COUNTER: return taskCounter();
  }
}

int main() {
  init_hardware();

  Mode main_mode;
  while (1) {
    main_mode = task(main_mode);
  }
}

