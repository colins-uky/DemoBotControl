// DEMO BOT CONTROL
// UKRMT KATS SMALL ROBOT CONTROL SOFTWARE
// UNIVERSITY OF KENTUCKY 2019
//   _  __    _  _____ ____    ____   ___ _____
//  | |/ /   / \|_   _/ ___|  | __ ) / _ \_   _|
//  | ' /   / _ \ | | \___ \  |  _ \| | | || |
//  | . \  / ___ \| |  ___) | | |_) | |_| || |
//  |_|\_\/_/   \_\_| |____/  |____/ \___/ |_|


// THE ROBOT USES 4 OF THIS POLOLU MOTOR DRIVER
// https://www.pololu.com/product/1451


#define DEBUG true

// MOTOR CONTROL PINS
#define MOTOR1_INA    23
#define MOTOR1_INB    21
#define MOTOR1_PWM    22
#define MOTOR2_INA    2
#define MOTOR2_INB    5
#define MOTOR2_PWM    3
#define MOTOR3_INA    17
#define MOTOR3_INB    15
#define MOTOR3_PWM    16
#define MOTOR4_INA    19
#define MOTOR4_INB    18
#define MOTOR4_PWM    20
String data_in;
char tmp;

enum {
  MOTOR1,
  MOTOR2,
  MOTOR3,
  MOTOR4,
  MOTORS_LEFT,  // LEFT SIDE MOTORS 3 AND 4
  MOTORS_RIGHT, // RIGHT SIDE MOTORS 1 AND 2
  MOTORS_ALL    // ALL MOTORS
} motors;

