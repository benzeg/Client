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

    public:
        void setGain(int value);
        void setContrast(int value);
        void setGamma(int value);
        void setSaturation(int value);
        void setSharpness(int value);
        void setWBB(int value);
        void setWBG(int value);
        void setWBR(int value);
        void setOffset(int value);
        void setCaptureFormat(char *format);
        void connect();
        void toggleStream();
        
    protected:
        void newMessage(INDI::BaseDevice baseDevice, int messageID) override;
        
};


void onBlobUpdated(INDI::PropertyBlob property);