//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

//Library Includes
#include <WinSock2.h>
#include <WS2tcpip.h>
//#include <Windows.h>
#include <iostream>
#include <thread>

//Local Includes
#include "utils.h"
#include "consoletools.h"
#include "network.h"
#include "networkentity.h"
#include "socket.h"

//This includes
#include "client.h"


CClient::CClient()
	:m_pcPacketData(0)
	, m_pClientSocket(0)
{
	ZeroMemory(&m_ServerSocketAddress, sizeof(m_ServerSocketAddress));

	//Create a Packet Array and fill it out with all zeros.
	m_pcPacketData = new char[MAX_MESSAGE_LENGTH];
	ZeroMemory(m_pcPacketData, MAX_MESSAGE_LENGTH);

}

CClient::~CClient()
{
	delete[] m_pcPacketData;
	m_pcPacketData = 0;

	delete m_pClientSocket;
	m_pClientSocket = 0;

	delete m_pWorkQueue;
	m_pWorkQueue = 0;
}

/***********************
* Initialise: Initialises a client object by creating a client socket and filling out the socket address structure with details of server to send the data to.
* @author: 
* @parameter: none
* @return: void
********************/
bool CClient::Initialise()
{
	//Local Variables to hold Server's IP address and Port NUmber as entered by the user
	char _cServerIPAddress[128];
	ZeroMemory(&_cServerIPAddress, 128);
	char _cServerPort[10];
	ZeroMemory(&_cServerPort, 10);
	unsigned short _usServerPort;

	//Local variable to hold client's name
	char _cUserName[50];
	ZeroMemory(&m_cUserName, 50);

	//Zero out the memory for all the member variables.
	ZeroMemory(&m_cUserName, strlen(m_cUserName));

	

	//Create a work queue to distribute messages between the main  thread and the receive thread.
	m_pWorkQueue = new CWorkQueue<char*>();

	//Create a socket object
	m_pClientSocket = new CSocket();
	
	//Get the port number to bind the socket to
	unsigned short _usClientPort = QueryPortNumber(DEFAULT_CLIENT_PORT);
	//Initialise the socket to the port number
	if (!m_pClientSocket->Initialise(_usClientPort))
	{
		return false;
	}

	//Enable Broadcast

	int iBroadCastOption = 1;

	int iResult = setsockopt(m_pClientSocket->GetSocketHandle(), SOL_SOCKET, SO_BROADCAST, 
		reinterpret_cast<char*>(&iBroadCastOption), sizeof(iBroadCastOption));

	//Get the IP address of the server to send data to
	std::cout << "Enter server IP or empty for localhost: ";
	
	gets_s(_cServerIPAddress);
	if (_cServerIPAddress[0] == 0)
	{
		strcpy_s(_cServerIPAddress, "127.0.0.1");
	}
	//Get the Port Number of the server
	std::cout << "Enter server's port number or empty for default server port: ";
	gets_s(_cServerPort);
	//std::cin >> _usServerPort;
	
	if (_cServerPort[0] == 0)
	{
		_usServerPort = DEFAULT_SERVER_PORT;
	}
	else
	{
		_usServerPort = atoi(_cServerPort);
	}

	std::cout << "Attempting to connect to server at " << _cServerIPAddress << ":" << _usServerPort << std::endl;
	//Fill in the details of the server's socket address structure.
	//This will be used when stamping address on outgoing packets
	m_ServerSocketAddress.sin_family = AF_INET;
	m_ServerSocketAddress.sin_port = htons(_usServerPort);
	inet_pton(AF_INET, _cServerIPAddress, &m_ServerSocketAddress.sin_addr);

	//Send a hanshake message to the server as part of the Client's Initialization process.
	//Step1: Create a handshake packet
	
	do{
		std::cout << "Please enter a username : ";
		gets_s(_cUserName);
	} while (_cUserName[0] == 0);

	TPacket _packet;
	_packet.Serialize(HANDSHAKE, _cUserName); 
	SendData(_packet.PacketData);
	return true;
}

