#include <iostream>
#include <string.h>
#include <phpcpp.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <iomanip>
#include <json/json.h>

using namespace std;

char buffer [33]; //���ڴ��ת���õ�ʮ�������ַ������ɸ�����Ҫ���峤��

void example(Php::Parameters &params)
{
	//Php::Value r(0);
	double p1 = params[0];
	string p2 = params[1];
	double p3 = params[2];

	Php::warning << "params 1 is " << p1 << flush;
	Php::warning << "params 2 is " << p2 << flush;
	Php::warning << "params 3 is " << p3 << flush;
	printf("Hello World\n");
//	Php::out.flush();:
}

uint16_t test_crc16(uint8_t *buf, uint16_t len)
{
	uint16_t i, j;
	uint16_t crc_reg = 0xFFFF;
	uint16_t crc_val;

	for (i = 0; i < len; i++)
	{
		crc_val = buf[i] << 8;
		for (j = 0; j < 8; j++)
		{
			if (((int16_t)(crc_reg ^ crc_val)) < 0)
			crc_reg = (crc_reg << 1) ^ 0x1021;
			else
			crc_reg <<= 1;
			crc_val <<= 1;
		}
	}
	return crc_reg;

}

char * inttohex(int aa)
{
    static int i = 0;
    if (aa < 16)            //�ݹ��������
    {
        if (aa < 10)        //��ǰ��ת�����ַ������ַ���
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'A';
        buffer[i+1] = '\0'; //�ַ���������־
    }
    else
    {
        inttohex(aa / 16);  //�ݹ����
        i++;                //�ַ�������+1
        aa %= 16;           //���㵱ǰֵ
        if (aa < 10)        //��ǰ��ת�����ַ������ַ���
            buffer[i] = aa + '0';
        else
            buffer[i] = aa - 10 + 'A';
    }
    return (buffer);
}

void crc16_exec(Php::Parameters &params)
{
//	uint8_t a[] = {0x00, 0x23, 0x80, 0x01, 0x00, 0x00, 0x00, 0x27, 0x00, 0x01, 0x00, 0x00, 0x32, 0x30, 0x31, 0x39, 0x30, 0x32, 0x32, 0x30, 0x30,
//	                        0x30, 0x36, 0x30, 0x30, 0x32, 0x35, 0x00, 0x00, 0x13, 0x08, 0x12, 0x0e, 0x33, 0x20};

//	uint16_t len = sizeof(a);
//	printf("%0x,\n", test_crc16(a, sizeof(a)));
	int i;
	int a[params[0].size()-1];
	uint8_t hex_par[params[0].size()-1];
	std::cout << "sizeof(double) " << sizeof(double) << endl;
	std::cout << "sizeof(int) " << sizeof(int) << endl;
	std::cout << "sizeof(uint8_t) " << sizeof(uint8_t) << endl;

	char c[32] = {0};
	for (i = 1; i < params[0].size(); i++)
	{
		std::cout << params[0][i] << std::endl;
		c[i] = inttohex(params[0][i]);
		cout << c << endl;
	}
}


 /**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("yourextension", "1.1");
        
        // @todo    add your own functions, classes, namespaces to the extension
        extension.add<example>("example", {
        		Php::ByVal("a", Php::Type::Numeric),
				Php::ByVal("b", Php::Type::String),
				Php::ByVal("c", Php::Type::Numeric),
        });
        
        extension.add<crc16_exec>("crc16_exec", {
        		Php::ByVal("a", Php::Type::Array),
        });

        // return the extension
        return extension;
    }
}
