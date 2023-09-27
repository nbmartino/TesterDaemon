/*************************************************************************/

/* prototypes */

int BecomeDaemonProcess(const char *const lockFileName,
								const char *const logPrefix,
								const int logLevel,
								int *const lockFileDesc,
								int *const thisPID);
int ConfigureSignalHandlers(void);
int BindPassiveSocket(const unsigned long interfaceAddress,
							 const int portNum,
							 int *const boundSocket);
int AcceptConnections(const int master);
int HandleConnection(const int slave);
int WriteToSocket(const int sock,const char *const buffer,
						const size_t buflen);
int ReadLine(const int sock,char *const buffer,const size_t buflen,
				 size_t *const bytesRead);
void FatalSigHandler(int sig);
void TermHandler(int sig);
void HupHandler(int sig);
void Usr1Handler(int sig);
void TidyUp(void);