enum {
  DS_STOP,
  DS_FWD,
  DS_REV,
  DS_RT,
  DS_LT,
} drive_state;



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(100);

  setupMotorControlPins();

  driveDirection(DS_STOP);
  driveSpeed(MOTORS_ALL, 0);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void loop() {
  // PROCESS SERIAL MESSAGES AND DRIVE MOTORS ACCORDINGLY

  if (Serial.available() > 0) {
                // read the incoming byte:
                  
    if (tmp=='\n')
    {
                //FORMAT: 'M' proceeded by four four character substrings consisting of 0 or 1 for direction and a three digit pwm value
                //Example: 'M1255025511270127' would correspond to:
                //Motor 1 fwd at full speed, Motor 2 rvs at full speed, Motor 3 fwd at half speed, Motor 4 rvs at half speed
                data_in = Serial.readString();
                drive(MOTOR1,toInt(data_in.substring(1,2),toInt(data_in.substring(2,5)));
                drive(MOTOR2,toInt(data_in.substring(6,7),toInt(data_in.substring(6,9)));
                drive(MOTOR3,toInt(data_in.substring(10,11),toInt(data_in.substring(10,13)));
                drive(MOTOR4,toInt(data_in.substring(14,15),toInt(data_in.substring(14,17)));
                data_in = "";
    }
    else data_in += tmp;
  }

}
                      
void drive(  int m, int d, int spd ){

  if( spd>255)  spd = 255;
  if( spd<0)    spd = 0;
  
  switch (m)
  {
    case MOTOR1:
       if( d==1 )
       {
          digitalWrite(MOTOR1_INA, LOW );
          digitalWrite(MOTOR1_INB, HIGH );
          analogWrite(MOTOR1_PWM, spd);
       } 
  
     // DRIVE REVERSE
      else if( d==0 )
      {
          digitalWrite(MOTOR1_INA, HIGH );
          digitalWrite(MOTOR1_INB, LOW );
          analogWrite(MOTOR1_PWM, spd);
      }
    break;

    case MOTOR2:
       if( d==1 )
       {
          digitalWrite(MOTOR2_INA, LOW );
          digitalWrite(MOTOR2_INB, HIGH );
          analogWrite(MOTOR2_PWM, spd);
       } 
  
     // DRIVE REVERSE
      else if( d==0 )
      {
          digitalWrite(MOTOR2_INA, HIGH );
          digitalWrite(MOTOR2_INB, LOW );
          analogWrite(MOTOR2_PWM, spd);
      }
    break;

    case MOTOR3:
       if( d==1 )
       {
          digitalWrite(MOTOR3_INA, LOW );
          digitalWrite(MOTOR3_INB, HIGH );
          analogWrite(MOTOR3_PWM, spd);
       } 
  
     // DRIVE REVERSE
      else if( d==0 )
      {
          digitalWrite(MOTOR3_INA, HIGH );
          digitalWrite(MOTOR3_INB, LOW );
          analogWrite(MOTOR3_PWM, spd);
      }
    break;
      
    case MOTOR4:
       if( d==1 )
       {
          digitalWrite(MOTOR4_INA, LOW );
          digitalWrite(MOTOR4_INB, HIGH );
          analogWrite(MOTOR4_PWM, spd);
       } 
  
     // DRIVE REVERSE
      else if( d==0 )
      {
          digitalWrite(MOTOR4_INA, HIGH );
          digitalWrite(MOTOR4_INB, LOW );
          analogWrite(MOTOR4_PWM, spd);
      }
    break;
      
  // ERROR STATE BAD DIRECTION PROVIDED
  else {
    if(DEBUG) {
      Serial.print("bad drive state in call to setDirection(");
      Serial.print(d);
      Serial.println(");");
    }
  }
}
  
void driveDirection( int d ){

  // ALL STOP CONDITION
  if( d==DS_STOP ){
    motorsOff();
  } 

  // DRIVE FORWARD
  else if( d==DS_FWD ){
    forward();
  } 
  
  // DRIVE REVERSE
  else if( d==DS_REV ){
    reverse();
  }
  
  // TURN RUGHT
  else if( d==DS_RT ){
    right();
  } 

  // TURN LEFT
  else if( d==DS_LT ){
    left();
  }
  
  // ERROR STATE BAD DIRECTION PROVIDED
  else {
    if(DEBUG) {
      Serial.print("bad drive state in call to setDirection(");
      Serial.print(d);
      Serial.println(");");
    }
  }
}

void driveSpeed(int m, int spd)
{
  if( spd>255)  spd = 255;
  if( spd<0)    spd = 0;
  
  switch (m)
  {
    case MOTOR1:
      analogWrite(MOTOR1_PWM, spd);
    break;

    case MOTOR2:
      analogWrite(MOTOR2_PWM, spd);
    break;

    case MOTOR3:
      analogWrite(MOTOR3_PWM, spd);
    break;

    case MOTOR4:
      analogWrite(MOTOR4_PWM, spd);
    break;

    case MOTORS_LEFT:
      analogWrite(MOTOR3_PWM, spd);
      analogWrite(MOTOR4_PWM, spd);
    break;

    case MOTORS_RIGHT:
      analogWrite(MOTOR1_PWM, spd);
      analogWrite(MOTOR2_PWM, spd);
    break;

    case MOTORS_ALL:
      analogWrite(MOTOR1_PWM, spd);
      analogWrite(MOTOR2_PWM, spd);
      analogWrite(MOTOR3_PWM, spd);
      analogWrite(MOTOR4_PWM, spd);
    break;

    default:
      if(DEBUG) Serial.println("Error in driveSpeed()");
      break;
  }
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INPUT: DRIVE MODE FROM drive_state ENUM
// CONFIGURES THE DIRECTION PINS OF THE MOTOR CONTROLLERS
// BASED ON DRIVE STATE CHOICE
void driveDirection( int d ){

  // ALL STOP CONDITION
  if( d==DS_STOP ){
    motorsOff();
  } 

  // DRIVE FORWARD
  else if( d==DS_FWD ){
    forward();
  } 
  
  // DRIVE REVERSE
  else if( d==DS_REV ){
    reverse();
  }
  
  // TURN RUGHT
  else if( d==DS_RT ){
    right();
  } 

  // TURN LEFT
  else if( d==DS_LT ){
    left();
  }
  
  // ERROR STATE BAD DIRECTION PROVIDED
  else {
    if(DEBUG) {
      Serial.print("bad drive state in call to setDirection(");
      Serial.print(d);
      Serial.println(");");
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void forward()
{
  digitalWrite(MOTOR1_INA, LOW );
  digitalWrite(MOTOR1_INB, HIGH );
  digitalWrite(MOTOR2_INA, LOW );
  digitalWrite(MOTOR2_INB, HIGH );
  digitalWrite(MOTOR3_INA, HIGH );
  digitalWrite(MOTOR3_INB, LOW );
  digitalWrite(MOTOR4_INA, HIGH );
  digitalWrite(MOTOR4_INB, LOW );
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void reverse()
{
  digitalWrite(MOTOR1_INA, HIGH );
  digitalWrite(MOTOR1_INB, LOW );
  digitalWrite(MOTOR2_INA, HIGH );
  digitalWrite(MOTOR2_INB, LOW );
  digitalWrite(MOTOR3_INA, LOW );
  digitalWrite(MOTOR3_INB, HIGH );
  digitalWrite(MOTOR4_INA, LOW );
  digitalWrite(MOTOR4_INB, HIGH );
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void left()
{
  digitalWrite(MOTOR1_INA, LOW );
  digitalWrite(MOTOR1_INB, HIGH );
  digitalWrite(MOTOR2_INA, LOW );
  digitalWrite(MOTOR2_INB, HIGH );
  digitalWrite(MOTOR3_INA, LOW );
  digitalWrite(MOTOR3_INB, HIGH );
  digitalWrite(MOTOR4_INA, LOW );
  digitalWrite(MOTOR4_INB, HIGH );
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void right()
{
  digitalWrite(MOTOR1_INA, HIGH );
  digitalWrite(MOTOR1_INB, LOW );
  digitalWrite(MOTOR2_INA, HIGH );
  digitalWrite(MOTOR2_INB, LOW );
  digitalWrite(MOTOR3_INA, HIGH);
  digitalWrite(MOTOR3_INB, LOW );
  digitalWrite(MOTOR4_INA, HIGH );
  digitalWrite(MOTOR4_INB, LOW );
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void motorsOff()
{
  digitalWrite(MOTOR1_INA, LOW );
  digitalWrite(MOTOR1_INB, LOW );
  digitalWrite(MOTOR2_INA, LOW );
  digitalWrite(MOTOR2_INB, LOW );
  digitalWrite(MOTOR3_INA, LOW );
  digitalWrite(MOTOR3_INB, LOW );
  digitalWrite(MOTOR4_INA, LOW );
  digitalWrite(MOTOR4_INB, LOW );
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void setupMotorControlPins()
{
  // MOTOR 1 INIT
  pinMode(MOTOR1_INA, OUTPUT);
  pinMode(MOTOR1_INB, OUTPUT);
  pinMode(MOTOR1_PWM, OUTPUT);

  // MOTOR 2 INIT
  pinMode(MOTOR2_INA, OUTPUT);
  pinMode(MOTOR2_INB, OUTPUT);
  pinMode(MOTOR2_PWM, OUTPUT);

  // MOTOR 3 INIT
  pinMode(MOTOR3_INA, OUTPUT);
  pinMode(MOTOR3_INB, OUTPUT);
  pinMode(MOTOR3_PWM, OUTPUT);

  // MOTOR 4 INIT
  pinMode(MOTOR4_INA, OUTPUT);
  pinMode(MOTOR4_INB, OUTPUT);
  pinMode(MOTOR4_PWM, OUTPUT);
}

