template<class T>
class SingletonBase
{
protected:
	SingletonBase()
	{

	}
	static T* _instance;
public:
	static T* getInstance()
	{
		if(!_instance)
		{
			_instance = new T;
			_instance->Init();
		}
		return _instance;
	}
	void Init()
	{

	}
};

template<class T>
T* SingletonBase<T>::_instance = 0;