#include <robot_control/robot_joint_client.h>

int main(int argc, char *argv[]){
	bool real_time = true;

    ethercat::EtherCatManager manager(NETWORK_CARD_NAME);
	
	robot_control::RobotJointClient* joint1;
    joint1 = new robot_control::RobotJointClient (manager , 1);


	joint1->changeOPmode(CYCLIC_SYNCHRONOUS_VELOCITY_MODE);

	for(int i = 0; i < 50000; i++){
		joint1->get_feedback();

		if(i%100 == 0 ){
			printf("pos: %.2f deg !.\n" , joint1->getMotorPos());
			printf("vel: %.2f deg/s !.\n" , joint1->getMotorVel());
			printf("torque: %f mN.m !.\n",joint1->getMotorTorque());
			printf("status word %04x .\n", joint1->getStatusWord());
			printf("op mode  %d .\n", joint1->readOpmode());

		}
		joint1->sentVel(-720);

		rt_timer_spin(DEFAULT_INTERPOLATION_TIME_PERIOD);

	}

	delete joint1;

	return 0;
}


