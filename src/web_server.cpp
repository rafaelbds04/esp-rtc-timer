#include "rtc.h"

#include "debug.h"
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <ESP8266WebServer.h>
#include "local_storage.h"

ESP8266WebServer server(80); // webserver object

void handleLocalDate()
{
    if (server.method() == HTTP_GET)
    {
        DynamicJsonDocument doc(2048);
        doc["date"] = getDateISOString();

        // Serialize JSON document
        String json;
        serializeJson(doc, json);
        server.send(200, "application/json", json);
    }
    if (server.method() == HTTP_POST)
    {
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, server.arg("plain"));
        const char *date = doc["date"];

        setDateTime(date);
        server.send(200, "application/json", "{success:true}");
    }
}

void handlePostSchedules()
{
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, server.arg("plain"));

    if (error)
    {
        DEBUG_INFO("DeserializeJson failed: ");
        // DEBUG_INFO(error.f_str());
        server.send(500, "application/json", error.f_str());
    }
    else
    {
        saveConfig(doc);
        server.send(200);
    }
    server.send(500, "application/json", "{error:unknown}");
}

void startWebServer()
{
    DEBUG_INFO("[startServer]");
    server.enableCORS(true);
    server.onNotFound([]
                      { server.send(404, F("text/plain"), F("Website not found")); });
    server.on("/local-date", handleLocalDate);
    server.on("/schedules", HTTP_POST, handlePostSchedules);
    server.serveStatic("/schedules", LittleFS, "/config.json", "max-age=67890");
    server.serveStatic("/", LittleFS, "/index.html", "max-age=67890");
    server.serveStatic("/novo", LittleFS, "/index.html");
    server.begin();

    delay(50);
}

void handleWebServer()
{
    server.handleClient();
}