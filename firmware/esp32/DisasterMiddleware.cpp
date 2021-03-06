#include "DisasterMiddleware.h"

// NOTE: multimethod so we can return the correct parameter type to chain on
DisasterMiddleware *DisasterMiddleware::connect(DisasterMiddleware *c)
{
    if (client == NULL)
    {
        client = c;
        client->server = this;
    }
    return c;
};
DisasterClient *DisasterMiddleware::connect(DisasterClient *c)
{
    if (client == NULL)
    {
        client = c;
        client->server = this;
    }
    return c;
};

void DisasterMiddleware::disconnect(DisasterClient *c)
{
    if (client == c)
    {
        server->disconnect(this);
        client->server = NULL;
        client = NULL;
        delete c;
    }
};

void DisasterMiddleware::setup()
{
    if (client)
    {
        client->setup();
    }
};

void DisasterMiddleware::loop()
{
    if (client)
    {
        client->loop();
    }
};

void DisasterMiddleware::receive(String message)
{
    if (client)
    {
        client->receive(message);
    }
};

void DisasterMiddleware::transmit(DisasterClient *c, String message)
{
    if (server)
    {
        server->transmit(this, message);
    }
};