bool CClient::SendData(char* _pcDataToSend)
{
	int _iBytesToSend = (int)strlen(_pcDataToSend) + 1;
	
	char _RemoteIP[MAX_ADDRESS_LENGTH];
	inet_ntop(AF_INET, &m_ServerSocketAddress.sin_addr, _RemoteIP, sizeof(_RemoteIP));
	//std::cout << "Trying to send " << _pcDataToSend << " to " << _RemoteIP << ":" << ntohs(m_ServerSocketAddress.sin_port) << std::endl;
	char _message[MAX_MESSAGE_LENGTH];
	strcpy_s(_message, strlen(_pcDataToSend) + 1, _pcDataToSend);

	int iNumBytes = sendto(
		m_pClientSocket->GetSocketHandle(),				// socket to send through.
		_pcDataToSend,									// data to send
		_iBytesToSend,									// number of bytes to send
		0,												// flags
		reinterpret_cast<sockaddr*>(&m_ServerSocketAddress),	// address to be filled with packet target
		sizeof(m_ServerSocketAddress)							// size of the above address struct.
		);
	//iNumBytes;
	if (_iBytesToSend != iNumBytes)
	{
		std::cout << "There was an error in sending data from client to server" << std::endl;
		return false;
	}
	return true;
}

void CClient::ReceiveData(char* _pcBufferToReceiveData)
{
	sockaddr_in _FromAddress; // Make a local variable to extract the IP and port number of the sender from whom we are receiving
	//In this case; it should be the details of the server; since the client only ever receives from the server
	int iSizeOfAdd = sizeof(_FromAddress);
	int _iNumOfBytesReceived;
	
	//Receive data into a local buffer
	char _buffer[MAX_MESSAGE_LENGTH];
	//For debugging purpose only, convert the Address structure to a string.
	char _pcAddress[50];
	ZeroMemory(&_pcAddress, 50);
	while(true)
	{
		// pull off the packet(s) using recvfrom()
		_iNumOfBytesReceived = recvfrom(			// pulls a packet from a single source...
			this->m_pClientSocket->GetSocketHandle(),						// client-end socket being used to read from
			_buffer,							// incoming packet to be filled
			MAX_MESSAGE_LENGTH,					   // length of incoming packet to be filled
			0,										// flags
			reinterpret_cast<sockaddr*>(&_FromAddress),	// address to be filled with packet source
			&iSizeOfAdd								// size of the above address struct.
			);
		inet_ntop(AF_INET, &_FromAddress, _pcAddress, sizeof(_pcAddress));

		if (_iNumOfBytesReceived < 0)
		{
			//Error in receiving data 
			std::cout << "recvfrom failed with error " << WSAGetLastError();
			_pcBufferToReceiveData = 0;
		}
		else if (_iNumOfBytesReceived == 0)
		{
			//The remote end has shutdown the connection
			_pcBufferToReceiveData = 0;
		}
		else
		{
			//There is valid data received.
			strcpy_s(_pcBufferToReceiveData, strlen(_buffer) + 1, _buffer);
			//strcpy_s(m_pcPacketData, strlen(_buffer) + 1, _buffer);
			//Put this packet data in the workQ
			m_pWorkQueue->push(_pcBufferToReceiveData);
		}
		//std::this_thread::yield(); //Yield the processor; giving the main a chance to run.
	}
}

void CClient::ProcessData(char* _pcDataReceived)
{

	TPacket _packetRecvd;
	_packetRecvd = _packetRecvd.Deserialize(_pcDataReceived);
	switch (_packetRecvd.MessageType)
	{
	case HANDSHAKE:
	{
		std::cout << "recieved message" << std::endl;
		break;
	}
	case DATA:
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		std::cout << "SERVER> " << _packetRecvd.MessageContent << std::endl;
		break;
	}
	default:
		break;

	}
}

void CClient::GetRemoteIPAddress(char *_pcSendersIP)
{
	inet_ntop(AF_INET, &(m_ServerSocketAddress.sin_addr), _pcSendersIP, sizeof(_pcSendersIP));
	return;
}

unsigned short CClient::GetRemotePort()
{
	return ntohs(m_ServerSocketAddress.sin_port);
}

void CClient::BroadcastData(char * _pcDataToBroadcast)
{
	//Make a broadcast packet
	TPacket packet;
	packet.Serialize(BROADCAST, _pcDataToBroadcast);

	//Stamp the packet with broadcast address
	m_ServerSocketAddress.sin_family = AF_INET;
	m_ServerSocketAddress.sin_addr.S_un.S_addr = INADDR_BROADCAST;
	m_ServerSocketAddress.sin_port = htons(DEFAULT_SERVER_PORT);

	sendto(m_pClientSocket->GetSocketHandle(), packet.PacketData, packet.PacketSize, 
		0, reinterpret_cast<sockaddr*>(&m_ServerSocketAddress), sizeof(m_ServerSocketAddress));

}

void CClient::GetPacketData(char* _pcLocalBuffer)
{
	strcpy_s(_pcLocalBuffer, strlen(m_pcPacketData) + 1, m_pcPacketData);
}

CWorkQueue<char*>* CClient::GetWorkQueue()
{
	return m_pWorkQueue;
}