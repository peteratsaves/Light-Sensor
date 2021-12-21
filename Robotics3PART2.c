#pragma config(Sensor, in4, POT, sensorPotentiometer)
#pragma config(Sensor, in6,    light_sensor,   sensorReflection)
#pragma config(Motor,  port9,           Servo,         tmotorServoStandard, openLoop)
	//int sensor_value;
	//sensor_value = SensorValue(POT);
int ServoMove(int servoPosition){

  writeDebugStreamLine("Servo Position = %d",servoPosition);
  int light = SensorValue(light_sensor); //gets light sensor value
  writeDebugStreamLine("POT = %d",SensorValue(POT));
  motor[Servo] = servoPosition; //moves servo to current position
  wait1Msec(200);
  return light;
}

task main()
{
	int max_position = -127; //sets default max position to first position
	int max_light = 800; //sets default max light to 800 (lowest light value)
	bool b = true;
	if(b){
		for(int i = -127; i<127 ; i +=10){ //checks all values in servo range incrementing by 10
		ServoMove(i);
		if (ServoMove(i) < max_light){ //if current light value is greater than the max, max light value becomes current light value and
			                             //max position value is changed to current position
			max_light = ServoMove(i);
			max_position = i;
		}
			}
		}
		motor[Servo]=max_position; //moves servo to position with the most light
		//ServoMove(max_position);
		wait1Msec(5000);
		writeDebugStreamLine("%d",max_position);
}
