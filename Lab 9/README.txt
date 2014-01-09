Zuokun Yu
zy2170
Lab 9
Lab works exactly as specified

A)
BASIC4TRACE: (0x7fff2e2320d0)->MyString(const char *) //MyString s1("one");
BASIC4TRACE: (0x7fff2e2320e0)->MyString(const char *) //MyString s2("two");
BASIC4TRACE: (0x7fff2e232110)->MyString(const MyString&) //Pass by value so copy constructor in add...MyString s1
BASIC4TRACE: (0x7fff2e232100)->MyString(const MyString&) //Pass by value so copy constructor in add...MyString s2
BASIC4TRACE: (0x7fff2e232080)->MyString(const char *) //MyString temp(" and ");
BASIC4TRACE: op+(const MyString&, const MyString&) //s1 + temp...+operator
BASIC4TRACE: (0x7fff2e232030)->MyString() //MyString temp in operator+ in mystring.cpp
BASIC4TRACE: (0x7fff2e232090)->MyString(const MyString&) //return by value so copy constructor for temp, creates new temporary object
BASIC4TRACE: (0x7fff2e232030)->~MyString() //Destructor for temp in operator+
BASIC4TRACE: op+(const MyString&, const MyString&)//(whatever obj was returned from s1 + temp) + s2...+operator
BASIC4TRACE: (0x7fff2e232030)->MyString() //MyString temp in operator+ in mystring.cpp
BASIC4TRACE: (0x7fff2e2320a0)->MyString(const MyString&) //return by value so copy constructor for temp, creates new temporary object
BASIC4TRACE: (0x7fff2e232030)->~MyString() //Destructor for temp in operator+
BASIC4TRACE: (0x7fff2e232120)->MyString(const MyString&) //return s1 + temp + s2...return by value so copy constructor creates temporary object
BASIC4TRACE: (0x7fff2e2320a0)->~MyString() //Deconstructs object from (whatever obj was returned from s1 + temp) + s2
BASIC4TRACE: (0x7fff2e232090)->~MyString() //Deconstructs object from s1 + temp
BASIC4TRACE: (0x7fff2e232080)->~MyString() //Deconstructs temp in add, out of scope
BASIC4TRACE: (0x7fff2e2320f0)->MyString(const MyString&) //MyString s3 = add(s1, s2);
BASIC4TRACE: (0x7fff2e232120)->~MyString() //Deconstructs object from s1 + temp + s2
BASIC4TRACE: (0x7fff2e232100)->~MyString() //Deconstructs s2 in add, out of scope
BASIC4TRACE: (0x7fff2e232110)->~MyString() //Deconstructs s1 in add, out of scope
one and two //cout << s3 << endl;
BASIC4TRACE: (0x7fff2e2320f0)->~MyString() //Deconstructs s3, out of scope
BASIC4TRACE: (0x7fff2e2320e0)->~MyString() //Deconstructs s2, out of scope
BASIC4TRACE: (0x7fff2e2320d0)->~MyString() //Deconstructs s1, out of scope

B)
BASIC4TRACE: (0x7fff1d8859a0)->MyString(const char *)
BASIC4TRACE: (0x7fff1d8859b0)->MyString(const char *)
//No copy constructors required since parameters are references
BASIC4TRACE: (0x7fff1d885950)->MyString(const char *)
BASIC4TRACE: op+(const MyString&, const MyString&)
BASIC4TRACE: (0x7fff1d885900)->MyString()
BASIC4TRACE: (0x7fff1d885960)->MyString(const MyString&)
BASIC4TRACE: (0x7fff1d885900)->~MyString()
BASIC4TRACE: op+(const MyString&, const MyString&)
BASIC4TRACE: (0x7fff1d885900)->MyString()
BASIC4TRACE: (0x7fff1d885970)->MyString(const MyString&)
BASIC4TRACE: (0x7fff1d885900)->~MyString()
BASIC4TRACE: (0x7fff1d8859d0)->MyString(const MyString&)
BASIC4TRACE: (0x7fff1d885970)->~MyString()
BASIC4TRACE: (0x7fff1d885960)->~MyString()
BASIC4TRACE: (0x7fff1d885950)->~MyString()
BASIC4TRACE: (0x7fff1d8859c0)->MyString(const MyString&)
BASIC4TRACE: (0x7fff1d8859d0)->~MyString()
//Local copies of s1 and s2 were created originally and therefore needed to be destructed. Not the case anymore since they're references.
one and two
BASIC4TRACE: (0x7fff1d8859c0)->~MyString()
BASIC4TRACE: (0x7fff1d8859b0)->~MyString()
BASIC4TRACE: (0x7fff1d8859a0)->~MyString()

C)
-fno-elide-constructors
The C++ standard allows an implementation to omit creating a temporary which is only used to initialize another object of the same type.
Specifying this option disables that optimization, and forces G++ to call the copy constructor in all cases. 
From:http://gcc.gnu.org/onlinedocs/gcc-3.4.6/gcc/C_002b_002b-Dialect-Options.html

BASIC4TRACE: (0x7fff1f9edc20)->MyString(const char *)
BASIC4TRACE: (0x7fff1f9edc30)->MyString(const char *)
BASIC4TRACE: (0x7fff1f9edbe0)->MyString(const char *)
BASIC4TRACE: op+(const MyString&, const MyString&)
BASIC4TRACE: (0x7fff1f9edbf0)->MyString()
//Originally, a copy constructor was used to create a temporary MyString object to initialize a MyString object
//for the return value of s1 + temp. This is omitted now.
BASIC4TRACE: op+(const MyString&, const MyString&)
BASIC4TRACE: (0x7fff1f9edc40)->MyString()
//Originally, a copy constructor was used to create a temporary MyString object to initialize a MyString object
//for (obj from s1 + temp) + s2. This is omitted now.
BASIC4TRACE: (0x7fff1f9edbf0)->~MyString()
BASIC4TRACE: (0x7fff1f9edbe0)->~MyString()
//Originally, a copy constructor was used to create a temporary MyString object to initialize a MyString object for
//the return value of s1 + temp + s2. This is omitted now.
//Originally, a copy constructor was used to create a temporary MyString object to initialize s3. This is omitted now.
one and two
BASIC4TRACE: (0x7fff1f9edc40)->~MyString()
BASIC4TRACE: (0x7fff1f9edc30)->~MyString()
BASIC4TRACE: (0x7fff1f9edc20)->~MyString()