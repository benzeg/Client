#include <libindi/basedevice.h>
#include <libindi/baseclient.h>

class Client : public INDI::BaseClient
{
    public:
        Client(const char *my_ccd);
        virtual ~Client();
    
    public:
        void setTemperature(double value);
        void takeExposure(double seconds);
        void init();

    private:
        INDI::BaseDevice mSimpleCCD;
        INDI::Properties mCCDProperties;
        const char *MYCCD;
        bool takenExposure = false;
        char *frameBuffer = nullptr;
        void setStreamExposure(double seconds);
        void onBlobUpdated(INDI::PropertyBlob property);

    public:
        void setGain(double value);
        void setContrast(double value);
        void setGamma(double value);
        void setSaturation(double value);
        void setSharpness(double value);
        void setWBB(double value);
        void setWBG(double value);
        void setWBR(double value);
        void setOffset(double value);
        void setCaptureFormat(char *format);
        void setStreamEncoder(char *encoder);
        void connect();
        void toggleStream(int onState);
        void toggleStream();
        void setExposure(double seconds);
        void setCompression(char *status);      
        void setROI(int x, int y, int width, int height);

    protected:
        void newMessage(INDI::BaseDevice baseDevice, int messageID) override;
        
};


void onBlobUpdated(INDI::PropertyBlob property);