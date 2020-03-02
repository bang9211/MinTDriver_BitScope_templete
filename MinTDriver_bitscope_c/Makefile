SName = MinTDriver_bitscope
SensorC = $(SName).c
SensorO = $(SName).o
SensorLib = lib$(SName).so

$(SensorLib):$(SensorO)
	gcc -shared -o $(SensorLib) $(SensorO) -L /MinT/usr/wiringPi -lwiringPi -Wall -g -ansi -lBitLib -I ${JAVA_HOME}/include -I ${JAVA_HOME}/include/linux
	mkdir -p /MinT/driver/
	mv $(SensorLib) /MinT/driver/
$(SensorO):$(SensorC)
	gcc -c -fPIC $(SensorC) -I ${JAVA_HOME}/include -I ${JAVA_HOME}/include/linux
clean:
	rm -rf $(SensorO)