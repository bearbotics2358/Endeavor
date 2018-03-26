#ifndef SRC_GUNNAR_H_
#define SRC_GUNNAR_H_

#include <mosquittopp.h>

class Gunnar : public mosqpp::mosquittopp
{
	public:
		Gunnar(const char *id, const char *host, int port);
		~Gunnar();

		void on_connect(int rc);
		void on_message(const struct mosquitto_message *message);
		void on_subscribe(int mid, int qos_count, const int *granted_qos);

		float GetDistance();
		float GetAngle();
	private:
		float cubeDistance = 0;
		float cubeAngle = 0;
};




#endif
