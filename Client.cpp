#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>

#include <fcntl.h>

#include <filesystem>
#include <chrono>
#include <ctime>

#include "Client.h"

/**************************************************************************************
**
***************************************************************************************/
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
int main(int argc , char *argv[]) {
  #ifdef __EMSCRIPTEN__
  // do nothing
  #endif
};
Client::Client(const char *my_ccd)
{
  MYCCD = my_ccd;
  init();
}

Client::~Client()
{
}

/**************************************************************************************
**
***************************************************************************************/
void Client::takeExposure(double seconds)
{
    INDI::PropertyNumber ccdExposure = mSimpleCCD.getProperty("CCD_EXPOSURE");

    if (!ccdExposure.isValid())
    {
        IDLog("Error: unable to find CCD Simulator CCD_EXPOSURE property...\n");
        return;
    }

    // Take a 1 second exposure
    IDLog("Taking a %g second exposure.\n", seconds);
    ccdExposure[0].setValue(seconds);
    sendNewProperty(ccdExposure);
}

/**************************************************************************************
**
***************************************************************************************/
void Client::init()
{
  // wait for the availability of the device

  #ifdef __EMSCRIPTEN__
  emscripten_log(EM_LOG_CONSOLE, "Waiting for device %s", MYCCD);
  #endif
  watchDevice(MYCCD, [this](INDI::BaseDevice device)
  {
    mSimpleCCD = device; // save device

    #ifdef __EMSCRIPTEN__
    emscripten_log(EM_LOG_CONSOLE, "Waiting for device %s", MYCCD);
    #endif
    // wait for the availability of the "CONNECTION" property
    device.watchProperty("CONNECTION", [this](INDI::Property property)
    {
        IDLog("Connecting to INDI Driver...\n");
        IDLog("connection value: %s", property.getSwitch());
        if (mSimpleCCD.isConnected())
        {
            IDLog("CCD is connected.\n");
            setBLOBMode(B_ALSO, MYCCD, nullptr);
            mCCDProperties = mSimpleCCD.getProperties();
            for (const auto &oneProp : mCCDProperties) {
                IDLog("%s", oneProp.getName());
            }
                
        }
        else
        {
            #ifdef __EMSCRIPTEN__
            emscripten_log(EM_LOG_CONSOLE, "Waiting for device %s", MYCCD);
            #endif
            connectDevice(MYCCD);
        }
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_EXPOSURE", [this](INDI::Property property)
    {
        // exposure ready    
        IDLog("Exposure ready.\n");
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    // call if uD1"pdated of the "CC property - simplified way
    device.watchProperty("CCD1", [this](INDI::PropertyBlob property)
    {
      return onBlobUpdated(property);

    }, INDI::BaseDevice::WATCH_UPDATE);
  });
}

void Client::newMessage(INDI::BaseDevice baseDevice, int messageID)
{
    if (!baseDevice.isDeviceNameMatch(MYCCD))
        return;

    IDLog("Recveing message from Server:\n"
          "    %s\n\n", 
          baseDevice.messageQueue(messageID).c_str());

    IDLog(baseDevice.isConnected() ? "CCD is connected.\n" : "CCD is disconnected.\n");
}

void onBlobUpdated(INDI::PropertyBlob property)
{
  char fileName[64];
  time_t timer = time(nullptr); 

  sprintf(fileName, "exposure_%ld.fits", (long int)(timer));
  std::filesystem::path cwd = std::filesystem::current_path() / std::string(fileName); 

  #ifdef __EMSCRIPTEN__
  emscripten_log(EM_LOG_CONSOLE, "Current path is %s", cwd.c_str());
  #endif

  // Save FITS file to disk
  std::ofstream myfile(cwd.c_str(), std::ios::out | std::ios::binary);
  myfile.write(static_cast<char *>(property[0].getBlob()), property[0].getBlobLen());
  myfile.close();

  IDLog("Received image, saved as %s\n", cwd.c_str());

  #ifdef __EMSCRIPTEN__
  MAIN_THREAD_EM_ASM({
    updateCanvas(UTF8ToString($0));
  }, cwd.c_str());
  #endif
}