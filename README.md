ReceiverAndCallback
===================
Receiver class with IReciever interface parses input data for different kinds of packets and sends parsed data using ICallback interface.

Binary packet: starts with 0x24 ($ symbol) followed by 4 bytes of binary data, e.g. :"$abcd"
Text packet: string of characters, terminated with "\r\n\r\n" (CR LF CR LF), e.g. "textPacket\r\n\r\n"
Incoming data can be of any size, not aligned to packet sizes.

In order to read CR and LF symbols from std::cin, it was set to binary input.
Platform: Windows, MSVC 2010

USAGE:
iss_test.exe < test.txt

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
Visual Studio project uses "test.txt", when running Debug configuration (so you don't have to supply file name every time you wan't to run the program).
To change that, go to Project Properties -> Configuration Properties -> Debugging -> Command Arguments, and remove "< test.txt".
