#include <bitset>
#include <fstream>
#include <iostream>
#include <string>

constexpr auto MODE_CRYPT = "crypt";
constexpr auto MODE_DECRYPT = "decrypt";
constexpr auto INPUT_FILE_PARAM = "input file";
constexpr auto OUTPUT_FILE_PARAM = "output file";
constexpr auto KEY_PARAM = "key";
constexpr auto KEY_PARAM_MIN_VALUE = 0;
constexpr auto KEY_PARAM_MAX_VALUE = 255;

constexpr short ERR_CODE_INVALID_PARAM_LENGTH = 2;
constexpr short ERR_CODE_INVALID_KEY_VALUE = 3;
constexpr short ERR_CODE_INVALID_PROGRAM_MODE_PARAM = 4;

enum class ProgramMode
{
	CRYPT = 0,
	DECRYPT,
};

void CopyThroughCrypt(std::istream& fIn, std::ostream& fOut, const int& key, const ProgramMode& mode);

int main(int argc, char* argv[])
{
	std::ifstream fIn;
	std::ofstream fOut;

	if (argc != 5)
	{
		printf("Invalid argument count\n");
		printf("Usage: crypt.exe <%s|%s> <%s> <%s> <%s>\n", MODE_CRYPT, MODE_DECRYPT, INPUT_FILE_PARAM, OUTPUT_FILE_PARAM, KEY_PARAM);

		return EXIT_FAILURE;
	}

	short key = 0;
	auto mode = ProgramMode::CRYPT;

	try
	{
		if (std::strlen(argv[1]) == 0 || std::strlen(argv[2]) == 0 || std::strlen(argv[3]) == 0 || std::strlen(argv[4]) == 0)
		{
			throw ERR_CODE_INVALID_PARAM_LENGTH;
		}

		if (std::string(argv[1]) != MODE_CRYPT && std::string(argv[1]) != MODE_DECRYPT)
		{
			throw ERR_CODE_INVALID_PROGRAM_MODE_PARAM;
		}
		if (std::string(argv[1]) == MODE_CRYPT)
		{
			mode = ProgramMode::CRYPT;
		}
		if (std::string(argv[1]) == MODE_DECRYPT)
		{
			mode = ProgramMode::DECRYPT;
		}

		key = std::stoi(argv[4]);
		if (key < 0 || key > 255)
		{
			throw ERR_CODE_INVALID_KEY_VALUE;
		}
	}
	catch (short err_code)
	{
		printf("Invalid arguments value\n");
		printf("Usage: crypt.exe <%s|%s> <%s> <%s> <%s>\n", MODE_CRYPT, MODE_DECRYPT, INPUT_FILE_PARAM, OUTPUT_FILE_PARAM, KEY_PARAM);
		if (err_code == ERR_CODE_INVALID_PROGRAM_MODE_PARAM)
		{
			printf("<%s|%s> is program mode, use \"%s\" or \"%s\" to specify what program should do\n", MODE_CRYPT, MODE_DECRYPT, MODE_CRYPT, MODE_DECRYPT);
		}
		if (err_code == ERR_CODE_INVALID_KEY_VALUE)
		{
			printf("<%s> should be represented by value between %d and %d\n", KEY_PARAM, KEY_PARAM_MIN_VALUE, KEY_PARAM_MAX_VALUE);
		}
		exit(EXIT_FAILURE);
	}

	fIn.open(argv[2], std::ios::binary | std::ios::in);
	std::string tempStr;
	if (!fIn.is_open() || !getline(fIn, tempStr))
	{
		printf("Something bad with input file\n");
		return EXIT_FAILURE;
	}
	fIn.seekg(0, fIn.beg);

	fOut.open(argv[3], std::ios::binary | std::ios::in);
	if (!fOut.is_open())
	{
		printf("Something bad with output file\n");
		return EXIT_FAILURE;
	}

	printf("\nGot:\n");
	printf("<%s>: %s;\n", INPUT_FILE_PARAM, argv[2]);
	printf("<%s>: %s;\n", OUTPUT_FILE_PARAM, argv[3]);
	printf("Mode: %s;\n", mode == ProgramMode::CRYPT ? MODE_CRYPT : MODE_DECRYPT);
	printf("Key: %d;\n\n", key);

	CopyThroughCrypt(fIn, fOut, key, mode);

	fOut.flush();
	fIn.close();
	fOut.close();

	return EXIT_SUCCESS;
}

constexpr auto BYTE_SIZE = 8;

struct CryptSymbolContainer
{
	char symb;
	void setChar(const char& ch);
	char getContainedChar();
	void xorContainedCharBy(const int& key);
	void shuffleByInternalPattern(const ProgramMode& mode);
	std::string getContainedCharByteString();
};

void CryptSymbolContainer::setChar(const char& ch)
{
	symb = ch;
}

void CryptSymbolContainer::xorContainedCharBy(const int& key)
{
	symb ^= key;
}

char CryptSymbolContainer::getContainedChar()
{
	return symb;
}

char getPatternPosByIndex(const size_t& ind, const ProgramMode& mode)
{
	if (ind > BYTE_SIZE)
	{
		return 0;
	}
	char res = 0;
	switch (ind)
	{
		case 0: res = mode == ProgramMode::CRYPT ? 2 : 3; break;
		case 1: res = mode == ProgramMode::CRYPT ? 6 : 4; break;
		case 2: res = mode == ProgramMode::CRYPT ? 7 : 0; break;
		case 3: res = mode == ProgramMode::CRYPT ? 0 : 5; break;
		case 4: res = mode == ProgramMode::CRYPT ? 1 : 6; break;
		case 5: res = mode == ProgramMode::CRYPT ? 3 : 7; break;
		case 6: res = mode == ProgramMode::CRYPT ? 4 : 1; break;
		case 7: res = mode == ProgramMode::CRYPT ? 5 : 2; break;
		default: return 0;
	}

	return res;
}

void CryptSymbolContainer::shuffleByInternalPattern(const ProgramMode& mode)
{
	const unsigned char heldSymb = symb;
	symb = 0;
	size_t offset = 0;
	unsigned char mask = 128;

	for (size_t i = 0; i < BYTE_SIZE; (i++, mask = 128))
	{
		mask = mask >> i;
		if (heldSymb & mask)
		{
			offset = getPatternPosByIndex(i, mode);
			if (offset > i)
			{
				mask >>= (offset - i);
			}
			else
			{
				mask <<= (i - offset);
			}
			symb += mask;
		}
	}
}

std::string CryptSymbolContainer::getContainedCharByteString()
{
	std::bitset<BYTE_SIZE> bits(symb);
	return bits.to_string();
}

void CopyThroughCrypt(std::istream& fIn, std::ostream& fOut, const int& key, const ProgramMode& mode)
{
	CryptSymbolContainer ch{};
	char buff{};
	fIn.seekg(0, fIn.end);
	unsigned long long flength = fIn.tellg();
	fIn.seekg(0, fIn.beg);
	for (auto i = 0; i < flength; i++)
	{
		fIn.read(&buff, sizeof(buff));
		ch.setChar(buff);
		if (mode == ProgramMode::CRYPT)
		{
			ch.xorContainedCharBy(key);
			ch.shuffleByInternalPattern(mode);
		}
		else if (mode == ProgramMode::DECRYPT)
		{
			ch.shuffleByInternalPattern(mode);
			ch.xorContainedCharBy(key);
		}
		buff = ch.getContainedChar();
		fOut.write(&buff, sizeof(buff));
	}
}