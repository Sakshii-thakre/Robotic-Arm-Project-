#include <Servo.h>

// Servo motors
Servo M0, M1, M2, M3, M4, M5, M6;

// Color sensor pins
#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define sensorOut A0

// IR sensor
const int IR_PIN = 4;


//color detection veriables
int red = 0, green = 0, blue = 0;
int redCount = 0, greenCount = 0, blueCount = 0, yellowCount = 0;

void setup() {
    Serial.begin(9600);
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);
    pinMode(IR_PIN, INPUT);

    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    // Attach conveyor servo
    M0.attach(5);  // Conveyor motor
    M0.write(65); // Start conveyor
}

void loop() {
    if (digitalRead(IR_PIN) == LOW) {  // Object detected
        M0.write(0);
        delay(450);
        M0.write(90); // Stop conveyor
        delay(1000);

        String color = detectColor();
        Serial.print("Final detected color: ");
        Serial.println(color);

        M0.write(90);
        delay(5000);

        if (color == "Red") pickAndPlaceRed();
        else if (color == "Green") pickAndPlaceGreen();
        else if (color == "Blue") pickAndPlaceBlue();
        else if (color == "Yellow") pickAndPlaceYellow();

        M0.write(65); // Restart conveyor
    }
}


int getColor(int s2State, int s3State) {
    digitalWrite(S2, s2State);
    digitalWrite(S3, s3State);
    return pulseIn(sensorOut, LOW);
}

String detectColor() {

    redCount = 0;
    greenCount = 0;
    blueCount = 0;
    yellowCount = 0;

    
    red = getColor(LOW, LOW);
    green = getColor(HIGH, HIGH);
    blue = getColor(LOW, HIGH);

    Serial.print("Red: "); Serial.print(red);
    Serial.print(" Green: "); Serial.print(green);
    Serial.print(" Blue: "); Serial.println(blue);

    String detectedColor;

    if((red>green && red>blue) && green <= blue)
        {   
            detectedColor = "Green";
            greenCount++;
        }
    else if((red<green && red<blue) && green > blue)
        {  
            detectedColor = "Red";
            redCount++;
        }
    else if((blue>green && blue>red) && green >= red)
        {
            detectedColor = "Yellow";
            yellowCount++;
        }
    else if( blue < red && blue < green )
        {
            detectedColor = "Blue";
            blueCount++;
        }
    else
        {
            detectedColor = "Unknown Color";
        }

        return mostFrequentColor();
}



String mostFrequentColor() {
    if (redCount >= greenCount && redCount >= blueCount && redCount >= yellowCount) return "Red";
    else if (greenCount >= redCount && greenCount >= blueCount && greenCount >= yellowCount) return "Green";
    else if (blueCount >= redCount && blueCount >= greenCount && blueCount >= yellowCount) return "Blue";
    else if (yellowCount >= redCount && yellowCount >= greenCount && yellowCount >= blueCount) return "Yellow";
    else return "Unknown Color";
}

void pickAndPlaceRed() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Initializing motors...");

  M2.attach(7);
  M2.write(120);
  Serial.println("M2 homed");
  delay(500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(0);
  Serial.println("M1 homed");
  delay(500);
  M1.detach();
  Serial.println("M1 detached");

  M3.attach(8);
  M3.write(75);
  Serial.println("M3 homed");
  delay(500);
  M3.detach();
  Serial.println("M3 detached");

  M5.attach(10);
  M5.write(110);
  Serial.println("Gripper homed");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M2.attach(7);
  M2.write(90);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M6.attach(11);
  M6.write(90);
  Serial.println("Gripper open");
  delay(2500);
  M6.detach();
  Serial.println("M6 detached");

  M5.attach(10);
  M5.write(20);
  Serial.println("Gripper down");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M6.attach(11);
  M6.write(3);
  Serial.println("Gripper close");
  delay(2500);

  M2.attach(7);
  M2.write(135);
  Serial.println("Gripper up");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(180);
  Serial.println("Move to rack");
  delay(2500);
  M1.detach();
  Serial.println("M1 detached");

  M3.attach(8);
  M3.write(120);
  Serial.println("Arm2 down");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M5.attach(10);
  M5.write(120);
  Serial.println("Gripper up");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M2.attach(7);
  M2.write(112);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M3.attach(8);
  M3.write(100);
  Serial.println("Arm2 up");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M2.attach(7);
  M2.write(100);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M6.write(30);
  Serial.println("Gripper open");
  delay(2500);
  M6.detach();
  Serial.println("M6 detached");

  M2.attach(7);
  M2.write(135);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M5.attach(10);
  M5.write(110);
  Serial.println("Gripper homed");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M1.attach(6);
  M1.write(0);
  Serial.println("M1 homed");
  delay(2500);
  M1.detach();
  Serial.println("M1 detached");

  Serial.println("Red box placed!");
}

