#include <iostream>
#include <string>

//删除char数组中的特定字符
void DeleteSpesificChar()
{
	char buff[256]= "We, need, to, delete, the, comma.";
	std::cout << buff << std::endl;
	
	int i, j;
	for(i=j=0; buff[i]!= '\0'; i++)
	{
		if(buff[i]!=',')
		{
			buff[j++]= buff[i];
		}	
	}
	buff[j]= '\0';
	std::cout << buff << std::endl;
}

int main()
{
	DeleteSpesificChar();
	getchar();
	return 0;
}