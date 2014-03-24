ReceiverAndCallback
===================
Receiver class with IReciever interface parses input data for different kinds of packets and sends parsed data using ICallback interface.
Platform: Windows, MSVC 2010

Binary packet: starts with 0x24 ($ symbol) followed by 4 bytes of binary data, e.g. :"$abcd"
Text packet: string of characters, terminated with "\r\n\r\n" (CR LF CR LF), e.g. "textPacket\r\n\r\n"
Incoming data can be of any size, not aligned to packet sizes.

Program takes input file name as a mandatory parameter.

USAGE:
iss_test.exe test.txt

OUTPUT (for test.txt):
Bin: [abcd]
Bin: [1234]
Text: { firstTextPacket }
Bin: [1234]
Text: { SecontTextPacket }
Bin: [5678]
Bin: [abcd]
Text: { TextPacketWithBinaryPacketInTheMiddle }


ATTENTION:
If you don't want to input file name each time you run the program from Visual Studio, you can specify it as as a constant parameter.
Go to Project Properties -> Configuration Properties -> Debugging -> Command Arguments, and type input file name, e.g. "test.txt".
