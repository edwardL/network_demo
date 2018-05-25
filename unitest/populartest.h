#include "../frame/base/heap.h"
#include "../frame/file/singlemanager.h"
#include "../frame/datalayer/db/mysql_connection.h"
#include "../frame/base/stringutil.h"
#include "../frame/base/stringconverter.h"
#include "../frame/math/vector2.h"
#include "../frame/tinyxml/tinyxml_demo.h"
#include "../frame/timer/timer.h"
#include "../frame/base/tlvprotocol.h"
#include "../frame/file/roleparam.h"
#include "../frame/algorithm/Dijkstra/dijkstra.h"

#include <iostream>

class DijkstraTest
{
public:
	DijkstraTest()
	{
		int vexnum,edge;
		cout << "请输入图的顶点个数和边的条数:"<<endl;
		cin >> vexnum >> edge;
		cout << vexnum << edge;

		Graph graph(vexnum , edge);
		graph.createGraph();
		graph.print();
		graph.Dijkstra(2);
		graph.print_path(2);
	}
};

class HeapTest
{
public:
	HeapTest()
	{
		Heap<int> h;
		h.Push(12);
		h.Push(1);
		h.Push(13);
		h.Push(2);
		h.PrintHeap();
	}
};

class SingleManagerTest
{
public:
	SingleManagerTest()
	{
		SingleManager m_single_manager;
		m_single_manager.Init();
		int* a = new int(1);
		int* b = new int(2);
		m_single_manager.Add(a);
		m_single_manager.Add(b);
		m_single_manager.Remove(a);
		m_single_manager.Remove(b);
	}
};

class MysqlTest
{
public:
	MysqlTest()
	{
		MySQL_Connection conn;
	}
};

class StringUtilTest
{
public:
	StringUtilTest()
	{
		bool isStartWith = StringUtil::startsWith("hello world","hello");
		string basename,path;
		StringUtil::splitFileName("111.txt",basename,path);
		std::cout << basename << "---" << path << std::endl;
		std::cout<< isStartWith << "xxx" << std::endl;
		string result = StringUtil::replaceAll("helloworlld,","ll","haha");
		cout<< "replaceAll result is" << result << std::endl;
	}
};

class StringConvertTest
{
public:
	StringConvertTest()
	{
		float floatval = 11.01f;
		std::cout << StringConverter::toString(floatval) << endl;
		printf("float value is %f\n",StringConverter::parseFloat(StringConverter::toString(floatval),0.0f));
		if(StringConverter::parseBool("true",false)) printf("is true\n");
		std::vector<std::string> stringvec;
		stringvec.push_back("hello");
		stringvec.push_back("world");
		stringvec.push_back("hahaha");
		Vector2 ret = StringConverter::parseVector2("2   3");
		std::cout << ret << std::endl;
		std::cout << StringConverter::toString(stringvec) << std::endl;
	}
};

class Vector2Test
{
public:
	Vector2Test()
	{
		Vector2 v(2.0,2.0), v1(1.0f,2.0f);
		printf("vector2 length :%f\n",v.length());
		v += (v1);
		printf("vector2 length :%f\n",v.length());
		printf("vector2 distance: %f\n", v.distance(v1));
		printf("normalize vector : %f\n",v.normalize());

		std::cout << v << endl;
	}
};

class TixmlTest
{
public:
	TixmlTest()
	{
		TinyXmlDemo demo("coin.xml");
	}
};

class TimerTest
{
public:
	TimerTest()
	{
		//Timer timer;
		Sleep(10);  // 睡眠10毫秒
		unsigned long time = Timer::getInstance()->getMicroseconds();  // 微秒
		unsigned long millitimer =  Timer::getInstance()->getMilliseconds(); // 毫秒
		printf("current microseconds is %ld, millisecond is %ld\n",time,millitimer);
	}
};

class SerializeTest
{
public:
	SerializeTest()
	{
		RoleParam roleParam;
		TLVSerializer ser;
		char* data = new char[1024];
		ser.Reset(data,1024);
		roleParam.Serialize(ser);
		TLVUnserializer unSer;
		unSer.Reset(ser.Ptr(), ser.Size());
		RoleParam roleParam2;
		roleParam2.Unserialize(unSer);
	}
};