void pickAndPlaceGreen() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Initializing motors...");

  M2.attach(7);
  M2.write(120);
  Serial.println("M2 homed");
  delay(500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(0);
  Serial.println("M1 homed");
  delay(500);
  M1.detach();
  Serial.println("M1 detached");

  M3.attach(8);
  M3.write(75);
  Serial.println("M3 homed");
  delay(500);
  M3.detach();
  Serial.println("M3 detached");

  M5.attach(10);
  M5.write(110);
  Serial.println("Gripper homed");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M2.attach(7);
  M2.write(90);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M6.attach(11);
  M6.write(90);
  Serial.println("Gripper open");
  delay(2500);
  M6.detach();
  Serial.println("M6 detached");

  M5.attach(10);
  M5.write(20);
  Serial.println("Gripper down");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M6.attach(11);
  M6.write(3);
  Serial.println("Gripper close");
  delay(2500);

  M2.attach(7);
  M2.write(135);
  Serial.println("Gripper up");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(165);
  Serial.println("Move to rack");
  delay(2500);
  M1.detach();
  Serial.println("M1 detached");

  M3.attach(8);
  M3.write(120);
  Serial.println("Arm2 down");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M5.attach(10);
  M5.write(120);
  Serial.println("Gripper up");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M2.attach(7);
  M2.write(115);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M3.attach(8);
  M3.write(98);
  Serial.println("Arm2 up");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M2.attach(7);
  M2.write(100);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M6.write(30);
  Serial.println("Gripper open");
  delay(2500);
  M6.detach();
  Serial.println("M6 detached");

  M2.attach(7);
  M2.write(135);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(0);
  Serial.println("M1 homed");
  delay(500);
  M1.detach();
  Serial.println("M1 detached");

  Serial.println("Green Box Placed!");
}

void pickAndPlaceBlue() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Initializing motors...");

  M2.attach(7);
  M2.write(120);
  Serial.println("M2 homed");
  delay(500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(0);
  Serial.println("M1 homed");
  delay(500);
  M1.detach();
  Serial.println("M1 detached");

  M3.attach(8);
  M3.write(75);
  Serial.println("M3 homed");
  delay(500);
  M3.detach();
  Serial.println("M3 detached");

  M5.attach(10);
  M5.write(110);
  Serial.println("Gripper homed");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M2.attach(7);
  M2.write(90);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M6.attach(11);
  M6.write(90);
  Serial.println("Gripper open");
  delay(2500);
  M6.detach();
  Serial.println("M6 detached");

  M5.attach(10);
  M5.write(20);
  Serial.println("Gripper down");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M6.attach(11);
  M6.write(3);
  Serial.println("Gripper close");
  delay(2500);

  M2.attach(7);
  M2.write(135);
  Serial.println("Gripper up");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(180);
  Serial.println("Move to rack");
  delay(2500);
  M1.detach();
  Serial.println("M1 detached");

  M5.attach(10);
  M5.write(170);
  Serial.println("Gripper up");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M3.attach(8);
  M3.write(145);
  Serial.println("Arm2 down");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M2.attach(7);
  M2.write(90);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M3.attach(8);
  M3.write(120);
  Serial.println("Arm2 up");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M2.attach(7);
  M2.write(80);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M3.attach(8);
  M3.write(110);
  Serial.println("Arm2 up");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M2.attach(7);
  M2.write(75);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M6.write(30);
  Serial.println("Gripper open");
  delay(2500);
  M6.detach();
  Serial.println("M6 detached");

  M2.attach(7);
  M2.write(105);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M3.attach(8);
  M3.write(140);
  Serial.println("Arm2 up");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M2.attach(7);
  M2.write(135);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(0);
  Serial.println("M1 homed");
  delay(2500);
  M1.detach();
  Serial.println("M1 detached");

  Serial.println("Blue box placed!");
}

void pickAndPlaceYellow() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Initializing motors...");

  M2.attach(7);
  M2.write(120);
  Serial.println("M2 homed");
  delay(500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(0);
  Serial.println("M1 homed");
  delay(500);
  M1.detach();
  Serial.println("M1 detached");

  M3.attach(8);
  M3.write(75);
  Serial.println("M3 homed");
  delay(500);
  M3.detach();
  Serial.println("M3 detached");

  M5.attach(10);
  M5.write(110);
  Serial.println("Gripper homed");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M2.attach(7);
  M2.write(90);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M6.attach(11);
  M6.write(90);
  Serial.println("Gripper open");
  delay(2500);
  M6.detach();
  Serial.println("M6 detached");

  M5.attach(10);
  M5.write(20);
  Serial.println("Gripper down");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M6.attach(11);
  M6.write(3);
  Serial.println("Gripper close");
  delay(2500);

  M2.attach(7);
  M2.write(135);
  Serial.println("Gripper up");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(165);
  Serial.println("Move to rack");
  delay(2500);
  M1.detach();
  Serial.println("M1 detached");

  M5.attach(10);
  M5.write(170);
  Serial.println("Gripper up");
  delay(2500);
  M5.detach();
  Serial.println("M5 detached");

  M3.attach(8);
  M3.write(145);
  Serial.println("Arm2 down");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M2.attach(7);
  M2.write(95);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M3.attach(8);
  M3.write(120);
  Serial.println("Arm2 up");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M2.attach(7);
  M2.write(80);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M6.write(40);
  Serial.println("Gripper open");
  delay(2500);
  M6.detach();
  Serial.println("M6 detached");

  M2.attach(7);
  M2.write(105);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M3.attach(8);
  M3.write(150);
  Serial.println("Arm2 up");
  delay(2500);
  M3.detach();
  Serial.println("M3 detached");

  M2.attach(7);
  M2.write(135);
  Serial.println("Arm1 down");
  delay(2500);
  M2.detach();
  Serial.println("M2 detached");

  M1.attach(6);
  M1.write(0);
  Serial.println("M1 homed");
  delay(2500);
  M1.detach();
  Serial.println("M1 detached");

  Serial.println("Yellow box placed!");
}