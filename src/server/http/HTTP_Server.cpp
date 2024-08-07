#include "HTTP_Server.h"

HTTP_Server::HTTP_Server(SystemManager &sys, FilesystemManager &fs) :
    BaseServer(sys, fs, HTTP_PORT)
{
    setupRoutes();

    logger.begin("[Network][HTTP]");
    logger.printf("Listening on port %i\n", INFO, HTTP_PORT);
}

void HTTP_Server::secureRedirect()
{
    String redirect = "https://" + server.hostHeader();
    redirect.replace(":" + String(HTTP_PORT), ":" + String(HTTPS_PORT));

    server.sendHeader("Location", redirect);
    server.send(301, "text/plain", "");
}

void HTTP_Server::setupRoutes()
{
    server.on("/", route(secureRedirect));
}