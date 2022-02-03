#include <WebHelper.h>
#include <Constants.h>

void returnOK(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", "");
}

void returnFail(AsyncWebServerRequest *request, String msg)
{
    request->send(500, "text/plain", msg);
}

bool LoadFromSdCard(AsyncWebServerRequest *request)
{
    String path = request->url();
    String dataType = "text/plain";

    if (path.endsWith("/"))
    {
        path += "index.html";
    }

    if (path.endsWith(".src"))
        path = path.substring(0, path.lastIndexOf("."));
    else if (path.endsWith(".html"))
        dataType = "text/html";
    else if (path.endsWith(".htm"))
        dataType = "text/html";
    else if (path.endsWith(".css"))
        dataType = "text/css";
    else if (path.endsWith(".js"))
        dataType = "application/javascript";
    else if (path.endsWith(".png"))
        dataType = "image/png";
    else if (path.endsWith(".gif"))
        dataType = "image/gif";
    else if (path.endsWith(".jpg"))
        dataType = "image/jpeg";
    else if (path.endsWith(".ico"))
        dataType = "image/x-icon";
    else if (path.endsWith(".xml"))
        dataType = "text/xml";
    else if (path.endsWith(".pdf"))
        dataType = "application/pdf";
    else if (path.endsWith(".zip"))
        dataType = "application/zip";

    struct fileBlk
    {
        File dataFile;
    };
    fileBlk *fileObj = new fileBlk;

    fileObj->dataFile = SD.open(path.c_str());
    if (fileObj->dataFile.isDirectory())
    {
        path += "/index.html";
        dataType = "text/html";
        fileObj->dataFile = SD.open(path.c_str());
    }

    if (!fileObj->dataFile)
    {
        DBG_OUT.println("File failed: " + path);
        delete fileObj;
        return false;
    }

    if (request->hasParam("download"))
    {
        DBG_OUT.println("Download type octet-stream");
        dataType = "application/octet-stream";
    }

    // I'm not happy with this, it needs rework
    request->_tempObject = (void *)fileObj;
    request->send(dataType, fileObj->dataFile.size(), [request](uint8_t *buffer, size_t maxlen, size_t index) -> size_t
                  {
                      fileBlk *fileObj = (fileBlk *)request->_tempObject;
                      size_t thisSize = fileObj->dataFile.read(buffer, maxlen);
                      if ((index + thisSize) >= fileObj->dataFile.size())
                      {
                          fileObj->dataFile.close();
                          request->_tempObject = NULL;
                          delete fileObj;
                      }
                      return thisSize;
                  });
    return true;
}

void HandleDefault(AsyncWebServerRequest *request)
{
    String path = request->url();

    if (path.endsWith("/"))
        path += "index.htm";

    if (LoadFromSdCard(request))
        return;
    String message = "\nNo Handler\r\n";
    message += "URI: ";
    message += request->url();
    message += "\nMethod: ";
    message += (request->method() == HTTP_GET) ? "GET" : "POST";
    message += "\nParameters: ";
    message += request->params();
    message += "\n";
    for (uint8_t i = 0; i < request->params(); i++)
    {
        AsyncWebParameter *p = request->getParam(i);
        message += String(p->name().c_str()) + " : " + String(p->value().c_str()) + "\r\n";
    }
    request->send(404, "text/plain", message);
}

//------------------------------------------------------------------------------------------------------------------------
// Onderstaande functie wordt bij grotere blocky programma's meerdere malen aangeroepen.
// Het argument 'final' is true bij laatst ontvangen ethernet pakket.
//------------------------------------------------------------------------------------------------------------------------
//============================================================
//  HANDLE UPLOAD REQUEST (aangepast, hvw202201272008)
//============================================================
void HandleSDUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {

    //zend de blockly naar atmega instructies geconverteerde data naar de atmega uC via I2C
    programATmega(data, len, final);

}//HandleSDUpload
