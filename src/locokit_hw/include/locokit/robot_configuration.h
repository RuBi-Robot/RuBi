#ifndef LOCOKIT_SENSORS_MOTORS_DEFINITION_H
#define LOCOKIT_SENSORS_MOTORS_DEFINITION_H

//TODO: get real ID of the motors

// Define your sensors here
enum locokitSensor {
    LEFT_HIP_SPEED = 0,
    LEFT_KNEE_SPEED = 1,
    LEFT_ANKLE_SPEED = 2,
    RIGHT_HIP_SPEED = 3,
    RIGHT_KNEE_SPEED = 4,
    RIGHT_ANKLE_SPEED = 5,

    NUMBER_SENSORS = 6
};

// And the motors
enum locokitMotor {
    NUMBER_MOTORS = 6,

    FRONT_LEFT = 0,
    FRONT_RIGHT = 1,
    REAR_LEFT = 2,
    REAR_RIGHT = 3,

    LEFT_HIP_ID = 5,
    LEFT_KNEE_ID = 4,
    LEFT_ANKLE_ID = 8,
    RIGHT_HIP_ID = 19,
    RIGHT_KNEE_ID = 20
    RIGHT_ANKLE_ID = 21
};

// And more than likely you want to define this too
#define IP "192.168.2.2"
#define PORT 1241

#endif
