#include <Encoder.h>
#include <Adafruit_NeoPixel.h>
const int NUM_KNOBS = 5;

Adafruit_NeoPixel led_master(1, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_discord(1, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_browser(1, 13, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_music(1, 14, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_gaming(1, 2, NEO_GRB + NEO_KHZ800);

int analog_knob_values[NUM_KNOBS];
Encoder knob_master(0, 1);
Encoder knob_discord(3, 4);
Encoder knob_browser(5, 6);
Encoder knob_music(7, 8);
Encoder knob_gaming(9, 10);
int master_value, discord_value, browser_value, music_value, gaming_value;
int master_mute, discord_mute, browser_mute, music_mute, gaming_mute;
int master_debounce_time;

const int master_button = A0;
const int discord_button = A1;
const int browser_button = A2;
const int music_button = A3;
const int gaming_button = A4;

const int max_value = 100;

unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 175;

int master_state = 0;
int discord_state = 0;
int browser_state = 0;
int music_state = 0;
int gaming_state = 0;

void setup() {
  Serial.begin(9600);

  pinMode(master_button, INPUT_PULLUP);
  pinMode(discord_button, INPUT_PULLUP);
  pinMode(browser_button, INPUT_PULLUP);
  pinMode(music_button, INPUT_PULLUP);
  pinMode(gaming_button, INPUT_PULLUP);

  analog_knob_values[0] = 512;
  knob_master.write(51);
  analog_knob_values[1] = 512;
  knob_discord.write(51);
  analog_knob_values[2] = 512;
  knob_browser.write(51);
  analog_knob_values[3] = 512;
  knob_music.write(51);
  analog_knob_values[4] = 512;
  knob_gaming.write(51);

  master_mute = 0;
  discord_mute = 0;
  browser_mute = 0;
  music_mute = 0;
  gaming_mute = 0;

  led_master.begin();
  led_master.clear();
  led_discord.begin();
  led_discord.clear();
  led_browser.begin();
  led_browser.clear();
  led_music.begin();
  led_music.clear();
  led_gaming.begin();
  led_gaming.clear();
}

void loop() {
  master_value = knob_master.read();
  discord_value = knob_discord.read();
  browser_value = knob_browser.read();
  music_value = knob_music.read();
  gaming_value = knob_gaming.read();

  check_buttons();
  check_encoders();
  send_knob_values();

  led_master.show();
  led_discord.show();
  led_browser.show();
  led_music.show();
  led_gaming.show();
}

void send_knob_values() {
  String built_string = String("");

  for (int i = 0; i < NUM_KNOBS; i++) {
    built_string += String((int)analog_knob_values[i]);

    if (i < NUM_KNOBS - 1) {
      built_string += String("|");
    }
  }
  Serial.println(built_string);
}

void check_buttons(){
  if (digitalRead(master_button) == 0 && master_state == 0){
    master_mute = !master_mute;
    master_state = 1;
    delay(25);
  }
  if (digitalRead(master_button)==1){
    master_state = 0;
  }

  if (digitalRead(discord_button) == 0 && discord_state == 0){
    discord_mute = !discord_mute;
    discord_state = 1;
    delay(25);
  }
  if (digitalRead(discord_button)==1){
    discord_state = 0;
  }

  if (digitalRead(browser_button) == 0 && browser_state == 0){
    browser_mute = !browser_mute;
    browser_state = 1;
    delay(25);
  }
  if (digitalRead(browser_button)==1){
    browser_state = 0;
  }

  if (digitalRead(music_button) == 0 && music_state == 0){
    music_mute = !music_mute;
    music_state = 1;
    delay(25);
  }
  if (digitalRead(music_button)==1){
    music_state = 0;
  }

  if (digitalRead(gaming_button) == 0 && gaming_state == 0){
    gaming_mute = !gaming_mute;
    gaming_state = 1;
    delay(25);
  }
  if (digitalRead(gaming_button)==1){
    gaming_state = 0;
  }
}

void check_encoders(){
  if (master_value > 0 && master_value < max_value && master_mute == 0){
    analog_knob_values[0] = master_value * 10;
    led_master.setPixelColor(0, 0, 255, 204);
    led_master.setBrightness(analog_knob_values[0] / 10);
  }
  else if (master_mute == 0 && (master_value > max_value || master_value == max_value)){
    analog_knob_values[0] = max_value * 10;
    knob_master.write(max_value);
    led_master.setPixelColor(0, 0, 255, 204);
    led_master.setBrightness(analog_knob_values[0] / 10);
  }
  else if (master_mute == 1){
    analog_knob_values[0] = 0;
    led_master.setPixelColor(0, 212, 0, 255);
    led_master.setBrightness(50);
  }
  else {
    analog_knob_values[0] = 0;
    knob_master.write(0);
    led_master.setPixelColor(0, 212, 0, 255);
    led_master.setBrightness(50);
  }

  if (discord_value > 0 && discord_value < max_value && discord_mute == 0){
    analog_knob_values[1] = discord_value * 10;
    led_discord.setPixelColor(0, 0, 255, 204);
    led_discord.setBrightness(analog_knob_values[1] / 10);
  }
  else if (discord_mute == 0 && (discord_value > max_value || discord_value == max_value)){
    analog_knob_values[1] = max_value * 10;
    knob_discord.write(max_value);
    led_discord.setPixelColor(0, 0, 255, 204);
    led_discord.setBrightness(analog_knob_values[1] / 10);
  }
  else if (discord_mute == 1){
    analog_knob_values[1] = 0;
    led_discord.setPixelColor(0, 212, 0, 255);
    led_discord.setBrightness(50);
  }
  else {
    analog_knob_values[1] = 0;
    knob_discord.write(0);
    led_discord.setPixelColor(0, 212, 0, 255);
    led_discord.setBrightness(50);
  }

  if (browser_value > 0 && browser_value < max_value && browser_mute == 0){
    analog_knob_values[2] = browser_value * 10;
    led_browser.setPixelColor(0, 0, 255, 204);
    led_browser.setBrightness(analog_knob_values[2] / 10);
  }
  else if (browser_mute == 0 && (browser_value > max_value || browser_value == max_value)){
    analog_knob_values[2] = max_value * 10;
    knob_browser.write(max_value);
    led_browser.setPixelColor(0, 0, 255, 204);
    led_browser.setBrightness(analog_knob_values[2] / 10);
  }
  else if (browser_mute == 1){
    analog_knob_values[2] = 0;
    led_browser.setPixelColor(0, 212, 0, 255);
    led_browser.setBrightness(50);
  }
  else {
    analog_knob_values[2] = 0;
    knob_browser.write(0);
    led_browser.setPixelColor(0, 212, 0, 255);
    led_browser.setBrightness(50);
  }

  if (music_value > 0 && music_value < max_value && music_mute == 0){
    analog_knob_values[3] = music_value * 10;
    led_music.setPixelColor(0, 0, 255, 204);
    led_music.setBrightness(analog_knob_values[3] / 10);
  }
  else if (music_mute == 0 && (music_value > max_value || music_value == max_value)){
    analog_knob_values[3] = max_value * 10;
    knob_music.write(max_value);
    led_music.setPixelColor(0, 0, 255, 204);
    led_music.setBrightness(analog_knob_values[3] / 10);
  }
  else if (music_mute == 1){
    analog_knob_values[3] = 0;
    led_music.setPixelColor(0, 212, 0, 255);
    led_music.setBrightness(50);
  }
  else {
    analog_knob_values[3] = 0;
    knob_music.write(0);
    led_music.setPixelColor(0, 212, 0, 255);
    led_music.setBrightness(50);
  }

  if (gaming_value > 0 && gaming_value < max_value && gaming_mute == 0){
    analog_knob_values[4] = gaming_value * 10;
    led_gaming.setPixelColor(0, 0, 255, 204);
    led_gaming.setBrightness(analog_knob_values[4] / 10);
  }
  else if (gaming_mute == 0 && (gaming_value > max_value || gaming_value == max_value)){
    analog_knob_values[4] = max_value * 10;
    knob_gaming.write(max_value);
    led_gaming.setPixelColor(0, 0, 255, 204);
    led_gaming.setBrightness(analog_knob_values[4] / 10);
  }
  else if (gaming_mute == 1){
    analog_knob_values[4] = 0;
    led_gaming.setPixelColor(0, 212, 0, 255);
    led_gaming.setBrightness(50);
  }
  else {
    analog_knob_values[4] = 0;
    knob_gaming.write(0);
    led_gaming.setPixelColor(0, 212, 0, 255);
    led_gaming.setBrightness(50);
  }
}