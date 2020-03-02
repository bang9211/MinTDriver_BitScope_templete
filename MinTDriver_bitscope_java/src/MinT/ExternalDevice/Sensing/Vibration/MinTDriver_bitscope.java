package MinT.ExternalDevice.Sensing.Vibration;

import MinTFramework.ExternalDevice.Device;

/**
 *
 * @author hanyoungtak
 */
public class MinTDriver_bitscope extends Device {

    private native void initSensor();

    private native void freeSensor();

    private native double[] getVibrationData();

    public MinTDriver_bitscope() {
        super("MinTDriver_bitscope");
    }

    @Override
    protected void initDevice() {
        initSensor();
    }

    @Override
    protected void freeDevice() {
        freeSensor();
    }

    public double[] getData() {
        double[] data = getVibrationData();

        return data;
    }

}
