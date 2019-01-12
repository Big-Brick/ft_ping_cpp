#include <boost/filesystem.hpp>
#include <thread>
#include <chrono>
#include <fstream>
#include <json/json.h>
#include "../includes/IcmpPoller.h"
#include <future>


Json::Value checkFile(std::string path) {
    Json::Value configuration;
    Json::Reader reader;
    std::ifstream configFile(path, std::ifstream::binary);
    if (!reader.parse(configFile, configuration, true)) {
        std::cout << "Configuration file " <<  path << " is not correct : ", reader.getFormattedErrorMessages();
        return Json::nullValue;
    }
    if (!configuration.isMember("hostList")) {
        std::cout << "Error Configuration File is not correct, no member 'hostList'" << std::endl;
        return Json::nullValue;
    }
    if (!configuration.isMember("timeout")) {
        std::cout << "Error Configuration File is not correct, no member 'timeout'" << std::endl;
        return Json::nullValue;
    }
    if (!configuration.isMember("type")) {
        std::cout << "Error Configuration File is not correct, no member 'type'" << std::endl;
        return Json::nullValue;
    }
    return configuration;
}


int main(int argc , char *argv[]) {
  if (argc != 2) {
    std::cerr << "Please, define configuration file" << std::endl;
    return 1;
  }

    Poller* poller = NULL;
    std::future<void> backgroundPoll;

  std::time_t modificationTime = 0;

  boost::filesystem::path p(argv[1]);
  while (true) {
      if (boost::filesystem::exists(p)) {
          std::time_t currentModificationTime = boost::filesystem::last_write_time(p);
          if(modificationTime < currentModificationTime) {
              modificationTime = currentModificationTime;
              Json::Value configuration = checkFile(p.string());
              if (configuration != Json::nullValue) {
                  if (poller) {
                      if(configuration["type"].asString().compare("icmp") == 0) {
                          std::vector<std::string> hostList;
                          for (Json::Value host :configuration["hostList"]) {
                              hostList.push_back(host.asString());
                          }
                          double timeout = configuration["timeout"].asDouble();
                          poller->UpdatePoller(hostList, timeout);
                      }
                  }
                  else {
                      if (configuration["type"].asString().compare("icmp") == 0) {
                          std::vector<std::string> hostList;
                          for (Json::Value host :configuration["hostList"]) {
                              hostList.push_back(host.asString());
                          }
                          poller = new IcmpPoller(hostList, configuration["timeout"].asDouble());
                          backgroundPoll = std::async(std::launch::async, [poller](){ poller->Poll(); });
                      }
                  }
              }
          }
      } else {
          std::cout << "Could not find configuration file " << argv[1] << '\n';
          continue;
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}