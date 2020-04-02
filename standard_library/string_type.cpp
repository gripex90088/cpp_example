#include <iostream>
#include <string>
#include <unistd.h>
#include <cctype>   // define character handle function

using std::string;
using std::cout;
using std::endl;
using std::cin;

int init_string()
{
    // 初始化
    string name1;
    string name2("LiuDeHua");
    string name3(name2);
    string name4(10, 'a');
    
    cout << name1 << endl;
    cout << name2 << endl;
    cout << name3 << endl;
    cout << name4 << endl;
    
    return 0;
}

int cin_string()
{
    string s;

    cout << "please key your name: ";
    cin >> s ;
    cout << s << endl;
    
    return 0;
}


int getline_str()
{

    string name;
    getline(cin, name);
    cout << name << endl;
    return 0;
}

// 
int example_getline()
{
    string strline;

    
    while (getline(cin, strline)) {
        cout << strline << endl;
        sleep(1);
    }
    
    return 0;
}

int example_cin()
{

    string word;
  
    while(cin >> word)
        cout << word << endl;
   
    return 0;
}

int example_strsize()
{
    string str("Hello");
    cout << str << endl;

    string::size_type size = str.size();
    cout << "str size, char number is " 
         <<  size << endl;

    if (str.size() != 0) 
        cout << "str not null" << endl;

    if (str.empty() == false)
        cout << "str not empty" << endl;

    return 0;
}

int example_compare()
{

    string a("LiuDeHua");
    string b("ZhangXueYou");

    if (a == b) 
        cout << " a == b " << endl;
    else {
        if (a > b) {
            cout << " a > b " << endl;
        } else {
            cout << " a < b " << endl;
        }
    }
    return 0;
}

int example_cin_end()
{

    string a;
    string result;

    while (cin >> a) {
        if (cin )
        if (result.empty()) {
            result = a;
        } else {
            result = result + " " + a;
        }

        if (getchar() == '\n')
            break;
    }

    cout << result << endl;
    return 0;
}

int example_foreach() 
{
    string str("Hello");

    for (string::size_type i = 0; i < str.size(); ++i) {
        cout << str[i] << endl;
    }

    for (string::size_type i = 0; i < str.size(); ++i) {
        str[i] = '*';
    }

    cout << str << endl;
    return 0;
}

// character handle function
int main()
{
    string str("Hello, World!!^.^");
    string::size_type punct_cnt = 0; // 标点符号个数
    string::size_type number_cnt = 0; //
    
    string upper_str;
    for (string::size_type index = 0; index < str.size(); ++index) {
        if (ispunct(str[index])) {
            ++punct_cnt;
        }
        if (isdigit(str[index])) {
            ++number_cnt;
        }
        upper_str += toupper(str[index]);
    }

    cout << upper_str << endl;
    /* ispunct(); 检查字符是否为标点符号 */
    /* isalnum();  检查字符是否为字母或数字*/
    /* isalpha()  检查字符是不是字母*/
    /* iscntrl() 检查字符是不是控制字符 */
    /* isdigit(); 检查是不是数字　*/
    /* islower() 检查字符是不是小写字母 */
    /* isupper() 检查字符是不是大写字母　*/
    /* toupper() 将字符转换为大写　*/
    /* tolower() 将字符转换为小写　*/
    cout << "ｐｕｎｃｔ number is " << punct_cnt << endl;
    

    return 0;
}
