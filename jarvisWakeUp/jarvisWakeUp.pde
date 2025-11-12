import processing.serial.*;
import ddf.minim.*;

Serial myPort;
Minim minim;
AudioPlayer soundA;
String inString;

void setup() {
  size(400, 200);

  minim = new Minim(this);
  soundA = minim.loadFile("jarvis_sound.mp3");  // put this file in the "data" folder

  println("Available serial ports:");
  println(Serial.list());

  // 👉 After you see the list in the console, change [0] to the right index
  String portName = Serial.list()[0];
  println("Using port: " + portName);
  myPort = new Serial(this, portName, 9600);

  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  fill(255);
  textAlign(CENTER, CENTER);
  text("Listening for Arduino commands...", width/2, height/2);
}

void serialEvent(Serial p) {
  inString = p.readStringUntil('\n');

  if (inString != null) {
    inString = trim(inString);
    println("Got line: " + inString);  // DEBUG: see what Arduino actually sends

    if (inString.equals("PLAY1")) {
      println("Received PLAY1. Playing sound A.");
      soundA.rewind();
      soundA.play();
    }
  }
}

// 🔻 This is where you properly shut down Minim when you close the sketch
void stop() {
  if (soundA != null) {
    soundA.close();
  }
  if (minim != null) {
    minim.stop();
  }
  super.stop();
}
