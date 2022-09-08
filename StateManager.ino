Preferences preferences;

static const char *pref_name = "state";
static const char *limitKey = "limit";

static uint32_t tempLimit = 50;

void state_manager_setup() {
  Serial.println("Setting up STATE...");

  preferences.begin(pref_name, false); //Abre Preferences com permissão ReadWrite

  tempLimit = preferences.getUInt(limitKey, 50);

  Serial.println("STATE OK!");
}

uint32_t state_manager_get_limit() {
  return tempLimit;
}

void state_manager_set_limit(uint32_t value) {
  if (tempLimit != value) {
    tempLimit = value;
    preferences.putUInt(limitKey, value);
  }
}
