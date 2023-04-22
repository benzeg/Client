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
#include <thread>
#include <zlib.h>

#include <fcntl.h>

#include <filesystem>
#include <chrono>
#include <ctime>

#include "Client.h"
#include <opencv2/imgproc.hpp>

#define __BENCHMARK__
//#define __DEBUG__

/**************************************************************************************
**
***************************************************************************************/
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#ifndef __EMSCRIPTEN__
int main(int argc , char *argv[]) {
  Client client("SVBONY SV305 0");
  client.connectServer();
  sleep(10);
  client.setCompression("INDI_ENABLED");
  //client.takeExposure(1);
  client.toggleStream();
  std::cout << "Press Enter key to terminate the client.\n";
  std::cin.ignore();
};
#endif

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

    setCaptureFormat("FORMAT_RAW8");

    #ifdef __DEBUG__
    IDLog("Taking a %g second exposure.\n", seconds);
    #endif

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

    #ifdef __DEBUG__
    IDLog("Waiting for device %s", MYCCD);
    #endif
    // wait for the availability of the "CONNECTION" property
    device.watchProperty("CONNECTION", [this](INDI::Property property)
    {
        IDLog("Connecting to INDI Driver...\n");
        if (mSimpleCCD.isConnected())
        {
          #ifdef __DEBUG__
          IDLog("CCD is connected.\n");
          #endif

          setBLOBMode(B_ALSO, MYCCD, nullptr);
          mCCDProperties = mSimpleCCD.getProperties();
          for (const auto &oneProp : mCCDProperties) {
            #ifdef __DEBUG__
            IDLog("%s", oneProp.getName());
            #endif
          }
                
        }
        else
        {
            #ifdef __DEBUG__
            IDLog("Waiting for device %s", MYCCD);
            #endif
            connectDevice(MYCCD);
        }
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_EXPOSURE", [this](INDI::PropertyNumber property)
    {
      #ifdef __DEBUG__
      auto val = property[0].getValue();
      IDLog("Exposure value: %f\n", val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    // call if uD1"pdated of the "CC property - simplified way
    device.watchProperty("CCD1", [this](INDI::PropertyBlob property)
    {
      return onBlobUpdated(property);

    }, INDI::BaseDevice::WATCH_UPDATE);

    device.watchProperty("CCD_GAIN", [this](INDI::PropertyNumber property)
    {
      auto val = property[0].getValue();

      #ifdef __DEBUG__
      IDLog("Gain value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncGain($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_CONTRAST", [this](INDI::PropertyNumber property)
    {
      auto val = property[0].getValue();
      #ifdef __DEBUG__
      IDLog("Contrast value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncContrast($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_GAMMA", [this](INDI::PropertyNumber property)
    {
     
      auto val = property[0].getValue();
      #ifdef __DEBUG__
      IDLog("Gamma value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncGamma($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_SATURATION", [this](INDI::PropertyNumber property)
    {
      auto val = property[0].getValue();
      #ifdef __DEBUG__
      IDLog("Saturation value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncSaturation($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_SHARPNESS", [this](INDI::PropertyNumber property)
    {
     
      auto val = property[0].getValue();
      #ifdef __DEBUG__
      IDLog("Sharpness value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncSharpness($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_WBB", [this](INDI::PropertyNumber property)
    {
     
      auto val = property[0].getValue();
      #ifdef __DEBUG__
      IDLog("WBB value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncWBB($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_WBG", [this](INDI::PropertyNumber property)
    {
     
      auto val = property[0].getValue();
      #ifdef __DEBUG__
      IDLog("WBG value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncWBG($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_WBR", [this](INDI::PropertyNumber property)
    {
     
      auto val = property[0].getValue();
      #ifdef __DEBUG__
      IDLog("WBR value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncWBR($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_OFFSET", [this](INDI::PropertyNumber property)
    {
      auto val = property[0].getValue();
      #ifdef __DEBUG__
      IDLog("Offset value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncOffset($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_CAPTURE_FORMAT", [this](INDI::Property property)
    {
      #ifdef __DEBUG__
      auto captureFormatSP = property.getSwitch();
      auto onSwitch = captureFormatSP->findOnSwitch();
      IDLog("Image format state changed to %s.\n", onSwitch->getName());
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_VIDEO_STREAM", [this](INDI::Property property)
    {
      auto videoStreamSP = property.getSwitch();
      auto onSwitch = videoStreamSP->findOnSwitch();

      #ifdef __DEBUG__ 
      IDLog("Video stream state changed to %s.\n", onSwitch->getName());
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncVideoStreamOn($0);
      }, (strcmp(onSwitch->getName(), "STREAM_ON") == 0 ? 1 : 0));
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("STREAMING_EXPOSURE", [this](INDI::PropertyNumber property)
    {
      auto val = property[0].getValue();

      #ifdef __DEBUG__
      IDLog("Stream Exposure value: %f\n", val);
      #endif

      #ifdef __EMSCRIPTEN__
      MAIN_THREAD_EM_ASM({
        syncExposure($0);
      }, val);
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

    device.watchProperty("CCD_COMPRESSION", [this](INDI::Property property)
    {
      auto compressionSP = property.getSwitch();
      auto onSwitch = compressionSP->findOnSwitch();

      #ifdef __DEBUG__
      IDLog("compression state changed to %s.\n", onSwitch->getName());
      #endif
    }, INDI::BaseDevice::WATCH_NEW_OR_UPDATE);

  });
}

void Client::newMessage(INDI::BaseDevice baseDevice, int messageID)
{
    if (!baseDevice.isDeviceNameMatch(MYCCD))
        return;

    #ifdef __DEBUG__
    IDLog("Recveing message from Server:\n"
          "    %s\n\n", 
          baseDevice.messageQueue(messageID).c_str());

    IDLog(baseDevice.isConnected() ? "CCD is connected.\n" : "CCD is disconnected.\n");
    #endif
}

void onBlobUpdated(INDI::PropertyBlob property)
{
  IDLog("Received image");
  auto blob = property[0].getBlob();
  auto blobLen = property[0].getBlobLen();
  auto size = property[0].getSize();
  auto format = property[0].getFormat();
  IDLog("format: %s", format);

  // .stream.z
  if (strcmp(format, ".stream.z") == 0) {
    #ifdef __DEBUG__
    IDLog("Received compressed image");
    #endif

    // decompress
    #ifdef __BENCHMARK__
    auto const before = std::chrono::steady_clock::now();
    #endif

    std::vector<uint8_t> decompressedFrame;
    decompressedFrame.resize(size);
    uLongf nbytes = decompressedFrame.size();
    auto blobUint8 = static_cast<u_int8_t *>(blob);
    
    int ret = uncompress(decompressedFrame.data(), &nbytes, blobUint8, blobLen);

    #ifdef __BENCHMARK__
    auto const after = std::chrono::steady_clock::now();
    auto const duration = std::chrono::duration_cast <std::chrono::nanoseconds> (after - before).count();
    IDLog("Before compress size: %d\n", blobLen);
    IDLog("After compress size: %d\n", nbytes);
    IDLog("Decompression took %d nanoseconds\n", duration);
    #endif

    if (ret != Z_OK) {
      IDLog("Error decompressing image %d\n", ret);
      return;
    }

    // demosaic
    #ifdef __BENCHMARK__
    auto const beforeDemosaic = std::chrono::steady_clock::now();
    #endif

    auto decompressed = cv::Mat(1080, 1920, CV_8UC1, decompressedFrame.data());
    auto output = cv::Mat(1080, 1920, CV_8UC4);
    cv::cvtColor(decompressed, output, cv::COLOR_BayerGB2RGBA);

    uchar * arr = output.isContinuous()? output.data: output.clone().data;
    uint length = output.total()*output.channels();

    #ifdef __BENCHMARK__
    auto const afterDemosaic = std::chrono::steady_clock::now();
    auto const durationDemosaic = std::chrono::duration_cast <std::chrono::nanoseconds> (afterDemosaic - beforeDemosaic).count();
    IDLog("Before demosaic size: %d\n", nbytes);
    IDLog("After demosaic size: %d\n", length);
    IDLog("Demosaic took %d nanoseconds\n", durationDemosaic);
    #endif 

    #ifdef __EMSCRIPTEN__
    MAIN_THREAD_EM_ASM({
      updateImage($0, $1, $2);
    }, arr, length, format);
    #else
      std::ofstream myfile;
      myfile.open("ccd_simulator", std::ios::out | std::ios::binary);
      myfile.write(reinterpret_cast<char *>(decompressedFrame.data()), 1920 * 1080);
      myfile.close(); 

    #endif
  } else if(strcmp(format, ".stream") == 0) {
    // demosaic
    #ifdef __BENCHMARK__
    auto const beforeDemosaic = std::chrono::steady_clock::now();
    #endif

    auto depressed = cv::Mat(1080, 1920, CV_8UC1, blob);
    auto output = cv::Mat(1080, 1920, CV_8UC4);
    cv::cvtColor(depressed, output, cv::COLOR_BayerGB2RGBA);

    uchar * arr = output.isContinuous()? output.data: output.clone().data;
    uint length = output.total()*output.channels();

    #ifdef __BENCHMARK__
    auto const afterDemosaic = std::chrono::steady_clock::now();
    auto const durationDemosaic = std::chrono::duration_cast <std::chrono::nanoseconds> (afterDemosaic - beforeDemosaic).count();
    IDLog("Before demosaic size: %d\n", blobLen);
    IDLog("After demosaic size: %d\n", length);
    IDLog("Demosaic took %d nanoseconds\n", durationDemosaic);
    #endif 

    #ifdef __EMSCRIPTEN__
    MAIN_THREAD_EM_ASM({
      updateImage($0, $1, $2);
    }, arr, length, format);
    #endif
  } else {
    #ifdef __EMSCRIPTEN__
    MAIN_THREAD_EM_ASM({
      updateImage($0, $1, $2);
    }, blob, blobLen, format);
    #endif
    
  }
}

void Client::setGain(double value)
{
  INDI::PropertyNumber ccdGain = mSimpleCCD.getProperty("CCD_GAIN");

  #ifdef __DEBUG__  
  IDLog("Setting gain to %f \n", value);
  #endif

  ccdGain[0].setValue(value);
  sendNewProperty(ccdGain);
};

void Client::setContrast(double value)
{
  INDI::PropertyNumber ccdContrast = mSimpleCCD.getProperty("CCD_CONTRAST");

  #ifdef __DEBUG__  
  IDLog("Setting contrast to %f\n", value);
  #endif

  ccdContrast[0].setValue(value);
  sendNewProperty(ccdContrast);
};

void Client::setGamma(double value)
{
  INDI::PropertyNumber ccdGamma = mSimpleCCD.getProperty("CCD_GAMMA");

  #ifdef __DEBUG__  
  IDLog("Setting gamma to %f\n", value);
  #endif

  ccdGamma[0].setValue(value);
  sendNewProperty(ccdGamma);
};
void Client::setSaturation(double value)
{
  INDI::PropertyNumber ccdSaturation = mSimpleCCD.getProperty("CCD_SATURATION");

  #ifdef __DEBUG__  
  IDLog("Setting saturation to %f\n", value);
  #endif

  ccdSaturation[0].setValue(value);
  sendNewProperty(ccdSaturation);
};
void Client::setSharpness(double value)
{
  INDI::PropertyNumber ccdSharpness = mSimpleCCD.getProperty("CCD_SHARPNESS");

  #ifdef __DEBUG__  
  IDLog("Setting contrast to %f\n", value);
  #endif

  ccdSharpness[0].setValue(value);
  sendNewProperty(ccdSharpness);
};
void Client::setWBB(double value)
{
  INDI::PropertyNumber ccdWBB = mSimpleCCD.getProperty("CCD_WBB");

  #ifdef __DEBUG__  
  IDLog("Setting WBB to %f\n", value);
  #endif

  ccdWBB[0].setValue(value);
  sendNewProperty(ccdWBB);
};
void Client::setWBG(double value)
{
  INDI::PropertyNumber ccdWBG = mSimpleCCD.getProperty("CCD_WBG");
  
  #ifdef __DEBUG__
  IDLog("Setting contrast to %f\n", value);
  #endif

  ccdWBG[0].setValue(value);
  sendNewProperty(ccdWBG);
};
void Client::setWBR(double value)
{
  INDI::PropertyNumber ccdWBR = mSimpleCCD.getProperty("CCD_WBR");

  #ifdef __DEBUG__  
  IDLog("Setting contrast to %f\n", value);
  #endif

  ccdWBR[0].setValue(value);
  sendNewProperty(ccdWBR);
};
void Client::setOffset(double value)
{
  INDI::PropertyNumber ccdOffset = mSimpleCCD.getProperty("CCD_OFFSET");

  #ifdef __DEBUG__  
  IDLog("Setting contrast to %f\n", value);
  #endif

  ccdOffset[0].setValue(value);
  sendNewProperty(ccdOffset);
};

void Client::setCaptureFormat(char *format)
{
  INDI::PropertySwitch ccdCaptureFormat = mSimpleCCD.getProperty("CCD_CAPTURE_FORMAT");

  #ifdef __DEBUG__
  IDLog("Setting capture format to %s\n", format);
  #endif

  auto formatSwitch = ccdCaptureFormat.findWidgetByName(format);

  ccdCaptureFormat->reset();
  formatSwitch->setState(ISS_ON);

  sendNewSwitch(ccdCaptureFormat);
};

void Client::connect() {
  std::thread(&Client::connectServer, this).detach();
}

void Client::toggleStream(int onState) {
  INDI::PropertySwitch videoStreamSP = mSimpleCCD.getProperty("CCD_VIDEO_STREAM");
  auto onSwitch = videoStreamSP->findOnSwitch();
  videoStreamSP->reset();

  if (onState == 1) {
    #ifdef __DEBUG__
    IDLog("Turning on stream.\n");
    #endif
    auto streamOnSwitch = videoStreamSP.findWidgetByName("STREAM_ON");
    streamOnSwitch->setState(ISS_ON);
  } else {
    #ifdef __DEBUG__
    IDLog("Turning off stream.\n");
    #endif

    auto streamOffSwitch = videoStreamSP.findWidgetByName("STREAM_OFF");   
    streamOffSwitch->setState(ISS_ON);
  }

  sendNewSwitch(videoStreamSP);
}

void Client::toggleStream() {
  INDI::PropertySwitch videoStreamSP = mSimpleCCD.getProperty("CCD_VIDEO_STREAM");
  auto onSwitch = videoStreamSP->findOnSwitch();
  videoStreamSP->reset();
  if (strcmp(onSwitch->getName(), "STREAM_ON") == 0) {
    #ifdef __DEBUG__
    IDLog("Turning off stream.\n");
    #endif

    auto streamOffSwitch = videoStreamSP.findWidgetByName("STREAM_OFF");   
    streamOffSwitch->setState(ISS_ON);

  } else {
    #ifdef __DEBUG__
    IDLog("Turning on stream.\n");
    #endif
    auto streamOnSwitch = videoStreamSP.findWidgetByName("STREAM_ON");
    streamOnSwitch->setState(ISS_ON);

  }

  sendNewSwitch(videoStreamSP);
}

void Client::setStreamEncoder(char *encoder) {
  // raw
  // mjpeg - grayscale only

  INDI::PropertySwitch ccdStreamEncoder = mSimpleCCD.getProperty("CCD_STREAM_ENCODER");

  #ifdef __DEBUG__ 
  IDLog("Setting capture format to %s\n", encoder);
  #endif

  auto encoderSwitch = ccdStreamEncoder.findWidgetByName(encoder);

  ccdStreamEncoder->reset();
  encoderSwitch->setState(ISS_ON);

  sendNewSwitch(ccdStreamEncoder);
}

void Client::setStreamExposure(double seconds) {
  INDI::PropertyNumber ccdStreamExposure = mSimpleCCD.getProperty("STREAMING_EXPOSURE");

  #ifdef __DEBUG__ 
  IDLog("Setting stream exposure to %f\n", seconds);
  #endif

  ccdStreamExposure[0].setValue(seconds);
  sendNewProperty(ccdStreamExposure);
}

void Client::setExposure(double seconds) {
  setStreamExposure(seconds);
}

void Client::setCompression(char *status)
{
  INDI::PropertySwitch ccdCompression = mSimpleCCD.getProperty("CCD_COMPRESSION");

  #ifdef __DEBUG__  
  IDLog("Setting compression to %s\n", status);
  #endif

  auto compressionSwitch = ccdCompression.findWidgetByName(status);

  ccdCompression->reset();
  compressionSwitch->setState(ISS_ON);

  sendNewSwitch(ccdCompression);
};
