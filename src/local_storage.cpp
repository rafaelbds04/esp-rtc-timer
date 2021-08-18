#include <local_storage.h>

#include "FS.h"
#include "debug.h"
#include <LittleFS.h>

ArduinoJson6180_91::StaticJsonDocument<1024U> getConfigJson()
{
    File configFile = LittleFS.open("/config.json", "r");
    if (!configFile)
    {
        DEBUG_INFO("Failed to open config file");
    }

    size_t size = configFile.size();
    if (size > 1024)
    {
        DEBUG_INFO("Config file size is too large");
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);

    StaticJsonDocument<1024> doc;

    auto error = deserializeJson(doc, buf.get());
    if (error)
    {
        DEBUG_INFO("Failed to parse config file");
    }
    return doc;
}

char *getConfig()
{
    File configFile = LittleFS.open("/config.json", "r");
    if (!configFile)
    {
        DEBUG_INFO("Failed to open config file");
    }

    size_t size = configFile.size();
    if (size > 1024)
    {
        DEBUG_INFO("Config file size is too large");
    }

    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);

    // We don't use String here because ArduinoJson library requires the input
    // buffer to be mutable. If you don't use ArduinoJson, you may as well
    // use configFile.readString instead.
    configFile.readBytes(buf.get(), size);

    StaticJsonDocument<1024> doc;

    auto error = deserializeJson(doc, buf.get());
    if (error)
    {
        DEBUG_INFO("Failed to parse config file");
    }
    char output[1024];
    serializeJson(doc, output);
    return output;
}

bool loadConfig()
{
    File configFile = LittleFS.open("/config.json", "r");
    if (!configFile)
    {
        DEBUG_INFO("Failed to open config file");
        return false;
    }

    size_t size = configFile.size();
    if (size > 1024)
    {
        DEBUG_INFO("Config file size is too large");
        return false;
    }

    // Allocate a buffer to store contents of the file.
    std::unique_ptr<char[]> buf(new char[size]);

    // We don't use String here because ArduinoJson library requires the input
    // buffer to be mutable. If you don't use ArduinoJson, you may as well
    // use configFile.readString instead.
    configFile.readBytes(buf.get(), size);

    StaticJsonDocument<1024> doc;
    auto error = deserializeJson(doc, buf.get());
    if (error)
    {
        DEBUG_INFO("Failed to parse config file");
        return false;
    }
    return true;
}

bool saveConfig(ArduinoJson6180_91::StaticJsonDocument<1024> doc)
{
    LittleFS.rmdir("/config.json");
    File configFile = LittleFS.open("/config.json", "w");
    if (!configFile)
    {
        DEBUG_INFO("Failed to open config file for writing");
        return false;
    }

    serializeJson(doc, configFile);
    return true;
}

bool saveDefaultConfig()
{
    LittleFS.rmdir("/config.json");
    StaticJsonDocument<200> initDoc;

    char json[] = "[]";
    deserializeJson(initDoc, json);

    File configFile = LittleFS.open("/config.json", "w");
    if (!configFile)
    {
        DEBUG_INFO("Failed to open config file for writing");
        return false;
    }

    serializeJson(initDoc, configFile);
    return true;
}

void setupStorage()
{
    delay(1000);
    DEBUG_INFO("Mounting FS...");

    if (!LittleFS.begin())
    {
        DEBUG_INFO("Failed to mount file system");
        return;
    }

    if (!loadConfig())
    {
        if (!saveDefaultConfig())
        {
            DEBUG_INFO("Failed to save default config")
        }
        else
        {
            DEBUG_INFO("Default config created")
        }
    }
    else
    {
        DEBUG_INFO("Config saved");
    }
}