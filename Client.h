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
        
    protected:
        void newMessage(INDI::BaseDevice baseDevice, int messageID) override;
        
};


void onBlobUpdated(INDI::PropertyBlob property);